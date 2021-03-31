#pragma once
#include "GameStates/GameStatebase.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
#define MAX_X 30
#define MAX_Y 30
#define TILESIZE 40
typedef struct sCoor {
	int x;
	int y;
};

typedef struct sPoo {
	sCoor cStart;
	sCoor cDest;
	int dir;
};
typedef struct sEnemyData {
	int type;
	sCoor cEnemy;
	int dir;
	int move;
	int maxMove1;
	int maxMove2;
	int speed;
};
class Map2
{
private:
	int m_level;
	sPoo struPoo;
	int numEnemy;
	int numGold;
	int maxX, maxY;
	std::vector<std::shared_ptr<Sprite2D>> m_listTileMap;
	std::list<std::shared_ptr<sEnemyData>> m_listEnemy;
	std::list<std::shared_ptr<sCoor>> m_Gold;

	int map[40] = { 0,8,-1,1,-1,5,7,-1,3,-1,6,4,2,-1,-1,-1,-1,-2,-2,-2,0,0,0,0,0,0,0,0,1,1,3,3,4,4,2,2,-1,0,0,0 };
	int** map_convert;
public:
	Map2(int level);
	~Map2();
	//void readFile();
	void DrawMap();
	void MoveMap(float x, float y);
	sPoo getPoo() { return struPoo; }
	std::list<std::shared_ptr<sEnemyData>> getListEnemyData() { return m_listEnemy; }
	std::list<std::shared_ptr<sCoor>> getGold(){ return m_Gold; }
	Vector2 getStartPos() { return m_listTileMap[0]->Get2DPosition(); }
	int getNumEnemy() { return numEnemy; }
	int getNumGold() { return numGold; }
	int** getMapConvert() { return map_convert; }
};
