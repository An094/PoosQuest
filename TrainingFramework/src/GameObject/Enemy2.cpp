#include "Enemy2.h"
Enemy2::Enemy2(int x, int y, int dir, int move, int maxMove1, int maxMove2, int speed, std::shared_ptr<Map2> map)
	: Enemy(2, x, y, dir)
{
	maxMoveDis[0] = maxMoveDis[2] = maxMove1 * TILESIZE;
	maxMoveDis[1] = maxMoveDis[3] = maxMove2 * TILESIZE;
	currentMove = 0;

	defaultDir = dir;

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy2");
	

	sPoo poo = map->getPoo();
	int xPos = (x - poo.cStart.x) * TILESIZE + screenWidth / 2;
	int yPos = (y - poo.cStart.y) * TILESIZE + screenHeight / 2;
	oldPos.x = xPos;
	oldPos.y = yPos;
	defaultPos = Vector2(xPos, yPos);
	currentPos = oldPos;
	enemy = std::make_shared<SpriteAnimation2D>(model, shader, texture, 6, 0.1f);
	enemy->SetSize(40, 44);
	enemy->Set2DPosition(xPos, yPos);
}
Enemy2::~Enemy2()
{

}

void Enemy2::MoveDirWithPoo(float deltaTime, Vector2 vector)
{
	Vector2 leftMove(-1.0f, 0.0f);
	Vector2 rightMove(1.0f, 0.0f);
	Vector2 upMove(0.0f, -1.0f);
	Vector2 downMove(0.0f, 1.0f);
	Vector2 temp;
	int currentDir = getDir();
	switch (currentDir)
	{
	case 0:
	{
		temp = vector + upMove;
		break;
	}
	case 1:
	{
		temp = vector + rightMove;
		break;
	}
	case 2:
	{
		temp = vector + downMove;
		break;
	}
	case 3:
	{
		temp = vector + leftMove;
		break;
	}
	default:
		break;
	}
	if (currentMove <= maxMoveDis[currentDir])
	{
		currentMove += speed * deltaTime;
		Vector2 pos = getPos();
		pos += temp * speed * deltaTime;
		enemy->Set2DPosition(pos);
	}
	else
	{
		int newDir = currentDir - 1;
		if (newDir == -1) newDir = 3;
		setDir(newDir);
		currentMove = 0;
	}
}
void Enemy2::BackDefault()
{
	enemy->Set2DPosition(defaultPos);
	currentMove = 0;
	setDir(defaultDir);
}
void Enemy2::Draw()
{
	enemy->Draw();
}
void Enemy2::Update(float deltaTime)
{

	enemy->Update(deltaTime);
	//Move(deltaTime);
}