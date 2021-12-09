#ifndef IMAGE_PANEL
#define IMAGE_PANEL

#include <wx/wx.h>
#include "../utils/debug.hpp"

class ImagePanel : public wxPanel {
private:
	wxImage image;
	wxBitmap resized;
	uint16_t widht, height;
public:
	ImagePanel(wxFrame* parent);
	ImagePanel(wxFrame* parent, const wxString &file_name, wxBitmapType format);
	void sizeEvent(wxSizeEvent& event);
	void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);

	void changeImage(const wxImage &other);
	void changeImage(const wxString &file_path, wxBitmapType format = wxBITMAP_TYPE_JPEG);

	~ImagePanel();

	DECLARE_EVENT_TABLE()
};

#endif // IMAGE_PANEL
