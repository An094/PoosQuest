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
    width = readFile[index++];
    height = readFile[index++];
    char nameTileMap[12];
    for(int i=0;i<height;i++)
        for (int j = 0; j < width; j++) {
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
}

void Map::draw() 
{
    for (auto it : m_listTileMap)
    {
        it->Draw();
    }
}