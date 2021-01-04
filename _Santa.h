#ifndef _SANTA_H
#define _SANTA_H

#include "_Decls.h"


#define MAX_FOOTSTEP_IMG 5
#define MAX_IDLE_FRAMES 5
#define MAX_RUNNING_FRAMES 4
#define SCROLL_LEFT_LIMIT 600
#define SCROLL_RIGHT_LIMIT 660
#define SCROLL_UP_LIMIT 320
#define SCROLL_DOWN_LIMIT 340


class _Footstep;

class _Santa
{
    public:
        _Santa();
        virtual ~_Santa();

        enum States
        {
            stateIdle = 1,
            stateRunning = 2,
            stateHoldFish
        };

        float x;
        float y;
        float xSpeed;
        float ySpeed;
        float maxSpeed;
        float speedInc;
        int idleTimer;
        int idleFrame;
        int runningTimer;
        int runningFrame;
	    int animState;
	    int flipFlag;
	    bool movingLeft;
	    bool movingRight;
	    bool movingUp;
	    bool movingDown;
	    int footStepDelay;
	    int totalLives;
	    int totalFish;
	    char stringLives[8];
	    char stringFish[8];
	    bool inWater;
	    float frozenAmount;
	    int dolphinCounter;
	    int savedDolphin;
	    bool foundDolphin;
	    int dolphinTimer;
	    double dolphinSize;
	    bool dolphinEmerged;
	    double radarAmount;
	    double onIce;

	    ALLEGRO_BITMAP *imgIdle[MAX_IDLE_FRAMES];
	    ALLEGRO_BITMAP *imgRunning[MAX_RUNNING_FRAMES];
	    ALLEGRO_BITMAP *imgFootstep;
	    ALLEGRO_BITMAP *imgIconSanta;
	    ALLEGRO_BITMAP *imgIconFish;
	    ALLEGRO_BITMAP *imgFrozen;
	    ALLEGRO_BITMAP *imgHoldFish;
	    ALLEGRO_BITMAP *imgDolphin;
	    ALLEGRO_BITMAP *imgDolphinReflect;
	    ALLEGRO_BITMAP *imgRadarBG;
	    ALLEGRO_BITMAP *imgRadarBar;

	    std::vector<_Footstep*> footSteps;

	    void initialise();
	    void render(_Map *mapActive);
	    void renderFootsteps(_Map *mapActive);
	    void update(_Map *mapActive, int totalSnowflakes, bool keyboardEnabled);
	    void allegroEvent(ALLEGRO_EVENT event);
	    bool checkPenguins(_Map *mapActive, _PenguinSystem *penguinSystemActive);
	    void addLife();
	    void addFish();
	    void removeLife();
	    void removeFish();
	    void setLives(int _lives);
	    void setFish(int _fish);
	    void checkForDolphin(_Map *mapActive);
	    void updateDolphin();
};


class _Footstep
{
    public:
        _Footstep(float xArg, float yArg, float lifeSpanArg);
        virtual ~_Footstep();

        float x;
        float y;
        float lifeSpan;
        int frame;
};



#endif // _SANTA_H
