#include "GameManager.h"

GameManager* GameManager::mInstance = 0;

GameManager::GameManager()
{

}

GameManager::~GameManager()
{
	mInstance = NULL;
}

GameManager* GameManager::Instance()
{
	if (!mInstance)
	{
		mInstance = new GameManager;
	}

	return mInstance;
}
