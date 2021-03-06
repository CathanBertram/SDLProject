#pragma once
#include "Character.h"
#include "SDL.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, FACING startFace, bool gravity);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);
	void Render();

	bool GetDead() { return dead; }

	void SetDead() { dead = true; }
	void SetAlive() { dead = false; }

private:
	bool dead;
};

