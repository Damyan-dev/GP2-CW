#include "BGAudio.h"

BGAudio::BGAudio()
{
    int rate = 22050; // Sets the audio frequency.
    Uint16 format = AUDIO_S16SYS; // Sets the audio format, in this case we are using Signed 16-bit samples.
    int channels = 2; // Sets the audio channels.
    int buffer_size = 4096; // Sets the audio buffer size which dictates how much audio data will be stored.

    if (Mix_OpenAudio(rate, format, channels, buffer_size) != 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Cannot initialise audio: %s", Mix_GetError());
        exit(-1);
    }
}

// Audio destructor.
BGAudio::~BGAudio()
{
    SDL_Quit();
}

// Adds audio from a file.
void BGAudio::addAudioTrack(const char* path) 
{
    gameAudio = Mix_LoadMUS(path);
}

// Plays back audio from the previously stored audio file.
void BGAudio::playAudioTrack() 
{
    if (Mix_PlayingMusic() == 0) {
        Mix_PlayMusic(gameAudio, -1);
    }
}


