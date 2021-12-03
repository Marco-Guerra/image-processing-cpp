#include "main_frame.hpp"


MainFrame::MainFrame() :
		wxFrame(NULL, wxID_ANY, "Main Frame", wxPoint(50, 50), wxSize(800, 600)) {

    sizer = new wxBoxSizer(wxHORIZONTAL);
	this->SetSizer(sizer);

	drawPane = new ImagePanel(this, "../images/full_hd.jpg", wxBITMAP_TYPE_JPEG);
	sizer->Add(drawPane, 1, wxEXPAND);

	wxMenu *menuFile = new wxMenu();
	menuFile->Append(ID_OPEN, "Abrir a imagem",
		"ao selecionar essa opção será levado ao gerenciador de arquivos do sistema");

	wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "File");

	SetMenuBar(menuBar);
	CreateStatusBar();
    SetStatusText("WxWidgets main frame!");

	Bind(wxEVT_MENU, &MainFrame::onOpen, this, ID_OPEN);
}

void MainFrame::onOpen(wxCommandEvent& event) {
	auto dialog = new wxFileDialog(this, "Escolha uma imagem jpg para abrir", "../images");
	if (dialog->ShowModal() == wxID_OK) {
		auto file_name = dialog->GetPath();
		drawPane->changeImage(file_name);
	}else {
		auto dial = new wxMessageDialog(this, 
			wxT("Error loading file"), wxT("Error"), wxOK | wxICON_ERROR);

		dial->ShowModal();
	}
}

MainFrame::~MainFrame() {
    
}
