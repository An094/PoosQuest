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
	m_GamePlay = std::make_shared<GamePlay>(1);
	
	ResourceManagers::GetInstance()->PlaySound("test.mp3");

}
void GSPlay::InitLevel(int level)
{
	m_time = 0.0f;
	isStart = true;
	isLost = false;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Tile\\-1");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth * 3, screenHeight * 3);

	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\back_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(20, 20);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	map2 = std::make_shared<Map2>(level);


	//Khoi tao Enemy
	for (auto it : map2->getListEnemyData()) {
		switch (it->type)
		{
		case 0:
		{
			printf("vao switch\n");
			auto enemy = std::make_shared<Enemy0>(it->cEnemy.x, it->cEnemy.y, it->dir, it->move, it->maxMove1, it->speed, map2);
			m_listEnemy.push_back(enemy);
			break;
		}

		default:
			break;
		}
	}
	for (auto it : map2->getGold()) {
		auto gold = std::make_shared<Gold>(it->x, it->y, map2);
		m_listGold.push_back(gold);
	}
	RemGold = m_listGold.size();
	//Khoi tao Poo
	m_poo2 = std::make_shared<Poo2>(map2->getPoo().dir, map2->getPoo().cDest.x, map2->getPoo().cDest.y, map2, m_listEnemy, m_listGold);
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
/*
void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	m_poo2->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{
	if (isLost)
	{
		m_poo2->MOVE = 0;
		m_time += deltaTime;
		if (m_time >= 0.6f)
		{
			m_time = 0.0f;
			isLost = false;
			Reset();
			
		}
	}
	for (auto obj : m_listGold)
	{
		obj->Update(deltaTime);
	}
	for (auto it : m_listEnemy)
	{
		it->Update(deltaTime);
	}
	m_poo2->Update(deltaTime);
	if (m_poo2->CheckCollision())
	{
		isLost = true;	
	}
	if (m_poo2->CheckEatGold())
	{
		if (RemGold > 0)
		{
			RemGold = RemGold - 1;
		}
		
		std::cout << "Remaining Gold: " << RemGold << std::endl;
	}
	if ((RemGold == 0) && (m_poo2->CheckEndPoint()))
	{
		std::cout << "WIN";
		m_level++;
		//InitLevel(m_level);
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	map2->DrawMap();
	
	
	for (auto obj : m_listGold)
	{
		obj->Draw();
	}
	for (auto it : m_listEnemy)
	{
		it->Draw();
	}
	m_poo2->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}
void GSPlay::Reset()
{
	map2->BackDefault();
	for (auto it : m_listEnemy)
	{
		(it)->BackDefault();
	}
	for (auto it : m_listGold)
	{
		(it)->BackDefault();
	}
	m_poo2->BackDefault();
}
*/

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