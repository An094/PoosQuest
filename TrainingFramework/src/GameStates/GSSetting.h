#pragma once
#include "GameStatebase.h"
#include"GameButton.h"

class GSSetting :
	public GameStateBase
{
public:
	GSSetting();
	~GSSetting();

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
	std::vector<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<GameButton> buttonSound;
	std::vector<std::shared_ptr<GameButton>> m_listSound;
	std::shared_ptr<GameButton> buttonMusic;
	std::vector<std::shared_ptr<GameButton>> m_listMusic;
};

