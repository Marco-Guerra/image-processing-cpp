#include "image.hpp"

Image::Image() : mat() {
	debug("Criando a image sem parametros\n");
}

Image::Image(const std::string file_path, int flag) {
	debug("Criando a image e carregando os dados do arquivo\n");
	loadImage(file_path, flag);
}

Image::Image(const wxImage &wx) :
	mat(cv::Size(wx.GetWidth(),wx.GetHeight()), CV_8UC3, wx.GetData()) {
	debug("Criando a image e carregando os dados a partir da wxImage\n");
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
	auto dest = new Image();
	cv::GaussianBlur(mat, dest->getWritableMat(), cv::Size(ksize, ksize), 0);
	return dest;
}


Image* Image::threshold(double min_value, double max_value, int type) const {
	auto dest = new Image();
	cv::threshold(mat, dest->getWritableMat(), min_value, 255, type);
	return dest;
}

Image* Image::canny() const {
	auto dest = new Image();
	//cv::Canny(mat, )
	return dest;
}

Image* Image::toGray() const {
	auto dest = new Image();
	cv::cvtColor(mat, dest->getWritableMat(), cv::COLOR_BGR2GRAY);
	return dest;
}

Image* Image::roberts() const {

}

Image* Image::prewitt() const {

}

Image* Image::sobel() const {

}

Image* Image::log() const {

}

Image* Image::zerocross() const {

}

Image* Image::noise(uint64_t qnt) const {
	int r, c;
	const int rows = mat.rows;
	const int cols = mat.cols;
	const uint64_t img_pixels = rows * cols;

	auto ret = new Image();
	auto &dest = ret->getWritableMat();
	dest = mat;

	for (uint64_t i = 0; i < qnt; i++) {
		r = rand() % rows;
		c = rand() % cols;
		dest.at<cv::Vec3b>(r, c) = cv::Vec3b(0, 0, 0);
		r = rand() % rows;
		c = rand() % cols;
		dest.at<cv::Vec3b>(r, c) = cv::Vec3b(255, 255, 255);
	}
	
	return ret;
}

Image* Image::watershed() const {

}

Image* Image::histogram() const {

}

Image* Image::histogramAjus() const {

}

Image* Image::count() const {

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