#pragma once
#include "GameStates/GameStatebase.h"
#include "Map.h"
class Enemy {
private:
	EnemyData enemy;
public:
	Enemy(int, int, int, int, int, int, int);
	//virtual ~Enemy();
	virtual void loadImage() = 0;
	//virtual void move() = 0;
	int getDir() { return enemy.dir; }
	int getCoorX() { return enemy.cEnemy.x; }
	int getCoorY() { return enemy.cEnemy.y; }
	int getMaxMove() { return enemy.maxMove; }
	int getSpeed() { return enemy.speed; }
};
