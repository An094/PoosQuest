#pragma once
#include "Enemy.h"

class Enemy2 : public Enemy {
public:
	Enemy2(int x, int y, int dir, int move, int maxMove1, int maxMove2, int speed, std::shared_ptr<Map2> map);
	~Enemy2();
	void Update(float);
	void Draw();
	void MoveDirWithPoo(float, Vector2);
	void BackDefault();
	bool getActive() { return true; }
	Vector2 getPos() { return enemy->Get2DPosition(); }

private:
	float speed = 120.0f;
	float maxMoveDis[4];
	float currentMove;
	int defaultDir;
	Vector2 currentPos;
	Vector2 oldPos;
	Vector2 defaultPos;
	std::shared_ptr<Map2> m_map;
	std::shared_ptr<SpriteAnimation2D> enemy;
};