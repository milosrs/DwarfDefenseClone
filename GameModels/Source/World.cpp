#include "../Header/World.h"

World::World(const World& other) : objects(other.objects), map(other.map), width(other.width), height(other.height) {
	drawItemsOnMap();
}

World::World(std::vector<WorldObject*> objects, int n, int m): height(n), width(m), objects(objects) {
	map = new char* [n];

	for (int i = 0; i < height; i++) {
		map[i] = new char[m];
	}
	
	drawBoundaries();
	drawItemsOnMap();
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

void World::drawItemsOnMap() {
	for (WorldObject* o : objects) {
		drawItem(o);
	}
}

void World::addObject(WorldObject* o) {
	this->objects.push_back(o);

	drawItem(o);
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

void World::drawItem(WorldObject* o) {
	int px = std::get<0>(o->getPosition());
	int py = std::get<1>(o->getPosition());

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

	o->setPosition(std::tuple<int, int>(px, py));

	map[px][py] = (char)o->getObjectType();
}