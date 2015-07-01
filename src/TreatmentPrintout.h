/*
 * TreatmentPrintout.h
 *
 *  Created on: Aug 16, 2014
 *      Author: I028663
 */
#include "wx/print.h"
#include "wx/printdlg.h"

#include "Patient.h"

#ifndef TREATMENTPRINTOUT_H_
#define TREATMENTPRINTOUT_H_

class Treatment;
class Patient;
class TreatmentPrintout : public wxPrintout{
	const Patient& patient_;
	const Treatment& treatment_;
	const int tr_num_;
public:
	TreatmentPrintout(const Patient& patient, const Treatment& treatment, int tr_num):patient_(patient), treatment_(treatment), tr_num_(tr_num) { };

    virtual bool OnPrintPage(int page);
    virtual bool HasPage(int page);
    virtual bool OnBeginDocument(int startPage, int endPage);
    virtual void GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo);

	virtual ~TreatmentPrintout() {};
};

#endif /* TREATMENTPRINTOUT_H_ */
