/*
 * Treatment.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: dimitar
 */
#ifdef __WXMSW__
#include <winsock2.h>
#endif
#include "Bet1.h"

#include "Treatment.h"
#include "betconst.h"
#include "Patient.h"


Treatment::Treatment(int patientId,int treatmentId, const wxString& Date, const wxString& duration, const wxString& q, const wxString& Notes,	const wxString& Diagnose,	const wxImage& Graphic,const wxImage& Currents, const wxImage& Photo){
	this->patientId = patientId;
	this->treatmentId = treatmentId;
	this->Date = Date;
	this->Notes = Notes;
	this->Diagnose = Diagnose;
	this->Graphic = Graphic;
	this->Currents = Currents;
	this->Photo = Photo;
	this->Duration = duration;
	this->Q = q;
}

Treatment::~Treatment() {
}

bool operator==(const Treatment& l, const Treatment& r){
	return l.getTreatmentId() == r.getTreatmentId();
}

void Treatment::Print(const Patient& patient, int tr_num, wxRect pageRect, wxDC *dc) const {
	int curY = pageRect.y;
//calculate single line space
	dc->SetFont(wxGetApp().getNormFont());
	int space = dc->GetTextExtent("|").GetY();

//draw header
	dc->SetFont(wxGetApp().getTitleFont());
	wxString header = L"\u041C\u0435\u0434\u0438\u0446\u0438\u043D\u0441\u043A\u0438 \u0426\u0435\u043D\u0442\u044A\u0440 \u0418\u043D\u0442\u0435\u0433\u0440\u0430\u0442\u0438\u0432\u043D\u0430 \u041C\u0435\u0434\u0438\u0446\u0438\u043D\u0430";
	wxSize textExt = dc->GetTextExtent(header);
	dc->DrawText(header, pageRect.x + (pageRect.width - textExt.GetWidth())/2, curY);
	curY += textExt.GetHeight() + 1;
	dc->DrawLine(wxPoint(pageRect.x, curY), wxPoint(pageRect.x + pageRect.width - 1, curY));
//some space
	curY += 3*space;
//draw title
	dc->SetFont(wxGetApp().getTitleFont());
	wxString title = PRINTOUT_TITLE;
	textExt = dc->GetTextExtent(title);
	dc->DrawText(title, pageRect.x + (pageRect.width - textExt.GetWidth())/2, curY);
	curY += textExt.GetHeight() + space;
//draw infoline
	dc->SetFont(wxGetApp().getBoldFont());
	wxString infoline = wxString::Format(L"%s, %s      \u041F\u0440\u043E\u0446\u0435\u0434\u0443\u0440\u0430 %i, %s      (%s \u043C\u0438\u043D\u0443\u0442\u0438, %s C)", patient.getFullName(), patient.getBirthday(), tr_num, this->getDate(), this->getDuration(), this->getQ());
	textExt = dc->GetTextExtent(infoline);
	dc->DrawText(infoline, pageRect.x, curY);
	curY += textExt.GetHeight() + space;
//draw diagnose label
	dc->SetFont(wxGetApp().getBoldFont());
	wxString label = L"\u0414\u0438\u0430\u0433\u043D\u043E\u0437\u0430:";
	textExt = dc->GetTextExtent(label);
	dc->DrawText(label, pageRect.x, curY);
	curY += textExt.GetHeight();
//draw diagnose
	dc->SetFont(wxGetApp().getNormFont());
	textExt = dc->GetMultiLineTextExtent(patient.getDiagnosis());
	dc->DrawText(patient.getDiagnosis(), pageRect.x, curY);
	curY += textExt.GetHeight() + space;
//draw notes label
	dc->SetFont(wxGetApp().getBoldFont());
	label = L"\u0417\u0430\u0431\u0435\u043B\u0435\u0436\u043A\u0438:";
	textExt = dc->GetTextExtent(label);
	dc->DrawText(label, pageRect.x, curY);
	curY += textExt.GetHeight();
//draw notes
	dc->SetFont(wxGetApp().getNormFont());
	textExt = dc->GetMultiLineTextExtent(patient.getNotes());
	dc->DrawText(patient.getNotes(), pageRect.x, curY);
	curY += textExt.GetHeight() + space;
//draw currents
	dc->DrawBitmap(wxBitmap(this->getCurrents()), pageRect.x, curY);
	curY += this->getCurrents().GetHeight() + space;
//draw graphic
	dc->DrawBitmap(wxBitmap(this->getGraphic()), pageRect.x, curY);
	curY += this->getGraphic().GetHeight() + 2 * space;
//draw signature
	dc->SetFont(wxGetApp().getTitleFont());
	wxDateTime now; now.SetToCurrent();
	wxString signature = wxString::Format(L"\u0414\u0430\u0442\u0430: %s                                                        \u041B\u0435\u043A\u0443\u0432\u0430\u0449 \u043B\u0435\u043A\u0430\u0440:", now.FormatISODate());
	textExt = dc->GetTextExtent(signature);
	dc->DrawText(signature, pageRect.x, curY);
	curY += textExt.GetHeight() + 1;

}

