#ifndef MAIN_FRAME
#define MAIN_FRAME

#include <functional>
#include <wx/wx.h>

#include "image_panel.hpp"
#include "../image-processing/image.hpp"

class MainFrame : public wxFrame {
friend class MainFrameController;
private:
	Image img;
	wxBoxSizer *sizer;
    ImagePanel *drawPane;


// metodos que serao ligados a eventos
	// file
	void onOpen(wxCommandEvent& event);
	void onSave(wxCommandEvent& event);

	//metods
	void onMedianBlur(wxCommandEvent& event);

	// metodos auxiliares
	bool openImage();
	void showError(const wxString &message);

public:
	MainFrame();
	~MainFrame();
};

enum Identifiers {
	ID_OPEN,
	ID_REFRESH,
	ID_SAVE_FILE,
	ID_MEDIAN_BLUR
};

#endif // MAIN_FRAME
