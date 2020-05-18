#include "../Header/WorldObject.h"

WorldObject::WorldObject(std::tuple<int, int> position, std::string name, WorldObjectType objectType) {
	this->position = position;
	this->name = name;
	this->objectType = objectType;
}

WorldObject::WorldObject(WorldObject& other) {
	this->position = other.position;
	this->name = other.name;
	this->objectType = other.objectType;
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