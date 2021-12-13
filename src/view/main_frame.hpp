#ifndef MAIN_FRAME
#define MAIN_FRAME

#include <functional>
#include <wx/wxprec.h>
#include <wx/wx.h>

#include "image_panel.hpp"
#include "../image-processing/image_history.hpp"

enum DialogType {
	DIALOG_ERROR,
	DIALOG_INFO,
	DIALOG_QUESTION,
};

#define DEFAULT_IMAGE_FOLDER "../images"
#define INITIAL_IMAGE (const char  *)(DEFAULT_IMAGE_FOLDER "/full_hd.jpg")

class MainFrame : public wxFrame {
friend class MainFrameController;
private:
	ImageHistory img_history;

    ImagePanel *drawPane;

	wxBoxSizer *sizer;
	wxMenu *menu_metods;
	wxMenu *menu_file;
	wxMenuBar *menu_bar;


// metodos que serao ligados a eventos
	// file
	void onOpen(wxCommandEvent& event);
	void onSave(wxCommandEvent& event);
	void onUndo(wxCommandEvent& event);
	void onRedo(wxCommandEvent& event);

	//metods
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

	// metodos auxiliares
	bool openImage();
	bool showDialog(const wxString &message, DialogType type);

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

	// metods
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
	ID_COUNT
};


#endif // MAIN_FRAME
