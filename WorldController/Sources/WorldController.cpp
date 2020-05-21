#include "../Headers/WorldController.h"

WorldController::WorldController() {
	srand(time(NULL));

	width = rand() % range + minWidth;
	height = rand() % range + minHeight;
	std::string playerName; 

	std::cout << "Whats your name, traveler? ";
	std::cin >> playerName;

	w = std::make_unique<World>(height, width, playerName);

	while (direction != 'x') {
	#if defined _WIN32
		system("cls");
	#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
	#elif defined (__APPLE__)
		system("clear");
	#endif
		std::cout << std::flush;
		std::cout << *w.get() << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;
		std::cin >> direction;
		w->movePlayer((MoveDirection)direction);
	}
}

std::ostream& operator<<(std::ostream& os, WorldController& w) {
	return os;
}