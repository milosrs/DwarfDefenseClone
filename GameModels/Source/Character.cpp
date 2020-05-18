#include "../Header/Character.h"

void Character::move(int cells, MoveDirection direction) {
	switch (direction) {
		case MoveDirection::UP: std::get<1>(this->position) += cells; break;
		case MoveDirection::DOWN: std::get<1>(this->position) -= cells; break;
		case MoveDirection::LEFT: std::get<0>(this->position) -= cells; break;
		case MoveDirection::RIGHT: std::get<0>(this->position) += cells; break;
	}
}

void Character::fight(Character& target) {
	double damage = this->damage - target.armor;
	target.receiveDamage(damage);
}

void Character::receiveDamage(double damage) {
	this->health -= damage;
}