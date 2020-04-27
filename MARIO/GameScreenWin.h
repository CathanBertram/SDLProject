#pragma once
#include "GameScreen.h"
class GameScreenWin : public GameScreen
{
public:
	GameScreenWin(SDL_Renderer* renderer);
	~GameScreenWin();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
};

