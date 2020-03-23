#pragma once
#include "GameObject.h"
class QuestionBlock : public GameObject
{
public:
	QuestionBlock(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, bool gravity);
	~QuestionBlock();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	bool IsBroken() { return isBroken; }
	int GetNumOfHits() { return numOfHits; }
	void DecreaseHits() { numOfHits--; }

private:
	bool isBroken;
	int numOfHits;
};

