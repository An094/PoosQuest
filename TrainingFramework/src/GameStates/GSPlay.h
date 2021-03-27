#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Map.h"
#include "SpriteAnimation2D.h"
#include "Enemy0.h"
#include "Enemy.h"
#include "Poo.h"

class Sprite2D;
class Sprite3D;
class Text;
class Map;

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

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	
	void SetNewPostionForBullet();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_score;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	//khai bao Map
	std::unique_ptr<Map> map;
	std::list<std::shared_ptr<SpriteAnimation2D>> m_listSpriteAnimations;
	std::list<std::shared_ptr<Enemy>> m_listEnemy;
	std::shared_ptr<Poo> m_poo;
};

