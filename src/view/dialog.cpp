#include "dialog.hpp"

wxString Dialog::getCaption(DialogType type) {
	if (type == DIALOG_ERROR) {
		return "Erro";
	}else if (type == DIALOG_INFO) {
		return wxT("Informação");
	}
	return wxT("Confirmação");
}

long Dialog::getStyle(DialogType type) {
	if (type == DIALOG_ERROR) {
		return wxOK | wxICON_ERROR;
	}else if (type == DIALOG_INFO) {
		return wxOK;
	}
	return wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION;
}

Dialog::Dialog(wxFrame* parent, const wxString &message, DialogType type) :
	type(type),
	wxMessageDialog(parent, message, getCaption(type), getStyle(type)) {
	
	if (type != DIALOG_QUESTION) {
		ShowModal();
	}
}


bool Dialog::getUserInput() {
	return ShowModal() == wxID_YES;
}

Dialog::~Dialog() {
}
