#pragma once
#include <vector>
#include <memory>
#include <ostream>
#include <tuple>

#include "../Header/WorldObject.h"
#include "../Header/Player.h"
#include "../Header/Enemy.h"
#include "../../Enums/TurnResult.h"

class World{
private:
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<WorldObject>> objects;
	char** map;
	int width;
	int height;

	void drawWorld();
	void drawBoundaries();
	std::unique_ptr<Item> createItem(std::tuple<int, int>, int = 0);
	std::tuple<int, int> getFirstFreeCoordinate(int, int);
	std::tuple<int, int> generatePosition();
public:
	World() = default;
	World(int, int);

	void movePlayer(MoveDirection);
	void redrawWorld();
	TurnResult colide(Character* character, std::vector<std::unique_ptr<WorldObject>>::iterator wo);
	char** getMap();

	friend std::ostream& operator<<(std::ostream&, World&);
};