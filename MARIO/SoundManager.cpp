#include <iostream>
#include "SoundManager.h"

SoundManager::SoundManager()
{
	gMusic = NULL;
}

SoundManager::~SoundManager()
{
	Mix_FreeMusic(gMusic);
	gMusic = NULL;
	Mix_FreeChunk(sfx);
	sfx = NULL;
}

void SoundManager::PlayMusic(std::string filePath)
{
	LoadMusic(filePath);
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(gMusic, -1);
	}
}

void SoundManager::PlaySFX(std::string filePath)
{
	sfx = Mix_LoadWAV(filePath.c_str());
	if (sfx != NULL)
	{
		Mix_PlayChannel(-1, sfx, 0);
	}
	else
	{
		std::cerr << "Error Loading File " << filePath << std::endl;
	}

}

void SoundManager::LoadMusic(std::string filePath)
{
	gMusic = Mix_LoadMUS(filePath.c_str());
	if (gMusic == NULL)
	{
		std::cout << "Failed To Load Background Music! Error: " << Mix_GetError() << std::endl;
	}
}

void SoundManager::LoadSFX(std::string filePath)
{
	if (sfx == NULL)
	{
		std::cout << "Failed To Load sfx! Error: " << Mix_GetError() << std::endl;
	}
}


