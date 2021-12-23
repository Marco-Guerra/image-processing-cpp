#include "main_frame.hpp"

MainFrame::MainFrame() :
	wxFrame(NULL, wxID_ANY, "Image processing++", wxPoint(), wxSize(800, 600)),
	img_history(new Image(INITIAL_IMAGE)),
	drawPane(new ImagePanel(this, INITIAL_IMAGE, wxBITMAP_TYPE_JPEG)),
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
	menu_metods->Append(ID_ROBERTS, wxT("&Detectar bordas com método de Roberts"));
	menu_metods->Append(ID_PREWITT, wxT("&Detectar bordas com método de Prewitt"));
	menu_metods->Append(ID_SOBEL, wxT("&Detectar bordas com método de sobel"));
	menu_metods->Append(ID_LOG, "&Realizar Log na imagem");
	menu_metods->Append(ID_ZEROCROSS, "&Realizar");
	menu_metods->Append(ID_CANNY, wxT("&Detectar bordas com método de canny"));
	menu_metods->Append(ID_NOISE, "&Adicionar ruido (Salt and Peper)");
	menu_metods->Append(ID_WATERSHED, "&Realizar");
	menu_metods->Append(ID_HISTOGRAM, "&Mostrar o histograma da imagem");
	menu_metods->Append(ID_HISTOGRAM_AJUST, "&Realizar ajuste da escala de cinsa usando histograma");
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
	if (openImage()) {
		updateImage();
	}else {
		showDialog(wxT("Erro ao carregar a imagem"), DIALOG_ERROR);
	}
}

