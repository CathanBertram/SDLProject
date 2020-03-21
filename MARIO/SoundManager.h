#pragma once
#include <SDL_mixer.h>
#include <string>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	void PlayMusic(std::string filePath);
	void PlaySFX(std::string filePath);

private:
	void LoadMusic(std::string filePath);
	void LoadSFX(std::string filePath);
	Mix_Music* gMusic;
	Mix_Chunk* sfx;
};

