#pragma once
#include "LevelMap.h"
#include "Commons.h"
#include "Texture2D.h"

class PowBlock
{
public:
	PowBlock(SDL_Renderer* renderer, Vector2D pos);
	~PowBlock();

	void Render();
	Rect2D GetCollisionBox()
	{
		return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
	}
	void TakeAHit();
	bool IsAvailable()
	{
		return mNumberOfHitsLeft > 0;
	}
	bool IsCollidable() { return collidable; }

private:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	LevelMap* mLevelMap;

	float mSingleSpriteWidth;
	float mSingleSpriteHeight;

	int mNumberOfHitsLeft;

	bool collidable;
};

