#pragma once
#include "Character.h"
#include "SDL.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~CharacterMario();

	void Update(float deltaTime, SDL_Event e);
	void Render();
};

