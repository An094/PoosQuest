#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class GSMenu :
	public GameStateBase
{
public:
	GSMenu();
	~GSMenu();
	
	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void dynamicLogo(float);

private:
	bool notLoop = true;
	float maxMove = 15.0f;
	float speed = 25.0f;
	float currentMove = 0.0f;
	bool state = 0;
	float oldXPos = 240.0f;
	float oldYPos = 150.0f;
	float currentXPos = oldXPos;
	float currentYPos = oldYPos;
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Sprite2D> m_Logo;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	//std::shared_ptr<Text>  m_Text_gameName;

};

