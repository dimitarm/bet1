/*
 * DB.cpp
 *
 *  Created on: Jun 15, 2014
 *      Author: dimitar
 */
#include <sqlite3.h>
#include "DB.h"
#include <stdio.h>
#include "betconst.h"
#include <cstring>
#include <bzlib.h>
#include "Treatment.h"

DB* DB::theInstance = NULL;

DB* DB::getInst() {
	if (DB::theInstance == NULL) {
		DB::theInstance = new DB();
	}
	return DB::theInstance;
}

DB::DB() :
		m_sqldb(NULL) {
	// TODO Auto-generated constructor stub

}

DB::~DB() {
	// TODO Auto-generated destructor stub
}
//init statements
const char* DB::create_patients_stmt =
		"CREATE TABLE IF NOT EXISTS patients (id INTEGER PRIMARY KEY AUTOINCREMENT, lastname TEXT, firstname TEXT, birthday TEXT, street TEXT, postcode TEXT, city TEXT, "
				"phone TEXT, diagnosis TEXT, notes TEXT)";
const char* DB::create_treatments_stmt =
		"CREATE TABLE IF NOT EXISTS treatments (id INTEGER PRIMARY KEY AUTOINCREMENT, patientid INTEGER, date TEXT, diagnose TEXT, notes TEXT,"
				" graphic BLOB, currents BLOB, photo BLOB, photo_width INTEGER, photo_height INTEGER,"
				"duration TEXT, q TEXT, graphic_width INTEGER, graphic_height INTEGER, currents_width INTEGER, currents_height INTEGER)";
//patients
const char* DB::update_patient_stmt =
		"UPDATE patients SET lastname = \"%.50s\", firstname = \"%.50s\", birthday = \"%.50s\", street = \"%.50s\", postcode = \"%.50s\", city = \"%.50s\", "
				"phone = \"%.50s\", diagnosis = \"%.50s\", notes = \"%.50s\" WHERE id = %i";
const char* DB::delete_patient_stmt = "DELETE FROM patients WHERE id = %i";
const char* DB::delete_treatment2pat_stmt = "DELETE FROM treatments WHERE patientid = %i";

const char* DB::get_patients_stmt = "SELECT * FROM patients";
const char* DB::insert_patient_stmt =
		"INSERT INTO patients (lastname, firstname, birthday, street, postcode, city, phone, diagnosis, notes) "
				"VALUES (\"%.50s\", \"%.50s\", \"%.50s\", \"%.50s\", \"%.50s\", \"%.50s\", \"%.50s\", \"%.50s\", \"%.50s\")";
//treatments
const char* DB::get_treatments_stmt = "SELECT * FROM treatments WHERE patientid = %d";
//const char* DB::insert_treatment_stmt =
//		"INSERT INTO treatments (patientid, date, graphic, currents, photo) VALUES (?, ?, ?, ?, ?)";
const char* DB::insert_treatment_stmt2 =
		"INSERT INTO treatments (patientid, date, duration, q, graphic, currents, graphic_width, graphic_height, currents_width, currents_height) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

