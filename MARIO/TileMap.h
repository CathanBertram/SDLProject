#pragma once
#include <fstream>
#include <vector>
#include "Tile.h"

class Tile;

class TileMap
{
public:
	TileMap(vector<Tile*> tiles, SDL_Renderer* renderer, std::string imagePath);
	~TileMap();

	int GetTileAt(unsigned int h, unsigned int w);

	void ChangeTileAt(unsigned int h, unsigned int w, unsigned int newValue);

	void LoadLevel(std::string levelToLoad);

	vector<Tile*> tileMap;

private:
	SDL_Renderer* mRenderer;
	int levelWidth;
	int levelHeight;
};

