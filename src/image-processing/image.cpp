#include "image.hpp"

Image::Image(const std::string file_path, int flag) {
	loadImage(file_path, flag);
}

void Image::loadImage(const std::string file_path, int flag) {
	mat = cv::imread(file_path, flag);
}

void Image::medianBlur(int ksize) {
	cv::medianBlur(mat, mat, ksize);
}

void Image::averageBlur(int ksize) {
	cv::GaussianBlur(mat, mat, cv::Size(ksize, ksize), 0);
}

void Image::canny() {
	//cv::Canny(mat, )
}

void Image::toGray() {
	cv::cvtColor(mat, mat, cv::COLOR_BGR2GRAY);
}

const cv::Mat& Image::getMat() const {
	return mat;
}

wxImage Image::toWxImage() {
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
	memcpy(wx.GetData(), im2.data, imsize);
	return wx;
}