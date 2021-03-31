#include"Enemy.h"
Enemy::Enemy(int type, int x, int y, int dir): DynamicObject() {
	m_type = type;
	int xPos = x * TILESIZE;
	coor.x = x;
	coor.y = y;
	m_dir = dir;
}
Enemy::~Enemy()
{

}
