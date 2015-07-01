/*
 * MainFrame.cpp
 *
 *  Created on: Jun 16, 2014
 *      Author: dimitar
 */

#ifdef __WXMSW__
#include <winsock2.h>
#endif

#include <wx/textctrl.h>
#include <wx/numformatter.h>
#include <wx/utils.h>
#include <wx/generic/statbmpg.h>
#include <wx/mimetype.h>

#include <wx/pdfdc.h>

#include "MainFrame.h"
#include "betconst.h"
#include "DB.h"
#include <cassert>
#include <stdlib.h>
#include "BET1.h"
#include "TreatmentPrintout.h"
#include "Treatment.h"

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame) EVT_CLOSE(MainFrame::OnClose)
EVT_MENU(wxID_EXIT, MainFrame::OnExit)
EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
wxEND_EVENT_TABLE()

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) :
		wxFrame(NULL, wxID_ANY, title, pos, size), m_EmptyImage(706, 261, true) {
	m_EmptyImage.InitAlpha();
	unsigned char* alpha = m_EmptyImage.GetAlpha();
	for (int i = 0; i < m_EmptyImage.GetWidth() * m_EmptyImage.GetHeight(); i++)
		alpha[i] = wxIMAGE_ALPHA_TRANSPARENT;

	wxMenu *menuFile = new wxMenu;
	m_menuPrintId = wxNewId();
	m_menuSavePdfId = wxNewId();

	menuFile->Append(m_menuSavePdfId, "Save As PDF...");
	menuFile->Append(m_menuPrintId, "Print...");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);

	wxMenu *menuHelp = new wxMenu;
	menuHelp->Append(wxID_ABOUT);

	wxMenu *menuPatient = new wxMenu;
	m_menuNewPatientId = wxNewId();
	m_menuDeletePatientId = wxNewId();
	m_menuSavePatientId = wxNewId();
	menuPatient->Append(m_menuNewPatientId, "New...");
	menuPatient->Append(m_menuDeletePatientId, "Delete...");
	menuPatient->AppendSeparator();
	menuPatient->Append(m_menuSavePatientId, "Save...");

	wxMenu *menuTreatment = new wxMenu();
	m_menuNewTreatmentId = wxNewId();
	menuTreatment->Append(m_menuNewTreatmentId, "New...");

	m_pMenuBar = new wxMenuBar();
	m_pMenuBar->Append(menuFile, "&File");
	m_pMenuBar->Append(menuPatient, "&Patient");
	m_pMenuBar->Append(menuTreatment, "&Treatment");
	m_pMenuBar->Append(menuHelp, "&Help");
	SetMenuBar(m_pMenuBar);
	CreateStatusBar();
	SetStatusText("Welcome to BET1!");

	AddControls();

	Bind(wxEVT_LISTBOX, &MainFrame::OnSelectPatient, this, m_pPatientList->GetId());
	Bind(wxEVT_BUTTON, &MainFrame::OnPrevTreatment, this, m_pPrevTreatmentButton->GetId());
	Bind(wxEVT_BUTTON, &MainFrame::OnNextTreatment, this, m_pNextTreatmentButton->GetId());
	Bind(wxEVT_BUTTON, &MainFrame::OnNewPatient, this, m_pNewPatientButton->GetId());
	Bind(wxEVT_BUTTON, &MainFrame::OnDeletePatient, this, m_pDeletePatientButton->GetId());
	Bind(wxEVT_BUTTON, &MainFrame::OnSavePatient, this, m_pSavepatientDataButton->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pLastname->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pFirstname->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pBirthday->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pBirthday->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pStreet->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pPostcode->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pCity->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pPhone->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pDiagnosis->GetId());
	Bind(wxEVT_TEXT, &MainFrame::OnChangePatientData, this, m_pNotes->GetId());
	Bind(wxEVT_MENU, &MainFrame::OnNewTreatment, this, m_menuNewTreatmentId);
	Bind(wxEVT_MENU, &MainFrame::OnNewPatient, this, m_menuNewPatientId);
	Bind(wxEVT_MENU, &MainFrame::OnDeletePatient, this, m_menuDeletePatientId);
	Bind(wxEVT_MENU, &MainFrame::OnSavePatient, this, m_menuSavePatientId);
	Bind(wxEVT_MENU, &MainFrame::OnPrint, this, m_menuPrintId);
	Bind(wxEVT_MENU, &MainFrame::OnPdf, this, m_menuSavePdfId);

	m_pPatientNumber->Disable();
	reload();
}

