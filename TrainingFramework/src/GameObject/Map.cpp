#include "Map.h"
#include <iostream>

Map::Map(int level = 1) {
	m_level = level;
    m_map = new TileMap * [MAX_X];
    for (int i = 0; i < MAX_X; i++)
        m_map[i] = new TileMap[MAX_Y];
}
Map::~Map() {
    for (int i = 0; i < MAX_X; i++)
        delete[] m_map[i];
    delete[] m_map;
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
        enemyData[i].type = readFile[index++];
        enemyData[i].cEnemy.x = readFile[index++];
        enemyData[i].dir = readFile[index++];
        enemyData[i].move = readFile[index++];
        enemyData[i].maxMove = readFile[index++];
        enemyData[i].speed = readFile[index++];
    }
    shader = ResourceManagers::GetInstance()->GetShader("Animation");
    auto texture = ResourceManagers::GetInstance()->GetTexture("Poo\\poo_right");
    std::shared_ptr<SpriteAnimation2D> obj = std::make_shared<SpriteAnimation2D>(model, shader, texture, 6, 0.1f);
    obj->Set2DPosition(poo.cStart.x*TILESIZE+TILESIZE/2+50, poo.cStart.y * TILESIZE + TILESIZE / 2 + 140);
    obj->SetSize(60, 46);
    m_listSpriteAnimation.push_back(obj);
}

void Map::draw() 
{
    for (auto it : m_listTileMap)
    {
        it->Draw();
    }
    for (auto it : m_listSpriteAnimation)
    {
        it->Draw();
    }
}
void Map::update(float deltaTime) {
    for (auto obj : m_listSpriteAnimation)
    {
        obj->Update(deltaTime);
    }
}