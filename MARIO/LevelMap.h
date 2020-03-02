#pragma once

#include <fstream>
#include <vector>
#include "Main.h"

class LevelMap
{
public:	
	LevelMap(int map[MAP_HEIGHT][MAP_WIDTH]);
	~LevelMap();

	int GetTileAt(unsigned int h, unsigned int w);

	void ChangeTileAt(unsigned int h, unsigned int w, unsigned int newValue);

private:
	int** mMap;
};

