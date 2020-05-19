#pragma once
#include <vector>
#include <ostream>

#include "Character.h"
#include "Item.h"

class Player : public Character {
private:
	std::vector<Item*> items;

public:
	Player() = default;
	Player(std::vector<Item*> items, double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType);

	void addNewItem(Item& item);
	void useConsumable(int);

	friend std::ostream& operator<<(std::ostream&, Player&);
};