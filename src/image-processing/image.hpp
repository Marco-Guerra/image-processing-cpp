#ifndef IMAGE
#define IMAGE

#include <opencv2/opencv.hpp>
#include <wx/wx.h>

#include "../utils/debug.hpp"

class Image {
private:
	cv::Mat mat;

	cv::Mat& getWritableMat();

public:
	Image();
	Image(const std::string file_path, int flag = 1);
	Image(const wxImage &wx);
	void loadImage(const std::string file_path, int flag = 1);

	// low pass
	Image* medianBlur(int ksize) const;
	Image* averageBlur(int ksize) const;

	// high pass
	Image* reinforce(double r) const;
	void reinforce(double r);

	Image* threshold(double min_value = 0.0, double max_value = 255.0, int type = cv::THRESH_BINARY) const;
	Image* canny() const;
	Image* toGray() const;
	Image* roberts() const;
	Image* prewitt() const;
	Image* sobel() const;
    Image* log() const;
    Image* zerocross() const;
    Image* noise(uint64_t qnt) const;
    Image* watershed() const;
    Image* histogram() const;
    Image* histogramAjus() const;
    Image* count() const;

	const cv::Mat &getMat() const;
	wxImage toWxImage() const;
};

#endif // IMAGE
