#include <SDL_image.h>
#include <iostream>
#include "Texture2D.h"
#include "GameManager.h"

using namespace std;

Texture2D::Texture2D(SDL_Renderer* renderer)
{
	mRenderer = renderer;
}

Texture2D::~Texture2D()
{
	Free();
	mRenderer = NULL;
}



bool Texture2D::LoadFromFile(std::string path)
{
	Free();

	SDL_Surface* pSurface = IMG_Load(path.c_str());

	if (pSurface != NULL)
	{
		mTexture = SDL_CreateTextureFromSurface(mRenderer, pSurface);
		if (mTexture == NULL)
		{
			cout << "Unable to create texture from surface. Error: " << SDL_GetError() << endl;
		}
		SDL_FreeSurface(pSurface);

		mWidth = pSurface->w;
		mHeight = pSurface->h;
	}
	else
	{
		cout << "Unable to create texture from surface. Error: " << IMG_GetError() << endl;
	}
	return mTexture != NULL;
}

void Texture2D::Free()
{
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
	}
}

void Texture2D::Render(Vector2D newPosition, SDL_RendererFlip flip, double angle)
{
	SDL_Rect renderLocation{ newPosition.x, newPosition.y, mWidth, mHeight };
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &renderLocation, angle, NULL, flip);
}

void Texture2D::Render(SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip, double angle)
{

	SDL_RenderCopyEx(mRenderer, mTexture, &srcRect, &destRect, angle, NULL, flip);
}
