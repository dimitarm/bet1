/*
 * BetTxtControl.h
 *
 *  Created on: Jul 15, 2014
 *      Author: I028663
 */

#ifndef BETTXTCONTROL_H_
#define BETTXTCONTROL_H_

#include <wx/textctrl.h>

class BetTxtControl: public wxTextCtrl {
public:
	BetTxtControl(wxWindow *parent, wxWindowID id,
            const wxString& value = wxEmptyString,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize,
            long style = 0,
            const wxValidator& validator = wxDefaultValidator,
            const wxString& name = wxTextCtrlNameStr);

    bool ProcessEvent(wxEvent& event);
	virtual ~BetTxtControl();
};

#endif /* BETTXTCONTROL_H_ */
