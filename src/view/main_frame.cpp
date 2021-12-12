#include "main_frame.hpp"

MainFrame::MainFrame() :
		wxFrame(NULL, wxID_ANY, "Main Frame", wxPoint(), wxSize(800, 600)),
		img(new Image("../images/full_hd.jpg")),
		drawPane(new ImagePanel(this, "../images/full_hd.jpg", wxBITMAP_TYPE_JPEG)),
		sizer(new wxBoxSizer(wxHORIZONTAL)),
		menu_metods(new wxMenu()),
		menu_file(new wxMenu()),
		menu_bar(new wxMenuBar()) {

	debug("Construindo MainFrame\n");

	SetSizer(sizer);
	sizer->Add(drawPane, 1, wxEXPAND);

	menu_metods->Append(ID_LOW_PASS, "&Realizar passa baixa...\tCtrl-L");
	menu_metods->Append(ID_HIGH_PASS, "&Realizar passa alta...\tCtrl-H");
	menu_metods->Append(ID_THRESHOLD, "&Realizar threshold");
	menu_metods->Append(ID_GRAY, wxT("&Realizar transformação escala de cinsa"));
	menu_metods->Append(ID_ROBERTS, "&Realizar");
	menu_metods->Append(ID_PREWITT, "&Realizar");
	menu_metods->Append(ID_SOBEL, "&Realizar");
	menu_metods->Append(ID_LOG, "&Realizar");
	menu_metods->Append(ID_ZEROCROSS, "&Realizar");
	menu_metods->Append(ID_CANNY, "&Realizar");
	menu_metods->Append(ID_NOISE, "&Realizar");
	menu_metods->Append(ID_WATERSHED, "&Realizar");
	menu_metods->Append(ID_HISTOGRAM, "&Realizar");
	menu_metods->Append(ID_HISTOGRAM_AJUST, "&Realizar");
	menu_metods->Append(ID_COUNT, "&Realizar");

	menu_file->Append(ID_OPEN, "Abrir uma imagem\tCtrl-O",
		wxT("Selecionando essa opção será levado ao gerenciador de arquivos do sistema"));
	menu_file->Append(ID_SAVE_FILE, "&Salvando a imagem atual...\tCtrl-S",
		"Abre um menu para selecionar onde salvar a imagem");
	menu_file->AppendSeparator();
	menu_file->Append(ID_UNDO, wxT("&Desfazer ação...\tCtrl-Z"));
	menu_file->Append(ID_REDO, wxT("&Refazer ação...\tCtrl-Y"));

    menu_bar->Append(menu_file, "Imagem");
    menu_bar->Append(menu_metods, wxT("Métodos"));

	SetMenuBar(menu_bar);
	CreateStatusBar();
    SetStatusText("WxWidgets main frame!");
	Centre();

	Bind(wxEVT_MENU, &MainFrame::onOpen, this, ID_OPEN);
	Bind(wxEVT_MENU, &MainFrame::onSave, this, ID_SAVE_FILE);
	Bind(wxEVT_MENU, &MainFrame::onUndo, this, ID_UNDO);
	Bind(wxEVT_MENU, &MainFrame::onRedo, this, ID_REDO);

	Bind(wxEVT_MENU, &MainFrame::onLowPass, this, ID_LOW_PASS);
	Bind(wxEVT_MENU, &MainFrame::onHighPass, this, ID_HIGH_PASS);
	Bind(wxEVT_MENU, &MainFrame::onThreshold, this, ID_THRESHOLD);
	Bind(wxEVT_MENU, &MainFrame::onGray, this, ID_GRAY);
	Bind(wxEVT_MENU, &MainFrame::onRoberts, this, ID_ROBERTS);
	Bind(wxEVT_MENU, &MainFrame::onPrewitt, this, ID_PREWITT);
	Bind(wxEVT_MENU, &MainFrame::onSobel, this, ID_SOBEL);
	Bind(wxEVT_MENU, &MainFrame::onLog, this, ID_LOG);
	Bind(wxEVT_MENU, &MainFrame::onZerocross, this, ID_ZEROCROSS);
	Bind(wxEVT_MENU, &MainFrame::onCanny, this, ID_CANNY);
	Bind(wxEVT_MENU, &MainFrame::onNoise, this, ID_NOISE);
	Bind(wxEVT_MENU, &MainFrame::onWatershed, this, ID_WATERSHED);
	Bind(wxEVT_MENU, &MainFrame::onHistogram, this, ID_HISTOGRAM);
	Bind(wxEVT_MENU, &MainFrame::onHistogramAjust, this, ID_HISTOGRAM_AJUST);
	Bind(wxEVT_MENU, &MainFrame::onCount, this, ID_COUNT);
}

