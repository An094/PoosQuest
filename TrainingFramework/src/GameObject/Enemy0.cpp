#include "Enemy0.h"
Enemy0::Enemy0(int x, int y, int dir, int move, int maxMove, int speed)
	: Enemy(0, x, y, dir, move, maxMove, speed)
{
	maxMoveDis = maxMove * TILESIZE;
	currentCoorX = x;
	currentCoorY = y;
	oldXPos = currentCoorX * TILESIZE + TILESIZE / 2 + 50;
	oldYPos = currentCoorY * TILESIZE + TILESIZE / 2 + 140;
	currentYPos = oldYPos;
	currentXPos = oldXPos;
	currentMove = 0;
}
Enemy0::~Enemy0()
{

}
void Enemy0::loadImage()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
    auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	std::shared_ptr<Texture> texture;
	switch (getDir())
	{
	case 0:
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_up");
		break;
	case 1:
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_right");
		break;
	case 2:
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_down");
		break;
	case 3:
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_left");
		break;
	default:
		break;
	}
    enemy = std::make_shared<SpriteAnimation2D>(model, shader, texture, 8, 0.1f);
    enemy->SetSize(40, 44);
}
void Enemy0::move(float deltaTime)
{
	switch (getDir())
	{
	case 0:
	{
		if (currentMove <= maxMoveDis) {
			currentMove += 100.0f * deltaTime;
			currentYPos = oldYPos - currentMove;
			enemy->Set2DPosition(currentXPos,currentYPos);
		}
		else
		{
			oldYPos = currentYPos;
			currentMove = 0;
			setDir(2);
			loadImage();
		}
		break;
	}
	case 1:
	{
		if (currentMove <= maxMoveDis) {
			currentMove += 100.0f * deltaTime;
			currentXPos = oldXPos + currentMove;
			enemy->Set2DPosition(currentXPos, currentYPos);
		}
		else
		{
			oldXPos = currentXPos;
			currentMove = 0;
			setDir(3);
			loadImage();
		}
		break;
	}
	case 2:
	{
		if (currentMove <= maxMoveDis) {
			currentMove += 100.0f * deltaTime;
			currentYPos = oldYPos + currentMove;
			enemy->Set2DPosition(currentXPos,currentYPos);
		}
		else
		{
			oldYPos = currentYPos;
			currentMove = 0;
			setDir(0);
			loadImage();
		}
		break;
	}
	case 3:
	{
		if (currentMove <= maxMoveDis) {
			currentMove += 100.0f * deltaTime;
			currentXPos = oldXPos - currentMove;
			enemy->Set2DPosition(currentXPos, currentYPos);
		}
		else
		{
			oldXPos = currentXPos;
			currentMove = 0;
			setDir(1);
			loadImage();
		}
		break;
	}
	default:
		break;
	}
}
void Enemy0::draw()
{
	enemy->Draw();
}
void Enemy0::update(float deltaTime)
{
	
	enemy->Update(deltaTime);
	move(deltaTime);
}