#ifdef __WXMSW__
#include <winsock2.h>
#endif
#include "Bet1.h"
#include "BetProcedureFrame.h"
#include "MainFrame.h"
#include "betconst.h"
#include "Treatment.h"
#include <wx/event.h>
#include <stdlib.h>
#include <cstdlib>
#include <boost/thread.hpp>
#include <string>
#include <stdlib.h>

BetProcedureFrame::BetProcedureFrame(wxWindow* parent, const Patient& patient) :
		BaseProcedureFrame(parent), currents_graphic_(
				wxBitmap(wxT("graphic_small"), wxBITMAP_TYPE_PNG_RESOURCE).ConvertToImage(), 20, 15, 680, 120,
				DURATION_LIMIT + 30 * 60, //30min. for closing procedure
				80,
				{ wxColor(13, 193, 184), wxColor(0, 0, 255), wxColor(125, 0, 255), wxColor(255, 0, 0), wxColor(255, 125,
						0), wxColor(80, 170, 80) }), voltage_graphic_(
				wxBitmap(wxT("graphic_big"), wxBITMAP_TYPE_PNG_RESOURCE).ConvertToImage(), 26, 15, 674, 240,
				DURATION_LIMIT + 30 * 60, 120, { wxColor(0, 0, 225),
				wxColor(125, 0, 0),
				wxColor(0, 125, 0), wxColor(125, 0, 125) }), lightR_(wxT("lightr"), wxBITMAP_TYPE_PNG_RESOURCE), lightG_(
				wxT("lightg"), wxBITMAP_TYPE_PNG_RESOURCE), lightS_(wxT("lights"), wxBITMAP_TYPE_PNG_RESOURCE), switch1_(
		SW_OFF), switch2_(SW_OFF), switch3_(SW_OFF), switch4_(SW_OFF), switch5_(SW_OFF), switch6_(
		SW_OFF), cable_(CABLE_OUT), key_(KEY_ON), polarity_(false), voltage_(0), decrease_speed_(0.1), time_to_end_(60), q_(
				0), duration_(0), state_(
		STATE_INITIAL), conf_channel_alarm_wait_(10){
	for (int i = 0; i < 7; i++) {
		voltages_[i] = 0;
		currents_[i] = 0;
	}
	patient_id_ = patient.getPatientNumber();
	m_txtPatientName->SetLabel(patient.getFullName());
	m_txtTreatmentNumber->SetLabel(wxString::Format("%i", patient.getTreatmentCount() + 1));
	m_bmpElectrodes->SetBitmap(currents_graphic_.getImage());
	m_bmpVoltage->SetBitmap(voltage_graphic_.getImage());
	my_timer_.SetOwner(this);
	m_bmpInd1->SetBitmap(lightS_);
	m_bmpInd2->SetBitmap(lightS_);
	m_bmpInd3->SetBitmap(lightS_);
	m_bmpInd4->SetBitmap(lightS_);
	m_bmpInd5->SetBitmap(lightS_);
	m_bmpInd6->SetBitmap(lightS_);
	updateFloatValue(voltage_, m_txtVoltage);
	updateIntegerValue(0, m_txtCurrent);
	updateDurationValue(time_to_end_, m_txtDuration);
	parseOptions();
	Bind(wxEVT_TIMER, &BetProcedureFrame::OnTimer, this);

	if (options_.find(std::string("port")) == options_.end() )
		throw std::runtime_error("port not specified in configuration file");
	protocol_.start(options_[std::string("port")].as<std::string>());
	decrease_speed_ = options_[std::string("decrease_speed")].as<float>();
	regulator_speed_ = options_[std::string("regulator_speed")].as<float>();
	conf_channel_alarm_wait_ = options_[std::string("channel_alarm_wait")].as<unsigned int>();
	Bind(wxEVT_KEY_DOWN, &BetProcedureFrame::OnKeyEvent, this, wxID_ANY);
	DoGoInInitialState();
	my_timer_.Start(1000);
	wxGetApp().setProcedureFrame(this);
}

BetProcedureFrame::~BetProcedureFrame() {
	protocol_.stop();
}

void BetProcedureFrame::parseOptions() {
	po::options_description desc("configuration options");
	desc.add_options()("port", po::value<std::string>(), "com port")
			("decrease_speed",	po::value<float>()->default_value(0.1), "decrease speed")
			("regulator_speed",	po::value<float>()->default_value(0.1), "regulator speed")
			("r_min_value",	po::value<unsigned int>()->default_value(10), "minimum R value [ohm]")
			("alarm_time", po::value<unsigned int>()->default_value(20), "alarm time [min]")
			("r_alarm_value", po::value<unsigned int>()->default_value(800), "alarm R value [ohm]")
			("r_max_value",	po::value<unsigned int>()->default_value(10000), "maximum R value [ohm]")
			("r_max_hist_value", po::value<unsigned int>()->default_value(8000), "maximum R value (lower bound) [ohm]")
			("v_check_value", po::value<unsigned int>()->default_value(5), "U check value for open circuit [V]")
			("channel_alarm_wait",po::value<unsigned int>()->default_value(30), "channel alarm delay [sec]");
	ifstream ifs(std::string(CONFIG_FILE).c_str());
	po::store(po::parse_config_file(ifs, desc), options_);
	notify(options_);
}

void BetProcedureFrame::updateFloatValue(float value, wxStaticText* ctl) {
	char buffer[10];
	sprintf(buffer, "%-.1lf", value);
	ctl->SetLabel(buffer);
}

void BetProcedureFrame::updateFloatValue(float value, wxTextCtrl* ctl) {
	char buffer[10];
	sprintf(buffer, "%-.1lf", value);
	ctl->SetValue(buffer);
}

void BetProcedureFrame::updateIntegerValue(unsigned int value, wxStaticText* ctl) {
	char buffer[10];
	sprintf(buffer, "%-.u", value);
	ctl->SetLabel(buffer);
}

