#pragma once
#include "Texture2D.h"
#include "GameObject.h"

class Coin : public GameObject
{
public:
	Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, bool gravity);
	~Coin();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};

