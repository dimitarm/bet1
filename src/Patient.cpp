/*
 * Patient.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: dimitar
 */

#include "Patient.h"
#include "Treatment.h"
#include "DB.h"

Patient::Patient(int patientnumber, const wxString& Lastname, const wxString& Firstname, const wxString& Birthday,const wxString& Street,const wxString& Postcode,
		const wxString& City,const wxString& Phone, const wxString& Diagnosis, const wxString& Notes){

	properties[PLastname] = Lastname;
	properties[PFirstname] = Firstname;
	properties[PBirthday] = Birthday;
	properties[PStreet] = Street;
	properties[PPostcode] = Postcode;
	properties[PCity] = City;
	properties[PPhone] = Phone;
	properties[PDiagnosis] = Diagnosis;
	properties[PNotes] = Notes;
	properties[PFullName] = Firstname + " " + Lastname;

	this->PatientNumber = patientnumber;
	bTreatmentsLoaded = false;
}

Patient::~Patient() {
}

void Patient::loadTreatments()const{
	if (bTreatmentsLoaded){
		return;
	}
	treatments = DB::getInst()->getTreatmentsForPatient(PatientNumber);
	bTreatmentsLoaded = true;
}


bool operator==(const Patient& patientl, const Patient& patientr){
	return patientl.getPatientNumber() == patientr.getPatientNumber();
}
