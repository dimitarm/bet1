/*
 * BetTxtControl.cpp
 *
 *  Created on: Jul 15, 2014
 *      Author: I028663
 */

#include "BetTxtControl.h"

BetTxtControl::BetTxtControl(wxWindow *parent, wxWindowID id,
        const wxString& value,
        const wxPoint& pos,
        const wxSize& size,
        long style,
        const wxValidator& validator,
        const wxString& name) : wxTextCtrl(parent, id,value,pos,size,style,validator,name) {


}

bool BetTxtControl::ProcessEvent(wxEvent& event){
	if (event.GetEventType() == wxEVT_KEY_DOWN){
		wxKeyEvent* keyEvent = static_cast<wxKeyEvent*>(&event);
		if(!GetParent()->ProcessWindowEvent(event))
			return true;
	}
	return wxTextCtrl::ProcessEvent(event);
}

BetTxtControl::~BetTxtControl() {
}