void MainFrame::onOpen(wxCommandEvent& event) {
	if (!openImage()) {
		showDialog(wxT("Error loading file"), DIALOG_ERROR);
	}
}

void MainFrame::onSave(wxCommandEvent& event) {
	auto dialog = new wxFileDialog(
		this,
		"Escolha o nome da imagem para salvar",
		"../images",
		wxEmptyString,
		_T("*.jpg"),
		wxFD_SAVE
	);
	
	if (dialog->ShowModal() == wxID_OK) {
		if (drawPane->saveFile(dialog->GetPath())) {
			showDialog("Imagem salva com sucesso", DIALOG_INFO);
			return;
		}
	}
	showDialog("Falha ao salvar Imagem", DIALOG_ERROR);
}

void MainFrame::onUndo(wxCommandEvent& event) {
	showDialog("Rodou o Undo", DIALOG_INFO);
}

void MainFrame::onRedo(wxCommandEvent& event) {

}

void MainFrame::onLowPass(wxCommandEvent& event) {
	long temp = 0;
	int mat_filter_size;
	auto dialog_size = new wxTextEntryDialog(this, wxT("Entre com o tamanho da máscara"));
	//auto d = new wxAnyChoiceDialog;

	dialog_size->SetTextValidator(wxFILTER_DIGITS);
	while (1) {
		if (dialog_size->ShowModal() == wxID_OK) {
			dialog_size->GetValue().ToLong(&temp);
			if (temp % 2) break;
		}else {
			return; // o usuario cancelou o menu
		}
		dialog_size->SetValue("3");
		showDialog("O valor entrado precisa ser impar", DIALOG_ERROR);
	}
	mat_filter_size = static_cast<int>(temp);

	if(showDialog(
		wxT("Deseja usar filtro da mediana? Caso contrario será usado filtro da média"),
		DIALOG_QUESTION
	)){
		img->medianBlur(mat_filter_size);
	}else {
		img->averageBlur(mat_filter_size);
	}
	drawPane->changeImage(img->toWxImage());
	showDialog(wxT("Método passa baixa realizado com sucesso"), DIALOG_INFO);
}

void MainFrame::onHighPass(wxCommandEvent& event) {

}

void MainFrame::onThreshold(wxCommandEvent& event) {
	img->threshold(127);
	drawPane->changeImage(img->toWxImage());
	showDialog(wxT("Método Threshold realizado com sucesso"), DIALOG_INFO);
}

void MainFrame::onGray(wxCommandEvent& event) {
	img->toGray();
	drawPane->changeImage(img->toWxImage());
	showDialog(wxT("Transformação para escala de cinsa realizado com sucesso"), DIALOG_INFO);
}

void MainFrame::onRoberts(wxCommandEvent& event) {
	
}

void MainFrame::onPrewitt(wxCommandEvent& event) {
	
}

void MainFrame::onSobel(wxCommandEvent& event) {
	
}

void MainFrame::onLog(wxCommandEvent& event) {
	
}

void MainFrame::onZerocross(wxCommandEvent& event) {
	
}

void MainFrame::onCanny(wxCommandEvent& event) {
	
}

void MainFrame::onNoise(wxCommandEvent& event) {
	
}

void MainFrame::onWatershed(wxCommandEvent& event) {
	
}

void MainFrame::onHistogram(wxCommandEvent& event) {
	
}

void MainFrame::onHistogramAjust(wxCommandEvent& event) {
	
}

void MainFrame::onCount(wxCommandEvent& event) {
	
}

bool MainFrame::openImage() {
	auto dialog = new wxFileDialog(
		this,
		"Escolha uma imagem jpg para abrir",
		"../images",
		wxEmptyString,
		_T("*.jpg")
	);
	
	if (dialog->ShowModal() == wxID_OK) {
		img->loadImage(dialog->GetPath().ToStdString());
		drawPane->changeImage(img->toWxImage());
		return true;
	}
	return false;
}

bool MainFrame::showDialog(const wxString &message, DialogType type) {
	long style;
	wxString caption;

	if (type == DIALOG_ERROR) {
		caption = "Erro";
		style = wxOK | wxICON_ERROR;
	}else if (type == DIALOG_INFO) {
		caption = wxT("Informação");
		style = wxOK;
	}else if (type == DIALOG_QUESTION) {
		caption = wxT("Confirmação");
		style = wxYES_NO | wxNO_DEFAULT | wxICON_QUESTION;
	}
	auto dial = new wxMessageDialog (
		this, message, caption, style
	);
	const auto ret = dial->ShowModal();
	if (type == DIALOG_QUESTION) {
		return ret == wxID_YES;
	}
	return ret == wxID_OK;
}

MainFrame::~MainFrame() {
	debug("Destruindo MainFrame\n");
}
