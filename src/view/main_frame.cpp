#include "main_frame.hpp"

MainFrame::MainFrame() :
		wxFrame(NULL, wxID_ANY, "Main Frame", wxPoint(), wxSize(800, 600)),
		img("../images/full_hd.jpg"),
		sizer(new wxBoxSizer(wxHORIZONTAL)) {

	SetSizer(sizer);

	drawPane = new ImagePanel(this, "../images/full_hd.jpg", wxBITMAP_TYPE_JPEG);
	sizer->Add(drawPane, 1, wxEXPAND);

	wxMenu *menuMetods = new wxMenu();
	menuMetods->Append(ID_MEDIAN_BLUR, "Realizar passa baixa da media");

	wxMenu *menuFile = new wxMenu();
	menuFile->Append(ID_OPEN, "Abrir uma imagem",
		"ao selecionar essa opção será levado ao gerenciador de arquivos do sistema");
	menuFile->Append(ID_REFRESH, "Recarregar o conteudo da imagem");
	menuFile->Append(ID_SAVE_FILE, "Salvando a imagem atual",
		"Abre um menu para selecionar onde salvar a imagem");

	wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "File");
    menuBar->Append(menuMetods, "Metodos");

	SetMenuBar(menuBar);
	CreateStatusBar();
    SetStatusText("WxWidgets main frame!");
	Centre();

	Bind(wxEVT_MENU, &MainFrame::onOpen, this, ID_OPEN);
	Bind(wxEVT_MENU, &MainFrame::onMedianBlur, this, ID_MEDIAN_BLUR);
	Bind(wxEVT_MENU,
	[this](wxCommandEvent&) {
		drawPane->paintNow();
		drawPane->Refresh();
		Refresh();
	},
	ID_REFRESH);
}

void MainFrame::onOpen(wxCommandEvent& event) {
	if (!openImage()) {
		showError(wxT("Error loading file"));
	}
	drawPane->paintNow();
}

void MainFrame::onSave(wxCommandEvent& event) {

}

void MainFrame::onMedianBlur(wxCommandEvent& event) {
	img.medianBlur(35);
	drawPane->changeImage(img.toWxImage());
}

bool MainFrame::openImage() {
	auto dialog = new wxFileDialog(
		this, "Escolha uma imagem jpg para abrir", "../images", wxEmptyString, "*.jpg"
	);
	
	if (dialog->ShowModal() == wxID_OK) {
		img.loadImage(dialog->GetPath().ToStdString());
		drawPane->changeImage(img.toWxImage());
		return true;
	}
	return false;
}

void MainFrame::showError(const wxString &message) {
	auto dial = new wxMessageDialog (
		this, message, wxT("Error"), wxOK | wxICON_ERROR
	);
	dial->ShowModal();
}

MainFrame::~MainFrame() {
    
}
