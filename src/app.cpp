#include "app.hpp"

using namespace cv;
using namespace std;

IMPLEMENT_APP(App)

App::App() {
}

bool App::OnInit() {
	// make sure to call this first
	Mat image = imread("../images/image.jpg");
	if (image.empty())
	{
		cout << "Could not open or find the image" << endl;
		cin.get(); //wait for any key press
		return -1;
	}
	String windowName = "The Guitar"; //Name of the window

	namedWindow(windowName); // Create a window

	imshow(windowName, image); // Show our image inside the created window.

	waitKey(0); // Wait for any keystroke in the window

	destroyWindow(windowName); //destroy the created window

	wxInitAllImageHandlers();
	auto main = new MainFrame();
	main->Show(true);
	return true;
}

App::~App() {
}
