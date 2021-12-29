#include "image_history.hpp"

std::list<Image *>::const_iterator ImageHistory::getLast() {
	auto temp = history.cend();
	temp--;
	return temp;
}

ImageHistory::ImageHistory() : history(), current() {
}

ImageHistory::ImageHistory(Image *fisrt) : history(), current() {
	add(fisrt);
}

void ImageHistory::add(Image *const fisrt) {
	if (!isOnTop()) {
		remove();
	}
	history.push_back(fisrt);
	current = getLast();
}

void ImageHistory::remove() {
	current++;
	// apaga do current incluindo o mesmo ate o fim
    history.erase(current, history.cend());
}

bool ImageHistory::isOnTop() {
	if (history.empty()) {
		return true;
	}
	return current == getLast();
}

bool ImageHistory::next() {
	if (isOnTop()) {
		return false;
	}
	current++;
	return true;
}

bool ImageHistory::previus() {
	if (current == history.cbegin()) {
		return false;
	}
	current--;
	return true;
}

const Image* ImageHistory::getCurrent() const {
	return *current;
}

void ImageHistory::clean() {
    for (auto it : history) {
		delete it;
	}
	history.clear();
}

ImageHistory::~ImageHistory() {
	clean();
}
