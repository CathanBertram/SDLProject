#pragma once
#include "Character.h"

class Character;

class Collisions
{
public:
	Collisions();
	~Collisions();

	bool Circle(Circle2D obj1, Circle2D obj2);
	bool Box(Rect2D rect1, Rect2D rect2);

private:

};

