#include "image.hpp"

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
    cv::cvtColor(mat, dest->mat, cv::COLOR_BGR2GRAY);
    return dest;
}

Image* Image::roberts() const {}

Image* Image::prewitt() const {}

Image* Image::sobel(int x, int y, int size) const {
    auto dest = new Image();
    cv::Sobel(mat, dest->mat, CV_8U, x, y, size);
    return dest;
}

Image* Image::log() const {}

Image* Image::zerocross() const {}

Image* Image::noise(const double noise_probability) const {
    auto dest = new Image();
    int image_channels = mat.channels();
    uint64_t noisePoints =
        noise_probability * mat.rows * mat.cols * image_channels;
	
	dest->mat = mat.clone();

    for (long i = 0; i < noisePoints; i++) {
        int row = rand() % dest->mat.rows;
        int column = rand() % dest->mat.cols;
        int channel = rand() % image_channels;

        auto pixel = dest->mat.ptr(row) + (column * image_channels);

        *pixel = (rand() % 2) ? 255 : 0;
    }
	return dest;
}

Image* Image::watershed() const {}

Image* Image::histogram() const {}

Image* Image::histogramAjus() const {}

Image* Image::count() const {}

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
        // eu precisava copiar os dados sem fazer mudanca de cor,
        // mas tava dando seg foult
        cv::cvtColor(mat, temp_mat, cv::COLOR_BGR2RGB);
        // cv::cvtColor(temp_mat, temp_mat, cv::COLOR_RGB2BGR);
        // temp_mat = cv::Mat(mat, true);
    }

    size_t img_size = temp_mat.rows * temp_mat.cols * temp_mat.channels();
    wxImage wx(temp_mat.cols, temp_mat.rows, (unsigned char*)malloc(img_size),
               false);
    memcpy(wx.GetData(), temp_mat.data, img_size);
    return wx;
}