#include "../Header/Character.h"
#include "../Header/Item.h"
#include "../Header/World.h"

Character::Character(double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType) :
	maxHealth(maxHp), health(hp), damage(dmg), armor(armor), WorldObject(position, name, objectType) {

};

bool Character::move(int cells, MoveDirection direction, int width, int height) {
	bool move = true;

	switch (direction) {
	case MoveDirection::UP: {
		move = std::get<1>(this->position) > 1;
		
		if (move)
			std::get<1>(this->position) -= cells;
	}; break;
	case MoveDirection::DOWN: {
		move = std::get<1>(this->position) < height - 2;
		
		if (move)
			std::get<1>(this->position) += cells;
	}; break;
	case MoveDirection::LEFT: {
		move = std::get<0>(this->position) > 1;

		if (move)
			std::get<0>(this->position) -= cells;
	}; break;
	case MoveDirection::RIGHT: {
		move = std::get<0>(this->position) < width - 2;

		if (move)
			std::get<0>(this->position) += cells;
	}; break;
	}

	return move;
}

void Character::fight(Character& target) {
	Item* loot = nullptr;

	double damageDealt = this->damage - target.armor;
	double damageReceived = target.damage - this->armor;

	receiveDamage(damageReceived);
	target.receiveDamage(damageDealt);
}

bool Character::receiveDamage(double damage) {
	this->health -= damage;

	return this->health <= 0;
}