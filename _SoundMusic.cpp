#include "_SoundMusic.h"

using namespace irrklang;

_SoundMusic::_SoundMusic()
{
    soundEngine = createIrrKlangDevice();

    soundEngine->setSoundVolume(0.5);

    musicBackground = soundEngine->play2D("audio/xmas_93.mod", true, true, true, ESM_AUTO_DETECT, true);
    musicBackground->setVolume(0.5);

}

_SoundMusic::~_SoundMusic()
{
    soundEngine->drop();
}


void _SoundMusic::playVictory()
{
    soundEngine->play2D("audio/success.mp3", false);
}

void _SoundMusic::playWon()
{
    soundEngine->play2D("audio/victory.mp3", false);
}

void _SoundMusic::playDolphin()
{
    ISound *soundDolphin = soundEngine->play2D("audio/dolphinspeak.mp3", false, true);
    soundDolphin->setVolume(0.5);
    soundDolphin->setIsPaused(false);
}

void _SoundMusic::playLose()
{
    soundEngine->play2D("audio/lose.mp3", false);
}

void _SoundMusic::playPenguin()
{
    soundPenguin = soundEngine->play2D("audio/peng.mp3", true, true, true, ESM_AUTO_DETECT, true);
    soundPenguin->setVolume(0.5);
    soundPenguin->setIsPaused(false);
}

void _SoundMusic::stopPenguin()
{
    soundPenguin->setIsPaused(true);
    soundPenguin->drop();
}
