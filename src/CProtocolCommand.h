/*
 * CBetCommand.h
 *
 *  Created on: Jul 1, 2014
 *      Author: dimitar
 */

#include <string>

#ifndef CBETCOMMAND_H_
#define CBETCOMMAND_H_

class BetProcedureFrame;  //forward declaration
class CProtocolCommand;
typedef void (BetProcedureFrame::*bet_handler_type)(const std::string&, CProtocolCommand& command);

struct command_data{
	command_data(const command_data& data);
	command_data();
	float U;
	int I;
	int releta;
	unsigned int time_to_end;
};

class CProtocolCommand{
	std::string command_;
	unsigned int sizeof_reply_;
	unsigned int timeout_;
	bet_handler_type reply_handler_;
	std::string reply_;
	std::string error_message_;
	BetProcedureFrame*  bet_frame_;
	command_data data_;
	bool initialized_;

public:
	CProtocolCommand();
	CProtocolCommand(const std::string& command, int sizeof_reply, int timeout, bet_handler_type reply_handler, const std::string& error_message, BetProcedureFrame*  bet_frame, const command_data& data) ;
	CProtocolCommand(const CProtocolCommand& cmd);
	CProtocolCommand& operator=(const CProtocolCommand& cmd);

	void handle_reply(const std::string& reply);

	std::string command();

	unsigned int expected_sizeof_reply();

	unsigned int timeout();

	void handle_timeout();

	command_data data();

	virtual ~CProtocolCommand(){

	};
};

#endif /* CBETCOMMAND_H_ */
