#include "../Header/World.h"

World::World(int n, int m): height(n), width(m) {
	map = new char* [n];

	for (int i = 0; i < height; i++) {
		map[i] = new char[m];
	}
	
	drawBoundaries();
	drawWorld();
}

char** World::getMap() {
	return map;
}

std::ostream& operator<<(std::ostream& os, World& w) {
	os << std::endl;

	for (int i = 0; i < w.height; i++) {
		for (int j = 0; j < w.width; j++) {
			os << w.map[i][j];
		}

		os << std::endl;
	}

	return os;
}

void World::drawBoundaries() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
				map[i][j] = (char)WorldObjectType::MOUNTAIN;
			}
			else {
				bool shouldGenerateImpassable = (rand() % 100 + 1) > 80;

				if (shouldGenerateImpassable) {
					int impassableIndex = rand() % 3;
					map[i][j] = possibleImpassables[impassableIndex];
				}
				else {
					map[i][j] = ' ';
				}
			}
		}
	}
}

void World::drawWorld() {
	bool playerDrawn = false;
	int enemyCount = 0;
	int itemCount = 0;

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			bool shouldDrawPlayer = (rand() % 100 + 1) > 98 || (i == height - 2 && j == width - 2);
			bool shouldDrawEnemy = (rand() % 100 + 1) > 94;
			bool shouldDrawItem = (rand() % 100 + 1) > 93;
			bool shouldGenerateImpassable = (rand() % 100 + 1) > 83;
			std::tuple<int, int> position(j, i);

			if (shouldDrawPlayer && !playerDrawn) {
				this->player = std::make_unique<Player>(100, 100, 5, 3, position, "Rixon", WorldObjectType::PLAYER);
				map[i][j] = (char)WorldObjectType::PLAYER;
				playerDrawn = true;
			}
			else if (shouldDrawEnemy) {
				bool hasLoot = (rand() % 50 + 1) > 65;
				std::unique_ptr<Enemy> enemy = nullptr;

				if (hasLoot) {
					enemy = std::make_unique<Enemy>(createItem(std::tuple<int, int>(j, i), ++itemCount), 100, 100, 5, 3, position, "Enemy " + ++enemyCount, WorldObjectType::ENEMY);
					this->characters.push_back(std::move(enemy));
				}
				else {
					enemy = std::make_unique<Enemy>(100, 100, 5, 3, position, "Enemy " + ++enemyCount, WorldObjectType::ENEMY);
					this->characters.push_back(std::move(enemy));
				}

				map[i][j] = (char)WorldObjectType::ENEMY;
			}
			else if (shouldDrawItem) {
				std::shared_ptr<Item> item = createItem(std::tuple<int, int>(j, i), ++itemCount);
				map[i][j] = (char)item->getObjectType();
				this->items.push_back(std::move(item));
			}
			else if (shouldGenerateImpassable) {
				int impassableIndex = rand() % 3;
				map[i][j] = possibleImpassables[impassableIndex];
			}
			else {
				map[i][j] = ' ';
			}
		}
	}
}

std::shared_ptr<Item> World::createItem(std::tuple<int, int> position, int itemsCount) {
	int itemType = (rand() % 3);
	double armor = (double)(rand() % 15 + 1);
	double dmg = (double)(rand() % 15 + 1);
	double hp = (double)(rand() % 15 + 1);
	WorldObjectType type;
	std::string itemName = "Item " + itemsCount;

	switch (itemType) {
		case 0: return std::make_shared<Item>(armor, 0, hp, ItemType::EQUIPABLE, position, itemName, WorldObjectType::ARMOR);
		case 1: return std::make_shared<Item>(0, dmg, 0, ItemType::EQUIPABLE, position, itemName, WorldObjectType::WEAPON);
		case 2: return std::make_shared<Item>(0, 0, hp, ItemType::CONSUMABLE, position, itemName, WorldObjectType::CONSUMABLE);
	}
}

std::tuple<int, int> World::generatePosition() {
	int px = rand() % width;
	int py = rand() % height;

	if (px == width - 1) {
		px -= 1;
	}
	else if (px == 0) {
		++px;
	}

	if (py == height - 1) {
		py -= 1;
	}
	else if (py == 0) {
		++py;
	}

	return std::tuple<int, int>(px, py);
}