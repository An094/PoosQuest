#include "Map.h"
#include <iostream>
#include "Enemy0.h"

Map::Map(int level = 1) {
	m_level = level;
    m_map = new TileMap * [MAX_Y];
    for (int i = 0; i < MAX_X; i++)
        m_map[i] = new TileMap[MAX_X];
    map_convert = new int* [MAX_Y];
    for (int i = 0; i < MAX_X; i++)
        map_convert[i] = new int[MAX_Y];
}
Map::~Map() {
    for (int i = 0; i < MAX_Y; i++)
        delete[] m_map[i];
    delete[] m_map;
    for (int i = 0; i < MAX_Y; i++)
        delete[] map_convert[i];
    delete[] map_convert;
}

void Map::loadMap() {
    printf("Load Map\n");
    auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
    auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

    char str[50];
    sprintf(str, "..\\Data\\Maps\\%02d.txt", m_level);
    //Read file Map
    FILE* f = fopen(str, "r");
    if (f == NULL) {
        printf("Doc file that bai");
        return;
    }
    printf("load thanh cong\n");
    int ch;
    int index = 0;
    int readFile[500];
    while (1) {
        if (fscanf(f, "%d", &ch) == EOF)
            break;
        readFile[index++] = ch;
    }
    fclose(f);


    index = 0;
    maxX = readFile[index++];
    maxY = readFile[index++];
    char nameTileMap[12];
    for(int i=0;i<maxY;i++)
        for (int j = 0; j < maxX; j++) {
            m_map[i][j].indexX = j;
            m_map[i][j].indexY = i;
            m_map[i][j].type = readFile[index++];
            sprintf_s(nameTileMap, "Tile\\%02d", m_map[i][j].type);
            if (m_map[i][j].type == -1) map_convert[i][j] = 0;
            else map_convert[i][j] = map[m_map[i][j].type];
            auto texture = ResourceManagers::GetInstance()->GetTexture(std::string(nameTileMap));
            std::shared_ptr<Sprite2D> tile = std::make_shared<Sprite2D>(model, shader, texture);
            tile->Set2DPosition(j * TILESIZE + TILESIZE / 2 + 50, i * TILESIZE + TILESIZE / 2 + 150);
            tile->SetSize(TILESIZE, TILESIZE);
            m_listTileMap.push_back(tile);
        }
        
    poo.cStart.x = readFile[index++];
    poo.cStart.y = readFile[index++];
    poo.dir = readFile[index++];
    poo.cDest.x = readFile[index++];
    poo.cDest.y = readFile[index++];
    numEnemy = readFile[index++];
    for (int i = 0; i < numEnemy; i++) {
        std::shared_ptr<EnemyData> en = std::make_shared<EnemyData>();
        en->type = readFile[index++];
        en->cEnemy.x = readFile[index++];
        en->cEnemy.y = readFile[index++];
        en->dir = readFile[index++];
        en->move = readFile[index++];
        en->maxMove = readFile[index++];
        en->speed = readFile[index++];
        m_listEnemyData.push_back(en);
    }
   
    numGold = readFile[index++];
    for (int i = 0; i < numGold; i++) {
        std::shared_ptr<Coord> g = std::make_shared<Coord>();
        g->x = readFile[index++];
        g->y = readFile[index++];
        m_listGold.push_back(g);
    }

}

void Map::draw() 
{
    for (auto it : m_listTileMap)
    {
        it->Draw();
    }
}
void Map::update(float deltaTime) 
{
}