/*
 * Treatment.h
 *
 *  Created on: Jun 15, 2014
 *      Author: dimitar
 */
#include <wx/image.h>
#include <wx/string.h>
#include <wx/dc.h>

#ifndef TREATMENT_H_
#define TREATMENT_H_

class Patient;
class Treatment {
public:
	Treatment(int patientId,int treatmentId, const wxString& Date, const wxString& duration, const wxString& q, const wxString& Notes, const wxString& Diagnose,const wxImage& Graphic,const wxImage& Currents, const wxImage& Photo);
	virtual ~Treatment();

	const wxImage& getCurrents() const {
		return Currents;
	}

	const wxString& getDiagnose() const {
		return Diagnose;
	}

	const wxImage& getGraphic() const {
		return Graphic;
	}

	const wxString& getNotes() const {
		return Notes;
	}

	int getPatientId() const {
		return patientId;
	}

	const wxImage& getPhoto() const {
		return Photo;
	}

	int getTreatmentId() const {
		return treatmentId;
	}

	const wxString& getDate() const {
		return Date;
	}

	const wxString& getDuration() const {
		return Duration;
	}

	const wxString& getQ() const {
		return Q;
	}

	void Print(const Patient& patient, int tr_num, wxRect pageRect, wxDC *dc) const;

private:
	int patientId;
	int treatmentId;
	wxString Date;
	wxString Notes;
	wxString Duration;
	wxString Q;
	wxString Diagnose;
	wxImage Graphic;
	wxImage Currents;
	wxImage Photo;

};

bool operator==(const Treatment& l, const Treatment& r);

#endif /* TREATMENT_H_ */
