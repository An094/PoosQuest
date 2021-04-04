#pragma once
#include "Enemy.h"

class Enemy3 : public Enemy {
public:
	Enemy3(int x, int y, int dir, int move, int maxMove1, int maxMove2, std::shared_ptr<Map2> map);
	~Enemy3();
	void Update(float);
	void Draw();
	void MoveDirWithPoo(float, Vector2);
	void BackDefault();
	bool getActive();
	Vector2 getPos() { return enemy->Get2DPosition(); }

private:
	bool isChange;
	float speed = 120.0f;
	float maxMoveDis;
	float currentMove;
	int defaultDir;

	float m_move;
	float defaultMove;
	float m_maxMove[2];

	int status;

	Vector2 currentPos;
	Vector2 oldPos;
	Vector2 defaultPos;
	std::shared_ptr<Map2> m_map;
	std::shared_ptr<Sprite2D> enemy;
	std::vector<std::shared_ptr<Sprite2D>> vPose;
};