// DwarfDefenseClone.cpp : Defines the entry point for the application.
//

#include <cstdlib>
#include <ctime>

#include "DwarfDefenseClone.h"
#include "GameModels/Header/Player.h"
#include "GameModels/Header/Enemy.h"
#include "GameModels/Header/Item.h"
#include "GameModels/Header/World.h"

using namespace std;

struct Stats {
	double dmg = (double)(std::rand() % 20 + 1);
	double armor = (double)(std::rand() % 30 + 1);
	double hp = (double)(std::rand() % 15 + 1);
}typedef STATS;

std::tuple<int, int> generatePosition(int w, int h) {
	int px = rand() % w;
	int py = rand() % h;

	return std::tuple<int, int>(px, py);
}

std::vector<Item*> generateItems(int w, int h) {
	std::vector<Item*> ret;
	STATS randomStats1;
	STATS randomStats2;
	STATS randomStats3;

	ret.push_back(new Item(0, randomStats1.dmg, 0, ItemType::EQUIPABLE, generatePosition(w, h), "sword", WorldObjectType::WEAPON));
	ret.push_back(new Item(0, randomStats2.dmg, 0, ItemType::EQUIPABLE, generatePosition(w, h), "mace", WorldObjectType::WEAPON));
	ret.push_back(new Item(randomStats1.armor, 0, 0, ItemType::EQUIPABLE, generatePosition(w, h), "bulk armor", WorldObjectType::ARMOR));
	ret.push_back(new Item(randomStats2.armor, 0, randomStats2.hp, ItemType::EQUIPABLE, generatePosition(w, h), "holy armor", WorldObjectType::ARMOR));
	ret.push_back(new Item(0, 0, randomStats1.hp, ItemType::CONSUMABLE, generatePosition(w, h), "potion", WorldObjectType::TREASURE));
	ret.push_back(new Item(0, 0, randomStats2.hp, ItemType::CONSUMABLE, generatePosition(w, h), "potion", WorldObjectType::TREASURE));

	return ret;
}



int main()
{
	srand(time(NULL));
	int width = rand() % 50 + 1;
	int height = rand() % 50 + 1;

	std::vector<WorldObject*> wo;
	std::vector<Item*> items = generateItems(width, height);
	
	Player p(items, 100, 100, 5, 3, generatePosition(width, height), "Rixon", WorldObjectType::PLAYER);
	Enemy e(items[0], 100, 100, 5, 3, generatePosition(width, height), "Enemy of God!", WorldObjectType::ENEMY);

	wo.insert(wo.begin(), items.begin(), items.end());
	wo.push_back(&p);
	wo.push_back(&e);

	World w(wo, width, height);
	
	//Draw the world without obstacles
	std::cout << w << std::endl;

	//Print stats of chars and make them fight
	std::cout << p << std::endl;
	std::cout << e << std::endl;
	std::cout << "Round 1.... FIGHT!" << std::endl << std::endl << std::endl;

	p.fight(e);

	std::cout << p << std::endl;
	std::cout << e << std::endl;

	

	return 0;
}

