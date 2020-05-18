#pragma once
#include "WorldObject.h"

class Character : public WorldObject {
protected:
	double maxHealth;
	double health;
	double damage;
	double armor;
public:
	void move(int, MoveDirection);
	void fight(Character&);
	void receiveDamage(double);
};