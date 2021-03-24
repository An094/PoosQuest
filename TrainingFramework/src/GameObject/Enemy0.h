#pragma once
#include "Enemy.h"

class Enemy0 : public Enemy {
public:
	Enemy0(int x, int y, int dir, int move, int maxMove, int speed);
	~Enemy0();
	void loadImage();
	void move();
	void update(float);
	void draw();

private:
	std::list<std::shared_ptr<SpriteAnimation2D>> m_listEnemy;
};