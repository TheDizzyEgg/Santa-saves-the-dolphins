#include "_Map.h"
#include "_Decls.h"
#include "Map1.h"


_Map::_Map()
{
    x = 0;
    y = 0;
    x2 = 0;
    y2 = 0;
    xSpeed = 0;
    ySpeed = 0;
    moving = false;

    imgMain = NULL;
}

_Map::~_Map()
{
    if(imgBitmap != NULL)
    {
        al_destroy_bitmap(imgBitmap);
    }

    delete overNumbers;

    for(int i = 0; i<MAX_OVERTILES;i++)
    {
        al_destroy_bitmap(imgTileOver[i]);
    }

    writeLog("Map deleted successfully", 0);
}

void _Map::render()
{
    //al_draw_bitmap_region(imgMain, x, y, 1280, 720, 0, 0, 0);

    int xPos = 0;
    int yPos = 0;

    al_hold_bitmap_drawing(true);
    for(int yStep = y / 32; yStep < (y / 32) + 23 ; yStep++)
    {
        for(int xStep = x / 32; xStep < (x / 32) + 40; xStep++)
        {
            int tileNumber = mapData[yStep][xStep] - 1;

            if(tileNumber >= 0)
            {
                al_draw_bitmap_region(
                    imgBitmap,
                (tileNumber * 32) - (al_get_bitmap_width(imgBitmap) * ((tileNumber * 32) / al_get_bitmap_width(imgBitmap))),
                    ((tileNumber * 32) / al_get_bitmap_width(imgBitmap)) * 32,
                    32, 32, round(xPos - (((x/32) - (int)(x/32)) * 32)), round(yPos - (((y/32) - (int)(y/32)) * 32)), 0
                );
            }

            xPos += 32;
        }

        xPos = 0;
        yPos += 32;
    }

    al_hold_bitmap_drawing(false);
}



