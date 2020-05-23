#pragma once
#include <vector>
#include <memory>
#include <ostream>
#include <tuple>


#include "../Header/WorldObject.h"
#include "../Header/Player.h"
#include "../Header/Enemy.h"
#include "../../Enums/TurnResult.h"
#include "../../AI/Headers/AStar.h"

class World{
private:
	std::unique_ptr<Player> player;
	std::vector<std::unique_ptr<WorldObject>> objects;
	char** map;
	SearchCell** aiMap;
	int width;
	int height;
	AStar ai;

	void drawWorld(std::string);
	void drawBoundaries();
	std::unique_ptr<Item> createItem(std::tuple<int, int>, int = 0);
	std::tuple<int, int> getFirstFreeCoordinate(int, int);
	std::tuple<int, int> generatePosition();
	void createAIMap();
public:
	World() = default;
	World(int, int, std::string);

	void movePlayer(MoveDirection);
	void moveEnemies();
	void deleteDeadEnemies();
	void redrawWorld();
	void useConsumable(int index);
	TurnResult colide(Character* character, std::vector<std::unique_ptr<WorldObject>>::iterator wo);
	char** getMap();

	friend std::ostream& operator<<(std::ostream&, World&);
};