#include "Collisions.h"

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
}


bool Collisions::Circle(Circle2D obj1, Circle2D obj2)
{
	//Calculate Vector Between The Two Objects
	Vector2D vec = Vector2D((obj1.position.x - obj2.position.x),
							(obj1.position.y - obj2.position.y));
	//Calculate the length of the vector
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	double combinedDistance = (obj1.radius + obj2.radius);
	return distance < combinedDistance;
}

bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	if (rect1.x < rect2.x + rect2.w &&
		rect1.x + rect1.w > rect2.x &&
		rect1.y < rect2.y + rect2.h &&
		rect1.y + rect1.h > rect2.y)
	{
		return true;
	}
	return false;

}
