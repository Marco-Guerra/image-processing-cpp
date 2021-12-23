#ifndef IMAGE
#define IMAGE

#include <opencv2/opencv.hpp>
#include <wx/wx.h>

#include "../utils/debug.hpp"

/**
 * @brief Classe que representa uma imagem,
 * 
 * um wrapper envolta da cv::Mat para gerar novas imagens
 * a partir dos dados contidos na mesma, facilitando a integração
 * com o framework wxWidgets e simplificando mostrar a imagem para o usuário
 */
class Image {
private:
	cv::Mat mat; /// matriz contendo cada pixel da imagem

	// Gera uma nova matriz na escala de cinsa
	// a partir da matriz dentro da classe
	cv::Mat toGrayMat() const;

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
	Image* canny(int t1, int t2) const;
	Image* toGray() const;
	Image* roberts() const;
	Image* prewitt() const;
	Image* sobel(int x, int y, int size) const;
    Image* log() const;
    Image* zerocross() const;
    Image* noise(const double noise_probability) const;
    Image* watershed() const;
    Image* histogram() const;
    Image* histogramAjust() const;
    Image* count() const;

	const cv::Mat &getMat() const;
	wxImage toWxImage() const;
};

#endif // IMAGE
