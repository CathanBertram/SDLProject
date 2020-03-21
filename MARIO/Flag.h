#pragma once
#include "GameObject.h"
class Flag : public GameObject
{
public:
	Flag(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity);
	~Flag();

	void Render();
	void Update(float deltaTime, SDL_Event e);
};

