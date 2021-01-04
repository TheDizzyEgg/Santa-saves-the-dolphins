#include "_Santa.h"


_Santa::_Santa()
{

    x = 500.0;
    y = 180.0;
    xSpeed = 0.0;
    ySpeed = 0.0;
    maxSpeed = 4.0;
    speedInc = 0.1;
    idleTimer = 0;
    idleFrame = 0;
    runningTimer = 0;
    runningFrame = 0;
    animState = stateIdle;
    flipFlag = 0;
    movingLeft = false;
    movingRight = false;
    movingUp = false;
    movingDown = false;
    footStepDelay = 0;
    totalLives = 3;
    totalFish = 3;
    frozenAmount = 0.0;
    dolphinCounter = 0;
    savedDolphin = 0;
    foundDolphin = false;
    dolphinTimer = 0;
    dolphinSize = 0;
    dolphinEmerged = false;
    onIce = 1.0;

    sprintf(stringLives, "x%i%c", totalLives, '\0');
    sprintf(stringFish, "x%i%c", totalFish, '\0');

    imgIconSanta = al_load_bitmap("gfx/icon_santa.png");
    imgIconFish = al_load_bitmap("gfx/icon_fish.png");

    if(!imgIconSanta) writeLog("Unable to load gfx/icon_santa.png", 919);
    if(!imgIconFish) writeLog("Unable to load gfx/icon_fish.png", 918);
}

_Santa::~_Santa()
{
    for(int i=0; i<MAX_IDLE_FRAMES; i++)
    {
        if(imgIdle[i] != NULL)
        {
            al_destroy_bitmap(imgIdle[i]);
        }
    }

    for(int i=0; i<MAX_RUNNING_FRAMES; i++)
    {
        if(imgRunning[i] != NULL)
        {
            al_destroy_bitmap(imgRunning[i]);
        }
    }

    if(imgFootstep != NULL)
    {
        al_destroy_bitmap(imgFootstep);
    }

    if(imgIconSanta != NULL)
    {
        al_destroy_bitmap(imgIconSanta);
    }

    if(imgIconFish != NULL)
    {
        al_destroy_bitmap(imgIconFish);
    }

    for(int i=0; i<(int)footSteps.size();i++)
    {
        if(footSteps[i] != NULL)
        {
            delete footSteps[i];
        }

        footSteps.erase(footSteps.begin() + i);
    }

    if(imgFrozen != NULL)
    {
        al_destroy_bitmap(imgFrozen);
    }

    if(imgHoldFish != NULL)
    {
        al_destroy_bitmap(imgHoldFish);
    }

    if(imgDolphin != NULL)
    {
        al_destroy_bitmap(imgDolphin);
    }

    if(imgDolphinReflect != NULL)
    {
        al_destroy_bitmap(imgDolphinReflect);
    }

    if(imgRadarBG != NULL)
    {
        al_destroy_bitmap(imgRadarBG);
    }

    if(imgRadarBar != NULL)
    {
        al_destroy_bitmap(imgRadarBar);
    }

    writeLog("Santa cleaned successfully", 0);
}

