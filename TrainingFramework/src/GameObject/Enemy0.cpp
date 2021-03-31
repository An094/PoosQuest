#include "Enemy0.h"
Enemy0::Enemy0(int x, int y, int dir, int move, int maxMove, int speed, std::shared_ptr<Map2> map)
	: Enemy(0,x,y,dir)
{
	maxMoveDis = maxMove * TILESIZE;
	currentMove = 0;


	
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_up");
	auto tempSprite = std::make_shared<SpriteAnimation2D>(model, shader, texture, 8, 0.1f);
	tempSprite->SetSize(40, 44);
	vPoseE.push_back(tempSprite);//index 0

	texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_right");
	tempSprite = std::make_shared<SpriteAnimation2D>(model, shader, texture, 8, 0.1f);
	tempSprite->SetSize(40, 44);
	vPoseE.push_back(tempSprite);//index 1

	texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_down");
	tempSprite = std::make_shared<SpriteAnimation2D>(model, shader, texture, 8, 0.1f);
	tempSprite->SetSize(40, 44);
	vPoseE.push_back(tempSprite);//index 2

	texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_left");
	tempSprite = std::make_shared<SpriteAnimation2D>(model, shader, texture, 8, 0.1f);
	tempSprite->SetSize(40, 44);
	vPoseE.push_back(tempSprite);//index 3


	sPoo poo = map->getPoo();
	int xPos = (x - poo.cStart.x) * TILESIZE + screenWidth / 2;
	int yPos = (y - poo.cStart.y) * TILESIZE + screenHeight / 2;
	oldPos.x = xPos;
	oldPos.y = yPos;
	currentPos = oldPos;
	enemy = vPoseE[getDir()];
	enemy->Set2DPosition(xPos, yPos);
}
Enemy0::~Enemy0()
{

}
void Enemy0::Move(float deltaTime)
{
	switch (getDir())
	{
	case 0:
	{
		if (currentMove <= maxMoveDis) {
			currentMove += speed * deltaTime;
			currentPos.y = oldPos.y - currentMove;
			enemy->Set2DPosition(currentPos.x,currentPos.y);
		}
		else
		{
			oldPos = currentPos;
			currentMove = 0;
			setDir(2);
			enemy = vPoseE[2];
		}
		break;
	}
	case 1:
	{
		if (currentMove <= maxMoveDis) {
			currentMove += speed * deltaTime;
			currentPos.x = oldPos.x + currentMove;
			enemy->Set2DPosition(currentPos.x, currentPos.y);
		}
		else
		{
			oldPos = currentPos;
			currentMove = 0;
			setDir(3);
			enemy = vPoseE[3];
		}
		break;
	}
	case 2:
	{
		if (currentMove <= maxMoveDis) {
			currentMove += speed * deltaTime;
			currentPos.y = oldPos.y + currentMove;
			enemy->Set2DPosition(currentPos.x, currentPos.y);
		}
		else
		{
			oldPos = currentPos;
			currentMove = 0;
			setDir(0);
			enemy = vPoseE[0];
		}
		break;
	}
	case 3:
	{
		if (currentMove <= maxMoveDis) {
			currentMove += speed * deltaTime;
			currentPos.x = oldPos.x - currentMove;
			enemy->Set2DPosition(currentPos.x, currentPos.y);
		}
		else
		{
			oldPos = currentPos;
			currentMove = 0;
			setDir(1);
			enemy = vPoseE[1];
		}
		break;
	}
	default:
		break;
	}
}
void Enemy0::MoveWithPoo(float x, float y)
{
	Vector2 pos = getPos();
	enemy->Set2DPosition(pos.x + x, pos.y + y);
}
void Enemy0::Draw()
{
	enemy->Draw();
}
void Enemy0::Update(float deltaTime)
{
	
	enemy->Update(deltaTime);
	//Move(deltaTime);
}
