#include "GSCredit.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSCredit::GSCredit()
{

}


GSCredit::~GSCredit()
{
}



void GSCredit::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_credit");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\back_play");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(20, 20);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);

	//Text
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	text = std::make_shared< Text>(shader, font, "Game Design: Ngo Thai An", TEXT_COLOR::RED, 1.0);
	text->Set2DPosition(Vector2(90, 100));

	text2 = std::make_shared< Text>(shader, font, "based on Game Poo's Quest", TEXT_COLOR::RED, 1.0);
	text2->Set2DPosition(Vector2(80, 150));

	text3 = std::make_shared< Text>(shader, font, "by Khanh Nguyen", TEXT_COLOR::RED, 1.0);
	text3->Set2DPosition(Vector2(150, 200));

	text4 = std::make_shared< Text>(shader, font, "Programmer: Ngo Thai An", TEXT_COLOR::RED, 1.0);
	text4->Set2DPosition(Vector2(90, 250));


	text5 = std::make_shared< Text>(shader, font, "Instructors:", TEXT_COLOR::RED, 1.0);
	text5->Set2DPosition(Vector2(170, 350));

	text6 = std::make_shared< Text>(shader, font, "Nguyen Huu Hoang", TEXT_COLOR::RED, 1.0);
	text6->Set2DPosition(Vector2(135, 400));

	text7 = std::make_shared< Text>(shader, font, "Hoang Manh Hung", TEXT_COLOR::RED, 1.0);
	text7->Set2DPosition(Vector2(135, 450));
	//

}

void GSCredit::Exit()
{
}


void GSCredit::Pause()
{

}

void GSCredit::Resume()
{

}


void GSCredit::HandleEvents()
{

}

void GSCredit::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSCredit::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSCredit::Update(float deltaTime)
{

	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	text->Update(deltaTime);
}

void GSCredit::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	text->Draw();
	text2->Draw();
	text3->Draw();
	text4->Draw();
	text5->Draw();
	text6->Draw();
	text7->Draw();
}

