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
	void EnableJump() { mCanJump = true;}
	void DisableJump() { mCanJump = false;}
	void CancelJump();
	Vector2D CheckLeftMovement(float deltaTime);
	Vector2D CheckRightMovement(float deltaTime);

	void EnableLeftMovement() { leftMovement = true; }
	void EnableRightMovement() { rightMovement = true; }
	void DisableLeftMovement() { leftMovement = false; }
	void DisableRightMovement() { rightMovement = false; }

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

	bool leftMovement;
	bool rightMovement;

	FACING mFacingDirection;
	LevelMap* mCurrentLevelMap;
};

