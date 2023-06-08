#pragma once
enum class Event
{
	playerLostLife,
	playerEarnedPoint,
	playerMoved,
	burgerPartDropped1Level,
	burgerPartReachedPlate,
	burgerPartDroppedWith1EnemyOn,
	burgerPartDroppedWith2EnemiesOn,
	burgerPartDroppedWith3EnemiesOn,
	burgerPartDroppedWith4EnemiesOn,
	burgerPartDroppedWith5EnemiesOn,
	burgerPartDroppedWith6EnemiesOn,
	playerDied,
	enemyDied
};