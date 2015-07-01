/*
 * CProtocol.h
 *
 *  Created on: Jun 29, 2014
 *      Author: dimitar
 */

#include <string>
#include <queue>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

#include "CProtocolCommand.h"
#include "betconst.h"
#ifndef CPROTOCOL_H_
#define CPROTOCOL_H_

using namespace boost;

class CProtocol {
	bool preamble_ready_;
	bool command_ready_;
	bool error_;
	bool buffer_empty_;
	char preamble_response_[2];
	char cmd_response_[50];
	char empty_buffer_[100];
	std::queue<CProtocolCommand> commands_;
	bool volatile running_;
	mutex queue_mtx_;
	asio::io_service service_;
	asio::serial_port port_;
	CProtocolCommand active_command_;
	thread* orchestrator_;


public:

	CProtocol();

	void stop();


	void on_receive_reply(const system::error_code& error, std::size_t bytes);

	void on_empty_buffer(const system::error_code& error, std::size_t bytes);

	void on_write(const system::error_code& error, std::size_t bytes) ;

	void waitfor(int milliseconds, const bool& signal) ;

	void orchestrator_thread();

	void start(const std::string& port);

	void queue_command(const CProtocolCommand& cmd);
	bool error();

	virtual ~CProtocol();

};

#endif /* CPROTOCOL_H_ */
