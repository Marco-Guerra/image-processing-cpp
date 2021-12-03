#ifndef MAIN_FRAME
#define MAIN_FRAME

#include <wx/wx.h>
#include "image_panel.hpp"

class MainFrame : public wxFrame {
private:
	wxBoxSizer *sizer;
	wxFrame *frame;
    ImagePanel *drawPane;
public:
	MainFrame();

	void onOpen(wxCommandEvent& event);

	~MainFrame();
};

enum Identifiers {
	ID_OPEN
};

#endif // MAIN_FRAME
