#pragma once
#include "WorldObject.h"
#include "../../Enums/ItemType.h"
#include <iostream>
#include <fstream>

class Item : public WorldObject {
private:
	ItemType itemType;
	double armorBonus;
	double damageBonus;
	double hpBonus;
public:
	Item() = default;
	Item(double, double, double, ItemType, std::tuple<int, int> position, std::string name, WorldObjectType objectType);
	Item(Item*);

	ItemType getItemType();
	double getArmorBonus();
	double getDamageBonus();
	double getHPBonus();

	friend std::ostream& operator<<(std::ostream&, Item&);
	friend std::ofstream& operator<<(std::ofstream&, Item&);
};