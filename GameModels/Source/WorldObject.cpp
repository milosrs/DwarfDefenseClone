#include "../Header/WorldObject.h"

WorldObject::WorldObject(std::tuple<int, int> position, std::string name, WorldObjectType objectType): position(position), name(name), objectType(objectType) {
}

std::tuple<int, int> WorldObject::getPosition() {
	return this->position;
}

std::string WorldObject::getName() {
	return this->name;
}

WorldObjectType WorldObject::getObjectType() {
	return this->objectType;
}

void WorldObject::setPosition(std::tuple<int, int> position) {
	this->position = position;
}

void WorldObject::setName(std::string name) {
	this->name = name;
}

void WorldObject::setObjectType(WorldObjectType objectType) {
	this->objectType = objectType;
}