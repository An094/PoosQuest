#include "GSSetting.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
bool isPlaySound = true;
bool isPlayMusic = true;
bool playingMusic;
int count = 0;
bool isSoundPress;
bool isMusicPress;
GSSetting::GSSetting()
{

}


GSSetting::~GSSetting()
{
}



void GSSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_setting");

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



	//button Sound
	texture = ResourceManagers::GetInstance()->GetTexture("sound_on");
	buttonSound = std::make_shared<GameButton>(model, shader, texture);
	buttonSound->Set2DPosition(350, 290);
	buttonSound->SetSize(60, 60);
	buttonSound->SetOnClick([]() {
		count++;
		isSoundPress = true;
		isPlaySound = !isPlaySound;
	});
	m_listButton.push_back(buttonSound);

	//button Music
	texture = ResourceManagers::GetInstance()->GetTexture("sound_on");
	buttonMusic = std::make_shared<GameButton>(model, shader, texture);
	buttonMusic->Set2DPosition(350, 370);
	buttonMusic->SetSize(60, 60);
	buttonMusic->SetOnClick([]() {
		count++;
		isMusicPress = true;
		isPlayMusic = !isPlayMusic;
	});
	m_listButton.push_back(buttonMusic);

}

void GSSetting::Exit()
{
}


void GSSetting::Pause()
{

}

void GSSetting::Resume()
{

}


void GSSetting::HandleEvents()
{

}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSSetting::Update(float deltaTime)
{

	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if ((count % 2 == 0) && isSoundPress) {
		isPlaySound = !isPlaySound;
		isSoundPress = false;
	}
	if ((count % 2 == 0) && isMusicPress) {
		isPlayMusic = !isPlayMusic;
		isMusicPress = false;
	}
	if (isPlaySound) {
		m_listButton[1]->SetTexture(ResourceManagers::GetInstance()->GetTexture("sound_on"));
	}
	else {
		m_listButton[1]->SetTexture(ResourceManagers::GetInstance()->GetTexture("sound_off"));
	}
	if (isPlayMusic)
	{
		m_listButton[2]->SetTexture(ResourceManagers::GetInstance()->GetTexture("sound_on"));
		if (!playingMusic)
		{
			ResourceManagers::GetInstance()->PlaySound("menu.mp3", true);
			playingMusic = true;
		}

	}
	else {
		m_listButton[2]->SetTexture(ResourceManagers::GetInstance()->GetTexture("sound_off"));
		if (playingMusic) {
			ResourceManagers::GetInstance()->PauseSound("menu.mp3");
			playingMusic = false;
		}
	}
}

void GSSetting::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}

