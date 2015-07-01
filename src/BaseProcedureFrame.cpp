///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun  5 2014)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ProcedureFrame.h"

///////////////////////////////////////////////////////////////////////////

BaseProcedureFrame::BaseProcedureFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 237, 236, 233 ) );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText32 = new wxStaticText( this, wxID_ANY, wxT("Name: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	m_staticText32->SetFont( wxFont( 14, 74, 90, 90, false, wxT("Arial") ) );

	bSizer21->Add( m_staticText32, 0, wxALL, 5 );

	m_txtPatientName = new wxStaticText( this, wxID_ANY, wxT("_________________________________________"), wxDefaultPosition, wxDefaultSize, 0 );
	m_txtPatientName->Wrap( -1 );
	m_txtPatientName->SetFont( wxFont( 14, 70, 90, 90, false, wxT("Arial") ) );

	bSizer21->Add( m_txtPatientName, 0, wxALL, 5 );


	bSizer3->Add( bSizer21, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	m_staticText20 = new wxStaticText( this, wxID_ANY, wxT("Electrode Currents (mA):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	m_staticText20->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );

	bSizer18->Add( m_staticText20, 0, wxALL, 5 );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText21 = new wxStaticText( this, wxID_ANY, wxT("Output 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	m_staticText21->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText21->SetForegroundColour( wxColour( 13, 193, 184 ) );

	bSizer19->Add( m_staticText21, 0, wxALL, 5 );

	m_staticText22 = new wxStaticText( this, wxID_ANY, wxT("Output 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	m_staticText22->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText22->SetForegroundColour( wxColour( 0, 0, 255 ) );

	bSizer19->Add( m_staticText22, 0, wxALL, 5 );

	m_staticText23 = new wxStaticText( this, wxID_ANY, wxT("Output 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	m_staticText23->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText23->SetForegroundColour( wxColour( 125, 0, 255 ) );

	bSizer19->Add( m_staticText23, 0, wxALL, 5 );

	m_staticText24 = new wxStaticText( this, wxID_ANY, wxT("Output 4"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	m_staticText24->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText24->SetForegroundColour( wxColour( 255, 0, 0 ) );

	bSizer19->Add( m_staticText24, 0, wxALL, 5 );

	m_staticText25 = new wxStaticText( this, wxID_ANY, wxT("Output 5"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	m_staticText25->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText25->SetForegroundColour( wxColour( 255, 125, 0 ) );

	bSizer19->Add( m_staticText25, 0, wxALL, 5 );

	m_staticText26 = new wxStaticText( this, wxID_ANY, wxT("Output 6"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	m_staticText26->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText26->SetForegroundColour( wxColour( 80, 170, 80 ) );

	bSizer19->Add( m_staticText26, 0, wxALL, 5 );


	bSizer18->Add( bSizer19, 0, wxEXPAND, 5 );


	bSizer3->Add( bSizer18, 0, wxEXPAND, 5 );

	m_bmpElectrodes = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 706,140 ), 0 );
	bSizer3->Add( m_bmpElectrodes, 0, wxALIGN_CENTER_VERTICAL|wxALIGN_LEFT|wxALL, 5 );

	m_txtProcedureLabel = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtProcedureLabel->Wrap( -1 );
	m_txtProcedureLabel->SetFont( wxFont( 9, 74, 90, 90, false, wxT("Sans") ) );

	bSizer3->Add( m_txtProcedureLabel, 0, wxALL, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText28 = new wxStaticText( this, wxID_ANY, wxT("Voltage U [V]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	m_staticText28->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText28->SetForegroundColour( wxColour( 0, 0, 255 ) );

	bSizer20->Add( m_staticText28, 0, wxALL, 5 );

	m_staticText29 = new wxStaticText( this, wxID_ANY, wxT("Current [mA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	m_staticText29->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText29->SetForegroundColour( wxColour( 125, 0, 0 ) );

	bSizer20->Add( m_staticText29, 0, wxALL, 5 );

	m_staticText30 = new wxStaticText( this, wxID_ANY, wxT("Resistence R [Ohm x 10]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	m_staticText30->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText30->SetForegroundColour( wxColour( 0, 125, 0 ) );

	bSizer20->Add( m_staticText30, 0, wxALL, 5 );

	m_staticText31 = new wxStaticText( this, wxID_ANY, wxT("Charge Q [C x 10]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	m_staticText31->SetFont( wxFont( 12, 74, 90, 90, false, wxT("Arial") ) );
	m_staticText31->SetForegroundColour( wxColour( 125, 0, 125 ) );

	bSizer20->Add( m_staticText31, 0, wxALL, 5 );


	bSizer3->Add( bSizer20, 0, wxEXPAND, 5 );

	m_bmpVoltage = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 706,261 ), 0 );
	bSizer3->Add( m_bmpVoltage, 0, wxALL, 5 );


	bSizer3->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("&Voltage [V]") ), wxVERTICAL );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	m_txtVoltage = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtVoltage->SetMaxLength( 3 );
	m_txtVoltage->SetFont( wxFont( 28, 74, 90, 90, false, wxT("Arial") ) );
	m_txtVoltage->Enable( false );

	bSizer12->Add( m_txtVoltage, 0, wxALL, 5 );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxVERTICAL );

	m_butVoltage1 = new wxButton( this, wxID_ANY, wxT("+ 0.1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_butVoltage1->SetBackgroundColour( wxColour( 27, 126, 249 ) );

	bSizer13->Add( m_butVoltage1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	m_butVoltagem1 = new wxButton( this, wxID_ANY, wxT("- 0.1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_butVoltagem1->SetBackgroundColour( wxColour( 27, 126, 249 ) );

	bSizer13->Add( m_butVoltagem1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	bSizer12->Add( bSizer13, 0, wxEXPAND, 5 );

	m_button5 = new wxButton( this, wxID_ANY, wxT("-5"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button5->SetBackgroundColour( wxColour( 27, 126, 249 ) );

	bSizer12->Add( m_button5, 0, wxALIGN_CENTER_VERTICAL|wxALL|wxEXPAND, 5 );


	sbSizer2->Add( bSizer12, 0, wxEXPAND, 5 );


	bSizer11->Add( sbSizer2, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer21;
	sbSizer21 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("&Current [mA]") ), wxVERTICAL );

	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );

	m_txtCurrent = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	m_txtCurrent->SetMaxLength( 3 );
	m_txtCurrent->SetFont( wxFont( 28, 74, 90, 90, false, wxT("Arial") ) );

	bSizer121->Add( m_txtCurrent, 0, wxALL, 5 );

	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxVERTICAL );

	m_button31 = new wxButton( this, wxID_ANY, wxT("+ 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button31->SetBackgroundColour( wxColour( 253, 111, 10 ) );

	bSizer131->Add( m_button31, 0, wxALL, 5 );

	m_button41 = new wxButton( this, wxID_ANY, wxT("- 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button41->SetBackgroundColour( wxColour( 253, 111, 10 ) );

	bSizer131->Add( m_button41, 0, wxALL, 5 );


	bSizer121->Add( bSizer131, 1, 0, 5 );


	sbSizer21->Add( bSizer121, 0, 0, 5 );


	bSizer11->Add( sbSizer21, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer22;
	sbSizer22 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("&Duration [min]") ), wxVERTICAL );

	wxBoxSizer* bSizer122;
	bSizer122 = new wxBoxSizer( wxHORIZONTAL );

	m_txtDuration = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtDuration->SetMaxLength( 3 );
	m_txtDuration->SetFont( wxFont( 28, 74, 90, 90, false, wxT("Arial") ) );

	bSizer122->Add( m_txtDuration, 0, wxALL, 5 );

	wxBoxSizer* bSizer132;
	bSizer132 = new wxBoxSizer( wxVERTICAL );

	m_button32 = new wxButton( this, wxID_ANY, wxT("+1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button32->SetBackgroundColour( wxColour( 173, 46, 245 ) );

	bSizer132->Add( m_button32, 0, wxALL, 5 );

	m_button42 = new wxButton( this, wxID_ANY, wxT("-1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button42->SetBackgroundColour( wxColour( 173, 46, 245 ) );

	bSizer132->Add( m_button42, 0, wxALL, 5 );


	bSizer122->Add( bSizer132, 0, wxEXPAND, 5 );


	sbSizer22->Add( bSizer122, 0, wxEXPAND, 5 );


	bSizer11->Add( sbSizer22, 0, wxALL|wxEXPAND, 5 );


	bSizer3->Add( bSizer11, 0, wxEXPAND, 5 );


	bSizer1->Add( bSizer3, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 3, 2, 0, 0 );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxVERTICAL );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("U [V]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	m_staticText4->SetFont( wxFont( 13, 70, 90, 92, false, wxT("Arial") ) );
	m_staticText4->SetForegroundColour( wxColour( 0, 0, 255 ) );

	bSizer41->Add( m_staticText4, 0, wxALL, 5 );

	m_txtCurrentVoltage = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtCurrentVoltage->Wrap( -1 );
	m_txtCurrentVoltage->SetFont( wxFont( 16, 74, 90, 92, false, wxT("Arial") ) );

	bSizer41->Add( m_txtCurrentVoltage, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	gSizer1->Add( bSizer41, 1, wxALIGN_CENTER, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("I [mA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	m_staticText6->SetFont( wxFont( 13, 70, 90, 92, false, wxT("Arial") ) );
	m_staticText6->SetForegroundColour( wxColour( 125, 0, 0 ) );

	bSizer5->Add( m_staticText6, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtCurrentCurrent = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtCurrentCurrent->Wrap( -1 );
	m_txtCurrentCurrent->SetFont( wxFont( 16, 74, 90, 92, false, wxT("Arial") ) );

	bSizer5->Add( m_txtCurrentCurrent, 0, wxALIGN_CENTER|wxALL, 5 );


	gSizer1->Add( bSizer5, 1, wxALIGN_CENTER, 5 );

	wxBoxSizer* bSizer411;
	bSizer411 = new wxBoxSizer( wxVERTICAL );

	m_staticText41 = new wxStaticText( this, wxID_ANY, wxT("Rx [O]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	m_staticText41->SetFont( wxFont( 13, 70, 90, 92, false, wxT("Arial") ) );
	m_staticText41->SetForegroundColour( wxColour( 0, 125, 0 ) );

	bSizer411->Add( m_staticText41, 0, wxALL, 5 );

	m_txtCurrentR = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtCurrentR->Wrap( -1 );
	m_txtCurrentR->SetFont( wxFont( 16, 74, 90, 92, false, wxT("Arial") ) );

	bSizer411->Add( m_txtCurrentR, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	gSizer1->Add( bSizer411, 1, wxALIGN_CENTER, 20 );

	wxBoxSizer* bSizer412;
	bSizer412 = new wxBoxSizer( wxVERTICAL );

	m_staticText42 = new wxStaticText( this, wxID_ANY, wxT("Q [C]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	m_staticText42->SetFont( wxFont( 13, 70, 90, 92, false, wxT("Arial") ) );
	m_staticText42->SetForegroundColour( wxColour( 125, 0, 125 ) );

	bSizer412->Add( m_staticText42, 0, wxALL, 5 );

	m_txtCurrentQ = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtCurrentQ->Wrap( -1 );
	m_txtCurrentQ->SetFont( wxFont( 16, 74, 90, 92, false, wxT("Arial") ) );

	bSizer412->Add( m_txtCurrentQ, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	gSizer1->Add( bSizer412, 1, wxALIGN_CENTER, 20 );

	wxBoxSizer* bSizer413;
	bSizer413 = new wxBoxSizer( wxVERTICAL );

	m_staticText43 = new wxStaticText( this, wxID_ANY, wxT("Key"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	m_staticText43->SetFont( wxFont( 13, 70, 90, 92, false, wxT("Arial") ) );
	m_staticText43->SetForegroundColour( wxColour( 27, 126, 249 ) );

	bSizer413->Add( m_staticText43, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtKey = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtKey->Wrap( -1 );
	m_txtKey->SetFont( wxFont( 16, 70, 90, 92, false, wxT("Arial") ) );

	bSizer413->Add( m_txtKey, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	gSizer1->Add( bSizer413, 1, wxALIGN_CENTER, 20 );

	wxBoxSizer* bSizer414;
	bSizer414 = new wxBoxSizer( wxVERTICAL );

	m_staticText44 = new wxStaticText( this, wxID_ANY, wxT("Cable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	m_staticText44->SetFont( wxFont( 13, 70, 90, 92, false, wxT("Arial") ) );
	m_staticText44->SetForegroundColour( wxColour( 27, 126, 249 ) );

	bSizer414->Add( m_staticText44, 0, wxALL, 5 );

	m_txtCable = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_txtCable->Wrap( -1 );
	m_txtCable->SetFont( wxFont( 16, 70, 90, 92, false, wxT("Arial") ) );
	m_txtCable->SetForegroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	bSizer414->Add( m_txtCable, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );


	gSizer1->Add( bSizer414, 1, wxALIGN_CENTER, 20 );


	bSizer4->Add( gSizer1, 1, wxALIGN_CENTER|wxEXPAND, 5 );

	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxEmptyString ), wxVERTICAL );

	m_staticText16 = new wxStaticText( this, wxID_ANY, wxT("Locale Current [mA]"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	m_staticText16->SetFont( wxFont( 13, 74, 90, 90, false, wxT("Sans") ) );

	sbSizer1->Add( m_staticText16, 0, wxALIGN_CENTER|wxALL, 5 );

	wxGridSizer* gSizer2;
	gSizer2 = new wxGridSizer( 7, 3, 0, 0 );

	m_txtLimitCur1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER );
	m_txtLimitCur1->SetMaxLength( 2 );
	m_txtLimitCur1->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );

	gSizer2->Add( m_txtLimitCur1, 0, wxALL, 5 );

	m_bmpInd1 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 30,30 ), 0 );
	gSizer2->Add( m_bmpInd1, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtCur1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_txtCur1->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );
	m_txtCur1->Enable( false );

	gSizer2->Add( m_txtCur1, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtLimitCur2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER );
	m_txtLimitCur2->SetMaxLength( 2 );
	m_txtLimitCur2->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );

	gSizer2->Add( m_txtLimitCur2, 0, wxALL, 5 );

	m_bmpInd2 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 30,30 ), 0 );
	gSizer2->Add( m_bmpInd2, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtCur2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_txtCur2->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );
	m_txtCur2->Enable( false );

	gSizer2->Add( m_txtCur2, 0, wxALIGN_CENTER, 5 );

	m_txtLimitCur3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER );
	m_txtLimitCur3->SetMaxLength( 2 );
	m_txtLimitCur3->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );

	gSizer2->Add( m_txtLimitCur3, 0, wxALL, 5 );

	m_bmpInd3 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 30,30 ), 0 );
	gSizer2->Add( m_bmpInd3, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtCur3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_txtCur3->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );
	m_txtCur3->Enable( false );

	gSizer2->Add( m_txtCur3, 0, wxALIGN_CENTER, 5 );

	m_txtLimitCur4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER );
	m_txtLimitCur4->SetMaxLength( 2 );
	m_txtLimitCur4->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );

	gSizer2->Add( m_txtLimitCur4, 0, wxALL, 5 );

	m_bmpInd4 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 30,30 ), 0 );
	gSizer2->Add( m_bmpInd4, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtCur4 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_txtCur4->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );
	m_txtCur4->Enable( false );

	gSizer2->Add( m_txtCur4, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtLimitCur5 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER );
	m_txtLimitCur5->SetMaxLength( 2 );
	m_txtLimitCur5->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );

	gSizer2->Add( m_txtLimitCur5, 0, wxALL, 5 );

	m_bmpInd5 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 30,30 ), 0 );
	gSizer2->Add( m_bmpInd5, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtCur5 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_txtCur5->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );
	m_txtCur5->Enable( false );

	gSizer2->Add( m_txtCur5, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtLimitCur6 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_PROCESS_ENTER );
	m_txtLimitCur6->SetMaxLength( 2 );
	m_txtLimitCur6->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );

	gSizer2->Add( m_txtLimitCur6, 0, wxALL, 5 );

	m_bmpInd6 = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 30,30 ), 0 );
	gSizer2->Add( m_bmpInd6, 0, wxALIGN_CENTER|wxALL, 5 );

	m_txtCur6 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	m_txtCur6->SetFont( wxFont( 10, 74, 90, 90, false, wxT("Arial") ) );
	m_txtCur6->Enable( false );

	gSizer2->Add( m_txtCur6, 0, wxALIGN_CENTER|wxALL, 5 );

	m_staticText35 = new wxStaticText( this, wxID_ANY, wxT("Limit"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	gSizer2->Add( m_staticText35, 0, wxALIGN_CENTER|wxALL, 5 );


	gSizer2->Add( 0, 0, 1, wxEXPAND, 5 );

	m_staticText36 = new wxStaticText( this, wxID_ANY, wxT("Actual"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	gSizer2->Add( m_staticText36, 0, wxALIGN_CENTER|wxALL, 5 );


	sbSizer1->Add( gSizer2, 0, wxALIGN_CENTER, 5 );


	bSizer4->Add( sbSizer1, 0, wxALIGN_CENTER, 5 );

	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );

	m_button8 = new wxButton( this, wxID_ANY, wxT("&Polarity"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button8->SetFont( wxFont( 16, 74, 90, 90, false, wxT("Sans") ) );
	m_button8->SetBackgroundColour( wxColour( 55, 178, 25 ) );

	bSizer22->Add( m_button8, 0, wxALIGN_CENTER|wxALL, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	m_buttonSTART = new wxButton( this, wxID_ANY, wxT("&STOP"), wxDefaultPosition, wxSize( 120,-1 ), 0 );
	m_buttonSTART->SetFont( wxFont( 24, 74, 90, 90, false, wxT("Sans") ) );
	m_buttonSTART->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOBK ) );

	bSizer10->Add( m_buttonSTART, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 10 );


	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );

	m_buttonSTOP = new wxButton( this, wxID_ANY, wxT("&Emergency\n     STOP"), wxDefaultPosition, wxSize( -1,90 ), 0 );
	m_buttonSTOP->SetFont( wxFont( 24, 74, 90, 90, false, wxT("Sans") ) );
	m_buttonSTOP->SetBackgroundColour( wxColour( 205, 13, 13 ) );

	bSizer10->Add( m_buttonSTOP, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 10 );


	bSizer22->Add( bSizer10, 0, wxALIGN_CENTER, 5 );


	bSizer4->Add( bSizer22, 0, wxEXPAND, 5 );


	bSizer1->Add( bSizer4, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );

	// Connect Events
	this->Connect( wxEVT_CHAR, wxKeyEventHandler( BaseProcedureFrame::OnChar ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( BaseProcedureFrame::OnClose ) );
	m_butVoltage1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnVoltage1 ), NULL, this );
	m_butVoltagem1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnVoltageM1 ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnVoltageM5 ), NULL, this );
	m_button31->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnCurrent1 ), NULL, this );
	m_button41->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnCurrentM1 ), NULL, this );
	m_button32->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnDuration1 ), NULL, this );
	m_button42->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnDurationM1 ), NULL, this );
	m_bmpInd1->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd2->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd3->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd4->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd5->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd6->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnPolarity ), NULL, this );
	m_buttonSTART->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnStart ), NULL, this );
	m_buttonSTOP->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnStop ), NULL, this );
}

BaseProcedureFrame::~BaseProcedureFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CHAR, wxKeyEventHandler( BaseProcedureFrame::OnChar ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( BaseProcedureFrame::OnClose ) );
	m_butVoltage1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnVoltage1 ), NULL, this );
	m_butVoltagem1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnVoltageM1 ), NULL, this );
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnVoltageM5 ), NULL, this );
	m_button31->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnCurrent1 ), NULL, this );
	m_button41->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnCurrentM1 ), NULL, this );
	m_button32->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnDuration1 ), NULL, this );
	m_button42->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnDurationM1 ), NULL, this );
	m_bmpInd1->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd2->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd3->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd4->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd5->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_bmpInd6->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( BaseProcedureFrame::OnSwitchChange ), NULL, this );
	m_button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnPolarity ), NULL, this );
	m_buttonSTART->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnStart ), NULL, this );
	m_buttonSTOP->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( BaseProcedureFrame::OnStop ), NULL, this );

}
