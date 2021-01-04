#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "_Decls.h"


class _System
{
    public:
        _System();
        virtual ~_System();

        void initialise();
        void useBuffer();
        void useBuffer2();
        void useDisplay();
        void renderBuffer();
        void renderBuffer2();
        void loadIntroBitmap();

        bool running;
        bool redraw;
        float fadeAmount;
        int usefulCounter;

        ALLEGRO_DISPLAY *display = NULL;
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
        ALLEGRO_TIMER *timer = NULL;
        ALLEGRO_BITMAP *imgBuffer = NULL;
        ALLEGRO_BITMAP *imgBuffer2 = NULL;
        ALLEGRO_BITMAP *imgIntro = NULL;
        ALLEGRO_COLOR colorBlack;

        ALLEGRO_FONT *fontMain = NULL;
        ALLEGRO_FONT *fontSmall = NULL;
        ALLEGRO_FONT *fontLarge = NULL;

        void printText(ALLEGRO_FONT *fontActive, ALLEGRO_COLOR colorActive, float x, float y, float flags, const char *textData);
        void renderFade();
};

#endif // _SYSTEM_H
