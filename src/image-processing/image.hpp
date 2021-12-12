#ifndef IMAGE
#define IMAGE

#include <opencv2/opencv.hpp>
#include <wx/wx.h>

#include "../utils/debug.hpp"

class Image {
private:
	cv::Mat mat;

public:
	Image();
	Image(const std::string file_path, int flag = 1);
	void loadImage(const std::string file_path, int flag = 1);

	// low pass
	void medianBlur(int ksize);
	void averageBlur(int ksize);

	// high pass

	void threshold(double min_value = 0.0, double max_value = 255.0, int type = cv::THRESH_BINARY);
	void canny();
	void toGray();

	const cv::Mat &getMat() const;
	wxImage toWxImage();
};

#endif // IMAGE
