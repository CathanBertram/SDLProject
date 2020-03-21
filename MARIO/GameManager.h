#pragma once
#include "Collisions.h"
#include "SoundManager.h"

class GameManager
{
public:
	~GameManager();

	static GameManager* Instance();

	Collisions* collision;
	SoundManager* soundManager;

private:
	GameManager();
	static GameManager* mInstance;

};