void MainFrame::onSave(wxCommandEvent& event) {
	auto dialog = new wxFileDialog(
		this,
		"Escolha o nome da imagem para salvar",
		DEFAULT_IMAGE_FOLDER,
		wxEmptyString,
		"Imagens .jpg, .png, .tif |*.jpg;*.tif;*.png",
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
	if (img_history.previus()) {
		updateImage();
		showDialog("Desfazer executado com sucesso", DIALOG_INFO);
	}else {
		showDialog(
			wxT("Falha ao executar o desfazer, você já está no último elemento"),
			DIALOG_ERROR
		);
	}
}

void MainFrame::onRedo(wxCommandEvent& event) {
	if (img_history.next()) {
		updateImage();
		showDialog("Refazer executado com sucesso", DIALOG_INFO);
	}else {
		showDialog(
			wxT("Falha ao executar o refazer, você já está no topo da pilha"),
			DIALOG_ERROR
		);
	}
}

void MainFrame::onLowPass(wxCommandEvent& event) {
	long temp = 0;
	int mat_filter_size;
	auto dialog = wxTextEntryDialog(
		this,
		wxT("Entre com o tamanho da máscara")
	);
	dialog.SetTextValidator(wxFILTER_DIGITS);

	while (1) {
		if (dialog.ShowModal() == wxID_OK) {
			dialog.GetValue().ToLong(&temp);
			if (temp % 2) break;
		}else {
			return; // o usuario cancelou o menu
		}
		dialog.SetValue("3");
		showDialog("O valor entrado precisa ser impar", DIALOG_ERROR);
	}
	mat_filter_size = static_cast<int>(temp);
	const bool resp = showDialog (
		wxT("Deseja usar filtro da mediana? Caso contrario será usado filtro da média"),
		DIALOG_QUESTION
	);

	if(resp){
		img_history.add(img_history.getCurrent()->medianBlur(mat_filter_size));
	}else {
		img_history.add(img_history.getCurrent()->averageBlur(mat_filter_size));
	}
	updateImage();

	wxString message = wxT("Método passa baixa (");
	message += (resp? wxT("Mediana") : wxT("Média"));
	message += ") executado com sucesso";
	showDialog(message, DIALOG_INFO);
}

void MainFrame::onHighPass(wxCommandEvent& event) {
	long temp = 0;
	int mat_filter_size;
	auto dialog = wxTextEntryDialog(
		this,
		wxT("Entre com o tamanho da máscara")
	);
	dialog.SetTextValidator(wxFILTER_DIGITS);

	while (1) {
		if (dialog.ShowModal() == wxID_OK) {
			dialog.GetValue().ToLong(&temp);
			if (temp % 2) break;
		}else {
			return; // o usuario cancelou o menu
		}
		dialog.SetValue("3");
		showDialog("O valor entrado precisa ser impar", DIALOG_ERROR);
	}
	mat_filter_size = static_cast<int>(temp);
	auto img_temp = img_history.getCurrent()->averageBlur(mat_filter_size);

	const bool resp = showDialog (
		wxT("Executou-se o filtro da média deseja usar reforçar a imagem?"),
		DIALOG_QUESTION
	);
	if (resp) {
		double reforce;
		auto dialog = wxTextEntryDialog (
			this,
			wxT("Entre com o valor do reforço")
		);
		dialog.SetTextValidator(wxFILTER_NUMERIC);
		if (dialog.ShowModal() == wxID_OK) {
			dialog.GetValue().ToDouble(&reforce);
		}else {
			delete img_temp;
			return; // o usuario cancelou o menu
		}
		img_temp->reinforce(reforce);
	}

	img_history.add(img_temp);
	updateImage();
	wxString message = wxT("Método passa alta (");
	message += (resp? wxT("Alto Reforço") : wxT("Média"));
	message += ") executado com sucesso";
	showDialog(message, DIALOG_INFO);
}

void MainFrame::onThreshold(wxCommandEvent& event) {
	long temp;
	auto dialog = wxTextEntryDialog(
		this,
		wxT("Entre com o valor do threshold [0, 255]")
	);
	dialog.SetTextValidator(wxFILTER_DIGITS);
	while (1) {
		if (dialog.ShowModal() == wxID_OK) {
			dialog.GetValue().ToLong(&temp);
			if (temp <= 255) break;
		}else {
			return; // o usuario cancelou o menu
		}
		dialog.SetValue("127");
		showDialog(
			"O valor entrado precisa estar dentro da faixa [0, 255]",
			DIALOG_ERROR
		);
	}
	const uint8_t menu_val = static_cast<uint8_t>(temp);
	img_history.add(img_history.getCurrent()->threshold(menu_val));
	updateImage();
	showDialog(wxT("Método de Limiarização executado com sucesso"), DIALOG_INFO);
}

void MainFrame::onGray(wxCommandEvent& event) {
	img_history.add(img_history.getCurrent()->toGray());
	updateImage();
	showDialog(
		wxT("Transformação para escala de cinsa executado com sucesso"),
		DIALOG_INFO
	);
}

void MainFrame::onRoberts(wxCommandEvent& event) {
	img_history.add(img_history.getCurrent()->roberts());
	updateImage();
	showDialog(
		wxT("Detecção de bordas com método de Roberts executado com sucesso"),
		DIALOG_INFO
	);
}

void MainFrame::onPrewitt(wxCommandEvent& event) {
	img_history.add(img_history.getCurrent()->prewitt());
	updateImage();
	showDialog(
		wxT("Detecção de bordas com método de Prewitt executado com sucesso"),
		DIALOG_INFO
	);
}

void MainFrame::onSobel(wxCommandEvent& event) {
	long temp;
	auto dialog = wxTextEntryDialog(
		this,
		wxT("Entre com o tamanho da matriz")
	);
	dialog.SetTextValidator(wxFILTER_DIGITS);
	if (dialog.ShowModal() == wxID_OK) {
		dialog.GetValue().ToLong(&temp);
	}else {
		return; // o usuario cancelou o menu
	}
	const bool use_x = showDialog (
		wxT("Deseja-se calcular a derivada no eixo X?"),
		DIALOG_QUESTION
	);
	const bool use_y = showDialog (
		wxT("Deseja-se calcular a derivada no eixo Y?"),
		DIALOG_QUESTION
	);
	img_history.add(img_history.getCurrent()->sobel(use_x, use_y, temp));
	updateImage();
	showDialog(wxT("Método de Sobel executado com sucesso"), DIALOG_INFO);
}

void MainFrame::onLog(wxCommandEvent& event) {
	img_history.add(img_history.getCurrent()->log());
	updateImage();
	showDialog(wxT("Método de Log executado com sucesso"), DIALOG_INFO);
}

void MainFrame::onZerocross(wxCommandEvent& event) {
	
}

void MainFrame::onCanny(wxCommandEvent& event) {
	uint8_t t1, t2;
	long temp;
	auto dialog1 = wxTextEntryDialog(
		this,
		wxT("Entre com o Primeiro valor do threshold [0, 255]")
	);
	dialog1.SetTextValidator(wxFILTER_DIGITS);
	while (1) {
		if (dialog1.ShowModal() == wxID_OK) {
			dialog1.GetValue().ToLong(&temp);
			if (temp <= 255) break;
		}else {
			return; // o usuario cancelou o menu
		}
		dialog1.SetValue("127");
		showDialog(
			"O valor entrado precisa estar dentro da faixa [0, 255]",
			DIALOG_ERROR
		);
	}
	t1 = static_cast<uint8_t>(temp);
	auto dialog2 = wxTextEntryDialog(
		this,
		wxT("Entre com o Segundo valor do threshold [0, 255]")
	);
	dialog2.SetTextValidator(wxFILTER_DIGITS);
	while (1) {
		if (dialog2.ShowModal() == wxID_OK) {
			dialog2.GetValue().ToLong(&temp);
			if (temp <= 255) break;
		}else {
			return; // o usuario cancelou o menu
		}
		dialog2.SetValue("127");
		showDialog(
			"O valor entrado precisa estar dentro da faixa [0, 255]",
			DIALOG_ERROR
		);
	}
	t2 = static_cast<uint8_t>(temp);
	img_history.add(img_history.getCurrent()->canny(t1, t2));
	updateImage();
	showDialog(wxT("Método de Canny executado com sucesso"), DIALOG_INFO);
}

void MainFrame::onNoise(wxCommandEvent& event) {
	double percentage;
	auto dialog = wxTextEntryDialog (
		this,
		wxT("Entre com a probabilidade de um pixel ser alterado [0, 1]")
	);
	dialog.SetTextValidator(wxFILTER_NUMERIC);
	while (1) {
		if (dialog.ShowModal() == wxID_OK) {
			dialog.GetValue().ToDouble(&percentage);
			if (0.0 <= percentage && percentage <= 1) {
				break;
			}
		}else {
			return; // o usuario cancelou o menu
		}
		dialog.SetValue("0.05");
		showDialog(
			"O valor entrado precisa estar dentro da faixa [0, 1]",
			DIALOG_ERROR
		);
	}


	img_history.add(img_history.getCurrent()->noise(percentage));
	updateImage();
	showDialog(wxT("Ruído salt and peper adicionado com sucesso"), DIALOG_INFO);
}

void MainFrame::onWatershed(wxCommandEvent& event) {
	
}

void MainFrame::onHistogram(wxCommandEvent& event) {
	img_history.add(img_history.getCurrent()->histogram());
	updateImage();
	showDialog(wxT("Histograma gerado"), DIALOG_INFO);
}

void MainFrame::onHistogramAjust(wxCommandEvent& event) {
	img_history.add(img_history.getCurrent()->histogramAjust());
	updateImage();
	showDialog(wxT("ajuste da escala de cinsa usando histograma realizado com sucesso"), DIALOG_INFO);
}

void MainFrame::onCount(wxCommandEvent& event) {
	
}

bool MainFrame::openImage() {
	auto dialog = new wxFileDialog(
		this,
		"Escolha uma imagem jpg para abrir",
		DEFAULT_IMAGE_FOLDER,
		wxEmptyString,
		"Imagens .jpg, .png, .tif |*.jpg;*.tif;*.png",
		wxFD_OPEN|wxFD_FILE_MUST_EXIST
	);
	
	if (dialog->ShowModal() == wxID_OK) {
		auto path = dialog->GetPath().ToStdString();
		const bool resp = showDialog(
			"Deseja abrir a imagem " +
			path +
			wxT("? Todos os métodos executados na imagem anterior serão perdidos."),
			DIALOG_QUESTION
		);
		if (resp) {
			img_history.clean();
			img_history.add(new Image(path));
			return true;
		}
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

void MainFrame::updateImage() {
	drawPane->changeImage(img_history.getCurrent()->toWxImage());
}

MainFrame::~MainFrame() {
	debug("Destruindo MainFrame\n");
}