int _Map::create(int mapNumber)
{
    int mapWidth = 0, mapHeight = 0, tileWidth = 0;

    if(mapNumber == 1)
    {
        mapWidth = GfxTiles1Map1MapWidth;
        mapHeight = GfxTiles1Map1MapHeight;
        tileWidth = GfxTiles1Bitmap.TileWidth;

        imgBitmap = al_load_bitmap("gfx/Tiles1.bmp");

        mapData = new signed short*[mapHeight];
        for(int i = 0; i < mapHeight; ++i)
        mapData[i] = new signed short[mapWidth];

        boundsData = new signed short*[mapHeight];
        for(int i = 0; i < mapHeight; ++i)
        boundsData[i] = new signed short[mapWidth];

        colorData = new ALLEGRO_COLOR*[mapHeight * tileWidth];
        for(int i = 0; i < mapHeight * 32; ++i)
        colorData[i] = new ALLEGRO_COLOR[mapWidth * tileWidth];

        collisionData = new ALLEGRO_COLOR*[mapHeight * tileWidth];
        for(int i = 0; i < mapHeight * 32; ++i)
        collisionData[i] = new ALLEGRO_COLOR[mapWidth * tileWidth];

        for(int yy = 0; yy < mapHeight; yy++)
        {
            for(int xx = 0; xx < mapWidth; xx++)
            {
                mapData[yy][xx] = Tiles1Map1MapData[yy][xx];
                boundsData[yy][xx] = Tiles1Map1BoundMapData[yy][xx];
            }
        }

        overNumbers = new int[11];

        imgTileOver[0]  = al_load_bitmap("gfx/tileOver_01.png");
        imgTileOver[1]  = al_load_bitmap("gfx/tileOver_02.png");
        imgTileOver[2]  = al_load_bitmap("gfx/tileOver_03.png");
        imgTileOver[3]  = al_load_bitmap("gfx/tileOver_04.png");
        imgTileOver[4]  = al_load_bitmap("gfx/tileOver_05.png");
        imgTileOver[5]  = al_load_bitmap("gfx/tileOver_06.png");
        imgTileOver[6]  = al_load_bitmap("gfx/tileOver_07.png");
        imgTileOver[7]  = al_load_bitmap("gfx/tileOver_08.png");
        imgTileOver[8]  = al_load_bitmap("gfx/tileOver_09.png");
        imgTileOver[9]  = al_load_bitmap("gfx/tileOver_10.png");
        imgTileOver[10] = al_load_bitmap("gfx/tileOver_11.png");

        overNumbers[0] = 40;
        overNumbers[1] = 41;
        overNumbers[2] = 42;
        overNumbers[3] = 73;
        overNumbers[4] = 74;
        overNumbers[5] = 105;
        overNumbers[6] = 75;
        overNumbers[7] = 43;
        overNumbers[8] = 44;
        overNumbers[9] = 45;
        overNumbers[10] = 46;
    }


    imgWidth = (mapWidth * 32) - 1280;
    imgHeight = (mapHeight * 32) - 760;

    if(imgMain != NULL)
    {
        al_destroy_bitmap(imgMain);
        imgMain = NULL;
    }

    imgMain = al_create_bitmap(mapWidth * 32, mapHeight * 32);

    al_set_target_bitmap(imgMain);

    al_clear_to_color(al_map_rgb(255, 0, 255));

    for(int yStep = 0; yStep < mapHeight; yStep++)
    {
        for(int xStep = 0; xStep < mapWidth; xStep++)
        {
            int tileNumber = mapData[yStep][xStep] - 1;

            if(tileNumber >= 0)
            {
                al_draw_bitmap_region(
                    imgBitmap,
                (tileNumber * tileWidth) - (al_get_bitmap_width(imgBitmap) * ((tileNumber * tileWidth) / al_get_bitmap_width(imgBitmap))),
                    ((tileNumber * tileWidth) / al_get_bitmap_width(imgBitmap)) * 32,
                    32, 32, (float)(xStep * 32.0f), (float)(yStep * 32.0f), 0
                );
            }
        }
    }


    al_lock_bitmap(imgMain, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);

        for(int yy = 0; yy < mapHeight * tileWidth; yy++)
        {
            for(int xx = 0; xx < mapWidth * tileWidth; xx++)
            {
                colorData[yy][xx] = al_get_pixel(imgMain, xx, yy);
            }
        }

    al_unlock_bitmap(imgMain);


    for(int yStep = 0; yStep < mapHeight; yStep++)
    {
        for(int xStep = 0; xStep < mapWidth; xStep++)
        {
            int tileNumber = mapData[yStep][xStep];

            if(tileNumber == 1)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 92 || tileNumber == 48  || tileNumber == 50 || tileNumber == 101)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 2 || tileNumber == 32 || tileNumber == 93 || tileNumber == 102 || tileNumber == 109 || tileNumber == 111)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 15), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 7 || tileNumber == 91 || tileNumber == 99 || tileNumber == 110 || tileNumber == 112 || tileNumber == 120)
            {
                al_draw_filled_rectangle((xStep * 32) + 20, (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 8  || tileNumber == 72  || tileNumber == 74  || tileNumber == 75)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 13), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 9 || tileNumber == 21 || tileNumber == 80 || tileNumber == 113)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 15), al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle((xStep * 32) + 18, (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 13 || tileNumber == 69 || tileNumber == 100)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32) + 16, ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle((xStep * 32) + 18, (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 17 || tileNumber == 28  || tileNumber == 28)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 15), al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 15), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 18)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 13), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 29 || tileNumber == 121)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 15), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle((xStep * 32), (yStep * 32) + 16, ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
            }

            if(tileNumber == 30 || tileNumber == 39 || tileNumber == 41 || tileNumber == 45)
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32) + 12, ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 255));
            }

            if(isBitSet(boundsData[yStep][xStep] % 256, 1))
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 4), al_map_rgb(0, 0, 0));
            }

            if(isBitSet(boundsData[yStep][xStep] % 256, 2))
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32), ((xStep * 32) + 4), ((yStep * 32) + 32), al_map_rgb(0, 0, 0));
            }

            if(isBitSet(boundsData[yStep][xStep] % 256, 4))
            {
                al_draw_filled_rectangle((xStep * 32) + 28, (yStep * 32), ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 0));
            }

            if(isBitSet(boundsData[yStep][xStep] % 256, 3))
            {
                al_draw_filled_rectangle((xStep * 32), (yStep * 32) + 28, ((xStep * 32) + 32), ((yStep * 32) + 32), al_map_rgb(0, 0, 0));
            }
        }
    }


    al_lock_bitmap(imgMain, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);

        for(int yy = 0; yy < mapHeight * tileWidth; yy++)
        {
            for(int xx = 0; xx < mapWidth * tileWidth; xx++)
            {
                collisionData[yy][xx] = al_get_pixel(imgMain, xx, yy);
            }
        }

    al_unlock_bitmap(imgMain);

    al_destroy_bitmap(imgMain);

    return 0;
}


