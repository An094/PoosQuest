#pragma once
#include "GameStatebase.h"
#include"GameButton.h"

class GSCredit :
	public GameStateBase
{
public:
	GSCredit();
	~GSCredit();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:
	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Text>  text;
	std::shared_ptr<Text>  text2;
	std::shared_ptr<Text>  text3;
	std::shared_ptr<Text>  text4;
	std::shared_ptr<Text>  text5;
	std::shared_ptr<Text>  text6;
	std::shared_ptr<Text>  text7;
};

