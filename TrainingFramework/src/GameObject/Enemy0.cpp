#include "Enemy0.h"
Enemy0::Enemy0(int x, int y, int dir, int move, int maxMove, int speed, std::shared_ptr<Map2> map)
	: Enemy(0,x,y,dir)
{
	maxMoveDis = maxMove * TILESIZE;
	currentMove = 0;

	defaultDir = dir;
	
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	std::shared_ptr<Texture> texture;
	switch (getDir())
	{
	case 0:
	{
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_up");
		break;
	}
	case 1:
	{
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_right");
		break;
	}
	case 2:
	{
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_down");
		break;
	}
	case 3:
	{
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_left");
		break;
	}
	default:
		break;
	}

	sPoo poo = map->getPoo();
	int xPos = (x - poo.cStart.x) * TILESIZE + screenWidth / 2;
	int yPos = (y - poo.cStart.y) * TILESIZE + screenHeight / 2;
	oldPos.x = xPos;
	oldPos.y = yPos;
	defaultPos = Vector2(xPos, yPos);
	currentPos = oldPos;
	enemy = std::make_shared<SpriteAnimation2D>(model, shader, texture, 8, 0.1f);
	enemy->SetSize(40, 44);
	enemy->Set2DPosition(xPos, yPos);
}
Enemy0::~Enemy0()
{

}

void Enemy0::MoveDirWithPoo(float deltaTime, Vector2 vector)
{
	Vector2 leftMove(-1.0f, 0.0f);
	Vector2 rightMove(1.0f, 0.0f);
	Vector2 upMove(0.0f, -1.0f);
	Vector2 downMove(0.0f, 1.0f);
	Vector2 temp;
	switch (getDir())
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
	if (currentMove <= maxMoveDis)
	{
		currentMove += speed * deltaTime;
		Vector2 pos = getPos();
		pos += temp * speed * deltaTime;
		enemy->Set2DPosition(pos);
	}
	else
	{
		switch (getDir())
		{
		case 0:
		{
			setDir(2);
			enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_down"));
			break;
		}
		case 1:
		{
			setDir(3);
			enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_left"));
			break;
		}
		case 2:
		{
			setDir(0);
			enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_up"));
			break;
		}
		case 3:
		{
			setDir(1);
			enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_right"));
			break;
		}
		default:
			break;
		}
		currentMove = 0;
	}
}
void Enemy0::BackDefault()
{
	enemy->Set2DPosition(defaultPos);
	currentMove = 0;
	setDir(defaultDir);
	switch (defaultDir)
	{
	case 0:
	{
		enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_up"));
		break;
	}
	case 1:
	{
		enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_right"));
		break;
	}
	case 2:
	{
		enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_down"));
		break;
	}
	case 3:
	{
		enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_left"));
		break;
	}
	default:
		break;
	}
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