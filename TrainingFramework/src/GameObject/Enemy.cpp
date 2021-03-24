#include"Enemy.h"
Enemy::Enemy(int type, int x, int y, int dir, int move, int maxMove, int speed) {
	enemy.type = type;
	enemy.cEnemy.x = x;
	enemy.cEnemy.y = y;
	enemy.dir = dir;
	enemy.move = move;
	enemy.maxMove = maxMove;
	enemy.speed = speed;
}