bool DB::initDB() {

	char* err_msg;

	if (sqlite3_open(DB_FILE, &m_sqldb) != SQLITE_OK) {
		fprintf(stdout, "Can't open database: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_close(m_sqldb);
		return false;
	}
	if (sqlite3_exec(m_sqldb, create_patients_stmt, NULL, NULL, &err_msg) != SQLITE_OK) {
		fprintf(stdout, "Can't initialize database: %s\n", err_msg);
		sqlite3_close(m_sqldb);
		return false;
	}
	if (sqlite3_exec(m_sqldb, create_treatments_stmt, NULL, NULL, &err_msg) != SQLITE_OK) {
		fprintf(stdout, "Can't initialize database: %s\n", err_msg);
		sqlite3_close(m_sqldb);
		return false;
	}
	return true;
}

void DB::closeDB() {
	sqlite3_close(m_sqldb);
}

const std::vector<Patient> DB::getPatients() {
	sqlite3_stmt* stmt;
	std::vector<Patient> patients;

	if (sqlite3_prepare_v2(m_sqldb, get_patients_stmt, -1, &stmt,
	NULL) != SQLITE_OK) {
		fprintf(stdout, "Can't read patients: %s\n", sqlite3_errmsg(m_sqldb));
		return patients;
	};
	for (; sqlite3_step(stmt) == SQLITE_ROW;) {
		//read patient
		//id INTEGER PRIMARY KEY AUTOINCREMENT, lastname TEXT, firstname TEXT, birthday TEXT, street TEXT, postcode TEXT, city TEXT, phone TEXT

		int id = sqlite3_column_int(stmt, 0);
		wxString lastname = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 1))));
		wxString firstname = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 2))));
		wxString birthday = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 3))));
		wxString street = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 4))));
		wxString postcode = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 5))));
		wxString city = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 6))));
		wxString phone = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 7))));
		wxString diagnosis = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 8))));
		wxString notes = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 9))));
		Patient patient(id, lastname, firstname, birthday, street, postcode, city, phone, diagnosis, notes);
		patients.insert(patients.end(), patient);
	}

	sqlite3_finalize(stmt);
	return patients;
}
//(id INTEGER PRIMARY KEY AUTOINCREMENT, patientid INTEGER, date TEXT, diagnose TEXT, notes TEXT,"
//" graphic BLOB, currents BLOB, photo BLOB, photo_width INTEGER, photo_height INTEGER,"
//"duration TEXT, q TEXT, graphic_width INTEGER, graphic_height INTEGER, currents_width INTEGER, currents_width INTEGER)";
const std::vector<Treatment> DB::getTreatmentsForPatient(int patientId) {
	sqlite3_stmt* stmt;
	std::vector<Treatment> treatments;
	char stmt_text[sizeof(get_treatments_stmt) + 50];

	sprintf(stmt_text, get_treatments_stmt, patientId);

	if (sqlite3_prepare_v2(m_sqldb, stmt_text, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stdout, "Can't read treatments: %s\n", sqlite3_errmsg(m_sqldb));
		return treatments;
	};
	for (; sqlite3_step(stmt) == SQLITE_ROW;) {
		//read treatment
		//id INTEGER PRIMARY KEY AUTOINCREMENT, patientid INTEGER, date TEXT, diagnose TEXT, notes TEXT, graphic BLOB, currents BLOB, photo BLOB

		int id = sqlite3_column_int(stmt, 0);
		int patientid = sqlite3_column_int(stmt, 1);
		wxString date = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 2))));
		wxString diagnose = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 3))));
		wxString notes = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 4))));

		wxString duration = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 10))));
		wxString q = wxString::FromUTF8(
				reinterpret_cast<char*>(const_cast<unsigned char *>(sqlite3_column_text(stmt, 11))));


		int graphic_width = sqlite3_column_int(stmt, 12);
		int graphic_height = sqlite3_column_int(stmt, 13);
		int currents_width = sqlite3_column_int(stmt, 14);
		int currents_height = sqlite3_column_int(stmt, 15);
		wxImage graphic;
		int res = UnCompressImage(reinterpret_cast<const unsigned char*>(sqlite3_column_blob(stmt, 5)),
				sqlite3_column_bytes(stmt, 5), graphic_width, graphic_height, graphic);
		if (res != 0)
			fprintf(stdout, "Can't read all treatments: decompression error %d\n", res);

		wxImage currents;
		res = UnCompressImage(reinterpret_cast<const unsigned char*>(sqlite3_column_blob(stmt, 6)),
				sqlite3_column_bytes(stmt, 6), currents_width, currents_height, currents);
		if (res != 0)
			fprintf(stdout, "Can't read all treatments: decompression error %d\n", res);

		int photo_bytes = sqlite3_column_bytes(stmt, 7);
		wxImage photo;
		if (photo_bytes != 0) {
			int photo_width = sqlite3_column_int(stmt, 8);
			int photo_height = sqlite3_column_int(stmt, 9);

			res = UnCompressImage(reinterpret_cast<const unsigned char*>(sqlite3_column_blob(stmt, 7)),
					sqlite3_column_bytes(stmt, 7), photo_width, photo_height, photo);
			if (res != 0)
				fprintf(stdout, "Can't read all treatments: decompression error %d\n", res);
		}

		Treatment treatment(patientid, id, date, duration, q, notes, diagnose, graphic, currents, photo);
		treatments.insert(treatments.end(), treatment);
	}

	sqlite3_finalize(stmt);
	return treatments;
}

