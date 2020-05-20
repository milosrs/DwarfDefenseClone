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

int main()
{
	srand(time(NULL));
	int maxWidth = 30, maxHeight = 30, minWidth = 10, minHeight = 10, range = 20;
	char direction = '\0';
	int width = rand() % range + minWidth;
	int height = rand() % range + minHeight;

	std::vector<WorldObject*> wo;
	World w(width, height);

	std::cout << w << std::endl;
	
	while (direction != 'x') {
		std::cout << "Move your player: ";
		std::cin >> direction;

		w.movePlayer((MoveDirection)direction);
		
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << w << std::endl;

	}
	
	return 0;
}

