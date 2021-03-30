#include "Poo.h"
#include "Enemy.h"
Poo::Poo(int dir, int startCoorX, int startCoorY, int endCoorX, int endCoorY, std::shared_ptr<Map> map)
{
	poo.dir = dir;
	poo.cStart.x = startCoorX;
	poo.cStart.y = startCoorY;
	poo.cDest.x = endCoorX;
	poo.cDest.y = endCoorY;
	currentXPos = poo.cStart.x * TILESIZE + TILESIZE / 2 + 50.0f;
	currentYPos = poo.cStart.y * TILESIZE + TILESIZE / 2 + 140.0f;
	isAlive = true;
	m_map = map;
}
Poo::~Poo()
{

}
void Poo::loadImage()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	std::shared_ptr<Texture> texture;
	switch (getDir())
	{
	case 0:
		texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_up");
		break;
	case 1:
		texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_right");
		break;
	case 2:
		texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_down");
		break;
	case 3:
		texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_left");
		break;
	default:
		break;
	}
	m_poo = std::make_shared<SpriteAnimation2D>(model, shader, texture, 6, 0.1f);
	m_poo->SetSize(60, 46);
	m_poo->Set2DPosition(currentXPos, currentYPos);
}
void Poo::handleKeyEvents(int key, bool bIsPressed)
{
	if (bIsPressed)
	{
		MOVE = key;
	}
	else MOVE = 0;
}
void Poo::move(float deltaTime)
{
	if (isAlive)
	{
		if (MOVE == VK_UP) moveUp(deltaTime);
		else if (MOVE == VK_DOWN) moveDown(deltaTime);
		else if (MOVE == VK_LEFT) moveLeft(deltaTime);
		else if (MOVE == VK_RIGHT) moveRight(deltaTime);
		
	}
}
void Poo::draw()
{
	m_poo->Draw();
}
void Poo::update(float deltaTime)
{
	move(deltaTime);
	m_poo->Update(deltaTime);
	
}
void Poo::moveUp(float deltaTime)
{
	setDir(0);
	int yTemp = (int)(currentYPos -140.0f - yColl) / TILESIZE;
	int x1Temp = (int)(currentXPos -50.0f - xColl) / TILESIZE;
	int x2Temp = (int)(currentXPos -50.0f + xColl) / TILESIZE;
	if ((m_map->map_convert[yTemp][x1Temp] == 1) && (m_map->map_convert[yTemp][x2Temp] == 1))
	{
		currentYPos -= speed * deltaTime;
		//currentYPos -= 5.0f;
		m_poo->Set2DPosition(currentXPos, currentYPos);
		m_poo->SetTexture(ResourceManagers::GetInstance()->GetTexture("Poo\\poo_up"));
	}

}
void Poo::moveDown(float deltaTime)
{
	setDir(2);
	int yTemp = (int)(currentYPos - 140.0f + yColl) / TILESIZE;
	int x1Temp = (int)(currentXPos - 50.0f - xColl) / TILESIZE;
	int x2Temp = (int)(currentXPos - 50.0f + xColl) / TILESIZE;
	if ((m_map->map_convert[yTemp][x1Temp] == 1) && (m_map->map_convert[yTemp][x2Temp] == 1))
	{
		currentYPos += speed * deltaTime;
		//currentYPos += 5.0f;
		m_poo->Set2DPosition(currentXPos, currentYPos);
		m_poo->SetTexture(ResourceManagers::GetInstance()->GetTexture("Poo\\poo_down"));
	}

}
void Poo::moveRight(float deltaTime)
{
	setDir(1);
	int y1Temp = (int)(currentYPos - 140.0f - yColl) / TILESIZE;
	int y2Temp = (int)(currentYPos - 140.0f + yColl) / TILESIZE;
	int xTemp = (int)(currentXPos - 50.0f + xColl) / TILESIZE;
	//std::cout << "xTemp" << xTemp << " y1Temp" << y1Temp << " y2Temp" << y2Temp << std::endl;
	if ((m_map->map_convert[y1Temp][xTemp] == 1) && (m_map->map_convert[y2Temp][xTemp] == 1))
	{
		currentXPos += speed * deltaTime;
		//currentXPos += 5.0f;
		m_poo->Set2DPosition(currentXPos, currentYPos);
		m_poo->SetTexture(ResourceManagers::GetInstance()->GetTexture("Poo\\poo_right"));
	}

}
void Poo::moveLeft(float deltaTime)
{
	setDir(3);
	int y1Temp = (int)(currentYPos - 140.0f - yColl) / TILESIZE;
	int y2Temp = (int)(currentYPos - 140.0f + yColl) / TILESIZE;
	int xTemp = (int)(currentXPos - 50.0f - xColl) / TILESIZE;
	if ((m_map->map_convert[y1Temp][xTemp] == 1) && (m_map->map_convert[y2Temp][xTemp] == 1))
	{
		currentXPos -= speed * deltaTime;
		//currentXPos -= 5.0f;
		m_poo->Set2DPosition(currentXPos, currentYPos);
		m_poo->SetTexture(ResourceManagers::GetInstance()->GetTexture("Poo\\poo_left"));
	}

}
bool Poo::checkColli(std::shared_ptr<Enemy> enemy)
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