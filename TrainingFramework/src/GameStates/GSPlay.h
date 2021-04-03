#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "SpriteAnimation2D.h"
#include "Enemy0.h"
#include "Enemy.h"
#include "Poo2.h"
#include "Map2.h"
#include "Gold.h"
#include "GamePlay.h"

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
	std::shared_ptr<GamePlay> m_GamePlay;
	int m_level;
};

