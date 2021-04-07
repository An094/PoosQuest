#include "GSLoad.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern bool isPlaySound;
extern bool isPlayMusic;
extern bool playingMusic;
int levelGame = 1;
int levelMax = 8;
int typePoo = 0;
GSLoad::GSLoad()
{
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}


GSLoad::~GSLoad()
{
}



void GSLoad::Init()
{
	playingMusic = true;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\back_play");
	m_buttonBack = std::make_shared<GameButton>(model, shader, texture);
	m_buttonBack->Set2DPosition(30, 50);
	m_buttonBack->SetSize(40, 40);
	m_buttonBack->SetOnClick([]() {
		if (isPlayMusic) {
			playingMusic = true;
		}

		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(m_buttonBack);

	//Ani Poo
	auto aniShader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_down");
	AniPoo0 = std::make_shared<SpriteAnimation2D>(model, aniShader, texture, 6, 0.1f);
	AniPoo0->Set2DPosition(screenWidth / 2, 200);
	AniPoo0->SetSize(80, 60);

	texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo1_down");
	AniPoo1 = std::make_shared<SpriteAnimation2D>(model, aniShader, texture, 4, 0.1f);
	AniPoo1->Set2DPosition(screenWidth / 2, 200);
	AniPoo1->SetSize(60, 45);

	AniPoo = AniPoo0;
	//button char left
	texture = ResourceManagers::GetInstance()->GetTexture("Num\\Lw");
	m_buttonCharLeft = std::make_shared<GameButton>(model, shader, texture);
	m_buttonCharLeft->Set2DPosition(150, 200);
	m_buttonCharLeft->SetSize(20, 35);
	m_buttonCharLeft->SetOnClick([]() {
		std::cout << "ButtonPress";
		if (typePoo == 0) typePoo = 1;
		else if (typePoo == 1) typePoo = 0;
		});
	m_listButton.push_back(m_buttonCharLeft);
	//button char right
	texture = ResourceManagers::GetInstance()->GetTexture("Num\\Rw");
	m_buttonCharRight = std::make_shared<GameButton>(model, shader, texture);
	m_buttonCharRight->Set2DPosition(330, 200);
	m_buttonCharRight->SetSize(20, 35);
	m_buttonCharRight->SetOnClick([]() {
		if (typePoo == 0) typePoo = 1;
		else if (typePoo == 1) typePoo = 0;
		});
	m_listButton.push_back(m_buttonCharRight);


	char s0[10];
	char s1[10];
	sprintf(s0, "Num\\B%dw", levelGame / 10);
	sprintf(s1, "Num\\B%dw", levelGame % 10);
	texture = ResourceManagers::GetInstance()->GetTexture(std::string(s0));
	levelLeft = std::make_shared<Sprite2D>(model, shader, texture);
	levelLeft->Set2DPosition(screenWidth / 2 - 25, 300);
	levelLeft->SetSize(40, 50);

	texture = ResourceManagers::GetInstance()->GetTexture(std::string(s1));
	levelRight = std::make_shared<Sprite2D>(model, shader, texture);
	levelRight->Set2DPosition(screenWidth / 2 + 25, 300);
	levelRight->SetSize(40, 50);


	texture = ResourceManagers::GetInstance()->GetTexture("Num\\Lw");
	m_buttonLevelLeft = std::make_shared<GameButton>(model, shader, texture);
	m_buttonLevelLeft->Set2DPosition(150, 300);
	m_buttonLevelLeft->SetSize(20, 35);
	m_buttonLevelLeft->SetOnClick([]() {
		if(levelGame > 1) levelGame -= 1;
		});
	m_listButton.push_back(m_buttonLevelLeft);

	texture = ResourceManagers::GetInstance()->GetTexture("Num\\Rw");
	m_buttonLevelRight = std::make_shared<GameButton>(model, shader, texture);
	m_buttonLevelRight->Set2DPosition(330, 300);
	m_buttonLevelRight->SetSize(20, 35);
	m_buttonLevelRight->SetOnClick([]() {
		if(levelGame < levelMax)levelGame++;
		});
	m_listButton.push_back(m_buttonLevelRight);


	texture = ResourceManagers::GetInstance()->GetTexture("Menu\\Play");
	std::shared_ptr<GameButton> buttonPlay = std::make_shared<GameButton>(model, shader, texture);
	buttonPlay->Set2DPosition(screenWidth / 2, 450);
	buttonPlay->SetSize(200, 75);
	buttonPlay->SetOnClick([]() {
		//ResourceManagers::GetInstance()->PauseSound("menu.mp3");
		//ResourceManagers::GetInstance()->PlaySound("growing_on_me.mp3", true);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	});
	m_listButton.push_back(buttonPlay);




}

void GSLoad::Exit()
{
}


void GSLoad::Pause()
{

}

void GSLoad::Resume()
{

}


void GSLoad::HandleEvents()
{

}

void GSLoad::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSLoad::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSLoad::Update(float deltaTime)
{

	m_BackGround->Update(deltaTime);
	char s0[10];
	char s1[10];
	sprintf(s0, "Num\\B%dw", levelGame / 10);
	sprintf(s1, "Num\\B%dw", levelGame % 10);
	levelLeft->SetTexture( ResourceManagers::GetInstance()->GetTexture(std::string(s0)));
	levelRight->SetTexture(ResourceManagers::GetInstance()->GetTexture(std::string(s1)));
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	if (typePoo == 0) AniPoo = AniPoo0;
	else if (typePoo == 1) AniPoo = AniPoo1;
	AniPoo->Update(deltaTime);
}

void GSLoad::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	levelLeft->Draw();
	levelRight->Draw();
	AniPoo->Draw();
	//m_Text_gameName->Draw();
}

