#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "Application.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	m_level = 1;
	//InitLevel(1);
	ResourceManagers::GetInstance()->PlaySound("music_game.wav", true);
	m_GamePlay = std::make_shared<GamePlay>(m_level);
	
	//ResourceManagers::GetInstance()->PlaySound("button-synth-pop_z1rzwdEd_WM.mp3");

}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	m_GamePlay->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	m_GamePlay->HandleTouchEvents(x, y, bIsPressed);
}
void GSPlay::Update(float deltaTime)
{
	m_GamePlay->Update(deltaTime);
	if (m_GamePlay->isWin)
	{
		m_level++;
		m_GamePlay = std::make_shared<GamePlay>(m_level);
	}
}
void GSPlay::Draw()
{
	m_GamePlay->Draw();
}