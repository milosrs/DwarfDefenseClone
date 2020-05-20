#pragma once
#include <ostream>

#include "Character.h"
#include "Item.h"

class Enemy : public Character {
private:
	std::shared_ptr<Item> loot = nullptr;
public:
	Enemy() = default;
	Enemy(std::shared_ptr<Item> loot, double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType);
	Enemy(double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType);

	friend std::ostream& operator<<(std::ostream&, Enemy&);

	std::shared_ptr<Item> getLoot();
};