void _Map::deleteImgMain()
{
    al_destroy_bitmap(imgMain);
}


void _Map::renderOvertiles(_Santa *santaActive)
{
    int xPos;
    int yPos;

    for(int step=0; step<MAX_OVERTILES; step++)
    {
        xPos = (int)(((santaActive->x + this->x) + 32) / 32);
        yPos = (int)(((santaActive->y + this->y) + 59) / 32);

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step])
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((santaActive->x + this->x) + 32) / 32) -1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step])
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((santaActive->x + this->x) + 32) / 32) +1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step])
        al_draw_bitmap(this->imgTileOver[0 + step],(xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((santaActive->x + this->x) + 32) / 32);
        yPos = (int)(((santaActive->y + this->y) + 59) / 32) - 1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 70))
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((santaActive->x + this->x) + 32) / 32) -1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 70))
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((santaActive->x + this->x) + 32) / 32) +1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 70))
        al_draw_bitmap(this->imgTileOver[0 + step],(xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((santaActive->x + this->x) + 32) / 32);
        yPos = (int)(((santaActive->y + this->y) + 59) / 32) - 2;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 100))
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((santaActive->x + this->x) + 32) / 32) -1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 100))
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((santaActive->x + this->x) + 32) / 32) +1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 100))
        al_draw_bitmap(this->imgTileOver[0 + step],(xPos * 32) - this->x, (yPos * 32) - this->y, 0);
    }
}


void _Map::renderOvertiles(_Penguin *penguinActive)
{
    int xPos;
    int yPos;

    for(int step=0; step<MAX_OVERTILES; step++)
    {
        xPos = (int)(((penguinActive->x) + 20) / 32);
        yPos = (int)(((penguinActive->y) + 42) / 32);

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step])
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((penguinActive->x) + 20) / 32) -1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step])
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((penguinActive->x) + 20) / 32) +1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step])
        al_draw_bitmap(this->imgTileOver[0 + step],(xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((penguinActive->x) + 20) / 32);
        yPos = (int)(((penguinActive->y) + 42) / 32) - 1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 70))
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((penguinActive->x) + 20) / 32) -1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 70))
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((penguinActive->x) + 20) / 32) +1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 70))
        al_draw_bitmap(this->imgTileOver[0 + step],(xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((penguinActive->x) + 20) / 32);
        yPos = (int)(((penguinActive->y) + 42) / 32) - 2;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 100))
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((penguinActive->x) + 20) / 32) -1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 100))
        al_draw_bitmap(this->imgTileOver[0 + step], (xPos * 32) - this->x, (yPos * 32) - this->y, 0);

        xPos = (int)(((penguinActive->x) + 20) / 32) +1;

        if(this->boundsData[yPos][xPos] >> 8 == this->overNumbers[step] && (this->overNumbers[step] >= 100))
        al_draw_bitmap(this->imgTileOver[0 + step],(xPos * 32) - this->x, (yPos * 32) - this->y, 0);
    }
}
