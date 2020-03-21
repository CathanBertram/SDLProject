#pragma once
#include "GameScreen.h"
class GameScreenLevel2 : public GameScreen
{
public:
	GameScreenLevel2(SDL_Renderer* renderer, std::string filePath);
	~GameScreenLevel2();

	void Render();
	void Update(float deltaTime, SDL_Event e);
private:
	Texture2D* mBackgroundTexture;
	bool SetUpLevel();
};

