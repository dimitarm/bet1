///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __PROCEDUREFRAME_H__
#define __PROCEDUREFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/textctrl.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class BaseProcedureFrame
///////////////////////////////////////////////////////////////////////////////
class BaseProcedureFrame : public wxFrame
{
	private:

	protected:
		wxStaticText* m_staticText32;
		wxStaticText* m_txtPatientName;
		wxStaticText* m_staticText321;
		wxStaticText* m_txtTreatmentNumber;
		wxStaticText* m_staticText20;
		wxStaticText* m_staticText21;
		wxStaticText* m_staticText22;
		wxStaticText* m_staticText23;
		wxStaticText* m_staticText24;
		wxStaticText* m_staticText25;
		wxStaticText* m_staticText26;
		wxStaticBitmap* m_bmpElectrodes;
		wxStaticText* m_txtProcedureLabel;
		wxStaticText* m_staticText28;
		wxStaticText* m_staticText29;
		wxStaticText* m_staticText30;
		wxStaticText* m_staticText31;
		wxStaticBitmap* m_bmpVoltage;
		wxTextCtrl* m_txtVoltage;
		wxButton* m_butVoltage1;
		wxButton* m_butVoltagem1;
		wxButton* m_button5;
		wxTextCtrl* m_txtCurrent;
		wxButton* m_button31;
		wxButton* m_button41;
		wxTextCtrl* m_txtDuration;
		wxButton* m_button32;
		wxButton* m_button42;
		wxStaticText* m_staticText4;
		wxStaticText* m_txtCurrentVoltage;
		wxStaticText* m_staticText6;
		wxStaticText* m_txtCurrentCurrent;
		wxStaticText* m_staticText41;
		wxStaticText* m_txtCurrentR;
		wxStaticText* m_staticText42;
		wxStaticText* m_txtCurrentQ;
		wxStaticText* m_staticText43;
		wxStaticText* m_txtKey;
		wxStaticText* m_staticText44;
		wxStaticText* m_txtCable;
		wxStaticText* m_staticText16;
		wxTextCtrl* m_txtLimitCur1;
		wxStaticBitmap* m_bmpInd1;
		wxTextCtrl* m_txtCur1;
		wxTextCtrl* m_txtLimitCur2;
		wxStaticBitmap* m_bmpInd2;
		wxTextCtrl* m_txtCur2;
		wxTextCtrl* m_txtLimitCur3;
		wxStaticBitmap* m_bmpInd3;
		wxTextCtrl* m_txtCur3;
		wxTextCtrl* m_txtLimitCur4;
		wxStaticBitmap* m_bmpInd4;
		wxTextCtrl* m_txtCur4;
		wxTextCtrl* m_txtLimitCur5;
		wxStaticBitmap* m_bmpInd5;
		wxTextCtrl* m_txtCur5;
		wxTextCtrl* m_txtLimitCur6;
		wxStaticBitmap* m_bmpInd6;
		wxTextCtrl* m_txtCur6;
		wxStaticText* m_staticText35;
		wxStaticText* m_staticText36;
		wxButton* m_button8;
		wxButton* m_buttonSTART;
		wxButton* m_buttonSTOP;

		// Virtual event handlers, overide them in your derived class
		virtual void OnChar( wxKeyEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnVoltage1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVoltageM1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnVoltageM5( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCurrent1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnCurrentM1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDuration1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDurationM1( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSwitchChange( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnPolarity( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStart( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnStop( wxCommandEvent& event ) { event.Skip(); }


	public:

		BaseProcedureFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~BaseProcedureFrame();

};

#endif //__PROCEDUREFRAME_H__
