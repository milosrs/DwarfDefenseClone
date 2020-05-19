#include "../Header/Player.h"

Player::Player(std::vector<Item*> items, double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType) 
	: items(items), Character(maxHp, hp, dmg, armor, position, name, objectType) {

	for (Item* i : items) {
		if (i->getItemType() == ItemType::EQUIPABLE) {
			this->armor += i->getArmorBonus();
			this->damage += i->getDamageBonus();
			this->health += i->getHPBonus();
			this->maxHealth += i->getHPBonus();
		}
	}
};

void Player::addNewItem(Item& item) {
	if (item.getItemType() == ItemType::EQUIPABLE) {
		this->armor += item.getArmorBonus();
		this->damage += item.getDamageBonus();
		this->maxHealth += item.getHPBonus();
		this->health += item.getHPBonus();
	}
}

void Player::useConsumable(int index) {
	if (items[index]->getItemType() == ItemType::CONSUMABLE) {
		this->health += items[index]->getHPBonus();
		items.erase(items.begin(), items.begin() + index);
	}
}

std::ostream& operator<<(std::ostream& os, Player& p) {
	os << "******** Player stats ********** " << std::endl
		<< "Name: " << p.name << std::endl
		<< "Max HP: " << p.maxHealth << std::endl
		<< "Current HP: " << p.health << std::endl
		<< "DMG: " << p.damage << std::endl
		<< "Armor: " << p.armor << std::endl
		<< "Item count: " << p.items.size() << std::endl;

	return os;
}