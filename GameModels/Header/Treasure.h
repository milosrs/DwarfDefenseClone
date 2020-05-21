#pragma once
#include <vector>

#include "WorldObject.h"
#include "Item.h"

class Treasure : public WorldObject {
private:
	std::vector<std::unique_ptr<Item>> items;
public:
	Treasure() = default;
	Treasure(std::vector<std::unique_ptr<Item>> items, std::tuple<int, int> position, std::string name, WorldObjectType objectType);

	std::vector<std::unique_ptr<Item>> getItems();
};