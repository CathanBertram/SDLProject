#pragma once
#include "Collisions.h"
#include "SoundManager.h"
#include "GameScreenManager.h"
#include "Camera.h"

class GameManager
{
public:
	~GameManager();

	static GameManager* Instance();

	Collisions* collision;
	SoundManager* soundManager;
	GameScreenManager* gameScreenManager;
	Camera* camera;

private:
	GameManager();
	static GameManager* mInstance;

};
