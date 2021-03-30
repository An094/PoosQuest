#pragma once
#include "GameStates/GameStatebase.h"
#include "Map.h"
class Enemy;
class Poo {
private:
	PooData poo;
	std::shared_ptr<Map> m_map;
	std::shared_ptr<SpriteAnimation2D> m_poo;
	float currentXPos;
	float currentYPos;
	bool isAlive;
	float xColl = 10.0f;
	float yColl = 12.0f;
	float speed = 100.0f;
	int MOVE;
public:
	Poo(int, int, int, int, int, std::shared_ptr<Map>);
	~Poo();
	void loadImage();
	void move(float);
	void handleKeyEvents(int, bool);
	void moveUp(float);
	void moveDown(float);
	void moveLeft(float);
	void moveRight(float);
	void update(float);
	void draw();
	int getDir() { return poo.dir; }
	void setDir(int dir) { poo.dir = dir; }
	bool checkColli(std::shared_ptr<Enemy>);
};