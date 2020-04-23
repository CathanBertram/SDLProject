#pragma once
#include "Character.h"
#include "TileMap.h"
#include "Coin.h"

class Character;

class Collisions
{
public:
	Collisions();
	~Collisions();

	bool Circle(Character* obj1, Character* obj2);
	bool Box(Rect2D rect1, Rect2D rect2);

	bool CheckMapColl(Character* obj, TileMap* map);
	bool CheckMapCollV2(Character* obj, TileMap* map);
	bool CheckMapCollLR(Character* obj, TileMap* map);
	bool CheckMapCollLeft(Character* obj, float deltaTime, TileMap* map);
	bool CheckMapCollRight(Character* obj, float deltaTime, TileMap* map);
	bool CheckMapCollUp(Character* obj, TileMap* map);
	bool CheckMapCollDown(Character* obj, TileMap* map);
	bool CheckMapCollUR(Character* obj, float deltaTime, TileMap* map);
	bool CheckMapCollUL(Character* obj, float deltaTime, TileMap* map);
	bool CheckMapCollDR(Character* obj, float deltaTime, TileMap* map);
	bool CheckMapCollDL(Character* obj, float deltaTime, TileMap* map);
	void ObjectCollChecks(Character* obj, float deltaTime, TileMap* map);

	void CoinCollisions(Coin* obj, TileMap* map, float deltaTime);
	bool CharacterCollisions(Character* obj1, Character* obj2, TileMap* map, float deltaTime);

private:

};

