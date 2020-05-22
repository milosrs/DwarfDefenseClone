#pragma once
#include <math.h>
#include <tuple>
#include <memory>
#include "../../Enums/WorldObjectType.h"

class SearchCell {
public:
	int x, y;
	char sign;
	std::shared_ptr<SearchCell> parent;
	float G;
	float H;

	SearchCell() = default;
	SearchCell(int, int, char, std::shared_ptr<SearchCell>);
	float getG();
	float getH();
	float getF();
	float manhattanDistance(SearchCell*);

	static std::tuple<int, int> generateId(int x, int y);
};