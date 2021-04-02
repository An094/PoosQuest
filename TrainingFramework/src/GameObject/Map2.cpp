#include "Map2.h"
Map2::Map2(int level)
{
    //Cap phat map_convert
    map_convert = new int* [MAX_Y];
    for (int i = 0; i < MAX_X; i++)
        map_convert[i] = new int[MAX_Y];


    std::cout << "Map2 constructor" << std::endl;
	m_level = level;
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
    int ch, type;  //Y la chieu doc, X la chieu ngang
    int index = 0;
    int readFile[1024];
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
    //Ve map
    for (int i = 0; i < maxY; i++)
        for (int j = 0; j < maxX; j++) {
            type = readFile[index++];
            if (type == -1) map_convert[i][j] = 0;
            else map_convert[i][j] = map[type];
            sprintf_s(nameTileMap, "Tile\\%02d",type);
            auto texture = ResourceManagers::GetInstance()->GetTexture(std::string(nameTileMap));
            std::shared_ptr<Sprite2D> tile = std::make_shared<Sprite2D>(model, shader, texture);
            tile->SetSize(TILESIZE, TILESIZE);
            m_listTileMap.push_back(tile);
        }
    //Lay vi tri khoi dau vi tri ket thuc, huong cu Poo
    struPoo.cStart.x = readFile[index++];
    struPoo.cStart.y = readFile[index++];
    struPoo.dir = readFile[index++];
    struPoo.cDest.x = readFile[index++];
    struPoo.cDest.y = readFile[index++];
    //Lay du lieu Enemy
    numEnemy = readFile[index++];
    for (int i = 0; i < numEnemy; i++) {
        std::shared_ptr<sEnemyData> en = std::make_shared<sEnemyData>();
        en->type = readFile[index++];
        //Neu la enemy 0 hoac 3 thi co 6 dau vao
        if (en->type == 0 || en->type == 3)
        {
            en->cEnemy.x = readFile[index++];
            en->cEnemy.y = readFile[index++];
            en->dir = readFile[index++];
            en->move = readFile[index++];
            en->maxMove1 = readFile[index++];
            en->speed = readFile[index++];
        }
        else   //Neu la 1 hoac 2 thi co 7 dau vao
        {
            en->cEnemy.x = readFile[index++];
            en->cEnemy.y = readFile[index++];
            en->dir = readFile[index++];
            en->move = readFile[index++];
            en->maxMove1 = readFile[index++];
            en->maxMove2 = readFile[index++];
            en->speed = readFile[index++];
        }
        
        m_listEnemy.push_back(en);
    }
    //Lay du lieu Gold
    numGold = readFile[index++];
    for (int i = 0; i < numGold; i++) {
        std::shared_ptr<sCoor> g = std::make_shared<sCoor>();
        g->x = readFile[index++];
        g->y = readFile[index++];
        m_Gold.push_back(g);
    }


    //Xet toa do cho cac TileMap
    int distX, distY;
    for(int i = 0;i < maxY;i++)
        for (int j = 0; j < maxX; j++)
        {
            distY = (i - struPoo.cStart.y)*TILESIZE + screenHeight/2;
            distX = (j - struPoo.cStart.x)*TILESIZE + screenWidth/2;
            m_listTileMap[i * maxX + j]->Set2DPosition(distX, distY);
            Vector2 dfPos(distX, distY);
            defaultPos.push_back(dfPos);
        }

    for (int i = 0; i < maxY; i++)
    {
        for (int j = 0; j < maxX; j++) std::cout<<map_convert[i][j]<<" ";
        std::cout << "\n";
    }
        
        

}
Map2::~Map2()
{
    //giai phong map_convert
    for (int i = 0; i < MAX_Y; i++)
        delete[] map_convert[i];
    delete[] map_convert;
}
void Map2::DrawMap()
{
    for (auto it : m_listTileMap)
    {
        it->Draw();
    }
}
void Map2::MoveMap(float x, float y)
{
    for (int i = 0; i < maxY; i++)
        for (int j = 0; j < maxX; j++)
        {
            Vector2 currentPos = m_listTileMap[i * maxX + j]->Get2DPosition();
            m_listTileMap[i * maxX + j]->Set2DPosition(currentPos.x + x, currentPos.y + y);
        }
}
void Map2::BackDefault()
{
    for (int i = 0; i < maxY; i++)
        for (int j = 0; j < maxX; j++) {
            m_listTileMap[i * maxX + j]->Set2DPosition(defaultPos[i * maxX + j]);
        }
}