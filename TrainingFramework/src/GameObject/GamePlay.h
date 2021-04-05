#pragma once
#include "GameObject/BaseObject.h"
#include "GameButton.h"
#include "SpriteAnimation2D.h"
#include "Enemy0.h"
#include "Enemy3.h"
#include "Enemy.h"
#include "Poo2.h"
#include "Map2.h"
#include "Gold.h"

class Sprite2D;



class GamePlay
{
public:
	GamePlay(int);
	~GamePlay();

	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void Reset();
	bool isWin = false;
	static int num_deaths;
private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> Switch;
	std::shared_ptr<Sprite2D> Gray;
	std::shared_ptr<Sprite2D> Stage;
	std::shared_ptr<Sprite2D> S0;
	std::shared_ptr<Sprite2D> S1;
	std::shared_ptr<Sprite2D> Deaths;
	std::shared_ptr<Sprite2D> D0;
	std::shared_ptr<Sprite2D> D1;
	int m_level;
	bool isStart;
	bool isLost;
	bool isLoadSwitch;
	int RemGold;
	float m_time;
	float m_timeLoadSwitch;
	bool isNotiLost;

	std::list<std::shared_ptr<GameButton>>	m_listButton;
	//khai bao Map
	std::shared_ptr<Map2> map2;
	std::list<std::shared_ptr<Gold>> m_listGold;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	std::shared_ptr<Poo2> m_poo2;
};

