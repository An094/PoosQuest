#include"Gold.h"
#include"Map2.h"
Gold::Gold(int x, int y, std::shared_ptr<Map2> map)
{
	isExist = true;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("Animation");
	auto texture = ResourceManagers::GetInstance()->GetTexture("gold");
	m_Gold = std::make_shared<SpriteAnimation2D>(model, shader, texture, 8, 0.1f);
	sPoo poo = map->getPoo();
	int xPos = (x - poo.cStart.x) * TILESIZE + screenWidth / 2;
	int yPos = (y - poo.cStart.y) * TILESIZE + screenHeight / 2;
	defaultPos = Vector2(xPos, yPos);
	m_Gold->SetSize(20, 30);
	m_Gold->Set2DPosition(xPos, yPos);
}
Gold::~Gold()
{

}
void Gold::MoveWithPoo(float x, float y)
{
	Vector2 pos = getPos();
	m_Gold->Set2DPosition(pos.x + x, pos.y + y);
}
void Gold::BackDefault()
{
	m_Gold->Set2DPosition(defaultPos);
	m_Gold->SetTexture(ResourceManagers::GetInstance()->GetTexture("gold"));
	isExist = true;
}
void Gold::BeEaten()
{
	isExist = false;
}
void Gold::Draw()
{
	m_Gold->Draw();
}
void Gold::Update(float deltaTime)
{
	m_Gold->Update(deltaTime);
	if (!isExist)
	{
		m_Gold->SetTexture(ResourceManagers::GetInstance()->GetTexture("blank"));
	}
}