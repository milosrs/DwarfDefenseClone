#include "../Header/WorldObject.h"
#include "../../Dependencies/rapidjson/writer.h"
#include <iostream>
#include <fstream>

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

std::ofstream& operator<<(std::ofstream& os, WorldObject& wo) {
	os << wo.name;
	os << " ";
	os << (char)wo.objectType;
	os << " ";
	os << std::get<0>(wo.position);
	os << " ";
	os << std::get<1>(wo.position);
	os << std::endl;

	return os;
}