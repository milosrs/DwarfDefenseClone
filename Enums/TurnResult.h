#pragma once
enum class TurnResult {
	PLAYER_DEATH = 0,
	ENEMY_DEATH = 1,
	ITEM_PICKUP = 2,
	WALK = 3,
	CANT_MOVE = 4
};