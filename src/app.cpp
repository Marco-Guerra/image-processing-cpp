#include "app.hpp"

IMPLEMENT_APP(App)

App::App() {
}

bool App::OnInit() {
	// make sure to call this first
	wxInitAllImageHandlers();
	auto main = new MainFrame();
	main->Show();
	return true;
}

App::~App() {
}
