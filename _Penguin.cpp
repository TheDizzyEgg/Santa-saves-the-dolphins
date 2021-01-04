#include "_Penguin.h"

_Penguin::_Penguin(float _x, float _y, float _endX, float _endY, int _moveClock, int _type)
{
    x = _x;
    y = _y;
    startX = _x;
    startY = _y;
    endX = _endX;
    endY = _endY;
    moveTimer = 0;
    moveClock = _moveClock;
    moveState = 0;
    speedInc = 2.0;
    idleTimer = 0;
    idleFrame = 0;
    runningTimer = 0;
    runningFrame = 0;
    animState = stateIdle;
    flipFlag = 0;

    sprintf(stringLightX, "lightX[%i]", _type + 20);
    sprintf(stringLightY, "lightY[%i]", _type + 20);
    sprintf(stringLightPower, "lightPower[%i]", _type + 20);
    sprintf(stringLightDiffuse, "lightDiffuse[%i]", _type + 20);
    sprintf(stringLightAlive, "lightAlive[%i]", _type + 20);
}

_Penguin::~_Penguin()
{
}

void _Penguin::update()
{
    idleTimer++;

    if(idleTimer > 32)
    {
        idleTimer = 0;
        if(idleFrame + 1 < 3)
        {
            idleFrame++;
        }
        else
        {
            idleFrame = 0;
        }
    }

    runningTimer++;

    if(runningTimer > 4)
    {
        runningTimer = 0;
        if(runningFrame + 1 < 4)
        {
            runningFrame++;
        }
        else
        {
            runningFrame = 0;
        }
    }

    moveTimer++;

    if(moveTimer > moveClock && animState == stateIdle)
    {
        animState = stateRunning;

        if(moveState == 0) moveState = 1;
        if(moveState == 2) moveState = 3;
    }

    if(moveState == 1)
    {
        if(x < endX){
            flipFlag = 0;
            x += speedInc;
            if(x > endX) x = endX;
        }
        else if(x > endX){
            flipFlag = 1;
            x -= speedInc;
            if(x < endX) x = endX;
        }

        if(y < endY){
            y += speedInc;
            if(y > endY) y = endY;
        }
        else if(y > endY){
            y -= speedInc;
            if(y < endY) y = endY;
        }

        if(x == endX && y == endY){
            animState = stateIdle;
            moveState = 2;
            moveTimer = 0;
        }
    }

    if(moveState == 3)
    {
        if(x < startX){
            flipFlag = 0;
            x += speedInc;
            if(x > startX) x = startX;
        }
        else if(x > startX){
            flipFlag = 1;
            x -= speedInc;
            if(x < startX) x = startX;
        }

        if(y < startY){
            y += speedInc;
            if(y > startY) y = startY;
        }
        else if(y > startY){
            y -= speedInc;
            if(y < startY) y = startY;
        }

        if(x == startX && y == startY){
            animState = stateIdle;
            moveState = 0;
            moveTimer = 0;
        }
    }
}

_PenguinSystem::_PenguinSystem()
{
    imgIdle[0] = al_load_bitmap("gfx/penguin/penguin_idle_01.png");
    imgIdle[1] = al_load_bitmap("gfx/penguin/penguin_idle_02.png");
    imgIdle[2] = al_load_bitmap("gfx/penguin/penguin_idle_03.png");

    imgRunning[0] = al_load_bitmap("gfx/penguin/penguin_running_01.png");
    imgRunning[1] = al_load_bitmap("gfx/penguin/penguin_running_02.png");
    imgRunning[2] = al_load_bitmap("gfx/penguin/penguin_running_03.png");
    imgRunning[3] = al_load_bitmap("gfx/penguin/penguin_running_04.png");

    if(!imgIdle[0]) writeLog("Unable to load gfx/penguin_idle_01.png", 977);
    if(!imgIdle[1]) writeLog("Unable to load gfx/penguin_idle_02.png", 977);
    if(!imgIdle[2]) writeLog("Unable to load gfx/penguin_idle_03.png", 977);

    if(!imgRunning[0]) writeLog("Unable to load gfx/penguin_running_01.png", 977);
    if(!imgRunning[1]) writeLog("Unable to load gfx/penguin_running_02.png", 977);
    if(!imgRunning[2]) writeLog("Unable to load gfx/penguin_running_03.png", 977);
    if(!imgRunning[3]) writeLog("Unable to load gfx/penguin_running_04.png", 977);
}

_PenguinSystem::~_PenguinSystem()
{
    if(imgIdle[0] != NULL) al_destroy_bitmap(imgIdle[0]);
    if(imgIdle[1] != NULL) al_destroy_bitmap(imgIdle[1]);
    if(imgIdle[2] != NULL) al_destroy_bitmap(imgIdle[2]);

    if(imgRunning[0] != NULL) al_destroy_bitmap(imgRunning[0]);
    if(imgRunning[1] != NULL) al_destroy_bitmap(imgRunning[1]);
    if(imgRunning[2] != NULL) al_destroy_bitmap(imgRunning[2]);
    if(imgRunning[3] != NULL) al_destroy_bitmap(imgRunning[3]);

    for(int i=0; i<(int)penguin.size(); i++)
    {
        delete penguin[i];
        penguin.erase(penguin.begin() + i);
    }

    writeLog("PenguinSystem deleted succussfully", 0);
}

