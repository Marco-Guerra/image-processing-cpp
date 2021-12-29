#ifndef APP
#define APP

#include "../include/my_includes.hpp"
#include "../view/main_frame.hpp"

class App : public wxApp {
private:
public:
	App();
	bool OnInit();
	~App();
};

#endif // APP
