#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

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
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Tile\\-1");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth*3, screenHeight*3);

	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\back_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(20, 20);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


	//text game title
	
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(screenWidth/2, 100));

	
	//myMap = std::make_shared<Map2>(2);
	//Khoi tao map 
	//map = std::make_shared<Map>(2);
	//map->loadMap();
	map2 = std::make_shared<Map2>(2);

	

	
	
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
	//Khoi tao Poo
	m_poo2 = std::make_shared<Poo2>(map2->getPoo().dir, map2->getPoo().cDest.x, map2->getPoo().cDest.y, map2,m_listEnemy,m_listGold);
	//Khoi tao gold

	
	ResourceManagers::GetInstance()->PlaySound("test.mp3");

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
	for (auto obj : m_listGold)
	{
		obj->Update(deltaTime);
	}
	for (auto it : m_listEnemy)
	{
		it->Update(deltaTime);
		//m_poo->checkColli(it);
	}
	m_poo2->Update(deltaTime);

}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_score->Draw();
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