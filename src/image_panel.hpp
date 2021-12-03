#ifndef IMAGE_PANEL
#define IMAGE_PANEL

#include <wx/wx.h>

class ImagePanel : public wxPanel {
private:
	wxBitmap image;
public:
	ImagePanel(wxFrame* parent, const wxString &file_name, wxBitmapType format);
	void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);

	void changeImage(const wxBitmap &other);
	void changeImage(const wxString &file_path, wxBitmapType format = wxBITMAP_TYPE_JPEG);

	~ImagePanel();

	DECLARE_EVENT_TABLE()
};

#endif // IMAGE_PANEL
