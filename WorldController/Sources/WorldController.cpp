#include "../Headers/WorldController.h"

#if defined _WIN32
HANDLE hStdin;
DWORD fdwSaveOldMode;
DWORD fdwMode;
DWORD cNumRead;
INPUT_RECORD key[1] = { {} };

VOID WorldController::ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

VOID WorldController::setup() {
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	fdwMode = ENABLE_WINDOW_INPUT;

	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");
}

#endif

WorldController::WorldController() {
	bool worldUpdated = true;

	srand(time(NULL));
	setup();

	width = rand() % range + minWidth;
	height = rand() % range + minHeight;
	std::string playerName = "Player 1";
	w = std::make_unique<World>(height, width, playerName);

#if defined _WIN32	

	while (key[0].Event.KeyEvent.uChar.AsciiChar != 27) {
		if (worldUpdated) {
			system("cls");
			std::cout << *w.get() << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			worldUpdated = false;
		}
		
		if (!ReadConsoleInput(hStdin, key, 1, &cNumRead)) {
			ErrorExit("ReadConsoleInput");
		}

		if (key[0].EventType == KEY_EVENT && key[0].Event.KeyEvent.bKeyDown) {
			unsigned char actionChar = key[0].Event.KeyEvent.uChar.AsciiChar;

			if (actionChar >= 'a' && actionChar <= 'z') {
				w->movePlayer((MoveDirection)actionChar);
				w->deleteDeadEnemies();
				w->moveEnemies();
				worldUpdated = true;
			}
			else if (actionChar >= '1' && actionChar <= '9') {
				w->useConsumable(actionChar - 48);
				w->deleteDeadEnemies();
				w->moveEnemies();
				worldUpdated = true;
			}
		}
	}
#else
	std::cout << "Non-Windows OS aren't supported for this game...yet! :P" << std::endl;
#endif
}



std::ostream& operator<<(std::ostream& os, WorldController& w) {
	return os;
}