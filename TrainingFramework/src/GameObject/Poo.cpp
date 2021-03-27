#include "Poo.h"
Poo::Poo(int dir, int startCoorX, int startCoorY, int endCoorX, int endCoorY)
{
	poo.dir = dir;
	poo.cStart.x = startCoorX;
	poo.cStart.y = startCoorY;
	poo.cDest.x = endCoorX;
	poo.cDest.y = endCoorY;
	currentXPos = poo.cStart.x * TILESIZE + TILESIZE / 2 + 50;
	currentYPos = poo.cStart.y * TILESIZE + TILESIZE / 2 + 140;
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
void Poo::move(float deltaTime)
{
	switch (getDir())
	{
	case 0: {
		break;
	}
	case 1: {
		break;
	}
	case 2: {
		break;
	}
	case 3: {
		break;

	}
	default:
		break;
	}
}
void Poo::draw()
{
	m_poo->Draw();
}
void Poo::update(float deltaTime)
{
	m_poo->Update(deltaTime);
}