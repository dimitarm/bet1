/*
 * TreatmentPrintout.cpp
 *
 *  Created on: Aug 16, 2014
 *      Author: I028663
 */

#include "Treatment.h"
#include "Patient.h"
#include "TreatmentPrintout.h"
#include "betconst.h"

bool TreatmentPrintout::HasPage(int page){
	return (page == 1 ? true : false);
}

bool TreatmentPrintout::OnBeginDocument(int startPage, int endPage){
    if (!wxPrintout::OnBeginDocument(startPage, endPage))
        return false;
    return true;
}

void TreatmentPrintout::GetPageInfo(int *minPage, int *maxPage, int *selPageFrom, int *selPageTo){
    *minPage = 1;
    *maxPage = 1;
    *selPageFrom = 1;
    *selPageTo = 1;
}


bool TreatmentPrintout::OnPrintPage(int page){
    wxDC *dc = GetDC();
    if (!dc)
    	return false;

	// Draw page numbers at top left corner of printable area, sized so that
	// screen size of text matches paper size.
	MapScreenSizeToPage();
	treatment_.Print(patient_, tr_num_, GetLogicalPageRect(), dc);
	return true;
}


