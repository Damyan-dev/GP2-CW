#pragma once
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>
#include <iostream>
#include <vector>

class BGAudio
{
public:
	BGAudio();
	~BGAudio();

	void addAudioTrack(const char* path); // Adds audio track to memory.
	void playAudioTrack(); // Plays an audio track when called.

private:
	Mix_Music* gameAudio;
};

