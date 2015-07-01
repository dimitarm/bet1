/*
 * DB.h
 *
 *  Created on: Jun 15, 2014
 *      Author: dimitar
 */
#include <wx/string.h>
#include <wx/image.h>
#include <vector>
#include "Patient.h"
#include <sqlite3.h>

#ifndef DB_H_
#define DB_H_

class DB {
public:
	virtual ~DB();
	static DB* getInst();

	bool initDB();
	void closeDB();
	const std::vector<Patient> getPatients();
	const std::vector<Treatment> getTreatmentsForPatient(int patinetId);
	int createTreatment(int PatientNumber, const wxString& Date, const wxString& Duration, const wxString& Q, const wxImage& Graphic, const wxImage& Currents);

	int createPatient(const wxString& Lastname, const wxString& Firstname, const wxString& Birthday,const wxString& Street,const wxString& Postcode,const wxString& City,
			const wxString& Phone, const wxString& Diagnosis, const wxString& Notes);
	void updatePatient(int PatientNumber, const wxString& Lastname, const wxString& Firstname, const wxString& Birthday,const wxString& Street,const wxString& Postcode,
			const wxString& City,const wxString& Phone, const wxString& Diagnosis, const wxString& Notes);
	void deletePatient(int PatientNumber);

private:
	DB();

	std::vector<unsigned char> CompressImage(const wxImage& image);
	int UnCompressImage(const unsigned char* data, unsigned int size, unsigned int width, unsigned int height, wxImage& image);

	static DB* theInstance;

	sqlite3 *m_sqldb;
	static const char* insert_patient_stmt;
//	static const char* insert_treatment_stmt;
	static const char* insert_treatment_stmt2;
	static const char* update_patient_stmt;
	static const char* create_patients_stmt;
	static const char* create_treatments_stmt;
	static const char* get_treatments_stmt;
	static const char* get_patients_stmt;
	static const char* delete_patient_stmt;
	static const char* delete_treatment2pat_stmt;
};

#endif /* DB_H_ */
