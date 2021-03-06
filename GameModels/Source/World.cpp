#include "../Header/World.h"
#include "../Header/Treasure.h"
#include "../../AI/Headers/SearchCell.h"
#include "../../Dependencies/rlutil.h"

void SelectColor(char object) {
	switch ((WorldObjectType)object) {
	case WorldObjectType::ARMOR: rlutil::setColor(rlutil::WHITE); break;
	case WorldObjectType::WEAPON: rlutil::setColor(rlutil::YELLOW); break;
	case WorldObjectType::CONSUMABLE: rlutil::setColor(rlutil::MAGENTA); break;
	case WorldObjectType::ENEMY: rlutil::setColor(rlutil::LIGHTRED); break;
	case WorldObjectType::PLAYER: rlutil::setColor(rlutil::GREEN); break;
	case WorldObjectType::TREASURE:rlutil::setColor(rlutil::BROWN); break;
	default: rlutil::setColor(rlutil::GREY);
	};

	rlutil::setBackgroundColor(rlutil::BLACK);
}

const std::string impassables = "#!@";

World::World(int n, int m, std::string playerName): height(n), width(m) {
	map = new char* [n];
	aiMap = new SearchCell* [n];

	for (int i = 0; i < height; i++) {
		map[i] = new char[m];
		aiMap[i] = new SearchCell[m];
	}
	
	drawBoundaries();
	drawWorld(playerName);
	createAIMap();
}

char** World::getMap() {
	return map;
}

std::ostream& operator<<(std::ostream& os, World& w) {
	os << std::endl;

	for (int i = 0; i < w.height; i++) {
		for (int j = 0; j < w.width; j++) {
			SelectColor(w.map[i][j]);
			os << w.map[i][j];
		}

		os << std::endl;
	}

	os << *(w.player.get());

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

void World::createAIMap() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			aiMap[i][j].x = j;
			aiMap[i][j].y = i;
			aiMap[i][j].sign = map[i][j];
			aiMap[i][j].parent = nullptr;
		}
	}
}