void MainFrame::AddControls() {
	wxBoxSizer *box1sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *box2sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *box3sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *box4sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *box5sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *box6sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *box7sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *box8sizer = new wxBoxSizer(wxHORIZONTAL);
//	wxBoxSizer *box9sizer = new wxBoxSizer(wxHORIZONTAL); //image sizer
	wxBoxSizer *box10sizer = new wxBoxSizer(wxVERTICAL); //patient details sizer

	box1sizer->Add(box2sizer, 1, wxALL | wxEXPAND);
	box1sizer->Add(box3sizer, 0, wxALL | wxEXPAND);

	box2sizer->Add(box4sizer, 0, wxALL | wxEXPAND);
	box2sizer->Add(box7sizer, 1, wxALL | wxEXPAND);

	m_pPatientList = new wxListBox(this, -1, wxDefaultPosition, wxSize(100, -1), 0, NULL,
	wxLB_SINGLE | wxLB_NEEDED_SB | wxLB_SORT, wxDefaultValidator, "patients list");
	m_pNewPatientButton = new wxButton(this, -1, "New patient");
	m_pDeletePatientButton = new wxButton(this, -1, "Delete patient");

	box3sizer->Add(m_pPatientList, 1, wxALL | wxEXPAND, 4);
	box3sizer->Add(m_pNewPatientButton, 0, wxALL | wxALIGN_CENTER, 4);
	box3sizer->Add(m_pDeletePatientButton, 0, wxALL | wxALIGN_CENTER, 4);

	box4sizer->Add(box5sizer, 0, wxALL | wxEXPAND, 5);
	box4sizer->Add(box6sizer, 1, wxALL | wxEXPAND, 2);

	m_pSavepatientDataButton = new wxButton(this, -1, "Save patient data");
	box5sizer->Add(box10sizer, 1, wxALL | wxEXPAND);

	m_pLastname = new wxTextCtrl(this, -1, "");
	m_pFirstname = new wxTextCtrl(this, -1, "");
	m_pBirthday = new wxTextCtrl(this, -1, "");
	m_pStreet = new wxTextCtrl(this, -1, "");
	m_pPostcode = new wxTextCtrl(this, -1, "");
	m_pCity = new wxTextCtrl(this, -1, "");
	m_pPhone = new wxTextCtrl(this, -1, "");
	m_pPatientNumber = new wxTextCtrl(this, -1, "");

	AddPersonDetail(box10sizer, m_pPatientNumber, wxT("Patient number"));
	AddPersonDetail(box10sizer, m_pFirstname, wxT("First name"));
	AddPersonDetail(box10sizer, m_pLastname, wxT("Last name"));
	AddPersonDetail(box10sizer, m_pBirthday, wxT("Birthday"));
	AddPersonDetail(box10sizer, m_pStreet, wxT("Address"));
	AddPersonDetail(box10sizer, m_pPostcode, wxT("Post code"));
	AddPersonDetail(box10sizer, m_pCity, wxT("City"));
	AddPersonDetail(box10sizer, m_pPhone, wxT("Phone"));

	box5sizer->Add(m_pSavepatientDataButton, 0, wxTOP | wxALIGN_TOP | wxALIGN_CENTER_HORIZONTAL, 10);

	m_pDiagnosisLabel = new wxStaticText(this, -1, "", wxDefaultPosition, wxDefaultSize);

	m_pDiagnosis = new wxTextCtrl(this, -1, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
	m_pNotesLabel = new wxStaticText(this, -1, "");
	m_pNotes = new wxTextCtrl(this, -1, "", wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);

	box6sizer->Add(m_pDiagnosisLabel, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 4);
	box6sizer->Add(m_pDiagnosis, 1, wxEXPAND | wxALIGN_CENTER);
	box6sizer->Add(m_pNotesLabel, 0, wxTOP | wxBOTTOM | wxALIGN_CENTER, 4);
	box6sizer->Add(m_pNotes, 1, wxEXPAND | wxALIGN_CENTER);

	m_pPicture = new wxNotebook(this, -1, wxDefaultPosition, wxDefaultSize, wxNB_RIGHT);
	m_pGraphics1 = new wxGenericStaticBitmap(m_pPicture, wxID_ANY, m_EmptyImage);
	m_pCurrents = new wxGenericStaticBitmap(m_pPicture, wxID_ANY, m_EmptyImage);
//	m_pPhoto = new wxGenericStaticBitmap(m_pPicture, wxID_ANY, m_EmptyImage);
	m_pPicture->AddPage(m_pGraphics1, "Treatment", true);
	m_pPicture->AddPage(m_pCurrents, "Currents", false);
//	m_pPicture->AddPage(m_pPhoto, "Photo", false);

	box7sizer->Add(box8sizer, 0, wxALIGN_CENTER | wxEXPAND | wxTOP | wxBOTTOM, 5);
	box7sizer->Add(m_pPicture, 1, wxALIGN_CENTER | wxEXPAND);

	m_pPrevTreatmentButton = new wxButton(this, -1, "<<");
	m_pNextTreatmentButton = new wxButton(this, -1, ">>");
	m_pTreatmentImgLabel = new wxStaticText(this, -1, wxT(""));
	box8sizer->Add(m_pPrevTreatmentButton, 1, wxLEFT, 20);
	box8sizer->Add(m_pTreatmentImgLabel, 3, wxALIGN_CENTER | wxLEFT | wxRIGHT, 20);
	box8sizer->Add(m_pNextTreatmentButton, 1, wxRIGHT, 20);

	SetSizerAndFit(box1sizer); // use the sizer for layout and size window
}

void MainFrame::AddPersonDetail(wxSizer* mainSizer, wxWindow* control, const wxString& label) {
	wxBoxSizer* tempSizer;
	tempSizer = new wxBoxSizer(wxHORIZONTAL);
	tempSizer->Add(new wxStaticText(this, -1, label), 1, wxALIGN_CENTER | wxLEFT | wxRIGHT, 2);
	tempSizer->Add(control, 0);
	mainSizer->Add(tempSizer, 0, wxEXPAND | wxALIGN_CENTER | wxALL, 2);
}

void MainFrame::OnClose(wxCloseEvent& event) {
	checkForDirtyData();
	Destroy();
}

void MainFrame::OnExit(wxCommandEvent& event) {
	Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event) {
	wxMessageBox(LOGO, "ELO", wxOK | wxICON_INFORMATION);
}

void MainFrame::reload() {
	m_PatientIndex = -1;
	m_Patients = DB::getInst()->getPatients();
	m_pDiagnosis->Enable(false);
	m_pNotes->Enable(false);
	m_pLastname->Enable(false);
	m_pFirstname->Enable(false);
	m_pBirthday->Enable(false);
	m_pBirthday->Enable(false);
	m_pStreet->Enable(false);
	m_pPostcode->Enable(false);
	m_pCity->Enable(false);
	m_pPhone->Enable(false);
	m_pLastname->Clear();
	m_pFirstname->Clear();
	m_pBirthday->Clear();
	m_pBirthday->Clear();
	m_pStreet->Clear();
	m_pPostcode->Clear();
	m_pCity->Clear();
	m_pPhone->Clear();
	m_pDiagnosis->Clear();
	m_pNotes->Clear();
	m_pPatientList->Clear();
	m_pPatientNumber->Clear();
	m_DirtyFlag = false;
	setTreatment(-1);
	m_pMenuBar->Enable(m_menuNewTreatmentId, false);
	m_pDeletePatientButton->Disable();
	m_pSavepatientDataButton->Enable(false);
	m_pMenuBar->Enable(m_menuDeletePatientId, false);
	m_pMenuBar->Enable(m_menuSavePatientId, false);

	for (unsigned int i = 0; i < m_Patients.size(); i++) {
		Patient& pat = m_Patients[i];
		m_pPatientList->Append(pat.getFullName(), new PatientIndex(i));
	}
}

void MainFrame::setPatient(unsigned int index) {
	m_PatientIndex = index;
	Patient& pat = m_Patients[m_PatientIndex];
	m_pLastname->SetValue(pat.getLastname());
	m_pLastname->Enable(true);
	m_pFirstname->SetValue(pat.getFirstname());
	m_pFirstname->Enable(true);
	m_pBirthday->SetValue(pat.getBirthday());
	m_pBirthday->Enable(true);
	m_pStreet->SetValue(pat.getStreet());
	m_pStreet->Enable(true);
	m_pPostcode->SetValue(pat.getPostcode());
	m_pPostcode->Enable(true);
	m_pCity->SetValue(pat.getCity());
	m_pCity->Enable(true);
	m_pPhone->SetValue(pat.getPhone());
	m_pPhone->Enable(true);
	m_pDiagnosis->SetValue(pat.getDiagnosis());
	m_pDiagnosis->Enable(true);
	wxString label = pat.getFullName() + ", " + pat.getBirthday();
	m_pDiagnosisLabel->SetLabel("Diagnosis: " + label);
	m_pNotesLabel->SetLabel("Notes: " + label);
	m_pNotes->SetValue(pat.getNotes());
	m_pNotes->Enable(true);
	m_pDeletePatientButton->Enable();
	m_pSavepatientDataButton->Enable(false);
	m_pMenuBar->Enable(m_menuDeletePatientId, true);
	m_pMenuBar->Enable(m_menuSavePatientId, false);

	m_pPatientNumber->SetValue(wxNumberFormatter::ToString(pat.getPatientNumber(), 0, 0));
	m_pMenuBar->Enable(m_menuNewTreatmentId, true);
	if (pat.getTreatmentCount() > 0) {
		setTreatment(0);
	} else {
		setTreatment(-1);
	}
	m_DirtyFlag = false;
}

void MainFrame::OnSelectPatient(wxCommandEvent& event) {
	checkForDirtyData();
	m_PatientIndex = reinterpret_cast<PatientIndex*>(event.GetClientObject())->getId();
	setPatient(m_PatientIndex);
}

void MainFrame::setTreatment(int index) {
	m_TreatmentIndex = index;
	if (index == -1) {
		m_pPrevTreatmentButton->Enable(false);
		m_pNextTreatmentButton->Enable(false);
		m_pMenuBar->Enable(m_menuPrintId, false);
		m_pMenuBar->Enable(m_menuSavePdfId, false);
		m_pGraphics1->SetBitmap(m_EmptyImage);
		m_pCurrents->SetBitmap(m_EmptyImage);
//		m_pPhoto->SetBitmap(m_EmptyImage);
		Refresh();
		m_pTreatmentImgLabel->SetLabelText("");
	} else {
		const Treatment& tr = m_Patients[m_PatientIndex].getTreatment(m_TreatmentIndex);
		m_pGraphics1->SetBitmap(tr.getGraphic());
		m_pCurrents->SetBitmap(tr.getCurrents());
//		m_pPhoto->SetBitmap(tr.getPhoto());
		Refresh();
		if (index > 0)
			m_pPrevTreatmentButton->Enable(true);
		else
			m_pPrevTreatmentButton->Enable(false);
		if (m_Patients[m_PatientIndex].getTreatmentCount() > index + 1)
			m_pNextTreatmentButton->Enable(true);
		else
			m_pNextTreatmentButton->Enable(false);
		wxString label = wxString::Format(
				m_Patients[m_PatientIndex].getFullName() + ", " + tr.getDate() + ", " + " treatment %i ( %i )",
				m_TreatmentIndex + 1, m_Patients[m_PatientIndex].getTreatmentCount());
		m_pTreatmentImgLabel->SetLabelText(label);
		m_pMenuBar->Enable(m_menuPrintId, true);
		m_pMenuBar->Enable(m_menuSavePdfId, true);
	}

}

void MainFrame::OnPrevTreatment(wxCommandEvent& event) {
	setTreatment(m_TreatmentIndex - 1);
}

void MainFrame::OnNextTreatment(wxCommandEvent& event) {
	setTreatment(m_TreatmentIndex + 1);
}

void MainFrame::OnNewTreatment(wxCommandEvent& event) {
	try {
		checkForDirtyData();
		procedure_frame_ = new BetProcedureFrame(this, m_Patients[m_PatientIndex]);
		Hide();
		//to do cannot delete patient while in treatment
		procedure_frame_->Centre(wxBOTH | wxCENTER_ON_SCREEN);
		procedure_frame_->Show();
	} catch (const std::exception& error) {
		wxMessageBox(error.what(), "Cannot open COM port", wxOK | wxCENTRE, this);
	}
}

void MainFrame::OnProcedureFinished() {
	procedure_frame_->Hide();
	Show();
	if (wxMessageBox("Do you want to save the treatment", "Treatment", wxYES_NO) == wxYES) {
		int patid = m_Patients[m_PatientIndex].getPatientNumber();
		wxDateTime now;
		now.SetToCurrent();
		wxImage tr_img = procedure_frame_->getVoltageImage();
		wxImage cur_img = procedure_frame_->getCurrentsImage();
		wxString duration = wxString::Format("%d", int(procedure_frame_->getDuration() / 60 + 1));
		wxString q = wxString::Format("%d", int(procedure_frame_->getQ()));
		DB::getInst()->createTreatment(patid, now.FormatISODate(), duration, q, procedure_frame_->getVoltageImage(),
				procedure_frame_->getCurrentsImage());
	}
	reload();
}

void MainFrame::OnDeletePatient(wxCommandEvent& event) {
	if (wxMessageBox("Delete patient", "Patient", wxYES_NO, this) == wxYES) {
		DB::getInst()->deletePatient(m_Patients[m_PatientIndex].getPatientNumber());
		reload();
	}
}

bool MainFrame::checkForDirtyData() {
	if (m_DirtyFlag) {
		int answer = wxMessageBox("Save changes", "Patient", wxYES_NO, this);
		if (answer == wxNO) {
			return true;
		}
		DoSaveCurrentPatient();
	}
	return true;
}

void MainFrame::OnNewPatient(wxCommandEvent& event) {
	checkForDirtyData();
	int patId = DB::getInst()->createPatient("", "", "", "", "", "", "", "", "");
	reload();
	for (unsigned int i = 0; i < m_Patients.size(); i++) {
		if (m_Patients[i].getPatientNumber() == patId) {
			setPatient(i);
			return;
		}
	}
	assert(false);
}

void MainFrame::DoDeleteCurrentPatient() {
	DB::getInst()->deletePatient(m_Patients[m_PatientIndex].getPatientNumber());
}

void MainFrame::DoSaveCurrentPatient() {
	int old_pat = m_Patients[m_PatientIndex].getPatientNumber();
	DB::getInst()->updatePatient(m_Patients[m_PatientIndex].getPatientNumber(), m_pLastname->GetValue(),
			m_pFirstname->GetValue(), m_pBirthday->GetValue(), m_pStreet->GetValue(), m_pPostcode->GetValue(),
			m_pCity->GetValue(), m_pPhone->GetValue(), m_pDiagnosis->GetValue(), m_pNotes->GetValue());
	reload();
	for (unsigned int i = 0; i < m_Patients.size(); i++) {
		if (m_Patients[i].getPatientNumber() == old_pat) {
			setPatient(i);
			return;
		}
	}
	assert(false);
}

void MainFrame::OnSavePatient(wxCommandEvent& event) {
	DoSaveCurrentPatient();
}

void MainFrame::OnChangePatientData(wxCommandEvent& event) {
	m_pSavepatientDataButton->Enable(true);
	m_pMenuBar->Enable(m_menuSavePatientId, true);
	m_DirtyFlag = true;
}

void MainFrame::OnPdf(wxCommandEvent& event) {
	wxFileName fileName;
	fileName.SetPath(wxGetCwd());
	fileName.SetFullName(wxT("default.pdf"));
	wxPrintData printData;
	printData.SetOrientation(wxPORTRAIT);
	printData.SetPaperId(wxPAPER_A4);
	printData.SetFilename(fileName.GetFullPath());
	{
		wxPdfDC dc(printData);
		int w, h;
		dc.GetSize(&w, &h);

		float scaleX = float(w) / 730;
		float scaleY = float(h) / 730;
		float actualScale = wxMin(scaleX, scaleY);
		dc.SetUserScale(actualScale, actualScale);
		dc.SetDeviceOrigin(0, 0);

		// set wxPdfDC mapping mode style so
		// we can scale fonts and graphics
		// coords with a single setting
		dc.SetMapModeStyle(wxPDF_MAPMODESTYLE_PDF);
		dc.SetMapMode(wxMM_POINTS);
		bool ok = dc.StartDoc(_("Printing ..."));
		if (ok) {
			dc.StartPage();
			m_Patients[m_PatientIndex].getTreatment(m_TreatmentIndex).Print(m_Patients[m_PatientIndex],
					m_TreatmentIndex + 1, wxRect(10, 20, 710, 710), &dc);
			dc.EndPage();
			dc.EndDoc();
		}
	}

	wxFileType* fileType = wxTheMimeTypesManager->GetFileTypeFromExtension(wxT("pdf"));
	if (fileType != NULL) {
		wxString cmd = fileType->GetOpenCommand(fileName.GetFullPath());
		if (!cmd.IsEmpty()) {
			wxExecute(cmd);
		}
		delete fileType;
	}
}

void MainFrame::OnPrint(wxCommandEvent& event) {
	wxPrintPreview *preview = new wxPrintPreview(
			new TreatmentPrintout(m_Patients[m_PatientIndex], m_Patients[m_PatientIndex].getTreatment(m_TreatmentIndex),
					m_TreatmentIndex + 1),
			new TreatmentPrintout(m_Patients[m_PatientIndex], m_Patients[m_PatientIndex].getTreatment(m_TreatmentIndex),
					m_TreatmentIndex + 1));
	if (!preview->IsOk()) {
		delete preview;
		return;
	}

	wxPreviewFrame *frame = new wxPreviewFrame(preview, this, wxT("Print Preview"), wxPoint(100, 100),
			wxSize(600, 650));
	frame->Centre(wxBOTH);
	frame->InitializeWithModality(wxPreviewFrame_AppModal);
	frame->Show();
}
