#pragma once
#include "gamestatebase.h"
#include "GameButton.h"
#include "Map.h"
#include "SpriteAnimation2D.h"

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
	std::vector < std::shared_ptr<SpriteAnimation2D>> m_listSpriteAnimations;

};

