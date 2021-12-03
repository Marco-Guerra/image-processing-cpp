#ifndef APP
#define APP

#include <wx/wx.h>
#include <wx/sizer.h>

#include "main_frame.hpp"

class App : public wxApp {
private:
public:
	App();
	bool OnInit();
	~App();
};

#endif // APP