void World::drawWorld(std::string playerName) {
	bool playerDrawn = false;
	int enemyCount = 0;
	int itemCount = 0;
	int treasureCount = 0;

	for (int i = 1; i < height - 1; i++) {
		for (int j = 1; j < width - 1; j++) {
			std::tuple<int, int> position(j, i);

			std::vector<std::unique_ptr<WorldObject>>::iterator it = find_if(objects.begin(),
				objects.end(),
				[position](std::unique_ptr<WorldObject>& wo) {return wo->getPosition()._Equals(position); 
			});

			if (it == objects.end()) {
				bool shouldDrawPlayer = (rand() % 100 + 1) > 98 || (i == height - 2 && j == width - 2);
				bool shouldDrawEnemy = (rand() % 100 + 1) > 94;
				bool shouldDrawItem = (rand() % 100 + 1) > 93;
				bool shouldDrawTreasure = (rand() % 100 + 1) > 95;
				bool shouldGenerateImpassable = (rand() % 100 + 1) > 83;

				if (shouldDrawPlayer && !playerDrawn) {
					this->player = std::make_unique<Player>(100, 100, 5, 3, position, playerName, WorldObjectType::PLAYER);
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
						std::unique_ptr<Item> loot = createItem(std::tuple<int, int>(j, i), ++itemCount);
						enemy = std::make_unique<Enemy>(std::move(loot), maxHp, maxHp, maxDmg, maxArmor, position, std::string("Enemy ").append(std::to_string(++enemyCount)), WorldObjectType::ENEMY);
						this->objects.push_back(std::move(enemy));
					}
					else {
						enemy = std::make_unique<Enemy>(maxHp, maxHp, maxDmg, maxArmor, position, std::string("Enemy ").append(std::to_string(++enemyCount)), WorldObjectType::ENEMY);
						this->objects.push_back(std::move(enemy));
					}

					map[i][j] = (char)WorldObjectType::ENEMY;
				}
				else if (shouldDrawTreasure) {
					int treasureItems = rand() % 3 + 1;
					std::vector<std::unique_ptr<Item>> items;

					for (int i = 0; i < treasureItems; ++i) {
						items.push_back(createItem(std::tuple<int, int>(j, i), ++itemCount));
					}

					objects.push_back(std::make_unique<Treasure>(std::move(items), std::tuple<int, int>(j, i), std::string("Treasure ").append(std::to_string(++treasureCount)), WorldObjectType::TREASURE));
					map[i][j] = (char)WorldObjectType::TREASURE;
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

//I know this is the method I should use to move enemies and player but I had to hurry up :D
void World::movePlayer(MoveDirection direction) {
	std::tuple<int, int> position = player->getPosition();
	int px = std::get<0>(position), 
		py = std::get<1>(position);
	TurnResult turnResult = TurnResult::WALK;
	bool moved = player->move(1, direction, width, height);
	
	if (moved) {
		std::tuple<int, int> newPosition = player->getPosition();

		std::vector<std::unique_ptr<WorldObject>>::iterator element = find_if(objects.begin(),
			objects.end(),
			[newPosition](std::unique_ptr<WorldObject>& wo) {
				return wo->getPosition()._Equals(newPosition);
			}
		);

		if (element != objects.end()) {
			turnResult = colide(player.get(), element);
		}

		if (turnResult != TurnResult::CANT_MOVE) {
			map[py][px] = ' ';
			px = std::get<0>(player->getPosition());
			py = std::get<1>(player->getPosition());
			map[py][px] = (char)player->getObjectType();
			player->setPosition(newPosition);
		}
		else {
			//reset the position
			player->setPosition(position);
		}
	}

	createAIMap();
}

void World::deleteDeadEnemies() {
	objects.erase(std::remove_if(
		objects.begin(), 
		objects.end(), 
		[](std::unique_ptr<WorldObject>& wo) {
			return wo->getObjectType() == WorldObjectType::ENEMY && ((std::unique_ptr<Enemy>&)wo)->getHealth() <= 0;
		}),
		objects.end()
	);
}

void World::moveEnemies() {
	int enemyIndex = 0;

	for (std::unique_ptr<WorldObject>& wo : objects) {
		if (wo->getObjectType() == WorldObjectType::ENEMY) {
			int dirNo = rand() % 4;
			MoveDirection direction = MoveDirection::DOWN;

			switch (dirNo) {
			case 0: direction = MoveDirection::DOWN; break;
			case 1: direction = MoveDirection::LEFT; break;
			case 2: direction = MoveDirection::RIGHT; break;
			case 3: direction = MoveDirection::UP; break;
			}

			/*Yep....ugly*/
			std::tuple<int, int> position = wo->getPosition();
			int px = std::get<0>(position),
				py = std::get<1>(position);
			TurnResult turnResult = TurnResult::WALK;
			bool moved = ((std::unique_ptr<Enemy>&)wo)->move(1, direction, width, height);

			if (moved) {
				std::tuple<int, int> newPosition = wo->getPosition();
				std::string currentEnemyName = wo->getName();
				
				std::vector<std::unique_ptr<WorldObject>>::iterator element = find_if(objects.begin(),
					objects.end(),
					[newPosition, currentEnemyName](std::unique_ptr<WorldObject>& obj) {
						return obj->getPosition()._Equals(newPosition) && !obj->getName()._Equal(currentEnemyName);
					}
				);

				if (element == objects.end()) {
					if (wo->getPosition()._Equals(player->getPosition())) {
						turnResult = colide(player.get(), objects.begin() + enemyIndex);
					}

					if (turnResult != TurnResult::CANT_MOVE) {
						map[py][px] = ' ';
						px = std::get<0>(wo->getPosition());
						py = std::get<1>(wo->getPosition());
						map[py][px] = (char)wo->getObjectType();
						wo->setPosition(newPosition);
					}
					else {
						//reset the position
						wo->setPosition(position);
					}
				}
				else {
					//reset the position
					wo->setPosition(position);
				}
			}
		}

		++enemyIndex;
	}
}

TurnResult World::colide(Character* character, std::vector<std::unique_ptr<WorldObject>>::iterator wo) {
	TurnResult res = TurnResult::WALK;

	if(wo != objects.end()) {
		bool charIsPlayer = character->getObjectType() == WorldObjectType::PLAYER;
		WorldObjectType type = wo->get()->getObjectType();

		if (type == WorldObjectType::TREE || type == WorldObjectType::WATER || type == WorldObjectType::MOUNTAIN) {
			res = TurnResult::CANT_MOVE;
		}
		else if(charIsPlayer) {
			if (type == WorldObjectType::ARMOR || type == WorldObjectType::WEAPON || type == WorldObjectType::CONSUMABLE && charIsPlayer) {
				std::unique_ptr<WorldObject> woPtr = std::move((*(wo)));
				Item* item = (Item*)(woPtr.get());
				objects.erase(wo);
				woPtr.release();
				player->addNewItem(std::make_unique<Item>(item));
				res = TurnResult::ITEM_PICKUP;
			}
			else if (type == WorldObjectType::ENEMY) {
				Enemy* enemy = (Enemy*)wo->get();
				player->fight(enemy);

				if (player->getHealth() <= 0) {
					std::cout << "Game over!" << std::endl;
					exit(1);
					res = TurnResult::PLAYER_DEATH;
				}

				if (enemy->getHealth() <= 0) {
					std::unique_ptr<Item> loot = enemy->getLoot();

					if (loot != nullptr) {
						player->addNewItem(std::move(loot));
					}

					res = TurnResult::ENEMY_DEATH;
				}

				if (player->getHealth() > 0 && enemy->getHealth() > 0) {
					res = TurnResult::CANT_MOVE;
				}
			}
			else if (type == WorldObjectType::TREASURE) {
				std::unique_ptr<WorldObject> treasurePtr = std::move((*(wo)));
				Treasure* treasure = (Treasure*)treasurePtr.get();
				auto items = treasure->getItems();

				for (const auto& t : items) {
					player->addNewItem(std::make_unique<Item>(t.get()));
				}

				items.erase(items.begin(), items.end());
				treasurePtr.release();
				objects.erase(wo);
			}
		}
		else {
			res = TurnResult::CANT_MOVE;
		}
	}

	return res;
}

std::unique_ptr<Item> World::createItem(std::tuple<int, int> position, int itemsCount) {
	int itemType = (rand() % 3);
	double armor = (double)(rand() % 15 + 1);
	double dmg = (double)(rand() % 15 + 1);
	double hp = (double)(rand() % 15 + 1);
	WorldObjectType type;
	std::string itemName = std::string("Item ").append(std::to_string(++itemsCount));

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

void World::useConsumable(int index) {
	player->useConsumable(index);
}

std::ofstream& operator<<(std::ofstream& os, World& wo) {
	os << wo.width;
	os << " ";
	os << wo.height;
	os << " ";
	for (int i = 1; i < wo.height - 1; i++) {
		for (int j = 1; j < wo.width - 1; j++) {
			os << wo.map[i][j];
		}
	}
	os << " ";
	os << *(wo.player.get());
	os << " ";
	
	for (std::unique_ptr<WorldObject>& o : wo.objects) {
		switch (o->getObjectType()) {
		case WorldObjectType::ARMOR:
		case WorldObjectType::CONSUMABLE:
		case WorldObjectType::WEAPON: os << (Item) * ((Item*)((o.get()))); break;
		}
	}

	return os;
}