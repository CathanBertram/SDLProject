#include "CharacterMario.h"

CharacterMario::CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map, FACING startFace, bool gravity) : Character(renderer, imagePath, startPosition, map, startFace, gravity)
{
	mRenderer = renderer;

	mSingleSpriteWidth = mTexture->GetWidth() / 12;
	mSingleSpriteHeight = mTexture->GetHeight();
}

CharacterMario::~CharacterMario()
{
	delete  mRenderer;
	mRenderer = NULL;
}

void CharacterMario::Update(float deltaTime, SDL_Event e) 
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
		case SDLK_LEFT:
			mMovingLeft = true;
			break;
		case SDLK_RIGHT:
			mMovingRight = true;
			break;
		case SDLK_UP:
			Jump();	
			break;
		}

		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_LEFT:
			mMovingLeft = false;
			break;
		case SDLK_RIGHT:
			mMovingRight = false;
			break;
		}
		break;
	}
}

void CharacterMario::Render()
{
	Character::Render();
}
