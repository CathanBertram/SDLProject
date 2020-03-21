#pragma once
#include "Character.h"
#include "TileMap.h"

class Character;

class Collisions
{
public:
	Collisions();
	~Collisions();

	bool Circle(Circle2D obj1, Circle2D obj2);
	bool Box(Rect2D rect1, Rect2D rect2);

	bool CheckMapColl(Character* obj, TileMap* map);
	bool CheckMapCollV2(Character* obj, TileMap* map);
	bool CheckMapCollLR(Character* obj, TileMap* map);
	bool CheckMapCollLeft(Character* obj, float deltaTime, TileMap* map);
	bool CheckMapCollRight(Character* obj, float deltaTime, TileMap* map);
	bool CheckMapCollUp(Character* obj, TileMap* map);
	bool CheckMapCollDown(Character* obj, TileMap* map);
	void ObjectCollChecks(Character* obj, float deltaTime, TileMap* map);

private:

};