void _Santa::initialise()
{
	imgIdle[0] = al_load_bitmap("gfx/santa/santa_idle_01.png");
	imgIdle[1] = al_load_bitmap("gfx/santa/santa_idle_02.png");
	imgIdle[2] = al_load_bitmap("gfx/santa/santa_idle_03.png");
	imgIdle[3] = al_load_bitmap("gfx/santa/santa_idle_04.png");
	imgIdle[4] = al_load_bitmap("gfx/santa/santa_idle_05.png");

    if(!imgIdle[0] || !imgIdle[1] || !imgIdle[2] || !imgIdle[3] || !imgIdle[4])
    {
        writeLog("Error loading one of gfx/santa/santa_idle_01/02/03/04/05.png", 19);
    }

	imgRunning[0] = al_load_bitmap("gfx/santa/santa_run_01.png");
	imgRunning[1] = al_load_bitmap("gfx/santa/santa_run_02.png");
	imgRunning[2] = al_load_bitmap("gfx/santa/santa_run_03.png");
	imgRunning[3] = al_load_bitmap("gfx/santa/santa_run_04.png");

    if(!imgRunning[0] || !imgRunning[1] || !imgRunning[2])
    {
        writeLog("Error loading one of gfx/santa/santa_run_01/02/03/04.png", 19);
    }

    imgFootstep = al_load_bitmap("gfx/santa/footstep_snow_01.png");

    if(imgFootstep == NULL)
    {
        writeLog("Error loading gfx/santa/footstep_snow_01.png", 37);
    }

    imgFrozen = al_load_bitmap("gfx/santa/santa_frozen.png");

    if(!imgFrozen)
    {
        writeLog("Unable to load gfx/santa/santa_frozen.png", 36);
    }

    imgHoldFish = al_load_bitmap("gfx/santa/santa_fish.png");

    if(!imgHoldFish)
    {
        writeLog("Unable to load gfx/santa/santa_fish.png", 36);
    }

    imgDolphin = al_load_bitmap("gfx/dolphin_main.png");

    if(!imgDolphin)
    {
        writeLog("Unable to load gfx/dolphin_main.png", 36);
    }

    imgDolphinReflect = al_load_bitmap("gfx/dolphin_reflect.png");

    if(!imgDolphinReflect)
    {
        writeLog("Unable to load gfx/dolphin_reflect.png", 36);
    }

    imgRadarBG = al_load_bitmap("gfx/radar_bg.png");

    if(!imgRadarBG)
    {
        writeLog("Unable to load gfx/radar_bg.png", 36);
    }

    imgRadarBar = al_load_bitmap("gfx/radar_bar.png");

    if(!imgRadarBar)
    {
        writeLog("Unable to load gfx/radar_bar.png", 36);
    }
}

void _Santa::renderFootsteps(_Map *mapActive)
{
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ALPHA, ALLEGRO_INVERSE_ALPHA);

    al_hold_bitmap_drawing(true);
    for(int loop = 0; loop < (int)footSteps.size(); loop++)
    {
        al_draw_tinted_bitmap(imgFootstep, al_map_rgba_f(1, 1, 1, footSteps[loop]->lifeSpan), footSteps[loop]->x - mapActive->x, footSteps[loop]->y - mapActive->y, 0);
    }
    al_hold_bitmap_drawing(false);
}

void _Santa::render(_Map *mapActive)
{
    if(frozenAmount == 0.0)
    {
        if(animState == stateIdle)
        {
            al_draw_bitmap(imgIdle[idleFrame], x, y, flipFlag);

        }
        else if(animState == stateRunning)
        {
            al_draw_bitmap(imgRunning[runningFrame], x, y, flipFlag);
        }
        else if(animState == stateHoldFish)
        {
            if(flipFlag == 0)
                al_draw_bitmap(imgHoldFish, x + 11, y, flipFlag);
            if(flipFlag == 1)
                al_draw_bitmap(imgHoldFish, x - 13, y, flipFlag);
        }
    }
    else
    {
        al_draw_bitmap_region(imgIdle[0], 0, 0, 66, 58 * (1.0 - frozenAmount), x, y + 58 - (58 * (1.0 - frozenAmount)), flipFlag);
        al_draw_tinted_bitmap_region(imgFrozen, al_map_rgba_f(1.0, 1.0, 1.0, frozenAmount * 2), 0, 0, 66, 58 * (1.0 - frozenAmount), x, y + 58 - (58 * (1.0 - frozenAmount)), flipFlag);
    }

    if(foundDolphin)
    {
        if(savedDolphin == 0)
        {
            al_draw_bitmap_region(imgDolphin, 0, 0, 59, 28 * dolphinSize, x - 80, (y + 40) + 28 - (28 * dolphinSize), 0);
            al_draw_bitmap_region(imgDolphinReflect, 0, 28 - (dolphinSize * 28), 59, 28 * dolphinSize, x - 80, (y + 40) + 28, 0);
        }
        else if(savedDolphin == 1)
        {
            al_draw_bitmap_region(imgDolphin, 0, 0, 59, 28 * dolphinSize, x + 95, (y + 40) + 28 - (28 * dolphinSize), 1);
            al_draw_bitmap_region(imgDolphinReflect, 0, 28 - (dolphinSize * 28), 59, 28 * dolphinSize, x + 95, (y + 40) + 28, 1);
        }
    }
}

void _Santa::updateDolphin()
{
    dolphinTimer++;

    if(dolphinTimer > 2)
    {
        dolphinTimer = 0;
        dolphinSize += 0.01;

        if(dolphinSize > 1.0)
        {
            dolphinSize = 1.0;
            dolphinEmerged = true;
        }
    }
}

