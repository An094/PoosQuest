#pragma once
#include "DynamicObject.h"
#include "Map2.h"
extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
class Enemy;
class Gold;
class Poo2 :public DynamicObject
{
private:
	bool isAlive;
	std::shared_ptr<SpriteAnimation2D> m_poo;
	std::vector<std::shared_ptr<SpriteAnimation2D>> vPose;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	std::list<std::shared_ptr<Gold>> m_listGold;
	std::shared_ptr<Map2> myMap;
	int** mapconvert;
	Vector2 dest;
	float xColl = 14.0f;
	float yColl = 8.0f;
	float speed = 100.0f;
	int MOVE;
public:
	Poo2(int dir,int xEnd, int yEnd,std::shared_ptr<Map2> map, std::list<std::shared_ptr<Enemy>> listEnemy,std::list<std::shared_ptr<Gold>> listGold);
	~Poo2();
	std::shared_ptr<SpriteAnimation2D> getPoo() { return m_poo; }
	void Move(float);
	void MoveUp(float);
	void MoveRight(float);
	void MoveDown(float);
	void MoveLeft(float);
	void Update(float);
	void HandleKeyEvents(int, bool);
	void Draw();
	void CheckCollision();
	Vector2 getPos() { return m_poo->Get2DPosition(); }
	sCoor getCoorPoo();

};