void BetProcedureFrame::updateIntegerValue(unsigned int value, wxTextCtrl* ctl) {
	char buffer[10];
	sprintf(buffer, "%-.1u", value);
	ctl->SetValue(buffer);
}

//handles read on every second
void BetProcedureFrame::HandlerRead(const std::string& reply, CProtocolCommand&) {
	char buffer[5];
	int address = reply.c_str()[1] - 0x30;
	if (address < 0 || address > 7) {
		std::cout << "bad address " << address << std::endl;
		return;
	}

	int status1 = reply.c_str()[2];
	int status2 = reply.c_str()[3];
	if (status1 >= 'A' && status1 <= 'F')
		status1 -= 0x37;
	if (status1 >= 'a' && status1 <= 'f')
		status1 -= 0x57;
	if (status1 >= '0' && status1 <= '9')
		status1 -= 0x30;
	if (status2 >= 'A' && status2 <= 'F')
		status2 -= 0x37;
	if (status2 >= 'a' && status2 <= 'f')
		status2 -= 0x57;
	if (status2 >= '0' && status2 <= '9')
		status2 -= 0x30;
	int status = (status1 << 4) + status2;

	buffer[0] = reply.c_str()[4];
	buffer[1] = reply.c_str()[5];
	buffer[2] = reply.c_str()[6];
	buffer[3] = reply.c_str()[7];
	buffer[4] = 0;
	float voltage = strtoul(buffer, NULL, 16);
	buffer[0] = reply.c_str()[8];
	buffer[1] = reply.c_str()[9];
	buffer[2] = reply.c_str()[10];
	buffer[3] = reply.c_str()[11];
	float current = strtoul(buffer, NULL, 16);
	if (current < 0)
		current = 0;
	voltages_[address] = voltage / 100;
	currents_[address] = current / 10000;
	if (address == 0) {
		q_ += currents_[address];
		float r = calculateR();
		if (state_ == STATE_RUNNING || state_ == STATE_FINISHING) {
			voltage_graphic_.AddValue(0, voltages_[address]); //main voltage in V
			voltage_graphic_.AddValue(1, currents_[address] * 1000); //main current in mA
			voltage_graphic_.AddValue(2, r / 10);
			voltage_graphic_.AddValue(3, q_ / 10);
		}
		m_bmpVoltage->SetBitmap(voltage_graphic_.getImage());
		updateFloatValue(voltages_[address], m_txtCurrentVoltage);
		updateFloatValue(currents_[address] * 1000, m_txtCurrentCurrent);
		updateIntegerValue(r, m_txtCurrentR);
		updateIntegerValue(q_, m_txtCurrentQ);
		updateKeyChannel(status);
	}
	if (address > 0 and address < 7) {
		if (state_ == STATE_RUNNING || state_ == STATE_FINISHING) {
			currents_graphic_.AddValue(address - 1, currents_[address] * 1000);
			m_bmpElectrodes->SetBitmap(currents_graphic_.getImage());
		}
		updateSwitchesStatus(address, status);
	}
	if (state_ == STATE_RUNNING)
		checkR(address);
}

//checks for short circuit and open circuit
void BetProcedureFrame::checkR(int address) {
	bool check = false;
	check = (voltages_[address] != 0)
			&& ((switch1_ == SW_ON) || (switch2_ == SW_ON) || (switch3_ == SW_ON) || (switch4_ == SW_ON)
					|| (switch5_ == SW_ON) || (switch6_ == SW_ON));
	if (!check)
		return;

	float r = voltages_[address] / currents_[address];
	if (address != 0) {
		if (r < r_min_value_) {
			if (!signal_r_[address-1]) {
				DoSendZumer();
				char msg[256];
				sprintf(msg, "Short circuit detected in channel %d", address);
				thread(bind(&BetProcedureFrame::showMessage, std::string(msg), std::string("Warning")));
				signal_r_[address-1] = true;
			}
			if (counter_r_[address-1] > 0)
				counter_r_[address-1]--;
			else
				DoSwitchChange(address - 1);
		} else {
			counter_r_[address-1] = conf_channel_alarm_wait_;
			signal_r_[address-1] = false;
		}
		if (r < r_max_hist_value_ && !signal_r_[address-1]) //there's no sense to signal less than hist value if you have short circuit signal
			signal_open_r_[address-1] = true;

		if(signal_open_r_[address-1] || (voltages_[address] >= v_check_value_ && currents_[address] < 0.1))
			if (r > r_max_value_) {
				if (counter_open_r_[address-1] == conf_channel_alarm_wait_) {  //first time we notice open circuit just send zumer and show a message
					DoSendZumer();
					char msg[256];
					sprintf(msg, "Open circuit detected in channel %d", address);
					thread(bind(&BetProcedureFrame::showMessage, std::string(msg), std::string("Warning")));
				}
				if (counter_open_r_[address-1] > 0)
					counter_open_r_[address-1]--;
				if (counter_open_r_[address-1] == 0)
					DoSwitchChange(address - 1);
			}
			else   //get in initial state if
				counter_open_r_[address-1] = conf_channel_alarm_wait_;
	}
	if (address == 0 && alarm_time_ == 0 && r > r_alarm_value_ && r_alarm_value_ != INT_MAX) {
		DoSendZumer();
		thread(bind(&BetProcedureFrame::showMessage, std::string("Minimum R has not been reached"),
						std::string("Warning")));
		r_alarm_value_ = INT_MAX; //so that we avoid further notifications for the same reason
	}
}

void BetProcedureFrame::showMessage(std::string msg, std::string title) {
	wxMessageBox(msg, title, wxOK | wxCENTRE);
}

