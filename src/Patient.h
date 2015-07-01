/*
 * Patient.h
 *
 *  Created on: Jun 15, 2014
 *      Author: dimitar
 */
#include <wx/string.h>

#include <vector>
#include <map>

#ifndef PATIENT_H_
#define PATIENT_H_

class Treatment;
class Patient {
public:
	Patient(int patientnumber, const wxString& Lastname, const wxString& Firstname, const wxString& Birthday,const wxString& Street,const wxString& Postcode,
			const wxString& City,const wxString& Phone, const wxString& Diagnosis, const wxString& Notes);
	virtual ~Patient();

	enum PROPERTIES{PLastname, PFirstname, PBirthday, PStreet,	PPostcode, PCity, PPhone, PDiagnosis, PNotes, PFullName};

	const wxString& getFullName() const {
		return properties[PFullName];
	}

	const wxString& getBirthday() const {
		return properties[PBirthday];
	}

	const wxString& getCity() const {
		return properties[PCity];
	}

	const wxString& getFirstname() const {
		return properties[PFirstname];
	}

	const wxString& getLastname() const {
		return properties[PLastname];
	}

	int getPatientNumber() const {
		return PatientNumber;
	}

	const wxString& getPhone() const {
		return properties[PPhone];
	}

	const wxString& getPostcode() const {
		return properties[PPostcode];
	}

	const wxString& getStreet() const {
		return properties[PStreet];
	}

	const wxString& getDiagnosis() const {
		return properties[PDiagnosis];
	}

	const wxString& getNotes() const {
		return properties[PNotes];
	}

	const Treatment& getTreatment(int num) const {
		loadTreatments();
		return treatments[num];
	}

	int getTreatmentCount() const{
		loadTreatments();
		return treatments.size();
	}

	void loadTreatments() const;

private:

	int PatientNumber;
	mutable bool bTreatmentsLoaded;

	mutable std::map<PROPERTIES, wxString> properties;
	mutable std::vector<Treatment> treatments;
};

bool operator==(const Patient& patientl, const Patient& patientr);

#endif /* PATIENT_H_ */
