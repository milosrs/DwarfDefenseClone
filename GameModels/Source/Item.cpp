#include "../Header/Item.h"

Item::Item(double armorBonus, double dmgBonus, double hpBonus, ItemType itemType) : armorBonus(armorBonus), damageBonus(dmgBonus), hpBonus(hpBonus), itemType(itemType) {
}

Item::Item(Item& other): armorBonus(other.armorBonus), damageBonus(other.damageBonus), hpBonus(other.hpBonus), itemType(other.itemType) {
}

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