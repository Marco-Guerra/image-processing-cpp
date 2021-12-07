#ifndef IMAGE
#define IMAGE

#include <opencv2/opencv.hpp>
#include <wx/wx.h>

class Image {
private:
	cv::Mat mat;

public:
	Image(const std::string file_path, int flag = 1) {
		loadImage(file_path, flag);
	}

	void loadImage(const std::string file_path, int flag = 1) {
		mat = cv::imread(file_path, flag);
	}

	void medianBlur(int ksize) {
		cv::medianBlur(mat, mat, ksize);
	}

	const cv::Mat &getMat() const {
		return mat;
	}

	wxImage toWxImage() {
		cv::Mat im2;
		if (mat.channels() == 1) {
			cv::cvtColor(mat, im2, cv::COLOR_GRAY2RGB);
		}
		else if (mat.channels() == 4) {
			cv::cvtColor(mat, im2, cv::COLOR_BGRA2RGB);
		}
		else {
			cv::cvtColor(mat, im2, cv::COLOR_BGR2RGB);
		}

		long imsize = im2.rows * im2.cols * im2.channels();
		wxImage wx(im2.cols, im2.rows, (unsigned char *)malloc(imsize), false);
		unsigned char *s = im2.data;
		unsigned char *d = wx.GetData();
		for (long i = 0; i < imsize; i++) {
			d[i] = s[i];
		}
		return wx;
	}
};

#endif // IMAGE
