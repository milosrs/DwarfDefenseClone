#include "../Header/Enemy.h"
Enemy::Enemy(Item* loot, double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType) :
	loot(loot), Character(maxHp, hp, dmg, armor, position, name, objectType) {
	
	if (loot->getItemType() == ItemType::EQUIPABLE) {
		this->armor += loot->getArmorBonus();
		this->damage += loot->getDamageBonus();
		this->health += loot->getHPBonus();
		this->maxHealth += loot->getHPBonus();
	}
};


std::ostream& operator<<(std::ostream& os, Enemy& p) {
	os << "******** Enemy stats ********** " << std::endl
		<< "Name: " << p.name << std::endl
		<< "Max HP: " << p.maxHealth << std::endl
		<< "Current HP: " << p.health << std::endl
		<< "DMG: " << p.damage << std::endl
		<< "Armor: " << p.armor << std::endl;

	return os;
}

Item* Enemy::getLoot() {
	return loot;
}