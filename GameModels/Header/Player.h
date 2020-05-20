#pragma once
#include <vector>
#include <ostream>
#include <memory>

#include "Character.h"
#include "Item.h"

class Player : public Character {
private:
	std::vector<std::shared_ptr<Item>> items = { nullptr };

public:
	Player() = default;
	Player(std::vector<std::shared_ptr<Item>> items, double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType);
	Player(double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType);

	void addNewItem(std::shared_ptr<Item> item);
	void useConsumable(int);

	friend std::ostream& operator<<(std::ostream&, Player&);
};