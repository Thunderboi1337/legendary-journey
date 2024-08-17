#ifndef MUSIC_H
#define MUSIC_H
#include "raylib.h"

class Audio
{
private:
    /* data */
public:
    Audio(/* args */);
    ~Audio();

    Music music;

    void playMusic(void);

    bool pause;
};

#endif