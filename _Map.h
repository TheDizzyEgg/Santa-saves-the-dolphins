#ifndef _MAP_H
#define _MAP_H


#include "_Decls.h"

#define MAX_OVERTILES 10


class _Map
{
    public:
        _Map();
        virtual ~_Map();

    float x;
    float y;
    float x2;
    float y2;
    float xSpeed;
    float ySpeed;
    bool movingLeft;
    bool movingRight;
    bool movingUp;
    bool movingDown;
    bool moving;
    int imgHeight;
    int imgWidth;
    int *overNumbers;
    int xPos;
    int yPos;
    signed short **mapData;
    signed short **boundsData;
    ALLEGRO_COLOR **colorData;
    ALLEGRO_COLOR **collisionData;

    ALLEGRO_BITMAP *imgMain;
    ALLEGRO_BITMAP *imgBitmap;
    ALLEGRO_BITMAP *imgTileOver[11];

    int create(int mapNumber);
    void render();
    void deleteImgMain();
    void renderOvertiles(_Santa *santaActive);
    void renderOvertiles(_Penguin *peguinActive);
};


#endif // _MAP_H
