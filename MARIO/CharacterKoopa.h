#pragma once
#include "Character.h"
class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFace, float movementSpeed);
	~CharacterKoopa();

	void TakeDamage(float deltaTime);
	void Jump(float deltaTime);

	void Update(float deltaTime, SDL_Event e);
	void Render();

	bool GetAlive();
	void SetAlive(bool alive);

private:
	bool mInjured;
	float mInjuredTime;

	void Flip(float deltaTime);
	void FlipRightWayUp(float deltaTime);

	bool flippable;
	float flipCooldown;
	const int cFlipCooldown = 0.05;
	const int cKoopaFrameTime = 2;
};

