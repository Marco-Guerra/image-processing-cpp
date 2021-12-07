#include "image_panel.hpp"

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
EVT_PAINT(ImagePanel::paintEvent)
EVT_SIZE(ImagePanel::sizeEvent)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxFrame* parent) : wxPanel(parent), image() {
}

ImagePanel::ImagePanel(wxFrame* parent, const wxString &file_name, wxBitmapType format) :
						wxPanel(parent) {

    image.LoadFile(file_name, format);
}

void ImagePanel::sizeEvent(wxSizeEvent& event) {
    Refresh();
    //skip the event.
    event.Skip();
}

void ImagePanel::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this);
    render(dc);
    //Refresh();
    //evt.Skip();
}

void ImagePanel::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void ImagePanel::render(wxDC& dc) {
    int new_width, new_height;
    dc.GetSize(&new_width, &new_height);
    if (new_width != widht || new_height != height) {
        resized = wxBitmap(image.Scale(new_width, new_height, wxIMAGE_QUALITY_HIGH));
        widht = new_width;
        height = new_height;
        dc.DrawBitmap(resized, 0, 0, false);
    }else {
        dc.DrawBitmap(resized, 0, 0, false);
    }
}

void ImagePanel::changeImage(const wxImage &other) {
    image = other;
}

void ImagePanel::changeImage(const wxString &file_path, wxBitmapType format) {
    image.LoadFile(file_path, format);
}

ImagePanel::~ImagePanel() {
}