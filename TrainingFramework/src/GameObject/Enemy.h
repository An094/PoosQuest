#pragma once
#include "GameStates/GameStatebase.h"
#include "DynamicObject.h"
#include "Map2.h"
class Enemy : DynamicObject	{
private:
	//EnemyData enemy;
	int m_dir;
	int m_type;
	sCoor coor;
	std::shared_ptr<Map2> m_map;
public:
	Enemy(int type, int x, int y, int dir);
	virtual ~Enemy();
	virtual void Move(float) = 0;
	virtual void Update(float) = 0;
	virtual void Draw() = 0;
	virtual void MoveWithPoo(float, float) = 0;
	virtual Vector2 getPos() = 0;
	int getDir() { return m_dir; }
	void setDir(int dir) { m_dir = dir; }
};
