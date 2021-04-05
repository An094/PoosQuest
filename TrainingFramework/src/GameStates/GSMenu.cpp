#include "GSMenu.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern bool isPlaySound;
extern bool isPlayMusic;
extern bool playingMusic;
GSMenu::GSMenu()
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


GSMenu::~GSMenu()
{
}



void GSMenu::Init()
{
	ResourceManagers::GetInstance()->PlaySound("menu.mp3",  true);
	playingMusic = true;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);
	//logo
	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\Logo");
	m_Logo = std::make_shared<Sprite2D>(model, shader, texture);
	m_Logo->Set2DPosition(oldXPos, oldYPos);
	m_Logo->SetSize(300, 150);


	//play button
	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\button_play");
	std::shared_ptr<GameButton> buttonPlay = std::make_shared<GameButton>(model, shader, texture);
	buttonPlay->Set2DPosition(screenWidth / 2, 370);
	buttonPlay->SetSize(250, 100);
	buttonPlay->SetOnClick([]() {
		//ResourceManagers::GetInstance()->PauseSound("menu.mp3");
		//ResourceManagers::GetInstance()->PlaySound("growing_on_me.mp3", true);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		
		});
	m_listButton.push_back(buttonPlay);



	//credit button

	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\button_credit");
	std::shared_ptr<GameButton> buttonCredit = std::make_shared<GameButton>(model, shader, texture);
	buttonCredit->Set2DPosition(screenWidth - 35, screenHeight - 135);
	buttonCredit->SetSize(40, 40);
	buttonCredit->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Credit);
		});
	m_listButton.push_back(buttonCredit);
	

	//setting button
	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\button_setting");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth - 35, screenHeight - 85);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Setting);
		});
	m_listButton.push_back(button);

	//exit button
	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\button_exit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth -35, screenHeight-35);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		exit(0);
		});
	m_listButton.push_back(button);

	
}
void GSMenu::dynamicLogo(float deltaTime)
{
	if (currentMove <= maxMove)
	{
		if (state == 0)
		{
			currentMove += speed * deltaTime;
			currentYPos = oldYPos - currentMove;
			m_Logo->Set2DPosition(currentXPos, currentYPos);
		}
		else
		{
			currentMove += speed * deltaTime;
			currentYPos = oldYPos + currentMove;
			m_Logo->Set2DPosition(currentXPos, currentYPos);
		}
	}
	else
	{
		state = 1 - state;
		currentMove -= maxMove;
		oldYPos = currentYPos;
	}
}

void GSMenu::Exit()
{
}


void GSMenu::Pause()
{

}

void GSMenu::Resume()
{

}


void GSMenu::HandleEvents()
{

}

void GSMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSMenu::Update(float deltaTime)
{
	/*
	if (isPlayMusic)
	{
		ResourceManagers::GetInstance()->PlaySound("menu.mp3", true);
		isPlayMusic = false;
	}
	*/
	
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	m_Logo->Update(deltaTime);
	dynamicLogo(deltaTime);
}

void GSMenu::Draw()
{
	m_BackGround->Draw();
	m_Logo->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	
	//m_Text_gameName->Draw();
}

