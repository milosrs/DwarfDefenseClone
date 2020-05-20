#pragma once
#include <vector>
#include <memory>
#include <ostream>
#include <tuple>

#include "../Header/WorldObject.h"
#include "../Header/Player.h"
#include "../Header/Enemy.h"

class World{
private:
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<Character>> characters;
	std::vector<std::shared_ptr<Item>> items;
	std::vector<std::unique_ptr<WorldObject>> impassables;
	const std::string possibleImpassables = "#!@";
	char** map;
	int width;
	int height;

	void drawWorld();
	void drawBoundaries();
	std::shared_ptr<Item> createItem(std::tuple<int, int>, int = 0);
	std::tuple<int, int> getFirstFreeCoordinate(int, int);
	std::tuple<int, int> generatePosition();
public:
	World() = default;
	World(int, int);

	char** getMap();

	friend std::ostream& operator<<(std::ostream&, World&);
};