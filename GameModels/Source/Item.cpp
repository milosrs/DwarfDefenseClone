#include "../Header/Item.h"

Item::Item(double armorBonus, double dmgBonus, double hpBonus, ItemType itemType, std::tuple<int, int> position, std::string name, WorldObjectType objectType) : 
	armorBonus(armorBonus), damageBonus(dmgBonus), hpBonus(hpBonus), itemType(itemType), WorldObject(position, name, objectType) {
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