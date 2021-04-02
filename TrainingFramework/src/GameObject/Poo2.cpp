#include "Poo2.h"
#include "Enemy.h"
#include "Enemy0.h"
#include "Gold.h"
Poo2::Poo2(int dir, int xEnd, int yEnd,std::shared_ptr<Map2> map, std::list<std::shared_ptr<Enemy>> listEnemy, std::list<std::shared_ptr<Gold>> listGold) :DynamicObject()
{
	isAlive = true;
	defaultDir = dir;
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

	texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_dead");
	tempSprite = std::make_shared<SpriteAnimation2D>(model, shader, texture, 6, 0.1f);
	tempSprite->SetSize(60, 46);
	vPose.push_back(tempSprite);//index 4

	m_poo = vPose[getDir()];
	m_poo->Set2DPosition(screenWidth/2, screenHeight/2);
}
Poo2::~Poo2()
{
	m_poo.~shared_ptr();
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
	Vector2 upMove(0.0f, 1.25f);
	setDir(0);
	m_poo = vPose[0];
	myMap->MoveMap(0.0f, 1.25f *speed * deltaTime);
	for (auto it : m_listEnemy)
	{
		//(it)->MoveWithPoo(0.0f, 5.0f);
		//(it)->Move(deltaTime, 0.0f, speed * deltaTime);
		(it)->MoveDirWithPoo(deltaTime, upMove);
	}
	for (auto it : m_listGold)
	{
		(it)->MoveWithPoo(0.0f,1.25f * speed * deltaTime);
	}
}
void Poo2::MoveDown(float deltaTime)
{
	Vector2 downMove(0.0f, -1.25f);
	setDir(2);
	m_poo = vPose[2];
	myMap->MoveMap(0.0f, -1.25 * speed * deltaTime);
	for (auto it : m_listEnemy)
	{
		//(it)->MoveWithPoo(0.0f, -1 * speed * deltaTime);
		//(it)->Move(deltaTime, 0.0f,-1 * speed * deltaTime);
		(it)->MoveDirWithPoo(deltaTime, downMove);
	}
	for (auto it : m_listGold)
	{
		(it)->MoveWithPoo(0.0f, -1.25f * speed * deltaTime);
	}
}
void Poo2::MoveRight(float deltaTime)
{
	Vector2 rightMove(-1.25f, 0.0f);
	setDir(1);
	m_poo = vPose[1];
	myMap->MoveMap(-1.25f * speed * deltaTime, 0.0f);
	for (auto it : m_listEnemy)
	{
		//(it)->MoveWithPoo(-5.0f, 0.0f);
		//(it)->Move(deltaTime, -1 * speed * deltaTime, 0.0f);
		(it)->MoveDirWithPoo(deltaTime, rightMove);
	}
	for (auto it : m_listGold)
	{
		(it)->MoveWithPoo(-1.25f * speed * deltaTime, 0.0f);
	}
}
void Poo2::MoveLeft(float deltaTime)
{
	Vector2 leftMove(1.25f, 0.0f);
	setDir(3);
	m_poo = vPose[3];
	myMap->MoveMap(1.25f *speed * deltaTime, 0.0f);
	
	for (auto it : m_listEnemy)
	{
		//(it)->MoveWithPoo(speed * deltaTime, 0.0f);
		//(it)->Move(deltaTime, speed * deltaTime, 0.0f);
		(it)->MoveDirWithPoo(deltaTime, leftMove);
	}
	for (auto it : m_listGold)
	{
		(it)->MoveWithPoo(1.25f *speed * deltaTime, 0.0f);
	}
}
void Poo2::AutoMove(float deltaTime)
{
	for (auto it : m_listEnemy)
	{
		(it)->MoveDirWithPoo(deltaTime);
	}
}
void Poo2::MoveDir(Vector2 vector, float deltaTime)
{
	for (auto it : m_listEnemy)
	{
		(it)->MoveDirWithPoo(deltaTime, vector);
	}
}

bool Poo2::CheckCollision()
{
	for (auto it : m_listEnemy)
	{
		Vector2 posEnemy = it->getPos();
		float distX = screenWidth/2 - posEnemy.x;
		float distY = screenHeight/2 - posEnemy.y;
		distX = distX > 0 ? distX : (-distX);
		distY = distY > 0 ? distY : (-distY);
		if (distX < 15.0f && distY < 15.0f)
		{
			m_poo = vPose[4];

			return true;
		}
	}
	return false;
}
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
			else AutoMove(deltaTime);
			break;
		}
			
		case KEY_DOWN:
		{
			if ((mapconvert[bottom][left] != 3) && (mapconvert[bottom][right] != 3)
				&& (mapconvert[bottom][left] != 6) && (mapconvert[bottom][right] != 6)
				&& (mapconvert[bottom][left] != 7) && (mapconvert[bottom][right] != 7)
				&& (mapconvert[bottom][left] != -1) && (mapconvert[bottom][right] != -1))
				MoveDown(deltaTime);
			else AutoMove(deltaTime);

			break;
		}
			
		case KEY_RIGHT:
		{
			if ((mapconvert[top][right] != 2) && (mapconvert[bottom][right] != 2)
				&& (mapconvert[top][right] != 5) && (mapconvert[bottom][right] != 5)
				&& (mapconvert[top][right] != 6) && (mapconvert[bottom][right] != 6)
				&& (mapconvert[top][right] != -1) && (mapconvert[bottom][right] != -1))
				MoveRight(deltaTime);
			else AutoMove(deltaTime);

			break;
		}
			
		case KEY_LEFT:
		{
			if ((mapconvert[top][left] != 4) && (mapconvert[bottom][left] != 4)
				&& (mapconvert[top][left] != 8) && (mapconvert[bottom][left] != 8)
				&& (mapconvert[top][left] != 7) && (mapconvert[bottom][left] != 7)
				&& (mapconvert[top][left] != -1) && (mapconvert[bottom][left] != -1))
				MoveLeft(deltaTime);
			else AutoMove(deltaTime);
			break;
		}
			
		default:
		{
			AutoMove(deltaTime);
		}
			break;
		}

	}

}
void Poo2::BackDefault()
{
	m_poo = vPose[defaultDir];
}
void Poo2::Update(float deltaTime)
{
	m_poo->Update(deltaTime);
	Move(deltaTime);
	//CheckCollision();
}