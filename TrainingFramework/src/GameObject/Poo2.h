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
	std::vector<std::shared_ptr<SpriteAnimation2D>> vPose1;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	std::list<std::shared_ptr<Gold>> m_listGold;
	std::shared_ptr<Map2> myMap;
	int** mapconvert;
	Vector2 dest;
	float xColl = 14.0f;
	float yColl = 9.0f;
	float speed = 120.0f;
	int defaultDir;
	float timeLoadSound = 0.0f;
public:
	Poo2(int dir,int xEnd, int yEnd,std::shared_ptr<Map2> map, std::list<std::shared_ptr<Enemy>> listEnemy,std::list<std::shared_ptr<Gold>> listGold);
	~Poo2();
	std::shared_ptr<SpriteAnimation2D> getPoo() { return m_poo; }
	void Move(float);
	void MoveUp(float);
	void MoveRight(float);
	void MoveDown(float);
	void MoveLeft(float);
	void MoveDir(Vector2,float);
	void AutoMove(float);
	void Update(float);
	void HandleKeyEvents(int, bool);
	void Draw();
	bool CheckCollision();
	bool CheckEatGold();
	bool CheckEndPoint();
	void BackDefault();
	Vector2 getPos() { return m_poo->Get2DPosition(); }
	sCoor getCoorPoo();
	int MOVE;
	void soundMove(float);
};
