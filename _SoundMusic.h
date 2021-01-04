#ifndef _SOUNDMUSIC_H
#define _SOUNDMUSIC_H

#include "_Decls.h"

using namespace irrklang;

class _SoundMusic
{
    public:
        _SoundMusic();
        virtual ~_SoundMusic();

        ISoundEngine* soundEngine;
        ISound *musicBackground;
        ISound *soundPenguin;

        void playVictory();
        void playDolphin();
        void playPenguin();
        void stopPenguin();
        void playLose();
        void playWon();
};

#endif // _SOUNDMUSIC_H
