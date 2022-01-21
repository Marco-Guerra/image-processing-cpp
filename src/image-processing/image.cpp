#include "image.hpp"

cv::Mat Image::toGrayMat() const {
    cv::Mat temp_mat;
    if (mat.channels() == 3) {
        debug("Convertendo de BGR para escala de cinsa");
        cv::cvtColor(mat, temp_mat, cv::COLOR_BGR2GRAY);
    } else if (mat.channels() == 4) {
        debug("Convertendo de BGRA para escala de cinsa");
        cv::cvtColor(mat, temp_mat, cv::COLOR_BGRA2GRAY);
    }else {
        debug("A matriz já está em escala de cinsa, copiando");
        temp_mat = mat.clone();
    }
    return temp_mat;
}

Image::Image() : mat() { debug("Criando a image sem parametros\n"); }

Image::Image(const std::string file_path, int flag) {
    debug("Criando a image e carregando os dados do arquivo\n");
    loadImage(file_path, flag);
}

Image::Image(const wxImage& wx)
    : mat(cv::Size(wx.GetWidth(), wx.GetHeight()), CV_8UC3, wx.GetData()) {
    debug("Criando a image e carregando os dados a partir da wxImage\n");
    // cv::cvtColor(mat, mat, cv::COLOR_RGB2BGR);
}

void Image::loadImage(const std::string file_path, int flag) {
    mat = cv::imread(file_path, flag);  // cv::IMREAD_ANYCOLOR
}

Image* Image::medianBlur(int ksize) const {
    auto dest = new Image();
    cv::medianBlur(mat, dest->mat, ksize);
    return dest;
}

Image* Image::averageBlur(int ksize) const {
    auto dest = new Image();
    cv::GaussianBlur(mat, dest->mat, cv::Size(ksize, ksize), 0);
    return dest;
}

Image* Image::reinforce(double r) const {
    auto dest = new Image();
    dest->mat = (mat * (r - 1));
    return dest;
}

void Image::reinforce(double r) { this->mat *= (r - 1); }

Image* Image::threshold(double min_value, double max_value, int type) const {
    auto dest = new Image();
    cv::threshold(mat, dest->mat, min_value, max_value, type);
    return dest;
}

Image* Image::canny(int t1, int t2) const {
    auto dest = new Image();
    cv::Canny(mat, dest->mat, t1, t2);
    return dest;
}

Image* Image::toGray() const {
    auto dest = new Image();
    dest->mat = toGrayMat();
    return dest;
}

Image* Image::roberts() const {
    auto dest = new Image();

    cv::Mat temp_x, temp_y;
    const auto gray = toGrayMat();

    int8_t x_values[] = {
        -1, 0,
        0, 1
    };
    int8_t y_values[] = {
        0, -1,
        1, 0
    };
    const cv::Mat kx(cv::Size(2, 2), CV_8S, x_values);
    const cv::Mat ky(cv::Size(2, 2), CV_8S, y_values);


    cv::filter2D(gray, temp_x, -1, kx);
    cv::filter2D(gray, temp_y, -1, ky);

    dest->mat = temp_x + temp_y;
    cv::convertScaleAbs(dest->mat, dest->mat);

    return dest;
}

Image* Image::prewitt() const {
    auto dest = new Image();

    cv::Mat temp_x, temp_y;
    const auto gray = toGrayMat();

    int8_t x_values[] = {
        1, 1, 1,
        0, 0, 0,
        -1, -1, -1
    };
    int8_t y_values[] = {
        -1, 0, 1,
        -1, 0, 1,
        -1, 0, 1
    };

    const cv::Mat kx(cv::Size(3, 3), CV_8S, x_values);
    const cv::Mat ky(cv::Size(3, 3), CV_8S, y_values);

    cv::filter2D(gray, temp_x, -1, kx);
    cv::filter2D(gray, temp_y, -1, ky);

    dest->mat = temp_x + temp_y;
    cv::convertScaleAbs(dest->mat, dest->mat);

    return dest;
}

Image* Image::sobel(int x, int y, int size) const {
    auto dest = toGray();
    cv::Sobel(mat, dest->mat, CV_16U, x, y, size);
    cv::convertScaleAbs(dest->mat, dest->mat);
    return dest;
}

Image* Image::log() const {
    auto dest = new Image();
    const auto gray = toGrayMat();

	gray.convertTo(dest->mat, CV_32F);
	dest->mat = dest->mat + 1;
	cv::log(dest->mat, dest->mat);
	cv::normalize(dest->mat, dest->mat, 0, 255, cv::NORM_MINMAX);
	cv::convertScaleAbs(dest->mat, dest->mat);

    return dest;
}

Image* Image::zerocross() const {
	const cv::Mat filter = cv::getStructuringElement(cv::MORPH_RECT, {3, 3});
	cv::Mat min, max;
    auto dest = toGray();
	cv::Laplacian(mat, dest->mat, CV_16S, 3);
	dest->mat = toGrayMat();
	
	/*
	dest->mat.forEach<uint8_t>(
		[](uint8_t &pixel, const int* po) {
			pixel = 128;
		});
	return dest;
	*/

	cv::morphologyEx(dest->mat, min, cv::MORPH_ERODE, filter);
	cv::morphologyEx(dest->mat, max, cv::MORPH_DILATE, filter);
	
	debug (max.rows << ',' << max.cols << '\n');
	for (int i = 0; i < dest->mat.rows; i++) {
		for (int j = 0; j < dest->mat.cols; j++) {
			const auto actual_val = dest->mat.at<int16_t>(i, j);
			const auto min_val = min.at<int16_t>(i, j);
			const auto max_val = max.at<int16_t>(i, j);

			const bool is_min = (min_val < 0 && actual_val > 0);
			const bool is_max = (max_val > 0 && actual_val < 0);
			const bool resp = (is_min || is_max);
			dest->mat.at<int16_t>(i, j) = (resp? 255 : 0);
		}
	}
	debug("Sai do for\n");
	cv::convertScaleAbs(dest->mat, dest->mat);
	return dest;
}

