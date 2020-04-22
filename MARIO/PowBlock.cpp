#include "PowBlock.h"
#include "GameManager.h"

PowBlock::PowBlock(SDL_Renderer* renderer, Vector2D pos)
{
	mRenderer = renderer;
	mPosition = pos;

	string imagePath = "Images/PowBlock.png";
	mTexture = new Texture2D(mRenderer);
	if (!mTexture->LoadFromFile(imagePath))
	{
		cout << "Failed To load Texture: " << imagePath << endl;
		return;
	}

	mSingleSpriteWidth = mTexture->GetWidth() / 3;
	mSingleSpriteHeight = mTexture->GetHeight();
	mNumberOfHitsLeft = 3;
	mPosition = pos;
	collidable = true;
}

PowBlock::~PowBlock()
{
	mRenderer = NULL;
	delete mTexture;
	mTexture = NULL;
	mLevelMap = NULL;
}

void PowBlock::Render()
{
	if (mNumberOfHitsLeft > 0)
	{
		int left = mSingleSpriteWidth * (mNumberOfHitsLeft - 1);
		SDL_Rect portionOfSpritesheet = { left, 0, mSingleSpriteWidth, mSingleSpriteHeight };
		SDL_Rect destRect = { (int)(mPosition.x - GameManager::Instance()->camera->GetRect().x),(int)(mPosition.y - GameManager::Instance()->camera->GetRect().y), mSingleSpriteWidth, mSingleSpriteHeight };

		mTexture->Render(portionOfSpritesheet, destRect, SDL_FLIP_NONE);
	}
}


void PowBlock::TakeAHit()
{
	if (mNumberOfHitsLeft <= 0)
	{
		mNumberOfHitsLeft = 0;
		collidable = false;
	}
	else
	{
		mNumberOfHitsLeft--;
		mSingleSpriteHeight -= 8;
		GameManager::Instance()->soundManager->PlaySFX("AUDIO/PowBlock.ogg");
	}
}

