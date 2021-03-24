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

class Map
{
public:
	Map(int);
	~Map();
	void loadMap();
	void setLevel();
	void draw();

private:
	//TileMap m_map[MAX_X][MAX_Y];
	TileMap** m_map;
	int m_level;
	int width;
	int height;
	std::list<std::shared_ptr<Sprite2D>>	m_listTileMap;
};


