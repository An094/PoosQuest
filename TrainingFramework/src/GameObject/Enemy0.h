#pragma once
#include "Enemy.h"

class Enemy0 : public Enemy {
public:
	Enemy0(int x, int y, int dir, int move, int maxMove, int speed);
	~Enemy0();
	void loadImage();
	void move(float);
	void update(float);
	void draw();

private:
	float maxMoveDis;
	float currentMove;
	float currentCoorX;
	float currentCoorY;
	float currentXPos;
	float currentYPos;
	float oldXPos;
	float oldYPos;
	std::shared_ptr<SpriteAnimation2D> enemy;
	
};