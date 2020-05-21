#pragma once
#include <memory>
#include <vector>

class SearchCell;
class Enemy;

class AStar {
public:
	AStar();

	void findPath(std::tuple<int, int>, std::tuple<int, int>);
	std::tuple<int, int> nextPathPosition();
	void clearOpenList();
	void clearClosedList();
	void clearPathToGoal();
	bool areStartGoalInitialized();
	bool isGoalFound();
private:
	bool goalFound = false;
	bool startGoalInitialized = false;
	std::shared_ptr<SearchCell> start;
	std::shared_ptr<SearchCell> goal;
	std::vector<std::shared_ptr<SearchCell>> openList;
	std::vector<std::shared_ptr<SearchCell>> closedList;
	std::vector<std::tuple<int, int>> pathToGoal;

	void setStartGoal(SearchCell&, SearchCell&);
	void pathOpen(int x, int y, float newCost, std::shared_ptr<SearchCell> parent);
	std::shared_ptr<SearchCell> getNextCell();
	void continuePath();
};