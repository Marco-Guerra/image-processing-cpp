#include "image_history.hpp"

std::list<Image>::const_iterator ImageHistory::getLast() {
	auto temp = history.cend();
	return --temp;
}

ImageHistory::ImageHistory() : history(), current() {
}

ImageHistory::ImageHistory(const Image& fisrt) : history(), current() {
	add(fisrt);
}

void ImageHistory::add(const Image& fisrt) {
	history.push_back(fisrt);
	current = getLast();
}

void ImageHistory::remove() {
    history.erase(current, history.cend());
}

bool ImageHistory::isOnTop() {
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

const Image& ImageHistory::getCurrent() {
	return *current;
}

ImageHistory::~ImageHistory() {
    
}
