#include "Enemy0.h"
Enemy0::Enemy0(int x, int y, int dir, int move, int maxMove, int speed)
	: Enemy(0, x, y, dir, move, maxMove, speed)
{

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
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_down");
		break;
	case 2:
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_right");
		break;
	case 3:
		texture = ResourceManagers::GetInstance()->GetTexture("Enemy\\enemy0_left");
		break;
	default:
		break;
	}
    std::shared_ptr<SpriteAnimation2D> obj = std::make_shared<SpriteAnimation2D>(model, shader, texture, 8, 0.1f);
    obj->Set2DPosition(getCoorX() * TILESIZE + TILESIZE / 2 + 50, getCoorY()* TILESIZE + TILESIZE / 2 + 140);
    obj->SetSize(40, 44);
	m_listEnemy.push_back(obj);
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
}