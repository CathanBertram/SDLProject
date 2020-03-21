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

bool Collisions::CheckMapColl(Character* obj, TileMap* map)
{
	if (map != NULL)
	{
		for (int i = 0; i < map->tileMap.size(); i++)
		{
			for (int j = 0; j < map->tileMap[i].size(); j++)
			{
				if (map->tileMap[i][j]->collidable == true)
				{
					if (Box(obj->GetCollisionBox(), map->tileMap[i][j]->GetCollisionBox()))
					{
						return true;
					}
				}

			}
		}
		return false;
	}
	return false;
}

bool Collisions::CheckMapCollV2(Character* obj, TileMap* map)
{
	if (map != NULL)
	{
		if (map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight() / 2) / TILE_HEIGHT, obj->GetPosition().x / TILE_WIDTH) == true || //Left
			map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight() / 2) / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth()) / TILE_WIDTH) == true || //Right
			map->GetTileAt(obj->GetPosition().y / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth() / 2) / TILE_WIDTH) == true || //Top
			map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight()) / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth() / 2) / TILE_WIDTH) == true) //Bottom
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool Collisions::CheckMapCollLR(Character* obj, TileMap* map)
{
	if (map != NULL)
	{
		if (map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight() / 2) / TILE_HEIGHT, obj->GetPosition().x / TILE_WIDTH) == true || //Left
			map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight() / 2) / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth()) / TILE_WIDTH) == true) //Right
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool Collisions::CheckMapCollLeft(Character* obj, float deltaTime, TileMap* map)
{
	if (map != NULL)
	{
		if (map->GetTileAt(obj->GetPosition().y / TILE_HEIGHT, obj->CheckLeftMovement(deltaTime).x / TILE_WIDTH) == true ||
			map->GetTileAt((obj->GetPosition().y + (obj->GetSingleHeight() / 2)) / TILE_HEIGHT, obj->CheckLeftMovement(deltaTime).x / TILE_WIDTH) == true ||
			map->GetTileAt((obj->GetPosition().y + (obj->GetSingleHeight() - 1)) / TILE_HEIGHT, obj->CheckLeftMovement(deltaTime).x / TILE_WIDTH) == true)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool Collisions::CheckMapCollRight(Character* obj, float deltaTime, TileMap* map)
{
	if (map != NULL)
	{
		if (map->GetTileAt(obj->GetPosition().y / TILE_HEIGHT, (obj->CheckRightMovement(deltaTime).x + obj->GetSingleWidth()) / TILE_WIDTH) == true ||
			map->GetTileAt((obj->GetPosition().y + (obj->GetSingleHeight() / 2)) / TILE_HEIGHT, (obj->CheckRightMovement(deltaTime).x + obj->GetSingleWidth()) / TILE_WIDTH) == true ||
			map->GetTileAt((obj->GetPosition().y + (obj->GetSingleHeight() - 1)) / TILE_HEIGHT, (obj->CheckRightMovement(deltaTime).x + obj->GetSingleWidth()) / TILE_WIDTH) == true)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool Collisions::CheckMapCollUp(Character* obj, TileMap* map)
{
	if (map != NULL)
	{
		if (map->GetTileAt(obj->GetPosition().y / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth() / 2) / TILE_WIDTH) == true)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

bool Collisions::CheckMapCollDown(Character* obj, TileMap* map)
{
	if (map != NULL)
	{
		if (map->GetTileAt((obj->GetPosition().y + obj->GetSingleHeight()) / TILE_HEIGHT, (obj->GetPosition().x + obj->GetSingleWidth() / 2) / TILE_WIDTH) == true)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

void Collisions::ObjectCollChecks(Character* obj, float deltaTime, TileMap* map)
{
	obj->ResetNumOfMoves();
	obj->SetTempPos();
	FACING facing = obj->GetFacing();
	if (facing == FACING_LEFT)
	{
		//Check Collisions To The Left
		for (int i = 0; i < NUMBER_OF_MOVEMENTS; i++)
		{
			if (CheckMapCollLeft(obj, deltaTime, map) == true)
			{
				break;
			}
			else
			{
				obj->IncreaseNumOfMoves();
			}
		}
	}
	else if (facing == FACING_RIGHT)
	{
		for (int i = 0; i < NUMBER_OF_MOVEMENTS; i++)
		{
			//Check Collisions To The Right
			if (CheckMapCollRight(obj, deltaTime, map) == true)
			{
				break;
			}
			else
			{
				obj->IncreaseNumOfMoves();
			}
		}
	}

	//Check Collisions Up
	if (CheckMapCollUp(obj, map) == true)
	{
		obj->CancelJump();
	}

	//Check Collisions Down
	for (int i = 0; i < NUMBER_OF_MOVEMENTS; i++)
	{
		if (CheckMapCollDown(obj, map) == true)
		{
			obj->EnableJump();
			break;
		}
		else
		{
			obj->AddGravity(deltaTime);
			obj->DisableJump();
		}
	}
}
