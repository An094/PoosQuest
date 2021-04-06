#pragma once
#include "gamestatebase.h"
#include "GameButton.h"

class GSLoad :
	public GameStateBase
{
public:
	GSLoad();
	~GSLoad();

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
	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<GameButton> m_buttonAccept;
	std::shared_ptr<GameButton> m_buttonBack;
	std::list<std::shared_ptr<GameButton>> m_listButton;
	std::shared_ptr<GameButton> m_buttonCharLeft;
	std::shared_ptr<GameButton> m_buttonCharRight;
	std::shared_ptr<GameButton> m_buttonLevelLeft;
	std::shared_ptr<GameButton> m_buttonLevelRight;
	std::shared_ptr<Sprite2D> levelLeft;
	std::shared_ptr<Sprite2D> levelRight;
	std::shared_ptr<SpriteAnimation2D> AniPoo0;
	std::shared_ptr<SpriteAnimation2D> AniPoo1;
	std::shared_ptr<SpriteAnimation2D> AniPoo;
	//std::shared_ptr<Text>  m_Text_gameName;

};

