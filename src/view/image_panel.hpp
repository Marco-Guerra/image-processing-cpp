#ifndef IMAGE_PANEL
#define IMAGE_PANEL

#include <wx/wx.h>
#include "../utils/debug.hpp"

class ImagePanel : public wxPanel {
private:
	bool image_changed;
	wxImage image;
	wxBitmap resized;
	uint16_t widht, height;

	void sizeEvent(wxSizeEvent &event);
	void paintEvent(wxPaintEvent &event);

    void render(wxDC& dc);
public:
	ImagePanel(wxFrame* parent);
	ImagePanel(wxFrame* parent, const wxString &file_name, wxBitmapType format);

    void paintNow();
	void changeImage(const wxImage &other);
	void changeImage(const wxString &file_path, wxBitmapType format = wxBITMAP_TYPE_JPEG);
	bool saveFile(const wxString &full_path);

	~ImagePanel();

	wxDECLARE_EVENT_TABLE();
};

#endif // IMAGE_PANEL
