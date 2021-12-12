#include "image_panel.hpp"

BEGIN_EVENT_TABLE(ImagePanel, wxPanel)
EVT_PAINT(ImagePanel::paintEvent)
EVT_SIZE(ImagePanel::sizeEvent)
END_EVENT_TABLE()

ImagePanel::ImagePanel(wxFrame* parent) : wxPanel(parent),
                    image_changed(false), image(), resized() {
    debug ("Construindo o ImagePanel\n");
}

ImagePanel::ImagePanel(wxFrame* parent, const wxString &file_name, wxBitmapType format) :
						wxPanel(parent) {

    image.LoadFile(file_name, format);
}

void ImagePanel::sizeEvent(wxSizeEvent& event) {
    debug ("Entrei no size event\n");
    //skip the event.
    event.Skip();
}

void ImagePanel::paintEvent(wxPaintEvent &event) {
    wxPaintDC dc(this);
    render(dc);
}

void ImagePanel::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void ImagePanel::render(wxDC& dc) {
    int new_width, new_height;
    dc.GetSize(&new_width, &new_height);
    if (image_changed || new_width != widht || new_height != height) {
        resized = wxBitmap(image.Scale(new_width, new_height, wxIMAGE_QUALITY_HIGH));
        widht = new_width;
        height = new_height;
        dc.DrawBitmap(resized, 0, 0, false);
        image_changed = false;
    }else {
        dc.DrawBitmap(resized, 0, 0, false);
    }
    debug ("Renderizei a imagem\n");
}

void ImagePanel::changeImage(const wxImage &other) {
    debug ("Rodei o change image passando a image\n");
    image = other;
    image_changed = true;
    paintNow();
}

void ImagePanel::changeImage(const wxString &file_path, wxBitmapType format) {
    debug ("Rodei o change image passando o caminho\n");
    image.LoadFile(file_path, format);
    image_changed = true;
    paintNow();
}

bool ImagePanel::saveFile(const wxString &full_path) {
    return image.SaveFile(full_path);
}

ImagePanel::~ImagePanel() {
    debug ("Destruindo o ImagePanel\n");
}