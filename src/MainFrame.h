/*
 * MainFrame.h
 *
 *  Created on: Jun 16, 2014
 *      Author: dimitar
 */

#include <wx/wx.h>
#include <wx/generic/statbmpg.h>
#include <wx/notebook.h>
#include "Patient.h"
#include "BetProcedureFrame.h"
#include "ImagePanel.h"

#ifndef MAINFRAME_H_
#define MAINFRAME_H_

class MainFrame: public wxFrame {
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	void reload();

	enum Mode {
		mode_normal = 0, mode_newpatient = 1, mode_editpatient = 2, mode_newtreatment = 3
	};

	void OnProcedureFinished();

private:
wxDECLARE_EVENT_TABLE();
	void OnExit(wxCommandEvent& event);
	void OnClose( wxCloseEvent& event );
	void OnAbout(wxCommandEvent& event);
	void OnSelectPatient(wxCommandEvent& event);
	void OnPrevTreatment(wxCommandEvent& event);
	void OnNextTreatment(wxCommandEvent& event);
	void OnNewTreatment(wxCommandEvent& event);
	void OnNewPatient(wxCommandEvent& event);
	void OnDeletePatient(wxCommandEvent& event);
	void OnSavePatient(wxCommandEvent& event);
	void OnPrint(wxCommandEvent& event);
	void OnPdf(wxCommandEvent& event);
	void OnChangePatientData(wxCommandEvent& event);
	void AddControls();
	void AddPersonDetail(wxSizer* mainSizer, wxWindow* control, const wxString& label);
	void setTreatment(int index);
	void setPatient(unsigned int index);
	void DoSaveCurrentPatient();
	void DoDeleteCurrentPatient();
	bool checkForDirtyData();

	Mode mode;
	wxListBox* m_pPatientList;
	wxButton* m_pNewPatientButton;
	wxButton* m_pDeletePatientButton;
	wxButton* m_pSavepatientDataButton;
	wxButton* m_pPrevTreatmentButton;
	wxButton* m_pNextTreatmentButton;

	wxTextCtrl* m_pLastname;
	wxTextCtrl* m_pFirstname;
	wxTextCtrl* m_pBirthday;
	wxTextCtrl* m_pStreet;
	wxTextCtrl* m_pPostcode;
	wxTextCtrl* m_pCity;
	wxTextCtrl* m_pPhone;
	wxTextCtrl* m_pPatientNumber;

	wxStaticText* m_pDiagnosisLabel;
	wxTextCtrl* m_pDiagnosis;
	wxStaticText* m_pNotesLabel;
	wxTextCtrl* m_pNotes;
	wxGenericStaticBitmap* m_pGraphics1;
	wxGenericStaticBitmap* m_pCurrents;
//	wxGenericStaticBitmap* m_pPhoto;
	wxNotebook* m_pPicture;
	wxImage m_EmptyImage;

	wxStaticText* m_pTreatmentImgLabel;
	wxMenuBar *m_pMenuBar;
	int m_menuNewTreatmentId;
	int m_menuNewPatientId;
	int m_menuDeletePatientId;
	int m_menuSavePatientId;
	int m_menuPrintPreviewId;
	int m_menuSavePdfId;
	int m_menuPrintId;

	unsigned int m_PatientIndex;
	int m_TreatmentIndex;
	std::vector<Patient> m_Patients;
	bool m_DirtyFlag;

	BetProcedureFrame * procedure_frame_;
};

class PatientIndex: public wxClientData {
	int m_id;

public:
	PatientIndex(int id) {
		m_id = id;
	}
	~PatientIndex() {
		m_id--;
	}

	int getId() const {
		return m_id;
	}
};

#endif /* MAINFRAME_H_ */
