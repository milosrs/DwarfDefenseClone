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


int main()
{
	srand(time(NULL));
	int maxWidth = 60, maxHeight = 60, minWidth = 10, minHeight = 10, range = 50;

	int width = rand() % range + minWidth;
	int height = rand() % range + minHeight;

	std::vector<WorldObject*> wo;
	World w(width, height);
	
	//Draw the world without obstacles
	std::cout << w << std::endl;

	return 0;
}