void BetProcedureFrame::updateKeyChannel(int status) {
	bool problem = false;
	if (0x4 & status) { //KEY
		switch (0x3 & status) {
		case 0:
			key_ = KEY_SHORT;
			m_txtKey->SetLabel("Short");
			m_txtKey->SetForegroundColour(wxColor(255, 0, 0));
			problem = true;
			break;
		case 1:
			key_ = KEY_ON;
			m_txtKey->SetLabel("On");
			m_txtKey->SetForegroundColour(wxColor(255, 0, 0));
			problem = true;
			break;
		case 2:
			key_ = KEY_OFF;
			m_txtKey->SetLabel("Off");
			m_txtKey->SetForegroundColour(wxColor(0, 255, 0));
			break;
		case 3:
			key_ = KEY_BREAK;
			m_txtKey->SetLabel("Break");
			m_txtKey->SetForegroundColour(wxColor(255, 0, 0));
			problem = true;
			break;
		}
	} else {
		m_txtKey->SetLabel("Out");
		m_txtKey->SetForegroundColour(wxColor(255, 0, 0));
		problem = true;
	}
	if (0x8 & status) {  //CABLE
		cable_ = CABLE_OUT;
		m_txtCable->SetLabel("Out");
		m_txtCable->SetForegroundColour(wxColor(255, 0, 0));
		problem = true;
	} else {
		cable_ = CABLE_IN;
		m_txtCable->SetLabel("In");
		m_txtCable->SetForegroundColour(wxColor(0, 255, 0));
	}
	if(problem && (state_ == STATE_RUNNING || state_ == STATE_FINISHING)){
		DoTerminate();
		boost::thread(bind(&BetProcedureFrame::showMessage, std::string("Error"), std::string("Check Key or Cable")));
	}
}

void BetProcedureFrame::updateSwitchesStatus(int address, float status) {
	wxTextCtrl* ctl;
	switch (address) {
	case 1:
		ctl = m_txtCur1;
		switch1_ = (status ? SW_FAILURE : (switch1_ == SW_FAILURE ? SW_OFF : switch1_));
		m_bmpInd1->SetBitmap(switch1_ == SW_FAILURE ? lightR_ : (switch1_ == SW_ON ? lightG_ : lightS_));
		break;
	case 2:
		ctl = m_txtCur2;
		switch2_ = (status ? SW_FAILURE : (switch2_ == SW_FAILURE ? SW_OFF : switch2_));
		m_bmpInd2->SetBitmap(switch2_ == SW_FAILURE ? lightR_ : (switch2_ == SW_ON ? lightG_ : lightS_));
		break;
	case 3:
		ctl = m_txtCur3;
		switch3_ = (status ? SW_FAILURE : (switch3_ == SW_FAILURE ? SW_OFF : switch3_));
		m_bmpInd3->SetBitmap(switch3_ == SW_FAILURE ? lightR_ : (switch3_ == SW_ON ? lightG_ : lightS_));
		break;
	case 4:
		ctl = m_txtCur4;
		switch4_ = (status ? SW_FAILURE : (switch4_ == SW_FAILURE ? SW_OFF : switch4_));
		m_bmpInd4->SetBitmap(switch4_ == SW_FAILURE ? lightR_ : (switch4_ == SW_ON ? lightG_ : lightS_));
		break;
	case 5:
		ctl = m_txtCur5;
		switch5_ = (status ? SW_FAILURE : (switch5_ == SW_FAILURE ? SW_OFF : switch5_));
		m_bmpInd5->SetBitmap(switch5_ == SW_FAILURE ? lightR_ : (switch5_ == SW_ON ? lightG_ : lightS_));
		break;
	case 6:
		ctl = m_txtCur6;
		switch6_ = (status ? SW_FAILURE : (switch6_ == SW_FAILURE ? SW_OFF : switch6_));
		m_bmpInd6->SetBitmap(switch6_ == SW_FAILURE ? lightR_ : (switch6_ == SW_ON ? lightG_ : lightS_));
		break;
	}
	updateFloatValue(currents_[address] * 1000, ctl);
}

float BetProcedureFrame::calculateR() {
	float sum = 0;

	if (switch1_ == SW_ON)
		sum += currents_[1] / voltages_[1];
	if (switch2_ == SW_ON)
		sum += currents_[2] / voltages_[2];
	if (switch3_ == SW_ON)
		sum += currents_[3] / voltages_[3];
	if (switch4_ == SW_ON)
		sum += currents_[4] / voltages_[4];
	if (switch5_ == SW_ON)
		sum += currents_[5] / voltages_[5];
	if (switch6_ == SW_ON)
		sum += currents_[6] / voltages_[6];

	sum = 1.0f / sum;
	return sum;
}

void BetProcedureFrame::DoGoInInitialState() {
	state_ = STATE_INITIAL;
	m_buttonSTART->SetBackgroundColour( wxColor(0, 255, 0));
	//set buttons status
	m_buttonSTART->SetLabel("START");
	m_buttonSTART->Enable();
	m_buttonSTOP->Disable();
	m_butVoltage1->Disable();
	m_button5->Disable();  //-5
	m_butVoltagem1->Disable();
	m_txtVoltage->Disable();
	m_txtCurrent->Enable();
	m_txtDuration->Enable();
	m_button31->Disable();
	m_button41->Disable();
	m_button32->Disable();
	m_button42->Disable();
	m_txtLimitCur1->Enable();
	m_txtLimitCur2->Enable();
	m_txtLimitCur3->Enable();
	m_txtLimitCur4->Enable();
	m_txtLimitCur5->Enable();
	m_txtLimitCur6->Enable();
	m_button8->Enable();
	r_min_value_ = options_[std::string("r_min_value")].as<unsigned int>();
	alarm_time_ = options_[std::string("alarm_time")].as<unsigned int>() * 60; //convert to seconds
	r_alarm_value_ = options_[std::string("r_alarm_value")].as<unsigned int>();
	r_max_value_ = options_[std::string("r_max_value")].as<unsigned int>();
	r_max_hist_value_ = options_[std::string("r_max_hist_value")].as<unsigned int>();
	v_check_value_ = options_[std::string("v_check_value")].as<unsigned int>();
	DoZeroSwitches();
}

