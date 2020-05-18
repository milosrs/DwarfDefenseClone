#pragma once
#include "WorldObject.h"
#include "../../Enums/ItemType.h"

class Item : public WorldObject {
private:
	ItemType itemType;
	double armorBonus;
	double damageBonus;
	double hpBonus;
public:
	Item() = default;
	Item(double, double, double, ItemType);
	Item(Item&);

	ItemType getItemType();
	double getArmorBonus();
	double getDamageBonus();
	double getHPBonus();
};