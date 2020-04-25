#pragma once
#include "GameObject.h"
class GameOver : public GameObject
{
public:
	GameOver(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity);
	~GameOver();

	void Render();
	void Update(float deltaTime, SDL_Event e);

private:
};

