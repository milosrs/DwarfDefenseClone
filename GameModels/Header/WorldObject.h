#pragma once
#include <string>
#include <tuple>
#include <iostream>

#include "../../Enums/WorldObjectType.h"
#include "../../Enums/MoveDirection.h"

class WorldObject {
protected:
	std::tuple<int, int> position;
	std::string name;
	WorldObjectType objectType;

public:
	WorldObject() = default;
	WorldObject(std::tuple<int, int>, std::string, WorldObjectType);
	WorldObject(WorldObject&);

	void setPosition(std::tuple<int, int>);
	void setName(std::string name);
	void setObjectType(WorldObjectType);

	std::tuple<int, int> getPosition();
	std::string getName();
	WorldObjectType getObjectType();
};