void _Santa::allegroEvent(ALLEGRO_EVENT event)
{
    if(foundDolphin) return;

    if(event.type == ALLEGRO_EVENT_KEY_DOWN)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT && animState != stateHoldFish)
        {
            movingRight = true;
            movingLeft = false;

            animState = stateRunning;
            flipFlag = 0;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_LEFT && animState != stateHoldFish)
        {
            movingRight = false;
            movingLeft = true;

            animState = stateRunning;
            flipFlag = ALLEGRO_FLIP_HORIZONTAL;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_UP && animState != stateHoldFish)
        {
            movingUp = true;
            movingDown = false;

            animState = stateRunning;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_DOWN && animState != stateHoldFish)
        {
            movingUp = false;
            movingDown = true;

            animState = stateRunning;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            movingUp = false;
            movingDown = false;
            movingLeft = false;
            movingRight = false;

            animState = stateHoldFish;
        }

    }

    if(event.type == ALLEGRO_EVENT_KEY_UP)
    {
        if(event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
        {
            movingRight = false;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_LEFT)
        {
            movingLeft = false;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_UP)
        {
            movingUp = false;
        }
        if(event.keyboard.keycode == ALLEGRO_KEY_DOWN)
        {
            movingDown = false;
        }

        if(event.keyboard.keycode == ALLEGRO_KEY_SPACE)
        {
            animState = stateIdle;
        }
    }

    if(!movingDown && !movingUp && !movingLeft && !movingRight  && animState != stateHoldFish)
    {
        animState = stateIdle;
    }
}

