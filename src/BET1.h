/*
 * BET1.h
 *
 *  Created on: Jun 29, 2014
 *      Author: dimitar
 */
#include "Patient.h"
#include "MainFrame.h"
#include "BetProcedureFrame.h"

#ifndef BET1_H_
#define BET1_H_


class MainApp: public wxApp {
public:
	virtual bool OnInit();
	virtual int OnExit();
	int FilterEvent 	( 	wxEvent &  	event	);
	void setProcedureFrame(BetProcedureFrame*);

	const wxFont& getTitleFont();
	const wxFont& getNormFont();
	const wxFont& getBoldFont();

private:
	MainFrame *main_frame_;
	BetProcedureFrame* proc_frame_;
	wxFont title_font_;
	wxFont norm_font_;
	wxFont bold_font_;

	bool registerFonts();
};

DECLARE_APP(MainApp)

#endif /* BET1_H_ */
