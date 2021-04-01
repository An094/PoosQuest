#pragma once
#include "GameStates/GameStatebase.h"
class DynamicObject
{
public:
	DynamicObject();
	virtual ~DynamicObject();
	//virtual void Move(float,float,float) = 0;
	virtual Vector2 getPos() = 0;
	int getDir() { return m_dir; }
	void setDir(int dir) { m_dir = dir; }
private:
	int m_dir;
};
