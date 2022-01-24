#ifndef MAIN_FRAME
#define MAIN_FRAME

#include <functional>

#include "../include/wx.hpp"
#include "../include/debug.hpp"
#include "../include/config.hpp"

#include "../image-processing/image_history.hpp"
#include "image_panel.hpp"
#include "dialog.hpp"

class MainFrame : public wxFrame {
friend class MainFrameController;
private:
	ImageHistory img_history;

    ImagePanel *drawPane;

	wxBoxSizer *sizer;
	wxMenu *menu_file;
	wxMenu *menu_filter;
	wxMenu *menu_borders;
	wxMenu *menu_histogram;
	wxMenu *menu_transformation;
	wxMenu *menu_noise;
	wxMenu *menu_other_methods;
	wxMenuBar *menu_bar;


// métodos que serão ligados a eventos
	// file
	void onOpen(wxCommandEvent &event);
	void onSave(wxCommandEvent &event);
	void onUndo(wxCommandEvent &event);
	void onRedo(wxCommandEvent &event);

	// métodos que geram novas imagens
	void onLowPass       (wxCommandEvent &event);
	void onHighPass      (wxCommandEvent &event);
	void onThreshold     (wxCommandEvent &event);
	void onGray          (wxCommandEvent &event);
	void onRoberts       (wxCommandEvent &event);
	void onPrewitt       (wxCommandEvent &event);
	void onSobel         (wxCommandEvent &event);
	void onLog           (wxCommandEvent &event);
	void onZerocross     (wxCommandEvent &event);
	void onCanny         (wxCommandEvent &event);
	void onNoise         (wxCommandEvent &event);
	void onWatershed     (wxCommandEvent &event);
	void onHistogram     (wxCommandEvent &event);
	void onHistogramAjust(wxCommandEvent &event);
	void onCount         (wxCommandEvent &event);
	void onLaplacian     (wxCommandEvent &event);

	// metodos auxiliares
	bool openImage();
	// cria dialogo com usuário ver dialog.hpp
	bool showDialog(const wxString &message, DialogType type);
	// Manda a imagem atual do img_history para a tela
	void updateImage();

public:
	MainFrame();
	~MainFrame();
};

enum Identifiers {
	// file
	ID_OPEN,
	ID_SAVE_FILE,
	ID_UNDO,
	ID_REDO,

	// methods
	ID_THRESHOLD,
	ID_GRAY,
	ID_LOW_PASS,
	ID_HIGH_PASS,
	ID_ROBERTS,
	ID_PREWITT,
	ID_SOBEL,
	ID_LOG,
	ID_ZEROCROSS,
	ID_CANNY,
	ID_NOISE,
	ID_WATERSHED,
	ID_HISTOGRAM,
	ID_HISTOGRAM_AJUST,
	ID_COUNT,
	ID_LAPLACIAN
};


#endif // MAIN_FRAME
