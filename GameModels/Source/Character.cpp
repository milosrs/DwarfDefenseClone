#include "../Header/Character.h"
#include "../Header/Item.h"
#include "../Header/World.h"

Character::Character(double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType) :
	maxHealth(maxHp), health(hp), damage(dmg), armor(armor), WorldObject(position, name, objectType) {

};

void Character::move(int cells, MoveDirection direction) {
	switch (direction) {
		case MoveDirection::UP: std::get<1>(this->position) += cells; break;
		case MoveDirection::DOWN: std::get<1>(this->position) -= cells; break;
		case MoveDirection::LEFT: std::get<0>(this->position) -= cells; break;
		case MoveDirection::RIGHT: std::get<0>(this->position) += cells; break;
	}
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