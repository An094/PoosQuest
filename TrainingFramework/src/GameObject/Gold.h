#pragma once
#include "GameStates/GameStatebase.h"
class Map2;
class Gold
{
private:
	std::shared_ptr<SpriteAnimation2D> m_Gold;
public:
	Gold(int x, int y, std::shared_ptr<Map2> map);
	~Gold();
	void MoveWithPoo(float, float);
	void Draw();
	void Update(float);
	Vector2 getPos() { return m_Gold->Get2DPosition(); }
};