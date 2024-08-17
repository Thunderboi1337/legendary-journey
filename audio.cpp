#include "audio.h"
#include "stddef.h"
Audio::Audio()
{

    InitAudioDevice();
    music = LoadMusicStream("Knutte.mp3");

    if (music.stream.buffer == NULL) // Check if music failed to load
    {
        TraceLog(LOG_ERROR, "Failed to load music stream.");
        pause = true; // Prevent music from playing
    }
    else
    {
        pause = false;
        PlayMusicStream(music);
    }
}

Audio::~Audio()
{
    UnloadMusicStream(music);
}

void Audio::playMusic(void)
{
    if (music.stream.buffer != NULL) // Ensure music is valid
    {
        UpdateMusicStream(music);

        if (IsKeyPressed(KEY_M)) // Use IsKeyPressed to toggle on key press, not key down
        {
            pause = !pause;

            if (pause)
                PauseMusicStream(music);
            else
                ResumeMusicStream(music);
        }
    }
}
