#include "../Headers/Astar.h"
#include "../Headers/SearchCell.h"
#include "../../GameModels/Header/Enemy.h"
#include "../../Enums/WorldObjectType.h"
#include <list>
#include <tuple>

AStar::AStar() {}

void AStar::findPath(std::tuple<int, int> current, std::tuple<int, int> goal) {
	if (!startGoalInitialized) {
		openList.clear();
		closedList.clear();
		pathToGoal.clear();

		start = std::make_shared<SearchCell>(std::get<0>(current), std::get<1>(current), 'E', nullptr);
		this->goal = std::make_shared<SearchCell>(std::get<0>(goal), std::get<1>(goal), 'P', nullptr);
		startGoalInitialized = true;
		start->G = 0;
		start->H = start->manhattanDistance(this->goal.get());
		start->parent = nullptr;

		openList.push_back(start);
	}
}

std::shared_ptr<SearchCell> AStar::getNextCell() {
	float bestF = 999999.0;
	int cellIndex = -1;
	std::shared_ptr<SearchCell> nextCell;

	for (int i = 0; i < openList.size(); ++i) {
		if (openList[i]->getF() < bestF) {
			bestF = openList[i]->getF();
			cellIndex = i;
		}
	}

	if (cellIndex >= 0) {
		nextCell = openList[cellIndex];
		closedList.push_back(nextCell);
		openList.erase(openList.begin() + cellIndex);
	}

	return nextCell;
}

void AStar::pathOpen(int x, int y, float newCost, std::shared_ptr<SearchCell> parent) {
	//IF cell is blocked, you dont need to check anything
	if (parent->sign != (char)WorldObjectType::PLAYER || parent->sign != (char)WorldObjectType::EMPTY) {
		return;
	}

	//Cell already visited
	std::tuple<int, int> id = SearchCell::generateId(x, y);
	for (int i = 0; i < closedList.size(); ++i) {
		if (std::get<0>(id) == closedList[i]->x && std::get<1>(id) == closedList[i]->y) {
			return;
		}
	}

	std::shared_ptr<SearchCell> newChild = std::make_shared<SearchCell>(x, y, ' ', parent);
	newChild->G = newCost;
	newChild->H = parent->manhattanDistance(goal.get());

	for (int i = 0; i < openList.size(); ++i) {
		if (std::get<0>(id) == openList[i]->x && std::get<1>(id) == openList[i]->y) {
			float newF = newChild->G + newCost + openList[i]->H;

			if (openList[i]->getF() > newF) {
				openList[i]->G = newChild->G + newCost;
				openList[i]->parent = parent;
			}
			else {
				newChild.~shared_ptr();
				return;
			}
		}
	}

	openList.push_back(newChild);
}

void AStar::continuePath() {
	if (openList.empty()) {
		return;
	}

	std::shared_ptr<SearchCell> current = getNextCell();

	if (current->x == goal->x && current->y == goal->y) {
		goal->parent = current;
		std::shared_ptr<SearchCell> path;

		for (path = goal; path != nullptr; path = path->parent) {
			pathToGoal.push_back(std::tuple<int, int>(path->x, path->y));
		}

		goalFound = true;
	}
	else {
		pathOpen(current->x + 1, current->y, current->G + 1, current);	//RIGHT
		pathOpen(current->x, current->y + 1, current->G + 1, current);	//UP
		pathOpen(current->x - 1, current->y, current->G + 1, current);	//LEFT
		pathOpen(current->x, current->y - 1, current->G + 1, current);	//DOWN

		for (int i = 0; i < openList.size(); ++i) {
			if (current->x == openList[i]->x && current->y == openList[i]->y) {
				openList.erase(openList.begin() + i);
			}
		}
	}
}

std::tuple<int, int> AStar::nextPathPosition() {
	int index = 1;
	std::tuple<int, int> nextPos;
	std::tuple<int, int> distance;

	std::get<0>(nextPos) = closedList[closedList.size() - index]->x;
	std::get<1>(nextPos) = closedList[closedList.size() - index]->y;
	std::get<0>(distance) = std::get<0>(nextPos) - goal->x;
	std::get<1>(distance) = std::get<1>(nextPos) - goal->y;

	return nextPos;
}