void _PenguinSystem::createPenguins(_Map *mapActive)
{
    for(int yStep=0; yStep<40; yStep++)
    {
        for(int xStep=0; xStep<80; xStep++)
        {
            if(mapActive->boundsData[yStep][xStep] >> 8 == 20)
            {
                penguin.push_back(new _Penguin(xStep * 32, yStep * 32, (xStep + 11) * 32, yStep * 32, 100, 0));
            }
            else if(mapActive->boundsData[yStep][xStep] >> 8 == 21)
            {
                penguin.push_back(new _Penguin(xStep * 32, yStep * 32, (xStep + 14) * 32, yStep * 32, 100, 1));
            }
            else if(mapActive->boundsData[yStep][xStep] >> 8 == 22)
            {
                penguin.push_back(new _Penguin(xStep * 32, yStep * 32, (xStep + 8) * 32, yStep * 32, 200, 2));
            }
            else if(mapActive->boundsData[yStep][xStep] >> 8 == 23)
            {
                penguin.push_back(new _Penguin(xStep * 32, yStep * 32, (xStep + 10) * 32, yStep * 32, 50, 3));
            }
            else if(mapActive->boundsData[yStep][xStep] >> 8 == 24)
            {
                penguin.push_back(new _Penguin(xStep * 32, yStep * 32, xStep * 32, (yStep + 7) * 32, 120, 4));
            }
            else if(mapActive->boundsData[yStep][xStep] >> 8 == 25)
            {
                penguin.push_back(new _Penguin(xStep * 32, yStep * 32, xStep * 32, (yStep + 7) * 32, 70, 5));
            }
        }
    }
}

void _PenguinSystem::renderPenguins(_Map *mapActive)
{
    for(int i=0; i<(int)penguin.size(); i++)
    {
        if(penguin[i]->animState == _Penguin::stateIdle)
        {

            al_draw_bitmap(imgIdle[penguin[i]->idleFrame], penguin[i]->x - mapActive->x, penguin[i]->y - mapActive->y, penguin[i]->flipFlag);
        }
        else if(penguin[i]->animState == _Penguin::stateRunning)
        {
            al_draw_bitmap(imgRunning[penguin[i]->runningFrame], penguin[i]->x - mapActive->x, penguin[i]->y - mapActive->y,  penguin[i]->flipFlag);
        }

        mapActive->renderOvertiles(penguin[i]);
    }
}

void _PenguinSystem::updatePenguins()
{
    for(int i=0; i<(int)penguin.size(); i++)
    {
        penguin[i]->update();
    }
}


bool _PenguinSystem::checkFootsteps(_Santa *santaActive)
{
    static bool xCheck = false;
    static bool yCheck = false;

    if(santaActive->footSteps.size() <= 0) return false;

    for(int i=0; i<(int)penguin.size(); i++)
    {
        for(int j=0; j<(int)santaActive->footSteps.size(); j++)
        {
        xCheck = false;
        yCheck = false;

        if(penguin[i]->x < santaActive->footSteps[j]->x)
        {
            if(santaActive->footSteps[j]->x - penguin[i]->x < 50)
            {
                xCheck = true;
            }
        }
        if(penguin[i]->x >= santaActive->footSteps[j]->x)
        {
            if(penguin[i]->x - santaActive->footSteps[j]->x < 60)
            {
                xCheck = true;
            }
        }
        if(penguin[i]->y < santaActive->footSteps[j]->y)
        {
            if((santaActive->footSteps[j]->y) - penguin[i]->y < 50)
            {
                yCheck = true;
            }
        }
        if(penguin[i]->y >= santaActive->footSteps[j]->y)
        {
            if(penguin[i]->y - (santaActive->footSteps[j]->y) < 60)
            {
                yCheck = true;
            }
        }

        if((xCheck && yCheck))
        {
            caughtX = penguin[i]->x + 20;
            caughtY = penguin[i]->y + 24;
            penguin[i]->moveState = 10;
            penguin[i]->animState = _Penguin::stateRunning;
            caughtType = _Penguin::caughtStateFootstep;
            return(true);
        }
        }
    }

    return(false);
}

void _PenguinSystem::resetPenguins()
{
    for(int i=0; i<(int)penguin.size(); i++)
    {
        penguin[i]->animState = _Penguin::stateIdle;
        penguin[i]->x = penguin[i]->startX;
        penguin[i]->y = penguin[i]->startY;
        penguin[i]->moveState = 0;
        penguin[i]->moveTimer = 0;
    }
}
