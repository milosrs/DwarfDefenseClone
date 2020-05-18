#include "../Header/Player.h"

void Player::addNewItem(Item& item) {
	if (item.getItemType() == ItemType::EQUIPABLE) {
		this->armor += item.getArmorBonus();
		this->damage += item.getDamageBonus();
		this->maxHealth += item.getHPBonus();
		this->health += item.getHPBonus();
	}
}

void Player::useConsumable(int index) {
	if (items[index].getItemType() == ItemType::CONSUMABLE) {
		this->health += items[index].getHPBonus();
		items.erase(items.begin(), items.begin() + index);
	}
}