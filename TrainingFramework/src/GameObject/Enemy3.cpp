#include "Enemy3.h"
Enemy3::Enemy3(int x, int y, int dir, int move, int maxMove1, int maxMove2, std::shared_ptr<Map2> map)
	: Enemy(3, x, y, dir)
{
	setDir(dir);
	defaultDir = dir;
	isChange = false;
	m_move = move * 0.05f;
	defaultMove = m_move;
	m_maxMove[0] = maxMove1 * 0.05f;
	m_maxMove[1] = maxMove2 * 0.05;

	sPoo poo = map->getPoo();
	float xPos = (x - poo.cStart.x) * TILESIZE + screenWidth / 2;
	float yPos = (y - poo.cStart.y) * TILESIZE + screenHeight / 2;
	defaultPos = Vector2(xPos, yPos);
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	std::shared_ptr<Texture> texture;
	switch (getDir())
	{
	case 0:
	{
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy3_0");
		break;
	}
	case 1:
	{
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy3_1");
		break;
	}
	case 2:
	{
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy3_2");
		break;
	}
	default:
		break;
	}
	enemy = std::make_shared<Sprite2D>(model, shader, texture);
	enemy->SetSize(28, 40);
	enemy->Set2DPosition(xPos, yPos);

}
Enemy3::~Enemy3()
{

}

void Enemy3::MoveDirWithPoo(float deltaTime, Vector2 vector)
{
	Vector2 pos = getPos();
	pos += vector * speed * deltaTime;
	enemy->Set2DPosition(pos);
}
void Enemy3::BackDefault()
{
	enemy->Set2DPosition(defaultPos);
	m_move = defaultMove;
	setDir(defaultDir);
	switch (defaultDir)
	{
	case 0:
	{
		enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy3_0"));
		break;
	}
	case 1:
	{
		enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy3_1"));
		break;
	}
	case 2:
	{
		enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy3_2"));
		break;
	}
	default:
		break;
	}
}
bool Enemy3::getActive()
{
	if (getDir() != 1) return false;
	else return true;
}
void Enemy3::Draw()
{
	enemy->Draw();
}
void Enemy3::Update(float deltaTime)
{
	if (isChange)
	{
		setDir(1 - getDir());
		enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy3_1"));
		isChange = false;
	}
	else
	{
		m_move += deltaTime;
		if (m_move >= m_maxMove[getDir()])
		{
			m_move = 0.0f;
			isChange = true;
		}
		else
		{
			if (getDir() == 0)  enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy3_0"));
			else if (getDir() == 1) enemy->SetTexture(ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy3_2"));
			
		}
	}
}