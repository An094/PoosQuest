#include "Enemy0.h"
Enemy0::Enemy0(int x, int y, int dir, int move, int maxMove, int speed)
	: Enemy(0, x, y, dir, move, maxMove, speed)
{
	totalDest = maxMove * TILESIZE;
	currentCoorX = x;
	currentCoorY = y;
	oldXPos = currentCoorX * TILESIZE + TILESIZE / 2 + 50;
	oldYPos = currentCoorY * TILESIZE + TILESIZE / 2 + 140;
	currentYPos = oldYPos;
	currentXPos = oldXPos;
	des = 0;
}
Enemy0::~Enemy0()
{

}
void Enemy0::loadImage()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
    auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	std::shared_ptr<Texture> texture;
	int dir = getDir();
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
    //enemy->Set2DPosition(currentX * TILESIZE + TILESIZE / 2 + 50, currentY* TILESIZE + TILESIZE / 2 + 140);
    enemy->SetSize(40, 44);
	m_listEnemy.push_back(enemy);
}
void Enemy0::move(float deltaTime)
{
	switch (getDir())
	{
	case 0:
	{
		if (des <= totalDest) {
			des += 70.0f * deltaTime;
			currentYPos = oldYPos - des;
			enemy->Set2DPosition(currentXPos,currentYPos);
		}
		else
		{
			oldYPos = currentYPos;
			des = 0;
			setDir(2);
		}
		break;
	}
	case 2:
	{
		if (des <= totalDest) {
			des += 70.0f * deltaTime;
			currentYPos = oldYPos + des;
			enemy->Set2DPosition(currentXPos,currentYPos);
		}
		else
		{
			oldYPos = currentYPos;
			des = 0;
			setDir(0);
	
		}
		break;
	}
	default:
		break;
	}
}
void Enemy0::draw()
{
	for (auto it : m_listEnemy) {
		it->Draw();
	}
}
void Enemy0::update(float deltaTime)
{
	for (auto it : m_listEnemy) {
		it->Update(deltaTime);
	}
	move(deltaTime);
}