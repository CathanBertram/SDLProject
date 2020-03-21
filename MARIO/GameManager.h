#pragma once
#include "Collisions.h"
#include "SoundManager.h"
#include "GameScreenManager.h"

class GameManager
{
public:
	~GameManager();

	static GameManager* Instance();

	Collisions* collision;
	SoundManager* soundManager;
	GameScreenManager* gameScreenManager;

private:
	GameManager();
	static GameManager* mInstance;

};
