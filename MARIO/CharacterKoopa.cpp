#include "CharacterKoopa.h"
#include "GameManager.h"

CharacterKoopa::CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, FACING startFace, bool gravity, float movementSpeed) : Character(renderer, imagePath, startPosition, startFace, gravity)
{
	mFacingDirection = FACING(rand() % 2);
	speed = movementSpeed;
	mPosition = startPosition;

	mInjured = false;
	mJumping = false;
	flippable = true;

	mSingleSpriteWidth = mTexture->GetWidth() / 15;
	mSingleSpriteHeight = mTexture->GetHeight();
	slice = 1;

	flipCooldown = 0.0f;
	mCollisionRadius = 5.0f;
}

CharacterKoopa::~CharacterKoopa()
{
}

void CharacterKoopa::TakeDamage(float deltaTime)
{
	mInjured = true;
	mInjuredTime = INJURED_TIME;
	Jump(deltaTime);
}

void CharacterKoopa::Jump(float deltaTime)
{
	if (!mJumping)
	{
		Flip(deltaTime);	
		mJumpForce = INITIAL_JUMP_FORCE_SMALL;
		mJumping = true;
		mCanJump = false;
	}
}

void CharacterKoopa::Update(float deltaTime, SDL_Event e)
{
	if (!mInjured)
	{
		if (mFacingDirection == FACING_LEFT)
		{
			mMovingLeft = true;
			mMovingRight = false;
		}
		else if (mFacingDirection == FACING_RIGHT)
		{
			mMovingRight = true;
			mMovingLeft = false;
		}
	}
	else
	{
		mMovingLeft = false;
		mMovingRight = false;

		mInjuredTime -= deltaTime;
		if (mInjuredTime <= 0)
		{
			FlipRightWayUp(deltaTime);
		}
	}


	//Anim Controls
	if (mMovingLeft || mMovingRight)
	{
		frame += deltaTime * 10;
		if (frame > cKoopaFrameTime)
		{
			slice++;
			frame = 0;
		}
		if (slice >= 5)
		{
			slice = 1;
		}
	}
	else if (mInjured)
	{
		frame += deltaTime * 10;
		if (frame > cKoopaFrameTime)
		{
			slice++;
			frame = 0;
		}
		if (slice > 13)
		{
			slice = 12;
		}
	}

	//Flip Cooldown
	if (flipCooldown > 0)
	{
		flipCooldown -= deltaTime;
		if (flipCooldown <= 0 )
		{
			std::cerr << "Refresh" << std::endl;
			flippable = true;
			flipCooldown = 0;
		}
	}


	Character::Update(deltaTime, e);

}

void CharacterKoopa::Render()
{
	int left = mSingleSpriteWidth * slice;
	SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
	SDL_Rect destRect = { (int)(mPosition.x - GameManager::Instance()->camera->GetRect().x),(int)(mPosition.y - GameManager::Instance()->camera->GetRect().y), mSingleSpriteWidth, mSingleSpriteHeight };


	if (mFacingDirection == FACING_RIGHT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
	if (mFacingDirection == FACING_LEFT)
	{
		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_HORIZONTAL);
	}
}

bool CharacterKoopa::GetAlive()
{
	return false;
}

void CharacterKoopa::SetAlive(bool alive)
{
}

void CharacterKoopa::Injure()
{
	mInjuredTime = INJURED_TIME;
	mInjured = true;
	slice = 13;
}

void CharacterKoopa::FlipRightWayUp(float deltaTime)
{
	mInjured = false;
	Jump(deltaTime);
}

void CharacterKoopa::Flip(float deltaTime)
{
	if (mFacingDirection == FACING_LEFT)
	{
		mFacingDirection = FACING_RIGHT;
	}
	else if (mFacingDirection == FACING_RIGHT)
	{
		mFacingDirection = FACING_LEFT;
	}
}
