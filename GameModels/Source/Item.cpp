#include "../Header/Item.h"

Item::Item(double armorBonus, double dmgBonus, double hpBonus, ItemType itemType, std::tuple<int, int> position, std::string name, WorldObjectType objectType) : 
	armorBonus(armorBonus), damageBonus(dmgBonus), hpBonus(hpBonus), itemType(itemType), WorldObject(position, name, objectType) {
}

Item::Item(Item* other) : armorBonus(other->armorBonus), damageBonus(other->damageBonus), hpBonus(other->hpBonus), itemType(other->itemType), WorldObject(other->position, other->name, other->objectType)
{}

ItemType Item::getItemType() {
	return itemType;
}

double Item::getArmorBonus() {
	return armorBonus;
}

double Item::getDamageBonus() {
	return damageBonus;
}

double Item::getHPBonus() {
	return hpBonus;
}

std::ostream& operator<<(std::ostream& os, Item& i) {
	os << i.getName();

	if (i.getObjectType() != WorldObjectType::CONSUMABLE) {
		os << " -> ARM: " << i.getArmorBonus() << ", DMG: " << i.getDamageBonus() << ", HP: " << i.getHPBonus() << std::endl;
	}
	else {
		os << " -> Restores: " << i.getHPBonus() << std::endl;
	}

	return os;
}