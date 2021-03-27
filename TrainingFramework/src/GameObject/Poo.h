#pragma once
#include "GameStates/GameStatebase.h"
#include "Map.h"
class Poo {
private:
	PooData poo;
	float currentXPos;
	float currentYPos;
public:
	Poo(int, int, int, int, int);
	~Poo();
	void loadImage();
	void move(float);
	void update(float);
	void draw();
	int getDir() { return poo.dir; }
	void setDir(int dir) { poo.dir = dir; }
	std::shared_ptr<SpriteAnimation2D> m_poo;
};