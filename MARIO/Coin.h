#pragma once
#include "Texture2D.h"
#include "Character.h"

class Coin
{
public:
	Coin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition);
	~Coin();

	Rect2D GetCollisionBox()
	{
		return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
	};
	void Render();
	void Update(float deltaTime, SDL_Event e);
	float GetCollisionRadius() { return mCollisionRadius; }

private:
	//Spritesheet Variables
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float frame;
	int slice; //Slice From Spritesheet
	const int cFrameTime = 1; //Time For Anim Loop
	float mCollisionRadius;
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	Circle2D mCircle;
};