void BetProcedureFrame::DoGoInRunning() {
	state_ = STATE_RUNNING;
	for(int i = 0; i < 6; i++){
		counter_r_[i] = conf_channel_alarm_wait_;
		counter_open_r_[i] = conf_channel_alarm_wait_;
		signal_r_[i] = false;
		signal_open_r_[i] = false;
	}
	m_buttonSTART->SetLabel("STOP");
	m_buttonSTART->SetBackgroundColour(wxColor(255, 0, 0));
	m_buttonSTART->Enable();
	m_buttonSTOP->Enable();
	m_butVoltage1->Enable();
	m_button5->Enable();
	m_butVoltagem1->Enable();
	m_button31->Enable();
	m_button41->Enable();
	m_button32->Enable();
	m_button42->Enable();
	m_txtVoltage->Enable();
	m_txtLimitCur1->Disable();
	m_txtLimitCur2->Disable();
	m_txtLimitCur3->Disable();
	m_txtLimitCur4->Disable();
	m_txtLimitCur5->Disable();
	m_txtLimitCur6->Disable();
	m_button8->Disable();  //polarity
	r_min_value_ = options_[std::string("r_min_value")].as<unsigned int>();
	alarm_time_ = options_[std::string("alarm_time")].as<unsigned int>() * 60; //convert to seconds
	r_alarm_value_ = options_[std::string("r_alarm_value")].as<unsigned int>();
	r_max_value_ = options_[std::string("r_max_value")].as<unsigned int>();
}

void BetProcedureFrame::DoGoInFinishing() {
	state_ = STATE_FINISHING;
	m_butVoltage1->Disable();
	m_button5->Disable();  //-5
	m_butVoltagem1->Disable();
	m_txtVoltage->Disable();
	m_txtCurrent->Disable();
	m_txtDuration->Disable();
	m_button31->Disable();
	m_button41->Disable();
	m_button32->Disable();
	m_button42->Disable();
	m_buttonSTART->Disable();
	m_buttonSTART->SetBackgroundColour(wxColor(125, 125, 125));
}

//sends read command on every second
void BetProcedureFrame::OnTimer(wxTimerEvent& event) {
	if(protocol_.error()){
		my_timer_.Stop();
		wxMessageBox("Communication error", "Error", wxOK, this);
		state_ = STATE_ERROR;
		Close();
		return;
	}

	//std::cout << "state: " << state_ << " voltage_: " << voltage_ << " time_to_end_: " << time_to_end_ << std::endl;

//	voltage_graphic_.AddValue(0, 0); //main voltage
//	voltage_graphic_.AddValue(1, 80); //main current
//	currents_graphic_.AddValue(0, 0);
//	currents_graphic_.AddValue(1, 40);
//	m_bmpElectrodes->SetBitmap(currents_graphic_.getImage());
//	m_bmpVoltage->SetBitmap(voltage_graphic_.getImage());

	if (state_ == STATE_FINISHING || state_ == STATE_RUNNING)
		duration_++;

	if (state_ == STATE_RUNNING && time_to_end_ > 0) {
		time_to_end_ -= 1;
		if (alarm_time_ > 0)
			alarm_time_--;
		updateDurationValue(time_to_end_, m_txtDuration);
	}
	if (time_to_end_ == 0 && state_ == STATE_RUNNING)
		DoGoInFinishing();
	if (state_ == STATE_FINISHING && voltage_ > 0) {
		float volt = voltage_ - decrease_speed_;
		if (volt < 0)
			volt = 0;
		DoUpdateVoltage(volt);
	}

	sendCommand('R', 0, 14, &BetProcedureFrame::HandlerRead, "ERROR: Cannot read status", command_data());
	if (switch1_ == SW_ON)
		sendCommand('R', 1, 14, &BetProcedureFrame::HandlerRead, "ERROR: Cannot read status", command_data());
	if (switch2_ == SW_ON)
		sendCommand('R', 2, 14, &BetProcedureFrame::HandlerRead, "ERROR: Cannot read status", command_data());
	if (switch3_ == SW_ON)
		sendCommand('R', 3, 14, &BetProcedureFrame::HandlerRead, "ERROR: Cannot read status", command_data());
	if (switch4_ == SW_ON)
		sendCommand('R', 4, 14, &BetProcedureFrame::HandlerRead, "ERROR: Cannot read status", command_data());
	if (switch5_ == SW_ON)
		sendCommand('R', 5, 14, &BetProcedureFrame::HandlerRead, "ERROR: Cannot read status", command_data());
	if (switch6_ == SW_ON)
		sendCommand('R', 6, 14, &BetProcedureFrame::HandlerRead, "ERROR: Cannot read status", command_data());

//	CProtocolCommand dummy;
//	HandlerRead("r0000bba003000", dummy);
//	HandlerRead("r1000bba001000", dummy);
//	HandlerRead("r2480bba002000", dummy);
//	HandlerRead("r3440bca003000", dummy);
//	HandlerRead("r4440bca004000", dummy);
//	HandlerRead("r5440bca005000", dummy);
//	HandlerRead("r6440bca006000", dummy);
}

const wxImage& BetProcedureFrame::getCurrentsImage() {
	return currents_graphic_.getImage();
}

const wxImage& BetProcedureFrame::getVoltageImage() {
	return voltage_graphic_.getImage();
}

float BetProcedureFrame::getDuration() {
	return duration_;
}

float BetProcedureFrame::getQ() {
	return q_;
}

