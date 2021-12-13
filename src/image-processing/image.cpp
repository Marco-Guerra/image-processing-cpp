#include "image.hpp"

Image::Image() : mat() {
	debug("Criando a image sem parametros\n");
}

Image::Image(const std::string file_path, int flag) {
	debug("Criando a image e carregando os dados do arquivo\n");
	loadImage(file_path, flag);
}

Image::Image(const wxImage &wx) :
	mat(cv::Size(wx.GetWidth(),wx.GetHeight()),CV_8UC3,wx.GetData()) {
	debug("Criando a image e carregando os dados a partir da wxImage\n");
	cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
}

cv::Mat& Image::getWritableMat() {
	return mat;
}

void Image::loadImage(const std::string file_path, int flag) {
	mat = cv::imread(file_path, flag);
}

Image* Image::medianBlur(int ksize) const {
	auto dest = new Image();
	cv::medianBlur(mat, dest->getWritableMat(), ksize);
	return dest;
}

Image* Image::averageBlur(int ksize) const {
	//cv::GaussianBlur(mat, mat, cv::Size(ksize, ksize), 0);
}


void Image::threshold(double min_value, double max_value, int type) {
	cv::threshold(mat, mat, min_value, 255, type);
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

wxImage Image::toWxImage() const {
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

	size_t imsize = im2.rows * im2.cols * im2.channels();
	wxImage wx(im2.cols, im2.rows, (unsigned char *)malloc(imsize), false);
	memcpy(wx.GetData(), im2.data, imsize);
	return wx;
}