#ifndef DIALOG
#define DIALOG

#include "../include/wx.hpp"

enum DialogType {
	DIALOG_ERROR,
	DIALOG_INFO,
	DIALOG_QUESTION,
};

class Dialog : public wxMessageDialog {
private:
	DialogType type;

	static wxString getCaption(DialogType type);
	static long getStyle(DialogType type);
public:
	Dialog(wxFrame* parent, const wxString &message, DialogType type);
	bool getUserInput();
	~Dialog();
};

#endif // DIALOG
