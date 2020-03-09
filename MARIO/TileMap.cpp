#include "TileMap.h"

TileMap::TileMap(vector<Tile*> tiles, SDL_Renderer* renderer, std::string imagePath)
{
	mRenderer = renderer;
	LoadLevel(imagePath);
}

TileMap::~TileMap()
{
}

int TileMap::GetTileAt(unsigned int h, unsigned int w)
{
	return 0;
}

void TileMap::ChangeTileAt(unsigned int h, unsigned int w, unsigned int newValue)
{
}

void TileMap::LoadLevel(std::string levelToLoad)
{
	ifstream inFile;

	inFile.open(levelToLoad);

	if (!inFile.good())
	{
		std::cerr << "Could Not Open Level File" << std::endl;
		return;
	}

	inFile >> levelWidth;
	inFile >> levelHeight;

	int temp;
	int x = 0, y = 0;
	while (!inFile.eof())
	{
		inFile >> temp;
		switch (temp)
		{
		case 0:
			tileMap.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false));
			break;
		case 1:
			tileMap.push_back(new Tile(mRenderer, "Images/Ground.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, true));
			break;
		case 2:
			tileMap.push_back(new Tile(mRenderer, "Images/BrickNew.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, true));
			break;
		case 3:
			//Create Blank Tile
			//Create Mario
			break;
		case 4:
			//Create Blank Tile
			//Create Luigi
			break;
		case 5:
			//Create Blank Tile
			//Create Koopa
			break;
		case 6:
			//Create Blank Tile
			//Create PowBlock
			break;
		case 7:
			//Create Blank Tile
			//Create Coin
			break;
		case 8:
			//Create Blank Tile
			//Create Win Flag
			break;
		case 9:
			//Create Unbreakable Tile
			break;
		case 10:
			//Create Question Tile
			break;
		}
		x++;
		if (x >= levelWidth)
		{
			x = 0;
			y++;
		}
	}

	inFile.close();
}

