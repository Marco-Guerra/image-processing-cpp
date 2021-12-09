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
    std::cout << "Entrei no size event\n";
    //skip the event.
    event.Skip();
}

void ImagePanel::paintEvent(wxPaintEvent & evt) {
    wxPaintDC dc(this);
    render(dc);
}

void ImagePanel::paintNow() {
    wxClientDC dc(this);
    render(dc);
    std::cout << "Indo pegar o parent\n";
    const auto parent = GetParent();
    if (parent != nullptr) {
        std::cout << "Indo recarregar\n";
        parent->Refresh();
        parent->Update();
    }
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
    std::cout << "Renderizei a imagem\n";
}

void ImagePanel::changeImage(const wxImage &other) {
    image = other;
    std::cout << "Rodei o change image passando a image\n";
    paintNow();
}

void ImagePanel::changeImage(const wxString &file_path, wxBitmapType format) {
    image.LoadFile(file_path, format);
    std::cout << "Rodei o change image passando o caminho\n";
}

ImagePanel::~ImagePanel() {
}