#include "../Headers/SearchCell.h"
#include <boost/functional/hash.hpp>

SearchCell::SearchCell(int x, int y, char sign, std::shared_ptr<SearchCell> parent) : x(x), y(y), sign(sign), parent(parent), G(0), H(0) {}

float SearchCell::getF() {
	return G + H;
}

float SearchCell::manhattanDistance(SearchCell* endCell) {
	float xPoints = (float)(fabs(x - endCell->x));
	float yPoints = (float)(fabs(y - endCell->y));

	return xPoints + yPoints;
}

std::tuple<int, int> SearchCell::generateId(int x, int y) {
	return std::tuple<int, int>(x, y);
}