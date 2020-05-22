#include "../Header/Player.h"

Player::Player(std::vector<std::unique_ptr<Item>> items, double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType)
	: items(std::move(items)), Character(maxHp, hp, dmg, armor, position, name, objectType) {

	for (const auto& i : items) {
		if (i->getItemType() == ItemType::EQUIPABLE) {
			this->armor += i->getArmorBonus();
			this->damage += i->getDamageBonus();
			this->health += i->getHPBonus();
			this->maxHealth += i->getHPBonus();
		}
	}
};

Player::Player(double maxHp, double hp, double dmg, double armor, std::tuple<int, int> position, std::string name, WorldObjectType objectType) : Character(maxHp, hp, dmg, armor, position, name, objectType) {
}

void Player::addNewItem(std::unique_ptr<Item> item) {
	if (item->getItemType() == ItemType::EQUIPABLE) {
		this->armor += item->getArmorBonus();
		this->damage += item->getDamageBonus();
		this->maxHealth += item->getHPBonus();
		this->health += item->getHPBonus();
	}

	turnStatus.append(name).append(" acquired ").append(item->getName()).append("\n");
	items.push_back(std::move(item));
}

void Player::useConsumable(int index) {
	if (items[index]->getItemType() == ItemType::CONSUMABLE) {
		turnStatus.append(name).append(" used ").append(items[index]->getName()).append("\n");
		
		this->health += items[index]->getHPBonus();
		items.erase(items.begin() + index);
	}
}

std::ostream& operator<<(std::ostream& os, Player& p) {
	os << "******** Player stats ********** " << std::endl
		<< "Name: " << p.name << std::endl
		<< "Max HP: " << p.maxHealth << std::endl
		<< "Current HP: " << p.health << std::endl
		<< "DMG: " << p.damage << std::endl
		<< "Armor: " << p.armor << std::endl
		<< "-----------Items------------ " << std::endl << std::endl
		<< std::endl << p.turnStatus << std::endl;

	for (std::unique_ptr<Item>& i : p.items) {
		os << (*(i.get()));
	}

	p.turnStatus = "";

	return os;
}