void BetProcedureFrame::OnClose(wxCloseEvent& event) {
	if (event.CanVeto()) {
		if (state_ == STATE_RUNNING || state_ == STATE_FINISHING) {
			wxMessageBox("Cannot exit while procedure is running", "Finish",
			wxOK, this);
			return;
		}
	}
	my_timer_.Stop();
	if (state_ == STATE_RUNNING || state_ == STATE_FINISHING) {
		//finish prematurely
		DoTerminate();
	}
	protocol_.stop();
	wxGetApp().setProcedureFrame(nullptr);
	MainFrame* mainFrame = static_cast<MainFrame*>(GetParent());
	mainFrame->OnProcedureFinished();
	Destroy();
}

void BetProcedureFrame::OnVoltage1(wxCommandEvent& event) {
	float voltage = std::atof(m_txtVoltage->GetValue()) + VOLTAGE_LOW_INCREMENT;
	if (voltage > VOLTAGE_LIMIT)
		voltage = VOLTAGE_LIMIT;
	DoUpdateVoltage(voltage);
}

void BetProcedureFrame::OnVoltageM1(wxCommandEvent& event) {
	float voltage = std::atof(m_txtVoltage->GetValue()) - VOLTAGE_LOW_DECREMENT;
	if (voltage < 0)
		voltage = 0;
	DoUpdateVoltage(voltage);
}

void BetProcedureFrame::OnVoltageM5(wxCommandEvent& event) {
	float voltage = std::atof(m_txtVoltage->GetValue()) - VOLTAGE_DECREMENT;
	if (voltage < 0)
		voltage = 0;
	DoUpdateVoltage(voltage);
}

void BetProcedureFrame::DoUpdateVoltage(float voltage) {
	command_data data { };
	data.U = voltage;
	sendCommand('U', 0, data.U * 100, 4, &BetProcedureFrame::HandlerVoltage, "ERROR: Cannot update U", data);
}

void BetProcedureFrame::DoUpdateCurrent(int current) {
	command_data data { };
	data.I = current;
	sendCommand('I', 0, data.I * 10, 4, &BetProcedureFrame::HandlerCurrent, "ERROR: Cannot update U", data);
}

void BetProcedureFrame::OnCurrent1(wxCommandEvent& event) {
	int current = std::atoi(m_txtCurrent->GetValue()) + CURRENT_INCREMENT;
	if (current > CURRENT_LIMIT)
		current = CURRENT_LIMIT;
	DoUpdateCurrent(current);
}

void BetProcedureFrame::OnCurrentM1(wxCommandEvent& event) {
	int current = std::atoi(m_txtCurrent->GetValue()) - CURRENT_DECREMENT;
	if (current < 0)
		current = 0;
	DoUpdateCurrent(current);
}

void BetProcedureFrame::OnDuration1(wxCommandEvent& event) {
	int dur = std::atoi(m_txtDuration->GetValue()) * 60 + DURATION_INCREMENT;

	if(dur + duration_ > DURATION_LIMIT)
		wxMessageBox("Duration limit reached");
	else
		DoUpdateDuration(dur);
}

void BetProcedureFrame::DoUpdateDuration(unsigned int time) {
	command_data data { };
	data.time_to_end = time;
	sendCommand2BytesValue('T', 0, data.time_to_end / 60, 4, &BetProcedureFrame::HandlerDuration,
			"ERROR: Cannot update Duration", data);
}

void BetProcedureFrame::OnDurationM1(wxCommandEvent& event) {
	int dur = std::atoi(m_txtDuration->GetValue()) * 60 - DURATION_DECREMENT;
	if (dur < 0)
		dur = 0;
	DoUpdateDuration(dur);
}

void BetProcedureFrame::DoPolarityChange() {
	int mask = 0x40;
	int releta = (switch1_ == SW_ON) | ((switch2_ == SW_ON) << 1) | ((switch3_ == SW_ON) << 2)
			| ((switch4_ == SW_ON) << 3) | ((switch5_ == SW_ON) << 4) | ((switch6_ == SW_ON) << 5)
			| ((polarity_ == SW_ON) << 6);
	releta = releta xor mask;

	command_data data { };
	data.releta = releta;
	CProtocolCommand cmd = sendCommand2BytesValue('M', 0, releta, 4, &BetProcedureFrame::HandlerSwitchChange,
			"Cannot update switches", data);
}

void BetProcedureFrame::OnPolarity(wxCommandEvent& event) {
	if (state_ == STATE_RUNNING || state_ == STATE_FINISHING)
		return;
	DoPolarityChange();
}

void BetProcedureFrame::DoStart() {
	if (switch1_ == SW_ON) {
		DoUpdateCurrentLimit(1, atoi(m_txtLimitCur1->GetValue()));
		boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	}
	if (switch2_ == SW_ON) {
		DoUpdateCurrentLimit(2, atoi(m_txtLimitCur2->GetValue()));
		boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	}
	if (switch3_ == SW_ON) {
		DoUpdateCurrentLimit(3, atoi(m_txtLimitCur3->GetValue()));
		boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	}
	if (switch4_ == SW_ON) {
		DoUpdateCurrentLimit(4, atoi(m_txtLimitCur4->GetValue()));
		boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	}
	if (switch5_ == SW_ON) {
		DoUpdateCurrentLimit(5, atoi(m_txtLimitCur5->GetValue()));
		boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	}
	if (switch6_ == SW_ON) {
		DoUpdateCurrentLimit(6, atoi(m_txtLimitCur6->GetValue()));
		boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	}
	//set speed of finishing
	sendCommand2Values('S', 0, decrease_speed_ * 100, regulator_speed_ * 100, 4, &BetProcedureFrame::handlerDummy,
			"Cannot set stop speed", command_data());
	boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	DoUpdateSwitches();
	boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	DoUpdateCurrent(std::atoi(m_txtCurrent->GetValue()));
	boost::this_thread::sleep(boost::posix_time::milliseconds(50));
	DoUpdateDuration(std::atoi(m_txtDuration->GetValue()) * 60);
	//send start voltage 1V
	{
		command_data data { };
		data.U = 1;
		sendCommand('U', 0, data.U * 100, 4, &BetProcedureFrame::HandlerStart, "ERROR: Cannot update U", data);
	}
	return;
}

