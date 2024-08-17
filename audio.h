#ifndef MUSIC_H
#define MUSIC_H
#include "raylib.h"

class Audio
{
private:
    bool pause;

public:
    Audio();
    ~Audio();

    Music music;

    void playMusic(void);
};

#endif