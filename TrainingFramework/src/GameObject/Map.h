#pragma once
#include "GameStates/GameStatebase.h"


#define MAX_X 30
#define MAX_Y 30
#define TILESIZE 40

typedef struct TileMap {
	int indexX;
	int indexY;
	int type;
};
typedef struct Coord {
	int x;
	int y;
};
typedef struct EnemyData {
	int type;
	Coord cEnemy;
	int dir;
	int move;
	int maxMove;
	int speed;
};
typedef struct PooData {
	Coord cStart;
	Coord cDest;
	int dir;
};

class Map
{
public:
	Map(int);
	~Map();
	void loadMap();
	void setLevel();
	void draw();
	void update(float);

	TileMap** m_map;

	int m_level;
	int maxX;
	int maxY;
	PooData poo;
	int numEnemy;
	int numGold;
	std::list<std::shared_ptr<Coord>> m_listGold;
	std::list<std::shared_ptr<Sprite2D>>	m_listTileMap;
	std::vector<std::shared_ptr<EnemyData>> m_listEnemyData;
};


