/*
 * CProtocolCommand.cpp
 *
 *  Created on: Jul 2, 2014
 *      Author: dimitar
 */
#include <iostream>
#include "CProtocolCommand.h"
#include <assert.h>
#include <stdio.h>

CProtocolCommand::CProtocolCommand() {
	initialized_ = false;
}
CProtocolCommand::CProtocolCommand(const std::string& command, int sizeof_reply,
		int timeout, bet_handler_type reply_handler,
		const std::string& error_message, BetProcedureFrame* bet_frame,
		const command_data& data) :
		command_(command), sizeof_reply_(sizeof_reply), timeout_(timeout), reply_handler_(
				reply_handler), error_message_(error_message), bet_frame_(
				bet_frame), data_(data) {
	initialized_ = true;
}

CProtocolCommand::CProtocolCommand(const CProtocolCommand& cmd) {
	command_ = cmd.command_;
	sizeof_reply_ = cmd.sizeof_reply_;
	timeout_ = cmd.timeout_;
	reply_handler_ = cmd.reply_handler_;
	reply_ = cmd.reply_;
	error_message_ = cmd.error_message_;
	bet_frame_ = cmd.bet_frame_;
	data_ = cmd.data_;
	initialized_ = true;
}

CProtocolCommand& CProtocolCommand::operator=(const CProtocolCommand& cmd) {
	if (this != &cmd) {
		command_ = cmd.command_;
		sizeof_reply_ = cmd.sizeof_reply_;
		timeout_ = cmd.timeout_;
		reply_handler_ = cmd.reply_handler_;
		reply_ = cmd.reply_;
		error_message_ = cmd.error_message_;
		bet_frame_ = cmd.bet_frame_;
		data_ = cmd.data_;
		initialized_ = true;
	}
	return *this;
}

void CProtocolCommand::handle_reply(const std::string& reply) {
	assert(initialized_);
	char check_sum = 0;
	for (unsigned int i = 0; i < reply.size() - 2; i++)
		check_sum += reply[i];
	char sum1 = reply[reply.size() - 2];
	if (sum1 >= 'A' && sum1 <= 'F')
		sum1 -= 0x37;
	if (sum1 >= 'a' && sum1 <= 'f')
		sum1 -= 0x57;
	if (sum1 >= '0' && sum1 <= '9')
		sum1 -= 0x30;
	char sum2 = reply[reply.size() - 1];
	if (sum2 >= 'A' && sum2 <= 'F')
		sum2 -= 0x37;
	if (sum2 >= 'a' && sum2 <= 'f')
		sum2 -= 0x57;
	if (sum2 >= '0' && sum2 <= '9')
		sum2 -= 0x30;
	if ((((check_sum & 0xf0) >> 4) == sum1) && ((check_sum & 0xf) == sum2))
		(bet_frame_->*reply_handler_)(reply, *this);
	else
		std::cout << "bad check sum: " << reply << std::endl;
}

std::string CProtocolCommand::command() {
	assert(initialized_);
	return command_;
}

unsigned int CProtocolCommand::expected_sizeof_reply() {
	assert(initialized_);
	return sizeof_reply_;
}

unsigned int CProtocolCommand::timeout() {
	assert(initialized_);
	return timeout_;
}

void CProtocolCommand::handle_timeout() {
	assert(initialized_);
	std::cout << error_message_ << std::endl;
}

command_data CProtocolCommand::data() {
	assert(initialized_);
	return data_;
}

command_data::command_data(const command_data& data) {
	U = data.U;
	I = data.I;
	releta = data.releta;
	time_to_end = data.time_to_end;
}

command_data::command_data() {
	U = 1000;
	I = 1000;
	releta = 0xffff;
	time_to_end = 0xffff;
}
