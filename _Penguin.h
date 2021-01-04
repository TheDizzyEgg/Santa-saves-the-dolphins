#ifndef _PENGUIN_H
#define _PENGUIN_H

#include "_Decls.h"

#define PENG_MAX_IDLE_FRAMES 3
#define PENG_MAX_RUNNING_FRAMES 4



class _Penguin
{
    public:
        _Penguin(float _x, float _y, float _endX, float _endY, int _moveClock, int _type);
        virtual ~_Penguin();

        enum States
        {
            stateIdle = 1,
            stateRunning = 2,
        };

        enum CaughtStates
        {
            caughtStateSeen = 1,
            caughtStateFootstep = 2,
        };

        float x;
        float y;
        float startX;
        float startY;
        float endX;
        float endY;
        float speedInc;
        int idleTimer;
        int idleFrame;
        int runningTimer;
        int runningFrame;
	    int animState;
	    int flipFlag;
	    int moveTimer;
	    int moveClock;
	    int moveState;
        char stringLightX[32];
        char stringLightY[32];
        char stringLightPower[32];
        char stringLightDiffuse[32];
        char stringLightAlive[32];

        void render(_Map *mapActive);
        void update();
};

class _PenguinSystem
{
    public:
        _PenguinSystem();
        virtual ~_PenguinSystem();

        float caughtX, caughtY;
        int caughtType;

        ALLEGRO_BITMAP *imgIdle[PENG_MAX_IDLE_FRAMES];
        ALLEGRO_BITMAP *imgRunning[PENG_MAX_RUNNING_FRAMES];

        std::vector<_Penguin*> penguin;

        void createPenguins(_Map *mapActive);
        void renderPenguins(_Map *mapActive);
        void updatePenguins();
        bool checkFootsteps(_Santa *santaActive);
        void resetPenguins();

};

#endif // _PENGUIN_H
