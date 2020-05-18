#pragma once
#include <vector>

#include "Character.h"
#include "Item.h"

class Player : public Character {
public:
	void addNewItem(Item& item);
	void useConsumable(int);
private:
	std::vector<Item> items;
};