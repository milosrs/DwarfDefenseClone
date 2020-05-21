#include "../Header/Treasure.h"

Treasure::Treasure(std::vector<std::unique_ptr<Item>> items, std::tuple<int, int> position, std::string name, WorldObjectType objectType): 
	items(std::move(items)), WorldObject(position, name, objectType)
{

}