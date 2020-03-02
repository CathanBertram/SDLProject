#pragma once
#include "Character.h"
#include "SDL.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFace, bool gravity);
	~CharacterLuigi();

	void Update(float deltaTime, SDL_Event e);
	void Render();
};

