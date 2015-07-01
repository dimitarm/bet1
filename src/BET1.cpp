// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#ifdef __WXMSW__
#include <winsock2.h>
#endif
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/pdfdc.h>
#include <wx/pdffontmanager.h>
#include <wx/pdfprint.h>
#include <wx/filename.h>
#include <wx/mimetype.h>

#include "betconst.h"
#include "DB.h"
#include "MainFrame.h"
#include "Graphic.h"

#include "BET1.h"
#include "Treatment.h"

wxIMPLEMENT_APP(MainApp);

bool MainApp::OnInit() {
//	std::vector<unsigned char> buffer;
//	for (int i = 0; i < 1000; i++){
//		buffer.insert(buffer.end(), 0x55);
//	}
//	std::vector<unsigned char> archive;
//	Compressor::Compress(&buffer.front(), buffer.size(), archive);
//	std::vector<unsigned char> data;
//	Compressor::Uncompress(&archive.front(), archive.size(), data);
//
//	std::cout << data.size() <<std::endl;
//	return false;

	proc_frame_ = nullptr;
	if (!DB::getInst()->initDB()){
		return false;
	}
	if(!registerFonts())
		return false;
	wxImage::AddHandler(new wxPNGHandler);
	main_frame_ = new MainFrame(LOGO, wxDefaultPosition, wxSize(780, 700));
	main_frame_->SetSize(wxSize(780, 700));
	main_frame_->Centre(wxBOTH|wxCENTER_ON_SCREEN);
	main_frame_->Show(true);

	return true;
}

bool MainApp::registerFonts(){
	if (!title_font_.Create(14, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, FONT_NAME))
		return false;
	if (!norm_font_.Create(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, FONT_NAME))
		return false;
	if (!bold_font_.Create(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, FONT_NAME))
		return false;
	wxPdfFontManager::GetFontManager()->RegisterFont(title_font_, "title");
	wxPdfFontManager::GetFontManager()->RegisterFont(norm_font_, "norm");
	//wxPdfFontManager::GetFontManager()->RegisterFont(bold_font_, "bold");
	return true;
}

const wxFont& MainApp::getTitleFont(){
	return title_font_;
}

const wxFont& MainApp::getNormFont(){
	return norm_font_;
}

const wxFont& MainApp::getBoldFont(){
	return bold_font_;
}

int MainApp::OnExit(){
	DB::getInst()->closeDB();
	return 0;
}

void MainApp::setProcedureFrame(BetProcedureFrame* frame){
	proc_frame_ = frame;
}

int MainApp::FilterEvent 	( 	wxEvent &  	event	){
	if (event.GetEventType() == wxEVT_KEY_DOWN){
		wxKeyEvent* keyEvent = static_cast<wxKeyEvent*>(&event);
//		char buffer[20];
//		int code = keyEvent->GetKeyCode();
//		sprintf(buffer,"0x%x",code);
//		std::cout << buffer << " ";
//		sprintf(buffer,"0x%x",keyEvent->GetUnicodeKey());
//		std::cout << buffer << std::endl;
		if (proc_frame_ != nullptr && !proc_frame_->ProcessWindowEvent(event)){
			return 1;
		}
	}
	return wxApp::FilterEvent(event);
}