void _Santa::update(_Map *mapActive, int totalSnowflakes, bool keyboardEnabled)
{
    if(keyboardEnabled)
    {
        idleTimer++;

        if(idleTimer > 8)
        {
            idleTimer = 0;
            if(idleFrame + 1 < 5)
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

        if(movingRight == true)
        {
            if(xSpeed < maxSpeed) xSpeed += (speedInc * std::max(onIce, 0.4));
        }
        else if(movingLeft == true)
        {
            if(xSpeed > -maxSpeed) xSpeed -= (speedInc * std::max(onIce, 0.4));
        }
        else
        {
            if(xSpeed > 0 && xSpeed - (speedInc * onIce) > 0)
            {
                xSpeed -= (speedInc * onIce);
            }
            else if(xSpeed < 0 && xSpeed + (speedInc * onIce) < 0)
            {
                xSpeed += (speedInc * onIce);
            }
            else
            {
                xSpeed = 0;
            }
        }

        if(movingDown == true)
        {
            if(ySpeed < maxSpeed) ySpeed += (speedInc * std::max(onIce, 0.4));
        }
        else if(movingUp == true)
        {
            if(ySpeed > -maxSpeed) ySpeed -= (speedInc * std::max(onIce, 0.4));
        }
        else
        {
            if(ySpeed > 0 && ySpeed - (speedInc * onIce))
            {
                ySpeed -= (speedInc * onIce);
            }
            else if(ySpeed < 0 && ySpeed + (speedInc * onIce) < 0)
            {
                ySpeed += (speedInc * onIce);
            }
            else
            {
                ySpeed = 0;
            }
        }

        int pixelX = (int)(x + mapActive->x + 18);
        int pixelY = (int)(y + mapActive->y + 53);

        if(compareColors(mapActive->collisionData[pixelY + 3][pixelX + 14], al_map_rgb(0, 0, 255)))
        {
            inWater = true;
        }
        if(compareColors(mapActive->collisionData[pixelY + 3][pixelX + 14], al_map_rgb(220, 228, 233)))
        {
            onIce = 0.2;
        }
        else
        {
            onIce = 1.0;
        }
        for(int xStep = 0; xStep < 29; xStep++)
        {
            if(ySpeed < 0.0 && (compareColors(mapActive->collisionData[(int)(pixelY + ySpeed)][pixelX + xStep], al_map_rgb(0, 0, 0))))
            {
                ySpeed = 0.0;
            }
            else if(ySpeed > 0.0 && (compareColors(mapActive->collisionData[(int)(pixelY + 4 + ySpeed)][pixelX + xStep], al_map_rgb(0, 0, 0))))
            {
                ySpeed = 0.0;
            }
        }
        for(int yStep = 0; yStep < 3; yStep++)
        {
            if(xSpeed < 0.0 && (compareColors(mapActive->collisionData[(int)(pixelY + 1 + yStep)][pixelX - 4], al_map_rgb(0, 0, 0))))
            {
                xSpeed = 0.0;
            }
            else if(xSpeed > 0.0 && (compareColors(mapActive->collisionData[(int)(pixelY + 1 + yStep)][pixelX + 31], al_map_rgb(0, 0, 0))))
            {
                xSpeed = 0.0;
            }
        }

        mapActive->xSpeed = 0.0;
        mapActive->ySpeed = 0.0;

        if(mapActive->x == 0.0)
        {
            if(x + xSpeed > -80.0 && x + xSpeed < SCROLL_RIGHT_LIMIT)
            {
                x += xSpeed;
            }
            else
            {
                if(x + xSpeed <= -80.0)
                {
                    x = -80.0;
                    xSpeed = 0.0;
                }
                else if(x + xSpeed >= SCROLL_RIGHT_LIMIT)
                {
                    mapActive->x += xSpeed;
                    mapActive->xSpeed = xSpeed;
                }
            }
        }
        else if(mapActive->x == mapActive->imgWidth)
        {
            if(x + xSpeed > SCROLL_LEFT_LIMIT && x + xSpeed < 1280)
            {
                x += xSpeed;
            }
            else
            {
                if(x + xSpeed <= SCROLL_LEFT_LIMIT)
                {
                    mapActive->x += xSpeed;
                    mapActive->xSpeed = xSpeed;
                }
                else if(x + xSpeed >= 1280)
                {
                    x = 1280;
                    xSpeed = 0.0;
                }
            }
        }
        else
        {
            if(x + xSpeed > SCROLL_LEFT_LIMIT && x + xSpeed < SCROLL_RIGHT_LIMIT)
            {
                x += xSpeed;
            }
            else
            {
                if(x + xSpeed <= SCROLL_LEFT_LIMIT)
                {
                    x = SCROLL_LEFT_LIMIT;
                }
                else if(x + xSpeed >= SCROLL_RIGHT_LIMIT)
                {
                    x = SCROLL_RIGHT_LIMIT;
                }
            }

            if(x <= SCROLL_LEFT_LIMIT || x >= SCROLL_RIGHT_LIMIT)
            {
                if(mapActive->x + xSpeed > 0.0 && mapActive->x + xSpeed < mapActive->imgWidth)
                {
                    mapActive->x += xSpeed;
                    mapActive->xSpeed = xSpeed;
                }
                else
                {
                    if(mapActive->x + xSpeed <= 0.0)
                    {
                        mapActive->x = 0.0;
                    }
                    else if(mapActive->x + xSpeed >= mapActive->imgWidth)
                    {
                        mapActive->x = mapActive->imgWidth;
                    }
                }
            }
        }

        if(mapActive->y == 0.0)
        {
            if(y + ySpeed > 5.0 && y + ySpeed < SCROLL_DOWN_LIMIT)
            {
                y += ySpeed;
            }
            else
            {
                if(y + ySpeed <= 5.0)
                {
                    y = 5.0;
                    ySpeed = 0.0;
                }
                else if(y + ySpeed >= SCROLL_DOWN_LIMIT)
                {
                    mapActive->y += ySpeed;
                    mapActive->ySpeed = ySpeed;
                }
            }
        }
        else if(mapActive->y == mapActive->imgHeight)
        {
            if(y + ySpeed > SCROLL_UP_LIMIT && y + ySpeed < 720)
            {
                y += ySpeed;
            }
            else
            {
                if(y + ySpeed <= SCROLL_UP_LIMIT)
                {
                    mapActive->y += ySpeed;
                    mapActive->ySpeed = ySpeed;
                }
                else if(y + ySpeed >= 720)
                {
                    y = 720;
                    ySpeed = 0.0;
                }
            }
        }
        else
        {
            if(y + ySpeed > SCROLL_UP_LIMIT && y + ySpeed < SCROLL_DOWN_LIMIT)
            {
                y += ySpeed;
            }
            else
            {
                if(y + ySpeed <= SCROLL_UP_LIMIT)
                {
                    y = SCROLL_UP_LIMIT;
                }
                else if(y + ySpeed >= SCROLL_DOWN_LIMIT)
                {
                    y = SCROLL_DOWN_LIMIT;
                }
            }

            if(y <= SCROLL_UP_LIMIT || y >= SCROLL_DOWN_LIMIT)
            {
                if(mapActive->y + ySpeed > 0.0 && mapActive->y + ySpeed < mapActive->imgHeight)
                {
                    mapActive->y += ySpeed;
                    mapActive->ySpeed = ySpeed;
                }
                else
                {
                    if(mapActive->y + ySpeed <= 0.0)
                    {
                        mapActive->y = 0.0;
                    }
                    else if(mapActive->y + ySpeed >= mapActive->imgHeight)
                    {
                        mapActive->y = mapActive->imgHeight;
                    }
                }
            }
        }


        if(footStepDelay == 0 && (xSpeed != 0.0 || ySpeed != 0.0))
        {
            int pixelX = (int)((x+18) + mapActive->x);
            int pixelY = (int)((y+56) + mapActive->y);

            float k = (float)((rand()%200) / 1000.0f);

            float j, h;

            if(xSpeed > 0.0)
            {
                j = xSpeed;
            }
            else
            {
                j = fabs(xSpeed);
            }
            if(ySpeed > 0.0)
            {
                h = ySpeed;
            }
            else
            {
                h = fabs(ySpeed);
            }

            double normal = 0.0;

            if(j > 0.0 && h > 0.0) normal = (j * h) / (4.0 * 4.0);
            else if(j > 0.0 && h == 0.0) normal = (j) / (4.0);
            else if(j == 0.0 && h > 0.0) normal = (h) / (4.0);

            normal = normal < 0.2 ? (0.2) : (normal);
            normal = normal > 1.0 ? (1.0) : (normal);

            if(compareColors(mapActive->colorData[pixelY][pixelX] , al_map_rgb(167, 185, 194)) && compareColors(mapActive->colorData[pixelY][pixelX + 10] , al_map_rgb(167, 185, 194)))
            {
                footSteps.push_back(new _Footstep(((x + mapActive->x) + 18), ((y + mapActive->y) + 56), (0.4 + k) + (0.4 * normal)));
            }
            if(compareColors(mapActive->colorData[pixelY][pixelX+18] , al_map_rgb(167, 185, 194)) && compareColors(mapActive->colorData[pixelY][pixelX + 18] , al_map_rgb(167, 185, 194)))
            {
                footSteps.push_back(new _Footstep(((x + mapActive->x) + 36), ((y + mapActive->y) + 56), (0.4 + k) + (0.4 * normal)));
            }

            if(movingDown || movingLeft || movingRight || movingUp)
            {
                footStepDelay = 6;
            }
            else
            {
                footStepDelay = 4;
            }
        }
    }

    if(footStepDelay > 0) footStepDelay--;

    float toAdd = 0.0f;

    if(totalSnowflakes < 1000)
    {
        float fractAdd = (((float)totalSnowflakes * 1.0f) / 1000.0f);

        toAdd = 0.01 * fractAdd;

        toAdd = std::max(toAdd, 0.001f);
    }
    else
    {
        toAdd = 0.01;
    }

    for(int loop = 0; loop < (int)footSteps.size(); loop++)
    {

        if(std::max(footSteps[loop]->lifeSpan - toAdd, 0.000f) > 0.000f)
        {
            footSteps[loop]->lifeSpan -= toAdd;
        }

        if(footSteps[loop]->lifeSpan < 0.2f)
        {
            footSteps.erase(footSteps.begin() + loop);
        }
    }

    radarAmount = 0.0;

    if(mapActive->boundsData[(int)(((y + mapActive->y) + 59) / 32)][(int)(((x + mapActive->x) + 32) / 32)] >> 8 == 5 && savedDolphin == 0)
    {
        radarAmount = 0.3;
    }
    else if(mapActive->boundsData[(int)(((y + mapActive->y) + 59) / 32)][(int)(((x + mapActive->x) + 32) / 32)] >> 8 == 6 && savedDolphin == 0)
    {
        radarAmount = 0.6;
    }
    else if(mapActive->boundsData[(int)(((y + mapActive->y) + 59) / 32)][(int)(((x + mapActive->x) + 32) / 32)] >> 8 == 10 && savedDolphin == 0)
    {
        radarAmount = 1.0;
    }

    if(mapActive->boundsData[(int)(((y + mapActive->y) + 59) / 32)][(int)(((x + mapActive->x) + 32) / 32)] >> 8 == 7 && savedDolphin == 1)
    {
        radarAmount = 0.3;
    }
    else if(mapActive->boundsData[(int)(((y + mapActive->y) + 59) / 32)][(int)(((x + mapActive->x) + 32) / 32)] >> 8 == 8 && savedDolphin == 1)
    {
        radarAmount = 0.6;
    }
    else if(mapActive->boundsData[(int)(((y + mapActive->y) + 59) / 32)][(int)(((x + mapActive->x) + 32) / 32)] >> 8 == 11 && savedDolphin == 1)
    {
        radarAmount = 1.0;
    }
}


bool _Santa::checkPenguins(_Map *mapActive, _PenguinSystem *penguinSystemActive)
{
    static bool xCheck = false;
    static bool yCheck = false;

    for(int i=0; i<(int)penguinSystemActive->penguin.size(); i++)
    {
        xCheck = false;
        yCheck = false;

        if(penguinSystemActive->penguin[i]->x < x + mapActive->x)
        {
            if((x + mapActive->x) - penguinSystemActive->penguin[i]->x < 100)
            {
                xCheck = true;
            }
        }
        if(penguinSystemActive->penguin[i]->x >= x + mapActive->x)
        {
            if(penguinSystemActive->penguin[i]->x - (x + mapActive->x) < 110)
            {
                xCheck = true;
            }
        }
        if(penguinSystemActive->penguin[i]->y < y + mapActive->y)
        {
            if((y + mapActive->y) - penguinSystemActive->penguin[i]->y < 60)
            {
                yCheck = true;
            }
        }
        if(penguinSystemActive->penguin[i]->y >= y + mapActive->y)
        {
            if(penguinSystemActive->penguin[i]->y - (y + mapActive->y) < 80)
            {
                yCheck = true;
            }
        }

        if((xCheck && yCheck))
        {
            penguinSystemActive->caughtX = penguinSystemActive->penguin[i]->x + 20;
            penguinSystemActive->caughtY = penguinSystemActive->penguin[i]->y + 24;
            penguinSystemActive->penguin[i]->moveState = 10;
            penguinSystemActive->penguin[i]->animState = _Penguin::stateRunning;
            penguinSystemActive->caughtType = _Penguin::caughtStateSeen;
            return(true);
        }
    }

    return(false);
}

void _Santa::addLife()
{
    totalLives++;

    sprintf(stringLives, "x%i", totalLives);
}

void _Santa::addFish()
{
    totalFish++;

    sprintf(stringFish, "x%i", totalFish);
}


void _Santa::removeLife()
{
    totalLives--;

    sprintf(stringLives, "x%i", totalLives);
}

void _Santa::removeFish()
{
    totalFish--;

    sprintf(stringFish, "x%i", totalFish);
}

void _Santa::setLives(int _lives)
{
    totalLives = _lives;

    sprintf(stringLives, "x%i", totalLives);
}

void _Santa::setFish(int _fish)
{
    totalFish = _fish;

    sprintf(stringFish, "x%i", totalFish);
}

_Footstep::_Footstep(float xArg, float yArg, float lifeSpanArg)
{
    x = xArg;
    y = yArg;
    lifeSpan = lifeSpanArg;
}

_Footstep::~_Footstep()
{
}

float getPositiveF(float a, float range)
{
    if(a < 0.0f)
    {
        a = range + a;
        a = range - a;

        return(a);
    }

    return(a);
}


void _Santa::checkForDolphin(_Map *mapActive)
{
    if(mapActive->boundsData[(int)(((y + mapActive->y) + 59) / 32)][(int)(((x + mapActive->x) + 32) / 32)] >> 8 == 10 && savedDolphin == 0)
    {
        if(flipFlag == 1 && animState == stateHoldFish)
        {
            dolphinCounter++;

            if(dolphinCounter == 200)
            {
                foundDolphin = true;
            }
        }
    }

    if(mapActive->boundsData[(int)(((y + mapActive->y) + 59) / 32)][(int)(((x + mapActive->x) + 32) / 32)] >> 8 == 11 && savedDolphin == 1)
    {
        if(flipFlag == 0 && animState == stateHoldFish)
        {
            dolphinCounter++;

            if(dolphinCounter == 200)
            {
                foundDolphin = true;
            }
        }
    }
}



