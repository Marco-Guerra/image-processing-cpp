#ifndef IMAGE_HISTORY
#define IMAGE_HISTORY

#include <list>
#include "image.hpp"
#include "../utils/debug.hpp"

class ImageHistory {
private:
	std::list<Image> history;
	std::list<Image>::const_iterator current;

	std::list<Image>::const_iterator getLast();
public:
	ImageHistory();
	ImageHistory(const Image& fisrt);

	// Insere no fim da lista
	void add(const Image& fisrt);

	// remove desde o iterador ate o fim
	void remove();
	bool isOnTop();

	bool next();
	bool previus();

	const Image& getCurrent();
	~ImageHistory();
};

#endif // IMAGE_HISTORY
