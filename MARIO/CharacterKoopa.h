#pragma once
#include "Character.h"
class CharacterKoopa : public Character
{
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, FACING startFace, bool gravity, float movementSpeed);
	~CharacterKoopa();

	void TakeDamage(float deltaTime);
	void Jump(float deltaTime);

	void Update(float deltaTime, SDL_Event e);
	void Render();

	bool GetAlive();
	void SetAlive(bool alive);
	void Injure();
	bool GetInjured() { return mInjured; }

	void Flip(float deltaTime);
private:
	bool mInjured;
	float mInjuredTime;

	void FlipRightWayUp(float deltaTime);

	bool flippable;
	float flipCooldown;
	const int cFlipCooldown = 1;
	const int cKoopaFrameTime = 2;
};

