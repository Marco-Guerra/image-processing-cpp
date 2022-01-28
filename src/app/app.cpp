#include "app.hpp"

IMPLEMENT_APP(App)

App::App() {
}

bool App::OnInit() {
	srand (time(NULL));
	wxInitAllImageHandlers();
	auto main = new MainFrame();
	main->Show(true);
	return true;
}

App::~App() {
}
