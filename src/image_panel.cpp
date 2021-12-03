#include "image_panel.hpp"

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
EVT_PAINT(ImagePanel::paintEvent)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxFrame* parent, const wxString &file_name, wxBitmapType format) :
						wxPanel(parent) {

    image.LoadFile(file_name, format);
}

void ImagePanel::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this);
    render(dc);
}

void ImagePanel::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void ImagePanel::render(wxDC& dc) {
    dc.DrawBitmap(image, 0, 0);
}

void ImagePanel::changeImage(const wxBitmap &other) {
    image = other;
    paintNow();
    Refresh();
}

void ImagePanel::changeImage(const wxString &file_path, wxBitmapType format) {
    image.LoadFile(file_path, format);
    paintNow();
    Refresh();
}

ImagePanel::~ImagePanel() {
}