void BetProcedureFrame::OnStart(wxCommandEvent& event) {
	if (state_ == STATE_INITIAL) {
		if (validate())
			DoStart();
		return;
	}
	if (state_ == STATE_RUNNING) {
		DoGoInFinishing();
		return;
	}
}

void BetProcedureFrame::DoTerminate() {
	command_data data { };
	data.U = 0;
	sendCommand('U', 0, data.U * 100, 4, &BetProcedureFrame::handlerTerminateProcedure, "ERROR: Cannot update U", data);
}

void BetProcedureFrame::OnStop(wxCommandEvent& event) {
	DoTerminate();
}

void BetProcedureFrame::DoSendZumer() {
	sendCommand2BytesValue('Z', 0, 0xA0, 4, &BetProcedureFrame::handlerDummy, "ERROR: Cannot send zummer command",
			command_data());
}

void BetProcedureFrame::handlerTerminateProcedure(const std::string& reply, CProtocolCommand& command) {
	voltage_ = command.data().U;
	updateFloatValue(voltage_, m_txtVoltage);
	if (voltage_ == 0)
		DoGoInInitialState();
}

void BetProcedureFrame::handlerDummy(const std::string& reply, CProtocolCommand& command) {
}

void BetProcedureFrame::DoUpdateCurrentLimit(int current, int value) {
	command_data dummy { };
	sendCommand('I', current, value * 10, 4, &BetProcedureFrame::handlerDummy, "ERROR: Cannot update current limit",
			dummy);
}

void BetProcedureFrame::DoSwitchChange(int sw) {
	int mask = 0x1;
	mask = mask << sw;
	int releta = (switch1_ == SW_ON) | ((switch2_ == SW_ON) << 1) | ((switch3_ == SW_ON) << 2)
			| ((switch4_ == SW_ON) << 3) | ((switch5_ == SW_ON) << 4) | ((switch6_ == SW_ON) << 5)
			| ((polarity_ == SW_ON) << 6);
	releta = releta xor mask;
	DoUpdateSwitches(releta);
}

void BetProcedureFrame::DoZeroSwitches() {
	int releta = (polarity_ == SW_ON) << 6;
	DoUpdateSwitches(releta);
}

void BetProcedureFrame::DoUpdateSwitches() {
	int releta = (switch1_ == SW_ON) | ((switch2_ == SW_ON) << 1) | ((switch3_ == SW_ON) << 2)
			| ((switch4_ == SW_ON) << 3) | ((switch5_ == SW_ON) << 4) | ((switch6_ == SW_ON) << 5)
			| ((polarity_ == SW_ON) << 6);
	DoUpdateSwitches(releta);
}

void BetProcedureFrame::DoUpdateSwitches(int releta) {
	command_data data { };
	data.releta = releta;
	CProtocolCommand cmd = sendCommand2BytesValue('M', 0, releta, 4, &BetProcedureFrame::HandlerSwitchChange,
			"Cannot update switches", data);
}

void BetProcedureFrame::OnSwitchChange(wxMouseEvent& event) {
	if (state_ == STATE_RUNNING || state_ == STATE_FINISHING)
		return;
	wxObject* obj = event.GetEventObject();
	if (obj == m_bmpInd1 && switch1_ != SW_FAILURE) {
		DoSwitchChange(0);
	} else if (obj == m_bmpInd2 && switch2_ != SW_FAILURE) {
		DoSwitchChange(1);
	} else if (obj == m_bmpInd3 && switch3_ != SW_FAILURE) {
		DoSwitchChange(2);
	} else if (obj == m_bmpInd4 && switch4_ != SW_FAILURE) {
		DoSwitchChange(3);
	} else if (obj == m_bmpInd5 && switch5_ != SW_FAILURE) {
		DoSwitchChange(4);
	} else if (obj == m_bmpInd6 && switch6_ != SW_FAILURE) {
		DoSwitchChange(5);
	} else
		return;
}

void BetProcedureFrame::HandlerSwitchChange(const std::string& reply, CProtocolCommand& command) {
	int releta = command.data().releta;
	if (switch1_ != SW_FAILURE) {
		switch1_ = releta & 0x1;
		m_bmpInd1->SetBitmap(switch1_ ? lightG_ : lightS_);
	}
	if (switch2_ != SW_FAILURE) {
		if (releta & 0x2)
			switch2_ = SW_ON;
		else
			switch2_ = SW_OFF;
		m_bmpInd2->SetBitmap(switch2_ ? lightG_ : lightS_);
	}
	if (switch3_ != SW_FAILURE) {
		if (releta & 0x4)
			switch3_ = SW_ON;
		else
			switch3_ = SW_OFF;
		m_bmpInd3->SetBitmap(switch3_ ? lightG_ : lightS_);
	}
	if (switch4_ != SW_FAILURE) {
		if (releta & 0x8)
			switch4_ = SW_ON;
		else
			switch4_ = SW_OFF;
		m_bmpInd4->SetBitmap(switch4_ ? lightG_ : lightS_);
	}
	if (switch5_ != SW_FAILURE) {
		if (releta & 0x10)
			switch5_ = SW_ON;
		else
			switch5_ = SW_OFF;
		m_bmpInd5->SetBitmap(switch5_ ? lightG_ : lightS_);
	}
	if (switch6_ != SW_FAILURE) {
		if (releta & 0x20)
			switch6_ = SW_ON;
		else
			switch6_ = SW_OFF;
		m_bmpInd6->SetBitmap(switch6_ ? lightG_ : lightS_);
	}
	polarity_ = releta & 0x40;
	m_button8->SetBackgroundColour(polarity_ ? wxColor(255, 0, 0) : wxColor(0, 255, 0));
	//if all switches happen to be OFF and we are in procedure DoTerminate
	if (((switch1_ == SW_OFF || switch1_ == SW_FAILURE) && (switch2_ == SW_OFF || switch2_ == SW_FAILURE)
			&& (switch3_ == SW_OFF || switch3_ == SW_FAILURE) && (switch4_ == SW_OFF || switch4_ == SW_FAILURE)
			&& (switch5_ == SW_OFF || switch5_ == SW_FAILURE) && (switch6_ == SW_OFF || switch6_ == SW_FAILURE))
			&& (state_ == STATE_RUNNING || state_ == STATE_FINISHING)) {
		DoTerminate();
	}
}

