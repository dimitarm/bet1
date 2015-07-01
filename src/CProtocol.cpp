/*
 * CProtocol.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: dimitar
 */
#ifdef __WXMSW__
#include <winsock2.h>
#endif
#include <iostream>
#include "CProtocol.h"

CProtocol::CProtocol() :
		preamble_ready_(false), command_ready_(false), running_(false), port_(service_), orchestrator_(NULL), error_(false) {
}

bool CProtocol::error(){
	return error_;
}

void CProtocol::stop() {
	boost::system::error_code ec;
	if(running_){
		running_ = false;
		queue_mtx_.lock();
		while(!commands_.empty())
			commands_.pop();
		queue_mtx_.unlock();
		service_.stop();
		port_.cancel(ec);
		port_.close(ec);
		orchestrator_->detach();
		delete orchestrator_;
		orchestrator_ = NULL;
	}
}

void CProtocol::on_empty_buffer(const system::error_code& error, std::size_t bytes) {
	empty_buffer_[bytes] = 0;
	std::string reply(empty_buffer_);
	if (bytes > 0)
		std::cout << "on_empty_buffer: " << bytes << " " << reply << std::endl;
	buffer_empty_ = true;
	if(error != 0)
		std::cout << "on_empty_buffer error: " << error << " message: "<< error.message() << std::endl;
}

void CProtocol::on_receive_reply(const system::error_code& error, std::size_t bytes) {
	cmd_response_[bytes] = 0;
	std::string reply(cmd_response_);

	std::cout << "<- " << reply << std::endl;
	if (bytes != active_command_.expected_sizeof_reply())
		return;
	if(running_)
		active_command_.handle_reply(reply);
//		signal command finished
	command_ready_ = true;
	if(error != 0)
		std::cout << "on_receive_reply error: " << error << " message: "<< error.message() << " bytes: " << bytes << std::endl;
}

void CProtocol::on_write(const system::error_code& error, std::size_t bytes) {
	//signal on error
	std::cout << "on_write " << bytes << std::endl;
	if(error != 0)
		std::cout << "on_write error: " << error << " message: "<< error.message() << " bytes: " << bytes << std::endl;
}

void CProtocol::waitfor(int milliseconds, const bool& signal) {
	int counter;
	for (counter = 0; counter < milliseconds / 5 && !signal; counter++) {
		service_.poll();
		service_.reset();
		this_thread::sleep(posix_time::milliseconds(5));
	}
	//if (counter < milliseconds / 50)
//	std::cout << "waitfor: " << counter * 5 << " milliseconds" << std::endl;
}

void CProtocol::orchestrator_thread() {
	int error_count = 5;
	while (running_) {
		int size;
		queue_mtx_.lock();
		bool empty_queue = commands_.empty();
		if(!empty_queue){
			active_command_ = commands_.front();
			commands_.pop();
		}
		size = commands_.size();
		queue_mtx_.unlock();
		if(size > 10)
			std::cout << "GET commands in the queue: " << size << std::endl;

		if(empty_queue){
			this_thread::sleep(posix_time::milliseconds(50));
			continue;
		}
		if (!running_)
			break;


		preamble_ready_ = false;
		command_ready_ = false;
		buffer_empty_ = false;
		//empty buffer
		port_.async_read_some(asio::buffer(empty_buffer_),
				bind(&CProtocol::on_empty_buffer, this, boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
		//waitfor(20, buffer_empty_);
		port_.cancel();

		if (!running_) break;
		std::cout << "-> " << active_command_.command().data() << std::endl;
		asio::async_write(
				port_,
				asio::buffer(active_command_.command().data(), active_command_.command().size()),
				asio::transfer_exactly(active_command_.command().size()),
				bind(&CProtocol::on_write, this, asio::placeholders::error, asio::placeholders::bytes_transferred));
		if (!running_) break;
		asio::async_read(
				port_,
				asio::buffer(cmd_response_, active_command_.expected_sizeof_reply()),
				asio::transfer_exactly(active_command_.expected_sizeof_reply()),
				bind(&CProtocol::on_receive_reply, this, asio::placeholders::error, asio::placeholders::bytes_transferred));

		waitfor(active_command_.timeout(), command_ready_);
		if (!command_ready_) {
			std::cout << "command not ready " << std::endl;
			error_count--;
			if(error_count == 0){
				running_ = false;
				error_ = true;
			}
		}
		else
			error_count = 5;
	}
	//std::cout << "orchestrator_thread ready " << std::endl;

}

void CProtocol::start(const std::string& port) {
	port_.open(port);
	port_.set_option(boost::asio::serial_port_base::baud_rate(19200));
	port_.set_option(boost::asio::serial_port_base::character_size(8));
	port_.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
	port_.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));

	running_ = true;
	orchestrator_ = new thread(bind(&CProtocol::orchestrator_thread, this));
}

void CProtocol::queue_command(const CProtocolCommand& cmd) {
	queue_mtx_.lock();
	commands_.push(cmd);
	queue_mtx_.unlock();
}

CProtocol::~CProtocol() {
	if (orchestrator_ != NULL){
		orchestrator_->detach();
		delete orchestrator_;
	}
}

