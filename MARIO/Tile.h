#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity, bool collide, bool broke);
	~Tile();
	void Render();

	bool collidable;
	bool breakable;
};

