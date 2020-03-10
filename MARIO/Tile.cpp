#include "Tile.h"

Tile::Tile(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity, bool collide, bool broke) : GameObject(renderer, imagePath, startPosition, gravity)
{
	collidable = collide;
	slice = 0;
	mSingleSpriteWidth = mTexture->GetWidth();
	mSingleSpriteHeight = mTexture->GetHeight();  
	breakable = broke;
}


Tile::~Tile()
{
}

void Tile::Render()
{
	GameObject::Render();
}
