#pragma once
#include "../../Enums/MoveDirection.h"

class Enemy;

class AStar {
public:
	static MoveDirection getOptimalMove(char**, int h, int w, Enemy*);
private:
};