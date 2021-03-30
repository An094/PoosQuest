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
	m_BackGround->SetSize(screenWidth, screenHeight);

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
	

	//Khoi tao map 
	map = std::make_shared<Map>(2);
	map->loadMap();

	//Khoi tao Poo
	m_poo = std::make_shared<Poo>(map->poo.dir, map->poo.cStart.x, map->poo.cStart.y, map->poo.cDest.x, map->poo.cDest.y, map);
	m_poo->loadImage();
	
	//Khoi tao Enemy
	for (auto it : map->m_listEnemyData) {
		switch (it->type)
		{
		case 0: 
		{
			printf("vao switch\n");
			auto enemy = std::make_shared<Enemy0>(it->cEnemy.x, it->cEnemy.y, it->dir, it->move, it->maxMove, it->speed);
			enemy->loadImage();
			m_listEnemy.push_back(enemy);
			break;
		}
			
		default:
			break;
		}
	}
	//Khoi tao gold

	auto modelGold = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shaderGold = ResourceManagers::GetInstance()->GetShader("Animation");
	auto textureGold = ResourceManagers::GetInstance()->GetTexture("gold");
	for (auto it : map->m_listGold) {
		auto gold = std::make_shared<SpriteAnimation2D>(modelGold, shaderGold, textureGold, 8, 0.1f);
		gold->SetSize(20, 30);
		float x = it->x * TILESIZE + TILESIZE / 2 + 50;
		float y = it->y * TILESIZE + TILESIZE / 2 + 140;
		gold->Set2DPosition(x, y);
		m_listSpriteAnimations.push_back(gold);
	}
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
	m_poo->handleKeyEvents(key, bIsPressed);
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

	map->update(deltaTime);
	for (auto obj : m_listSpriteAnimations)
	{
		obj->Update(deltaTime);
	}
	m_poo->update(deltaTime);
	for (auto it : m_listEnemy)
	{
		it->update(deltaTime);
		m_poo->checkColli(it);
	}
	
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	map->draw();
	
	for (auto obj : m_listSpriteAnimations)
	{
		obj->Draw();
	}
	for (auto it : m_listEnemy)
	{
		it->draw();
	}
	m_poo->draw();
}

void GSPlay::SetNewPostionForBullet()
{
}