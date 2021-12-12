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

	void medianBlur(int ksize);
	void averageBlur(int ksize);
	void canny();
	void toGray();

	const cv::Mat &getMat() const;
	wxImage toWxImage();
};

#endif // IMAGE