void BetProcedureFrame::HandlerVoltage(const std::string& reply, CProtocolCommand& command) {
	voltage_ = command.data().U;
	updateFloatValue(voltage_, m_txtVoltage);
	if (voltage_ == 0)
		DoGoInInitialState();
}

void BetProcedureFrame::HandlerStart(const std::string&, CProtocolCommand& command) {
	voltage_ = command.data().U;
	updateFloatValue(voltage_, m_txtVoltage);
	DoGoInRunning();
}

void BetProcedureFrame::HandlerCurrent(const std::string& reply, CProtocolCommand& command) {
	int current = command.data().I;
	updateIntegerValue(current, m_txtCurrent);
}

void BetProcedureFrame::updateDurationValue(unsigned int value, wxTextCtrl* ctl) {
	char buffer[10];
	int addition = 0;
	if (value % 60 > 0)
		addition = 1;
	value /= 60;
	value += addition;
	sprintf(buffer, "%-.1u", value);
	ctl->SetValue(buffer);
}

void BetProcedureFrame::HandlerDuration(const std::string& reply, CProtocolCommand& command) {
	time_to_end_ = command.data().time_to_end;
	updateDurationValue(time_to_end_, m_txtDuration);
}

CProtocolCommand BetProcedureFrame::sendCommand(char cmd, unsigned char address, int reply_len,
		void (BetProcedureFrame::*handler)(const std::string&, CProtocolCommand&), const std::string& error_message,
		const command_data& data) {
	char buffer[5];
	buffer[0] = cmd;
	buffer[1] = address + 0x30;
	char check_sum = buffer[0] + buffer[1];
	snprintf(reinterpret_cast<char*>(buffer + 2), 3, "%-.2hhX", check_sum);
	CProtocolCommand v1cmd(std::string(buffer), reply_len, PROTOCOL_TIMEOUT, handler, error_message, this, data);
	protocol_.queue_command(v1cmd);
	return v1cmd;
}

//sends commands with value compressed in two bytes
CProtocolCommand BetProcedureFrame::sendCommand2BytesValue(char cmd, unsigned char address, unsigned int value,
		int reply_len, void (BetProcedureFrame::*handler)(const std::string&, CProtocolCommand&),
		const std::string& error_message, const command_data& data) {
	char buffer[7];
	buffer[0] = cmd;
	buffer[1] = address + 0x30;
	snprintf(reinterpret_cast<char*>(buffer + 2), 3, "%-.2X", value);
	char check_sum = 0;
	for (int i = 0; i < 4; i++)
		check_sum += buffer[i];
	snprintf(reinterpret_cast<char*>(buffer + 4), 3, "%-.2hhX", check_sum);

	CProtocolCommand v1cmd(std::string(buffer), reply_len, PROTOCOL_TIMEOUT, handler, error_message, this, data);
	protocol_.queue_command(v1cmd);
	return v1cmd;
}

CProtocolCommand BetProcedureFrame::sendCommand2Values(char cmd, unsigned char address, unsigned int value1,
		unsigned int value2, int reply_len, void (BetProcedureFrame::*handler)(const std::string&, CProtocolCommand&),
		const std::string& error_message, const command_data& data) {
	char buffer[9];
	buffer[0] = cmd;
	buffer[1] = address + 0x30;
	snprintf(reinterpret_cast<char*>(buffer + 2), 3, "%-.2X", value1);
	snprintf(reinterpret_cast<char*>(buffer + 4), 3, "%-.2X", value2);
	char check_sum = 0;
	for (int i = 0; i < 6; i++)
		check_sum += buffer[i];
	snprintf(reinterpret_cast<char*>(buffer + 6), 3, "%-.2hhX", check_sum);

	CProtocolCommand v1cmd(std::string(buffer), reply_len, PROTOCOL_TIMEOUT, handler, error_message, this, data);
	protocol_.queue_command(v1cmd);
	return v1cmd;
}

//sends commands with value compressed in four bytes
CProtocolCommand BetProcedureFrame::sendCommand(char cmd, unsigned char address, unsigned int value, int reply_len,
		void (BetProcedureFrame::*handler)(const std::string&, CProtocolCommand&), const std::string& error_message,
		const command_data& data) {
	char buffer[9];
	buffer[0] = cmd;
	buffer[1] = address + 0x30;
	snprintf(reinterpret_cast<char*>(buffer + 2), 5, "%-.4X", value);
	char check_sum = 0;
	for (int i = 0; i < 6; i++)
		check_sum += buffer[i];
	snprintf(reinterpret_cast<char*>(buffer + 6), 3, "%-.2hhX", check_sum);

	CProtocolCommand v1cmd(std::string(buffer), reply_len, PROTOCOL_TIMEOUT, handler, error_message, this, data);
	protocol_.queue_command(v1cmd);
	return v1cmd;
}

