#ifndef _SNOWFLAKE_H
#define _SNOWFLAKE_H

#include "_Decls.h"

#define TOTAL_SNOWFLAKES 1050

class _SnowflakeSystem;
class _Snowflake;

class _SnowflakeSystem
{
    public:
        _SnowflakeSystem();
        virtual ~_SnowflakeSystem();

        int totalFlakes;
        int counter;
        float sizeAdd;

        std::vector<_Snowflake*> snowFlake;

        ALLEGRO_BITMAP *imgFlake = NULL;
        ALLEGRO_TIMER *timerShift = NULL;
        ALLEGRO_TIMER *timerChange = NULL;

        void update(_Map *mapActive);
        void render();
};

class _Snowflake
{
    public:
        _Snowflake(float xArg, float yArg, float scaleArg, ALLEGRO_BITMAP *imgFlakeArg);
        virtual ~_Snowflake();

        float x;
        float y;
        float lastX;
        float lastY;
        float ySpeed;
        float xSpeed;
        float scale;
        int dir;
        bool alive;
        ALLEGRO_BITMAP *imgFlake = NULL;
};

#endif // _SNOWFLAKE_H
