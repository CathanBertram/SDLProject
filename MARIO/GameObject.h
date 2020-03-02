#pragma once

#include "Commons.h"
#include "Main.h"
#include "LevelMap.h"
#include "Texture2D.h"

class GameObject
{
public:
	GameObject(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity);
	~GameObject();
	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();
	Rect2D GetCollisionBox()
	{
		return Rect2D(mPosition.x, mPosition.y, mSingleSpriteWidth, mSingleSpriteHeight);
	};
	float GetCollisionRadius() {
		return mCollisionRadius;
	}

protected:
	void AddGravity(float deltaTime);

	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;
	Circle2D mCircle;
	float mCollisionRadius;

	//Spritesheet Variables
	FACING mFacingDirection;
	float mSingleSpriteWidth;
	float mSingleSpriteHeight;
	float frame;
	int slice; //Slice From Spritesheet
	const int cFrameTime = 1; //Time For Anim Loop

	bool gravityEnabled;
};

