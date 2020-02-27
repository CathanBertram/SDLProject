#include "CharacterLuigi.h"

CharacterLuigi::CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	mRenderer = renderer;
	mSingleSpriteWidth = mTexture->GetWidth() / 12;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterLuigi::~CharacterLuigi()
{
	delete  mRenderer;
	mRenderer = NULL;
}

void CharacterLuigi::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);
	if (mJumping && !mFalling)
	{
		slice = 5;
	}
	else if (mFalling)
	{
		slice = 6;
	}
	else if (moving == true)
	{
		frame += deltaTime * 10;
		if (frame > cFrameTime)
		{
			slice++;
			frame = 0;
		}
		if (slice >= 5)
		{
			slice = 1;
		}
	}
	else
	{
		frame = 0;
		slice = 0;
	}
	//Player Input
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = true;
			break;
		case SDLK_d:
			mMovingRight = true;
			break;
		case SDLK_w:
			Jump();
			break;
		}

		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			mMovingLeft = false;
			break;
		case SDLK_d:
			mMovingRight = false;
			break;
		}
		break;
	}
}

void CharacterLuigi::Render()
{
	Character::Render();
}
