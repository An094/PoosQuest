#include "Poo2.h"
#include "Enemy.h"
#include "Enemy0.h"
#include "Gold.h"
Poo2::Poo2(int dir, int xEnd, int yEnd,std::shared_ptr<Map2> map, std::list<std::shared_ptr<Enemy>> listEnemy, std::list<std::shared_ptr<Gold>> listGold) :DynamicObject()
{
	isAlive = true;
	myMap = map;
	mapconvert = map->getMapConvert();
	m_listEnemy = listEnemy;
	m_listGold = listGold;
	dest.x = xEnd * TILESIZE + TILESIZE / 2 + 50.0f;
	dest.y = yEnd * TILESIZE + TILESIZE / 2 + 140.0f;
	setDir(dir);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_up");
	auto tempSprite = std::make_shared<SpriteAnimation2D>(model, shader, texture, 6, 0.1f);
	tempSprite->SetSize(60, 46);
	vPose.push_back(tempSprite);//index 0

	texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_right");
	tempSprite = std::make_shared<SpriteAnimation2D>(model, shader, texture, 6, 0.1f);
	tempSprite->SetSize(60, 46);
	vPose.push_back(tempSprite);//index 1

	texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_down");
	tempSprite = std::make_shared<SpriteAnimation2D>(model, shader, texture, 6, 0.1f);
	tempSprite->SetSize(60, 46);
	vPose.push_back(tempSprite);//index 2

	texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_left");
	tempSprite = std::make_shared<SpriteAnimation2D>(model, shader, texture, 6, 0.1f);
	tempSprite->SetSize(60, 46);
	vPose.push_back(tempSprite);//index 3

	m_poo = vPose[getDir()];
	m_poo->Set2DPosition(screenWidth/2, screenHeight/2);
}
Poo2::~Poo2()
{

}

sCoor Poo2::getCoorPoo()
{
	sCoor CoorPoo;
	CoorPoo.x = (screenWidth / 2 - myMap->getStartPos().x) / TILESIZE;
	CoorPoo.y = (screenHeight / 2 - myMap->getStartPos().y) / TILESIZE;
	return CoorPoo;
}
void Poo2::HandleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		MOVE = key;
	}
	else MOVE = 0;
}
void Poo2::MoveUp(float deltaTime)
{
	//std::cout << "x: " << getCoorPoo().x << "y: " << getCoorPoo().y << std::endl;
	setDir(0);
	m_poo = vPose[0];
	myMap->MoveMap(0.0f, 5.0f);
	for (auto it : m_listEnemy)
	{
		(it)->MoveWithPoo(0.0f, 5.0f);
	}
	for (auto it : m_listGold)
	{
		(it)->MoveWithPoo(0.0f, 5.0f);
	}
}
void Poo2::MoveDown(float deltaTime)
{
	setDir(2);
	m_poo = vPose[2];
	myMap->MoveMap(0.0f, -5.0f);
	for (auto it : m_listEnemy)
	{
		(it)->MoveWithPoo(0.0f, -5.0f);
	}
	for (auto it : m_listGold)
	{
		(it)->MoveWithPoo(0.0f, -5.0f);
	}
}
void Poo2::MoveRight(float deltaTime)
{
	setDir(1);
	m_poo = vPose[1];
	myMap->MoveMap(-5.0f, 0.0f);
	for (auto it : m_listEnemy)
	{
		(it)->MoveWithPoo(-5.0f, 0.0f);
	}
	for (auto it : m_listGold)
	{
		(it)->MoveWithPoo(-5.0f, 0.0f);
	}
}
void Poo2::MoveLeft(float deltaTime)
{
	setDir(3);
	m_poo = vPose[3];
	myMap->MoveMap(5.0f, 0.0f);
	
	for (auto it : m_listEnemy)
	{
		(it)->MoveWithPoo(5.0f, 0.0f);
	}
	for (auto it : m_listGold)
	{
		(it)->MoveWithPoo(5.0f, 0.0f);
	}
}
/*
bool Poo2::checkColli(std::shared_ptr<Enemy> enemy)
{
	Vector2 coorEnemy = enemy->getPos();
	float distX = currentXPos - coorEnemy.x;
	distX = distX > 0 ? distX : (-distX);
	float distY = currentYPos - coorEnemy.y;
	distY = distY > 0 ? distY : (-distY);
	if (distX < 15.0f && distY < 15.0f)
	{
		std::cout << "game_over";
		return false;
	}
}
*/
void Poo2::Draw()
{
	m_poo->Draw();
}
void Poo2::Move(float deltaTime)
{
	if (isAlive)
	{
		sCoor currentCoor = getCoorPoo();
		//std::cout << "x: " << currentCoor.x << "y: " << currentCoor.y << std::endl;

		int left = (screenWidth / 2 - xColl + TILESIZE/2 - myMap->getStartPos().x) / TILESIZE;
		int right = (screenWidth / 2 + xColl + TILESIZE/2 - myMap->getStartPos().x) / TILESIZE;
		int top = (screenHeight / 2 - yColl + 0.75f *TILESIZE-  myMap->getStartPos().y) / TILESIZE;
		int bottom = (screenHeight / 2 + yColl + 0.75f*TILESIZE - myMap->getStartPos().y) / TILESIZE;


		switch (MOVE)
		{
		case KEY_UP:
		{

			if ((mapconvert[top][left] != 1) && (mapconvert[top][right] != 1)
				&& (mapconvert[top][left] != 5) && (mapconvert[top][right] != 5)
				&& (mapconvert[top][left] != 8) && (mapconvert[top][right] != 8)
				&& (mapconvert[top][left] != -1) && (mapconvert[top][right] != -1))
				MoveUp(deltaTime);
			break;
		}
			
		case KEY_DOWN:
			if ((mapconvert[bottom][left] != 3) && (mapconvert[bottom][right] != 3)
				&& (mapconvert[bottom][left] != 6) && (mapconvert[bottom][right] != 6)
				&& (mapconvert[bottom][left] != 7) && (mapconvert[bottom][right] != 7)
				&& (mapconvert[bottom][left] != -1) && (mapconvert[bottom][right] != -1)) 
				MoveDown(deltaTime);
			break;
		case KEY_RIGHT:
			if ((mapconvert[top][right] != 2)&&(mapconvert[bottom][right] != 2)
				&& (mapconvert[top][right] != 5) && (mapconvert[bottom][right] != 5)
				&& (mapconvert[top][right] != 6) && (mapconvert[bottom][right] != 6)
				&& (mapconvert[top][right] != -1) && (mapconvert[bottom][right] != -1)) 
				MoveRight(deltaTime);
			break;
		case KEY_LEFT:
			if ((mapconvert[top][left] != 4) && (mapconvert[bottom][left] != 4)
				&& (mapconvert[top][left] != 8) && (mapconvert[bottom][left] != 8)
				&& (mapconvert[top][left] != 7) && (mapconvert[bottom][left] != 7)
				&& (mapconvert[top][left] != -1) && (mapconvert[bottom][left] != -1)) 
				MoveLeft(deltaTime);
			break;
		default:
			break;
		}

	}

}
void Poo2::Update(float deltaTime)
{
	m_poo->Update(deltaTime);
	Move(deltaTime);
}