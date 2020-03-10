#pragma once
#include "GameObject.h"

class Texture2D;

class Character : public GameObject
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, FACING startFace, bool gravity);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	bool IsJumping() { return mJumping; };
	void CancelJump();

protected:
	bool mMovingLeft;
	bool mMovingRight;

	void Jump();
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	bool mFalling;

	bool moving;
	float speed;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

	FACING mFacingDirection;
	LevelMap* mCurrentLevelMap;
};

