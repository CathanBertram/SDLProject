#pragma once
#include "GameObject.h"

class Tile : GameObject
{
public:
	Tile(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity, bool collide);
	~Tile();
	void Render();

	bool collidable;
};

