#include "../Header/World.h"

const std::string impassables = "#!@";

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

	os << w.player.get();

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
					map[i][j] = impassables[impassableIndex];
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
			std::tuple<int, int> position(j, i);

			std::vector<std::unique_ptr<WorldObject>>::iterator it = find_if(objects.begin(),
				objects.end(),
				[position](std::unique_ptr<WorldObject>& wo) {return wo->getPosition()._Equals(position); });

			if (it == objects.end()) {
				bool shouldDrawPlayer = (rand() % 100 + 1) > 98 || (i == height - 2 && j == width - 2);
				bool shouldDrawEnemy = (rand() % 100 + 1) > 94;
				bool shouldDrawItem = (rand() % 100 + 1) > 93;
				bool shouldGenerateImpassable = (rand() % 100 + 1) > 83;

				if (shouldDrawPlayer && !playerDrawn) {
					this->player = std::make_unique<Player>(100, 100, 5, 3, position, "Rixon", WorldObjectType::PLAYER);
					map[i][j] = (char)WorldObjectType::PLAYER;
					playerDrawn = true;
				}
				else if (shouldDrawEnemy) {
					bool hasLoot = (rand() % 50 + 1) > 65;
					double maxHp = (double)(rand() % 70 + 20);
					double maxDmg = (double)(rand() % 20 + 5);
					double maxArmor = (double)(rand() % 15 + 0);
					std::unique_ptr<Enemy> enemy = nullptr;

					if (hasLoot) {
						enemy = std::make_unique<Enemy>(createItem(std::tuple<int, int>(j, i), ++itemCount), maxHp, maxHp, maxDmg, maxArmor, position, "Enemy " + ++enemyCount, WorldObjectType::ENEMY);
						this->objects.push_back(std::move(enemy));
					}
					else {
						enemy = std::make_unique<Enemy>(maxHp, maxHp, maxDmg, maxArmor, position, "Enemy " + ++enemyCount, WorldObjectType::ENEMY);
						this->objects.push_back(std::move(enemy));
					}

					map[i][j] = (char)WorldObjectType::ENEMY;
				}
				else if (shouldDrawItem) {
					std::unique_ptr<Item> item = createItem(std::tuple<int, int>(j, i), ++itemCount);
					map[i][j] = (char)item->getObjectType();
					this->objects.push_back(std::move(item));
				}
				else if (shouldGenerateImpassable) {
					std::unique_ptr<WorldObject> impassable = nullptr;
					int impassableIndex = rand() % 3;
					WorldObjectType type = WorldObjectType::TREE;

					switch (impassableIndex) {
					case 0: type = WorldObjectType::MOUNTAIN; break;
					case 1: type = WorldObjectType::WATER; break;
					default: type = WorldObjectType::TREE;
					}

					impassable = std::make_unique<WorldObject>(std::tuple<int, int>(j, i), "impassable", type);
					objects.push_back(std::move(impassable));
					map[i][j] = (char)type;
				}
				else {
					map[i][j] = ' ';
				}
			}
		}
	}
}

void World::movePlayer(MoveDirection direction) {
	std::tuple<int, int> position = player->getPosition();
	int px = std::get<0>(position), 
		py = std::get<1>(position);

	bool moved = player->move(1, direction, width, height);
	
	if (moved) {
		std::tuple<int, int> newPosition = player->getPosition();

		std::vector<std::unique_ptr<WorldObject>>::iterator element = find(objects.begin(),
			objects.end(),
			[newPosition](std::unique_ptr<WorldObject>& wo) {
				wo->getPosition()._Equals(newPosition);
			}
		);

		if (element != objects.end()) {
			//colide(player.get(), element->get());
		}

		map[py][px] = ' ';
		px = std::get<0>(player->getPosition());
		py = std::get<1>(player->getPosition());
		map[py][px] = (char)WorldObjectType::PLAYER;
	}
}

/*bool World::colide(Character* character, std::vector<std::unique_ptr<WorldObject>>::iterator wo) {
	if(wo->get()->getObjectType() == WorldObjectType::TREE || wo->get()->getObjectType() == WorldObjectType::WATER || wo->get()->getObjectType() == WorldObjectType::MOUNTAIN) {
		return false;
	}
	else {
		if (wo->get()->getObjectType() == WorldObjectType::ARMOR || wo->get()->getObjectType() == WorldObjectType::WEAPON || wo->get()->getObjectType() == WorldObjectType::CONSUMABLE) {
			if (std::is_base_of<Character*, Enemy*>::value) {
				return false;
			}
			else if (std::is_base_of<Character*, Player*>::value) {
				std::cout << "Should somehow expand inventory" << std::endl;
				((Player*)character)->addNewItem(std::move(objects.at(wo)));
			}
		}
	}
}*/

std::unique_ptr<Item> World::createItem(std::tuple<int, int> position, int itemsCount) {
	int itemType = (rand() % 3);
	double armor = (double)(rand() % 15 + 1);
	double dmg = (double)(rand() % 15 + 1);
	double hp = (double)(rand() % 15 + 1);
	WorldObjectType type;
	std::string itemName = "Item " + itemsCount;

	switch (itemType) {
		case 0: return std::make_unique<Item>(armor, 0, hp, ItemType::EQUIPABLE, position, itemName, WorldObjectType::ARMOR);
		case 1: return std::make_unique<Item>(0, dmg, 0, ItemType::EQUIPABLE, position, itemName, WorldObjectType::WEAPON);
		case 2: return std::make_unique<Item>(0, 0, hp, ItemType::CONSUMABLE, position, itemName, WorldObjectType::CONSUMABLE);
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