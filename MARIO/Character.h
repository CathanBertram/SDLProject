#pragma once
#include <SDL.h>
#include <iostream>
#include "Commons.h"
#include "Main.h"
#include "LevelMap.h"
#include "Texture2D.h"

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	float GetCollisionRadius();

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
	Rect2D GetCollisionBox()
	{
		return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
	};
	bool IsJumping() { return mJumping; };
	void CancelJump();
protected:
	FACING mFacingDirection;
	bool mMovingLeft;
	bool mMovingRight;
	float gravity = 300.0f;
	const float JUMP_FORCE_DECREMENT = 1000.0f;
	const float INITIAL_JUMP_FORCE = 800.0f;

	void Jump();
	void AddGravity(float deltaTime);
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	bool mFalling;

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	Circle2D mCircle;
	float mCollisionRadius;

	//Spritesheet Variables
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float frame;
	int slice; //Slice From Spritesheet
	bool moving;
	const int cFrameTime = 1; //Time For Anim Loop
	float speed;
	bool mJumping;
	bool mCanJump;
	float mJumpForce;

private:

	LevelMap* mCurrentLevelMap;
};

