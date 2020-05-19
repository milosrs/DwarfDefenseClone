#pragma once
#include <ostream>

#include "Character.h"
#include "Item.h"

class Enemy : public Character {
private:
	Item* loot;
public:
	Enemy() = default;
	Enemy(Item* loot, double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType);

	friend std::ostream& operator<<(std::ostream&, Enemy&);

	Item* getLoot();
};