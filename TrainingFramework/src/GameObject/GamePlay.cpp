#include "GamePlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Text.h"
#include "Application.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern bool isPlaySound;
extern bool isPlayMusic;
extern bool playingMusic;
extern int typePoo;
bool isPause;
int GamePlay::num_deaths = 0;
GamePlay::GamePlay(int level)
{
	ResourceManagers::GetInstance()->PauseSound("menu.mp3");
	isPause = false;
	playingMusic = false;
	m_level = level;
	m_time = 0.0f;
	isStart = true;
	isLost = false;
	isLoadSwitch = true;
	m_timeLoadSwitch = 0.0f;
	isNotiLost = false;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	//auto texture = ResourceManagers::GetInstance()->GetTexture("Tile\\-1");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	auto texture = ResourceManagers::GetInstance()->GetTexture("Menu\\Switch");
	Switch = std::make_shared<Sprite2D>(model, shader, texture);
	Switch->Set2DPosition(0, screenHeight / 2);
	Switch->SetSize(screenWidth, screenHeight);

	//BackGround
	texture = ResourceManagers::GetInstance()->GetTexture("Tile\\-1");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth * 3, screenHeight * 3);

	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\Gray");
	Gray = std::make_shared<Sprite2D>(model, shader, texture);
	Gray->Set2DPosition(screenWidth / 2, 50);
	Gray->SetSize(screenWidth, 50);

	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\back_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(30, 50);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		num_deaths = 0;
		if (isPlayMusic) {
			ResourceManagers::GetInstance()->PauseSound("music_game.wav");
			ResourceManagers::GetInstance()->PlaySound("menu.mp3", true);
			playingMusic = true;
		}
		
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	texture = ResourceManagers::GetInstance()->GetTexture("pause");
	buttonPause1 = std::make_shared<GameButton>(model, shader, texture);
	buttonPause1->Set2DPosition(450, 50);
	buttonPause1->SetSize(40, 40);
	buttonPause1->SetOnClick([]() {
		std::cout << "pause";
		isPause = true;
		});

	texture = ResourceManagers::GetInstance()->GetTexture("play");
	buttonPause2 = std::make_shared<GameButton>(model, shader, texture);
	buttonPause2->Set2DPosition(450, 50);
	buttonPause2->SetSize(40, 40);
	buttonPause2->SetOnClick([]() {
		isPause = false;
		});


	buttonPause = buttonPause1;

	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\Stage");
	Stage = std::make_shared<Sprite2D>(model, shader, texture);
	Stage->Set2DPosition(screenWidth / 4, 50);
	Stage->SetSize(100, 25);

	char s0[10];
	char s1[10];
	sprintf(s0, "Num\\B%d", level / 10);
	sprintf(s1, "Num\\B%d", level % 10);
	texture = ResourceManagers::GetInstance()->GetTexture(std::string(s0));
	S0 = std::make_shared<Sprite2D>(model, shader, texture);
	S0->Set2DPosition(screenWidth / 4 + 75, 50);
	S0->SetSize(20, 25);

	texture = ResourceManagers::GetInstance()->GetTexture(std::string(s1));
	S1 = std::make_shared<Sprite2D>(model, shader, texture);
	S1->Set2DPosition(screenWidth / 4 + 95, 50);
	S1->SetSize(20, 25);

	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\Deaths");
	Deaths = std::make_shared<Sprite2D>(model, shader, texture);
	Deaths->Set2DPosition(2.75f * screenWidth / 4 -20, 50);
	Deaths->SetSize(100, 25);

	char d0[10];
	char d1[10];
	sprintf(d0, "Num\\B%d", num_deaths / 10);
	sprintf(d1, "Num\\B%d", num_deaths % 10);

	texture = ResourceManagers::GetInstance()->GetTexture(std::string(d0));
	D0 = std::make_shared<Sprite2D>(model, shader, texture);
	D0->Set2DPosition(2.75f * screenWidth / 4 + 55, 50);
	D0->SetSize(20, 25);

	texture = ResourceManagers::GetInstance()->GetTexture(std::string(d1));
	D1 = std::make_shared<Sprite2D>(model, shader, texture);
	D1->Set2DPosition(2.75f * screenWidth / 4 + 75, 50);
	D1->SetSize(20, 25);


	map2 = std::make_shared<Map2>(level);


	//Khoi tao Enemy
	for (auto it : map2->getListEnemyData()) {
		switch (it->type)
		{
		case 0:
		{
			auto enemy = std::make_shared<Enemy0>(it->cEnemy.x, it->cEnemy.y, it->dir, it->move, it->maxMove1, it->speed, map2);
			m_listEnemy.push_back(enemy);
			break;
		}
		case 2:
		{
			auto enemy = std::make_shared<Enemy2>(it->cEnemy.x, it->cEnemy.y, it->dir, it->move, it->maxMove1, it->maxMove2, it->speed, map2);
			m_listEnemy.push_back(enemy);
			break;
		}
		case 3:
		{
			auto enemy = std::make_shared<Enemy3>(it->cEnemy.x, it->cEnemy.y, it->dir, it->move, it->maxMove1, it->speed, map2);
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


GamePlay::~GamePlay()
{

}


void GamePlay::HandleKeyEvents(int key, bool bIsPressed)
{
	m_poo2->HandleKeyEvents(key, bIsPressed);
}

void GamePlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
	buttonPause->HandleTouchEvents(x, y, bIsPressed);
}

void GamePlay::Update(float deltaTime)
{
	if (isPause) {
		buttonPause = buttonPause2;
		return;
	}
	buttonPause = buttonPause1;
	if (isLoadSwitch)
	{
		float xSwitch = Switch->Get2DPosition().x;
		float xSwitchDis = Switch->Get2DPosition().x - screenWidth / 2;
		xSwitchDis = xSwitchDis > 0 ? xSwitchDis : -1.0f * xSwitchDis;
		if (xSwitchDis > 16.0f)
		{
			xSwitch += 1000.0f * deltaTime;
			Switch->Set2DPosition(xSwitch, screenHeight / 2);
		}
		else
		{
			m_timeLoadSwitch += deltaTime;
			xSwitch = screenWidth / 2;
			Switch->Set2DPosition(xSwitch, screenHeight / 2);
			if (m_timeLoadSwitch >= 0.7f)
			{
				xSwitch += 17.0f;
				Switch->Set2DPosition(xSwitch, screenHeight / 2);
			}
		}
	}
	if (isLost)
	{
		m_poo2->MOVE = 0;
		m_time += deltaTime;
		if (m_time >= 0.6f)
		{
			m_time = 0.0f;
			isLost = false;
			isNotiLost = false;
			Reset();
			num_deaths++;
			char d0[10];
			char d1[10];
			sprintf(d0, "Num\\B%d", num_deaths / 10);
			sprintf(d1, "Num\\B%d", num_deaths % 10);
			D0->SetTexture(ResourceManagers::GetInstance()->GetTexture(std::string(d0)));
			D1->SetTexture(ResourceManagers::GetInstance()->GetTexture(std::string(d1)));
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
		if (!isNotiLost && isPlaySound)
		{
			isNotiLost = true;
			ResourceManagers::GetInstance()->PlaySound("kill.mp3");
		}

		isLost = true;
	}
	if (m_poo2->CheckEatGold())
	{
		if(isPlaySound) ResourceManagers::GetInstance()->PlaySound("coin.mp3");
		if (RemGold > 0)
		{
			RemGold = RemGold - 1;
		}

		//std::cout << "Remaining Gold: " << RemGold << std::endl;
	}
	if ((RemGold == 0) && (m_poo2->CheckEndPoint()))
	{
		std::cout << "WIN";
		m_level++;
		isWin = true;
	}
}

void GamePlay::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	buttonPause->Draw();
	map2->DrawMap();


	for (auto it : m_listEnemy)
	{
		it->Draw();
	}

	for (auto obj : m_listGold)
	{
		obj->Draw();
	}
	m_poo2->Draw();
	Gray->Draw();
	Stage->Draw();
	S0->Draw();
	S1->Draw();
	Deaths->Draw();
	D0->Draw();
	D1->Draw();
	Switch->Draw();
	
}

void GamePlay::Reset()
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