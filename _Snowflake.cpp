#include "_Snowflake.h"



_Snowflake::_Snowflake(float xArg, float yArg, float scaleArg, ALLEGRO_BITMAP *imgFlakeArg)
{
    x = xArg;
    y = yArg;

    scale = scaleArg;

    ySpeed = 2 + (0.2 * (rand() % 16));

    dir = 1;
    xSpeed = -2 + (rand() % 4);

}

_Snowflake::~_Snowflake()
{
    //dtor
}

_SnowflakeSystem::_SnowflakeSystem()
{
    totalFlakes = 100;
    counter = 0;

    imgFlake = al_load_bitmap("gfx/snowflake.png");

    timerShift = al_create_timer(1.0 / 240);

    timerChange = al_create_timer(15 + rand()%15);


	if (!timerShift) {
		writeLog("Failed to create timerShift", 177);
	}

	if (!timerChange) {
		writeLog("Failed to create timerChange", 177);
	}

	al_start_timer(timerShift);
	al_start_timer(timerChange);

    for(int i=0; i < 400; i++)
    {
        snowFlake.push_back(new _Snowflake(-600 + rand() % 2480, 0 + rand() % 720, 4 + rand() % 8, imgFlake));
    }
}

_SnowflakeSystem::~_SnowflakeSystem()
{
    if(imgFlake != NULL)
    {
        al_destroy_bitmap(imgFlake);
    }

    if(timerShift != NULL)
    {
        al_destroy_timer(timerShift);
    }

    if(timerChange != NULL)
    {
        al_destroy_timer(timerChange);
    }

    for(int i=0; i<(int)snowFlake.size(); i++)
    {
        delete snowFlake[i];
        snowFlake.erase(snowFlake.begin() + i);
    }

    writeLog("Snowflake system cleaned successfully", 0);
}

void _SnowflakeSystem::update(_Map *mapActive)
{

    for(int i = 0; i < (int)snowFlake.size(); i++)
    {
        if(snowFlake[i]->dir == 1)
        {
            snowFlake[i]->xSpeed += 0.01;

            if(snowFlake[i]->xSpeed >= 1.0) snowFlake[i]->dir = 2;
        }
        else if(snowFlake[i]->dir == 2)
        {
            snowFlake[i]->xSpeed -= 0.01;

            if(snowFlake[i]->xSpeed <= -1.0) snowFlake[i]->dir = 1;
        }

        snowFlake[i]->y += snowFlake[i]->ySpeed;
        snowFlake[i]->x += snowFlake[i]->xSpeed;

        if(mapActive->ySpeed != 0.0)
            snowFlake[i]->y -= mapActive->ySpeed;
        if(mapActive->xSpeed != 0.0)
            snowFlake[i]->x -= mapActive->xSpeed;

        if(snowFlake[i]->y > 720)
        {
            if((int)snowFlake.size() > totalFlakes && (int)al_get_timer_count(timerShift) > 0)
            {
                snowFlake.erase(snowFlake.begin() + i);

                al_set_timer_count(timerShift, 0);
            }
            else
            {
                snowFlake[i]->x = -600 + rand() % 2480;
                snowFlake[i]->y = -360 + rand() % 360;

                snowFlake[i]->scale = 4 + rand() % 16;

                snowFlake[i]->ySpeed = 2 + (0.2 * (rand() % 8));
            }
        }
    }

    if((int)al_get_timer_count(timerShift) > 0 && (int)snowFlake.size() < totalFlakes)
    {
        snowFlake.push_back(new _Snowflake(-600 + rand() % 2480, -360 + rand() % 360, 4 + rand() % 8, imgFlake));

        al_set_timer_count(timerShift, 0);
    }

    if(al_get_timer_count(timerChange) > 0)
    {
        if(totalFlakes < 1050)
        {
            al_set_timer_speed(timerChange, 15 + rand()%15);
            totalFlakes = 1050;
        }
        else
        {
            al_set_timer_speed(timerChange, 15 + rand()%15);
            totalFlakes = 100;
        }

        al_set_timer_count(timerChange, 0);
    }

    sizeAdd = (snowFlake.size() * 10) / 1050;
}

void _SnowflakeSystem::render()
{
    al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);

    al_hold_bitmap_drawing(true);
    for(int i = 0; i < (int)snowFlake.size(); i++)
    {
        if(snowFlake[i]->x > 0 && snowFlake[i]->x < 1280 && snowFlake[i]->y > 0 && snowFlake[i]->y < 720) al_draw_scaled_bitmap(imgFlake, 0, 0, 16, 15, snowFlake[i]->x, snowFlake[i]->y, (snowFlake[i]->scale * 2) + sizeAdd, (snowFlake[i]->scale * 2) + sizeAdd, 0);
    }
    al_hold_bitmap_drawing(false);
}
