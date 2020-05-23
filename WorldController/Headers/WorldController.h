#pragma once
#include <ostream>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <iostream>
#if defined _WIN32
#include <Windows.h>
#endif

#include "../../GameModels/Header/World.h"


class WorldController {
private:
	std::unique_ptr<World> w;
	int maxWidth = 30, maxHeight = 30, minWidth = 10, minHeight = 10, range = 20;
	int width;
	int height;

#if defined _WIN32
	VOID setup();
	VOID ErrorExit(LPSTR lpszMessage);
#endif

public:
	WorldController();

	friend std::ostream& operator<<(std::ostream&, WorldController&);
};