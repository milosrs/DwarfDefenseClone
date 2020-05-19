#pragma once
#include "WorldObject.h"

class World;

class Character : public WorldObject {
protected:
	double maxHealth;
	double health;
	double damage;
	double armor;
public:
	Character() = default;
	Character(double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType);

	void move(int, MoveDirection);
	void fight(Character&);
	bool receiveDamage(double);
};