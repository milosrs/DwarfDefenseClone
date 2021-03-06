#include "../Header/Enemy.h"
Enemy::Enemy(std::unique_ptr<Item> loot, double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType) :
	loot(std::move(loot)), Character(maxHp, hp, dmg, armor, position, name, objectType) {
	
	if (loot->getItemType() == ItemType::EQUIPABLE) {
		this->armor += loot->getArmorBonus();
		this->damage += loot->getDamageBonus();
		this->health += loot->getHPBonus();
		this->maxHealth += loot->getHPBonus();
	}
};

Enemy::Enemy(double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType):
	Character(maxHp, hp, dmg, armor, position, name, objectType){}

std::ostream& operator<<(std::ostream& os, Enemy& p) {
	os << "******** Enemy stats ********** " << std::endl
		<< "Name: " << p.name << std::endl
		<< "Max HP: " << p.maxHealth << std::endl
		<< "Current HP: " << p.health << std::endl
		<< "DMG: " << p.damage << std::endl
		<< "Armor: " << p.armor << std::endl;

	return os;
}

std::unique_ptr<Item> Enemy::getLoot() {
	return std::move(loot);
}

std::string Enemy::toString(Enemy& p) {
	std::string ret = std::string("******** Enemy stats ********** ").append("\n")
		.append("Name: ").append(p.name).append("\n")
		.append("Max HP: ").append(std::to_string(p.maxHealth)).append("\n")
		.append("Current HP: ").append(std::to_string(p.health)) .append("\n")
		.append("DMG: ").append(std::to_string(p.damage)).append("\n")
		.append("Armor: ").append(std::to_string(p.armor)).append("\n");

	return ret;
}

std::ofstream& operator<<(std::ofstream& os, Enemy& wo) {
	os << *(wo.loot.get());

	return os;
}