void BetProcedureFrame::OnKeyEvent(wxKeyEvent& event) {
	int code = event.GetKeyCode();
	bool special = false;
	//set focus
	if (code == 'v' || code == 'V') {
		m_txtVoltage->SetFocus();
		special = true;
	}
	if (code == 'd' || code == 'D') {
		m_txtDuration->SetFocus();
		special = true;
	}
	if (code == 'c' || code == 'C') {
		m_txtCurrent->SetFocus();
		special = true;
	}
	//switches
	if (code >= 0x154 && code <= 0x159 && state_ == STATE_INITIAL) {
		DoSwitchChange(code - 0x154); //0...5
		special = true;
	}
	//currents limit
	if (code >= 0x31 && code <= 0x36 && event.ControlDown()) {
		int cur = code - 0x31;
		switch (cur) {
		case 0:
			m_txtLimitCur1->SetFocus();
			break;
		case 1:
			m_txtLimitCur2->SetFocus();
			break;
		case 2:
			m_txtLimitCur3->SetFocus();
			break;
		case 3:
			m_txtLimitCur4->SetFocus();
			break;
		case 4:
			m_txtLimitCur5->SetFocus();
			break;
		case 5:
			m_txtLimitCur6->SetFocus();
			break;
		}
		special = true;
	}
	//start procedure
	if (code == 's' || code == 'S') {
		if (state_ == STATE_INITIAL && validate())
			DoStart();
		if (state_ == STATE_RUNNING)
			DoGoInFinishing();

		special = true;
	}
	//increase values
	if ((code == 0x184 || code == 0x3d) && state_ == STATE_RUNNING) {      //'+'
		wxWindow* focusWnd = wxWindow::FindFocus();
		if (focusWnd == m_txtVoltage) {
			float value = std::atof(m_txtVoltage->GetValue()) + VOLTAGE_LOW_INCREMENT;
			if (value > VOLTAGE_LIMIT)
				value = VOLTAGE_LIMIT;
			DoUpdateVoltage(value);
		}
		if (focusWnd == m_txtCurrent) {
			int value = std::atoi(m_txtCurrent->GetValue()) + CURRENT_INCREMENT;
			if (value > CURRENT_LIMIT)
				value = CURRENT_LIMIT;
			DoUpdateCurrent(value);
		}
		if (focusWnd == m_txtDuration) {
			int value = std::atoi(m_txtDuration->GetValue()) * 60 + DURATION_INCREMENT;
			if (value > DURATION_LIMIT)
				value = DURATION_LIMIT;
			DoUpdateDuration(value);
		}
		special = true;
	}
	//decrease values
	if ((code == 0x2d) && state_ == STATE_RUNNING) {      //'-'
		wxWindow* focusWnd = wxWindow::FindFocus();
		if (focusWnd == m_txtVoltage) {
			float value = std::atof(m_txtVoltage->GetValue()) - VOLTAGE_LOW_DECREMENT;
			if (value < 0)
				value = 0;
			DoUpdateVoltage(value);
		}
		if (focusWnd == m_txtCurrent) {
			int value = std::atoi(m_txtCurrent->GetValue()) - CURRENT_DECREMENT;
			if (value < 0)
				value = 0;
			DoUpdateCurrent(value);
		}
		if (focusWnd == m_txtDuration) {
			int value = std::atoi(m_txtDuration->GetValue()) * 60 - DURATION_DECREMENT;
			if (value < 0)
				value = 0;
			DoUpdateDuration(value);
		}
		special = true;
	}

	if ((code == 'P' || code == 'p') && state_ == STATE_INITIAL) {
		DoPolarityChange();
		special = true;
	}
	if ((code == 'E' || code == 'e') && state_ != STATE_INITIAL) {
		DoTerminate();
		special = true;
	}

	if (state_ != STATE_INITIAL)
		special = true;
	event.Skip(special);
}

bool BetProcedureFrame::ValidateControl(wxTextCtrl* ctrl, int low_limit, int limit, const char* low_message, const char* message) {
	if (std::atoi(ctrl->GetValue()) < low_limit) {
		wxMessageBox(low_message);
		ctrl->SetFocus();
		return false;
	}
	if (std::atoi(ctrl->GetValue()) > limit) {
		wxMessageBox(message);
		ctrl->SetFocus();
		return false;
	}
	return true;
}

bool BetProcedureFrame::validate() {

	if (!ValidateControl(m_txtCurrent, 1, CURRENT_LIMIT, "Current not entered", "Current limit reached"))
		return false;
	if (switch1_ == SW_ON && !ValidateControl(m_txtLimitCur1, 1, CURRENTS_LIMIT, "Current not entered", "Currents limit reached"))
		return false;
	if (switch2_ == SW_ON && !ValidateControl(m_txtLimitCur2, 1, CURRENTS_LIMIT, "Current not entered", "Currents limit reached"))
		return false;
	if (switch3_ == SW_ON && !ValidateControl(m_txtLimitCur3, 1, CURRENTS_LIMIT, "Current not entered", "Currents limit reached"))
		return false;
	if (switch4_ == SW_ON && !ValidateControl(m_txtLimitCur4, 1, CURRENTS_LIMIT, "Current not entered", "Currents limit reached"))
		return false;
	if (switch5_ == SW_ON && !ValidateControl(m_txtLimitCur5, 1, CURRENTS_LIMIT, "Current not entered", "Currents limit reached"))
		return false;
	if (switch6_ == SW_ON && !ValidateControl(m_txtLimitCur6, 1, CURRENTS_LIMIT, "Current not entered", "Currents limit reached"))
		return false;
	if (!ValidateControl(m_txtDuration, 1, DURATION_LIMIT/60, "Duration not entered", "Duration limit reached"))
		return false;
	if (switch1_ != SW_ON && switch2_ != SW_ON && switch3_ != SW_ON && switch4_ != SW_ON && switch5_ != SW_ON
			&& switch6_ != SW_ON) {
		wxMessageBox("No channel set");
		return false;
	}
	if (cable_ != CABLE_IN || key_ != KEY_OFF) {
		wxMessageBox("Cable is not In or key is not OFF");
		return false;
	}
	return true;
}
