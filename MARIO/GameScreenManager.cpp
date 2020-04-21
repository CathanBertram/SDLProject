#include "GameScreen.h"
#include "GameScreenManager.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	mRenderer = renderer;
	mCurrentScreen = NULL;
	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	mRenderer = NULL;
	delete mCurrentScreen;
	mCurrentScreen = NULL;
}

void GameScreenManager::Render()
{
	mCurrentScreen->Render();
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	mCurrentScreen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS newScreen)
{
	if (mCurrentScreen !=NULL)
	{
		delete mCurrentScreen;
	}
	switch (newScreen)
	{
	case SCREEN_INTRO:
		tempScreenIntro = new GameScreenIntro(mRenderer);
		mCurrentScreen = (GameScreen*)tempScreenIntro;
		tempScreenIntro = NULL;
		break;
	case SCREEN_MENU:
		break;
	case SCREEN_LEVEL1:
		tempScreenL1 = new GameScreenLevel1(mRenderer, "Level/level.txt");
		mCurrentScreen = (GameScreen*)tempScreenL1;
		tempScreenL1 = NULL;
		break;
	case SCREEN_LEVEL2:
		tempScreenL2 = new GameScreenLevel2(mRenderer, "Level/2.txt");
		mCurrentScreen = (GameScreen*)tempScreenL2;
		tempScreenL2 = NULL;
		break;
	case SCREEN__GAMEOVER:
		break;
	case SCREEN_HIGHSCORES:
		break;
	default:
		break;
	}
}

