#include "../Headers/Astar.h"
#include "../../GameModels/Header/Enemy.h"
#include <list>
#include <tuple>

MoveDirection AStar::getOptimalMove(char**, int h, int w, Enemy* e) {
	int H = (h - 1) * (w - 1);

	std::list<std::tuple<int, int>> openList;
	openList.push_back(e->getPosition());

	/*do {
			
	}*/

	return MoveDirection::DOWN;
}