#pragma once
#include "GameObject.h"

class Coin : public GameObject
{
public:
	Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity);
	~Coin();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void Jump(float deltaTime, float force);

	void AddCoinGravity(float deltaTime);

private:
	bool mFalling;
	bool mCanJump;
	float mJumpForce;
	bool mJumping;
};

