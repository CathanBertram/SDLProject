#include "Character.h"
#include "Texture2D.h"
#include "GameScreen.h"
#include "GameManager.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, FACING startFace, bool gravity) : GameObject(renderer, imagePath, startPosition, gravity)
{
	mPosition = startPosition;
	mMovingLeft = false;
	mMovingRight = false;
	speed = PLAYER_SPEED;
	mFacingDirection = startFace;

	frame = 1;
}

Character::~Character()
{
	mCurrentLevelMap = NULL;
	delete mCurrentLevelMap;
}

void Character::Render()
{
	int left = mSingleSpriteWidth * slice;
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x - GameManager::Instance()->camera->GetRect().x),(int)(mPosition.y - GameManager::Instance()->camera->GetRect().y), mSingleSpriteWidth, mSingleSpriteHeight };
	
	if (mFacingDirection==FACING_RIGHT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
	if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	//Adds Gravity Force
	/*if (gravityEnabled)
	{
		AddGravity(deltaTime);
		mCanJump = false;

	}
	else
	{
		mCanJump = true;
	}*/

	//Jump Force Change
	if (mJumping)
	{
		//Adjust Position
		mPosition.y -= mJumpForce * deltaTime;

		//Reduce Jump Force
		mJumpForce -= JUMP_FORCE_DECREMENT * deltaTime;

		if (GRAVITY > mJumpForce)
		{
			mFalling = true;
		}
		//Check If Jump Force = 0
		if (mJumpForce <= 0.0f)
		{
			mJumping = false;
		}
	}
	else
	{
		mFalling = false;
	}

	//Changes Character Direction
	if (mMovingLeft)
	{
		moving = true;
		MoveLeft(deltaTime);
	}
	else if (mMovingRight)
	{
		moving = true;
		MoveRight(deltaTime);
	}
	else
	{
		moving = false;
	}
}

void Character::CancelJump()
{
	mJumpForce = 0.0f;
}

void Character::Jump()
{
	if (!mJumping && mCanJump)
	{
		GameManager::Instance()->soundManager->PlaySFX("AUDIO/Jump.ogg");
		mJumpForce = INITIAL_JUMP_FORCE;
		mJumping = true;
		mCanJump = false;
	}
}

void Character::MoveLeft(float deltaTime)
{
	for (int i = 0; i < numOfMoves; i++)
	{
		mFacingDirection = FACING_LEFT;
		mPosition.x -= (speed / NUMBER_OF_MOVEMENTS) * deltaTime;
	}
}

void Character::MoveRight(float deltaTime)
{
	for (int i = 0; i < numOfMoves; i++)
	{
		mFacingDirection = FACING_RIGHT;
		mPosition.x += (speed / NUMBER_OF_MOVEMENTS) * deltaTime;
	}
}

Vector2D Character::CheckLeftMovement(float deltaTime)
{
	tempPos.x -= (speed / NUMBER_OF_MOVEMENTS) * deltaTime;
	return tempPos;
}

Vector2D Character::CheckRightMovement(float deltaTime)
{
	tempPos.x += (speed / NUMBER_OF_MOVEMENTS) * deltaTime;
	return tempPos;
}