Image* Image::noise(const double noise_probability) const {
    auto dest = new Image();
    int image_channels = mat.channels();
    uint64_t noise_points = noise_probability * mat.rows * mat.cols;
	
	dest->mat = mat.clone();

    for (long i = 0; i < noise_points; i++) {
        int row = rand() % dest->mat.rows;
        int column = rand() % dest->mat.cols;

		memset(
			dest->mat.ptr(row) + (column * image_channels),
			(rand() % 2) ? 255 : 0,
			image_channels
		);
    }
	return dest;
}

Image* Image::watershed() const {
    if (mat.channels() != 1) {
        std::cerr << "A imagem não está limiarizada\n";
        return nullptr;
    }
    auto dest = new Image();

	return dest;
}

Image* Image::histogram() const {
    // definições para gerar o histograma
    int size = 256;
    int hist_w = 800;
    int hist_h = 600;
    int bin_w = cvRound((double)hist_w / size);
    float range[2] = {0, 256};
    const float *const_acess = range;
    cv::Mat hist_image(hist_h, hist_w, CV_8UC3, cv::Scalar(0, 0, 0));

    auto dest = new Image();
    if (mat.channels() == 3) { // eh uma imagem bgr
        cv::Mat red_hist, green_hist, blue_hist;
        std::vector<cv::Mat> bgr_mat_vet;

        bgr_mat_vet.reserve(3);
        cv::split(mat, bgr_mat_vet);
        cv::calcHist(&bgr_mat_vet.at(0), 1, 0, cv::Mat(), blue_hist, 1, &size, &const_acess);
        cv::calcHist(&bgr_mat_vet.at(1), 1, 0, cv::Mat(), green_hist, 1, &size, &const_acess);
        cv::calcHist(&bgr_mat_vet.at(2), 1, 0, cv::Mat(), red_hist, 1, &size, &const_acess);

        cv::normalize(blue_hist, blue_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
        cv::normalize(green_hist, green_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
        cv::normalize(red_hist, red_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());

        for (int i = 1; i < size; i++) {
            cv::line (
                hist_image,
                cv::Point(bin_w * (i - 1), hist_h - cvRound(blue_hist.at<float>(i - 1))),
                cv::Point(bin_w * (i), hist_h - cvRound(blue_hist.at<float>(i))),
                COLOR_BLUE_SCALAR,
                2
            );
            cv::line (
                hist_image,
                cv::Point(bin_w * (i - 1), hist_h - cvRound(green_hist.at<float>(i - 1))),
                cv::Point(bin_w * (i), hist_h - cvRound(green_hist.at<float>(i))),
                COLOR_GREEN_SCALAR,
                2
            );
            cv::line (
                hist_image,
                cv::Point(bin_w * (i - 1), hist_h - cvRound(red_hist.at<float>(i - 1))),
                cv::Point(bin_w * (i), hist_h - cvRound(red_hist.at<float>(i))),
                COLOR_RED_SCALAR,
                2
            );
        }
    }else {
        cv::Mat gray_hist;
        cv::calcHist(&mat, 1, 0, cv::Mat(), gray_hist, 1, &size, &const_acess);
        cv::normalize(gray_hist, gray_hist, 0, hist_image.rows, cv::NORM_MINMAX, -1, cv::Mat());
        for (int i = 1; i < size; i++) {
            cv::line (
                hist_image,
                cv::Point(bin_w * (i - 1), hist_h - cvRound(gray_hist.at<float>(i - 1))),
                cv::Point(bin_w * (i), hist_h - cvRound(gray_hist.at<float>(i))),
                COLOR_GRAY_SCALAR,
                2
            );
        }
    }

    dest->mat = hist_image;
	return dest;
}

Image* Image::histogramAjust() const {
    auto dest = new Image();
    if (mat.channels() == 1) {
        dest->mat = mat.clone();
    }else {
        cv::cvtColor(mat, dest->mat, cv::COLOR_BGR2GRAY);
    }
    cv::equalizeHist(dest->mat, dest->mat);
    return dest;
}

Image* Image::count(uint16_t &qnt) const {
    qnt = 4;
    return toGray();
}

Image* Image::laplacian(uint16_t kernal_size) const {
    auto dest = toGray();
	cv::Laplacian(mat, dest->mat, CV_16S, kernal_size);
	cv::convertScaleAbs(dest->mat, dest->mat);
	return dest;
}

const cv::Mat& Image::getMat() const { return mat; }

wxImage Image::toWxImage() const {
    cv::Mat temp_mat;
    if (mat.channels() == 1) {
        debug("Convertendo para imagem com 1 canal\n");
        cv::cvtColor(mat, temp_mat, cv::COLOR_GRAY2RGB);
    } else if (mat.channels() == 4) {
        debug("Convertendo para imagem com 4 canais\n");
        cv::cvtColor(mat, temp_mat, cv::COLOR_BGRA2RGB);
    } else {  // 3 canais = BGR no opencv
        debug("Convertendo para imagem com " << mat.channels() << " canais\n");
        cv::cvtColor(mat, temp_mat, cv::COLOR_BGR2RGB);
    }
    size_t img_size = temp_mat.rows * temp_mat.cols * temp_mat.channels();
    wxImage wx(
		temp_mat.cols, temp_mat.rows,
		(unsigned char*)malloc(img_size),
        false
	);
    memcpy(wx.GetData(), temp_mat.data, img_size);
    return wx;
}