int DB::createTreatment(int PatientNumber, const wxString& Date, const wxString& Duration, const wxString& Q, const wxImage& Graphic, const wxImage& Currents) {
	sqlite3_stmt* stmt;
//			"INSERT INTO treatments (patientid, date, duration, q, graphic, currents, graphic_width, graphic_height, currents_width, currents_height) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
	if (sqlite3_prepare_v2(m_sqldb, insert_treatment_stmt2, -1, &stmt, NULL) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		return -1;
	}
	if (sqlite3_bind_int(stmt, 1, PatientNumber) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	const char* date = Date.To8BitData().data();
	if (sqlite3_bind_text(stmt, 2, date, -1, SQLITE_STATIC) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	const char* dur = Duration.data();
	if (sqlite3_bind_text(stmt, 3, dur, -1, SQLITE_STATIC) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	const char* q = Q.data();
	if (sqlite3_bind_text(stmt, 4, q, -1, SQLITE_STATIC) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}

	std::vector<unsigned char> arc = CompressImage(Graphic);
	if (arc.size() == 0|| sqlite3_bind_blob(stmt, 5, reinterpret_cast<const void*>(&arc.front()),
			arc.size(), SQLITE_STATIC) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	std::vector<unsigned char> arc1 = CompressImage(Currents);
	if (arc1.size() == 0 || sqlite3_bind_blob(stmt, 6, reinterpret_cast<const void*>(&arc1.front()), arc1.size(),
	SQLITE_STATIC) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	if (sqlite3_bind_int(stmt, 7, Graphic.GetWidth()) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	if (sqlite3_bind_int(stmt, 8, Graphic.GetHeight()) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	if (sqlite3_bind_int(stmt, 9, Currents.GetWidth()) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	if (sqlite3_bind_int(stmt, 10, Currents.GetHeight()) != SQLITE_OK) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	if (sqlite3_step(stmt) != SQLITE_DONE) {
		fprintf(stderr, "Can't insert treatment: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_finalize(stmt);
		return -1;
	}
	sqlite3_finalize(stmt);
	return sqlite3_last_insert_rowid(m_sqldb);
}

void DB::updatePatient(int PatientNumber, const wxString& Lastname, const wxString& Firstname, const wxString& Birthday,
		const wxString& Street, const wxString& Postcode, const wxString& City, const wxString& Phone,
		const wxString& Diagnosis, const wxString& Notes) {
	char stmt_text[sizeof(update_patient_stmt) + 1000];
//	"UPDATE patients SET lastname = \"%.50s\", firstname = \"%.50s\", birthday = \"%.50s\", street \"%.50s\", postcode = \"%.50s\", city = \"%.50s\", phone = \"%.50s\" WHERE id = \"%i\")";
	char* err_msg;

	sprintf(stmt_text, update_patient_stmt, Lastname.utf8_str().data(), Firstname.utf8_str().data(),
			Birthday.utf8_str().data(), Street.utf8_str().data(), Postcode.utf8_str().data(), City.utf8_str().data(),
			Phone.utf8_str().data(), Diagnosis.utf8_str().data(), Notes.utf8_str().data(), PatientNumber);

	int err = sqlite3_exec(m_sqldb, stmt_text, NULL, NULL, &err_msg);
	if (err != SQLITE_OK) {
		fprintf(stderr, "Can't update patient: %s\n", sqlite3_errmsg(m_sqldb));
		sqlite3_free(err_msg);
	};
}

int DB::createPatient(const wxString& Lastname, const wxString& Firstname, const wxString& Birthday,
		const wxString& Street, const wxString& Postcode, const wxString& City, const wxString& Phone,
		const wxString& Diagnosis, const wxString& Notes) {
	char stmt_text[sizeof(insert_patient_stmt) + 1000];

	sprintf(stmt_text, insert_patient_stmt, Lastname.utf8_str().data(), Firstname.utf8_str().data(),
			Birthday.utf8_str().data(), Street.utf8_str().data(), Postcode.utf8_str().data(), City.utf8_str().data(),
			Phone.utf8_str().data(), Diagnosis.utf8_str().data(), Notes.utf8_str().data());
	if (sqlite3_exec(m_sqldb, stmt_text, NULL, NULL, NULL) != SQLITE_OK) {

		fprintf(stderr, "Can't insert patient: %s\n", sqlite3_errmsg(m_sqldb));
		return -1;
	};
	return sqlite3_last_insert_rowid(m_sqldb);
}

void DB::deletePatient(int PatientNumber) {
	char stmt_text[sizeof(delete_treatment2pat_stmt) + 1000];
	//delete all treatments for patient
	sprintf(stmt_text, delete_treatment2pat_stmt, PatientNumber);
	if (sqlite3_exec(m_sqldb, stmt_text, NULL, NULL, NULL) != SQLITE_OK) {

		fprintf(stderr, "Can't delete treatments: %s\n", sqlite3_errmsg(m_sqldb));
		return;
	};
	//delete patient
	sprintf(stmt_text, delete_patient_stmt, PatientNumber);
	if (sqlite3_exec(m_sqldb, stmt_text, NULL, NULL, NULL) != SQLITE_OK) {
		fprintf(stderr, "Can't delete patient: %s\n", sqlite3_errmsg(m_sqldb));
		return;
	};
}

int DB::UnCompressImage(const unsigned char* data, unsigned int size, unsigned int width, unsigned int height, wxImage& image) {
	std::vector<unsigned char> arc(width * height * 3 * 1.2 + 1024);

	unsigned int len = arc.size();
	int result = BZ2_bzBuffToBuffDecompress(reinterpret_cast<char*>(&arc.front()), &len,
			reinterpret_cast<char*>(const_cast<unsigned char*>(data)), size, 1, //small
			0);  //verbosity
	if (result != BZ_OK)
		return result;
	assert(len == width * height * 3);
	arc.resize(len);
	void* img_data = malloc(len);
	memcpy(img_data, &arc.front(), len);
	image.Create(width, height, reinterpret_cast<unsigned char*>(img_data), false);
	return 0;
}

std::vector<unsigned char> DB::CompressImage(const wxImage& image) {
	std::vector<unsigned char> arc(image.GetWidth() * image.GetHeight() * 3 * 1.2 + 1024);

	unsigned int len = arc.size();
	if (BZ2_bzBuffToBuffCompress(reinterpret_cast<char*>(&arc.front()), &len, reinterpret_cast<char*>(image.GetData()),
			image.GetWidth() * image.GetHeight() * 3, 5, 0, 30) != BZ_OK) {
		std::vector<unsigned char> empty(0);
		return empty;
	}
	arc.resize(len);
#ifdef __WXDEBUG__
	std::vector<unsigned char> data(image.GetWidth() * image.GetHeight() * 3 * 1.2 + 1024);
	len = data.size();
	BZ2_bzBuffToBuffDecompress(reinterpret_cast<char*>(data.data()), &len, reinterpret_cast<char*>(&arc.front()),
			arc.size(), 1, 0);
	data.resize(len);
	assert(data.size() == image.GetWidth() * image.GetHeight() * 3);
	assert(std::memcmp(image.GetData(), &data.front(), data.size()) == 0);
#endif

	return arc;
}
