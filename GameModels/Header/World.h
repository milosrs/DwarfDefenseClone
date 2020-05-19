#pragma once
#include <vector>
#include <memory>
#include <ostream>
#include <tuple>

#include "WorldObject.h"

class World{
private:
	std::vector<WorldObject*> objects;
	std::string impassables = "#!@";
	char** map;
	int width;
	int height;

	void drawItemsOnMap();
	void drawBoundaries();
	void drawItem(WorldObject*);
public:
	World() = default;
	World(std::vector<WorldObject*>, int, int);
	World(const World&);

	char** getMap();
	void addObject(WorldObject*);

	friend std::ostream& operator<<(std::ostream&, World&);
};