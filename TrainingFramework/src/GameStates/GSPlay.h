#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "SpriteAnimation2D.h"
#include "Enemy0.h"
#include "Enemy.h"
#include "Poo2.h"
#include "Map2.h"
#include "Gold.h"

class Sprite2D;
class Sprite3D;
class Text;


class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();
	void Reset();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();
private:

	std::shared_ptr<Sprite2D> m_BackGround;
	bool isLost;
	float m_time;
	
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	//khai bao Map
	std::shared_ptr<Map2> map2;
	std::list<std::shared_ptr<Gold>> m_listGold;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	std::shared_ptr<Poo2> m_poo2;
};

