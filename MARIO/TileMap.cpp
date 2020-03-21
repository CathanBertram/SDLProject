#include "TileMap.h"
#include "GameScreen.h"

TileMap::TileMap(vector<vector<Tile*> > tiles, SDL_Renderer* renderer, std::string imagePath)
{
	mRenderer = renderer;
	LoadLevel(imagePath);
}

TileMap::~TileMap()
{
	//Delete Vectors
	koopaPos.clear();
	powBlockPos.clear();
	coinPos.clear();
}

int TileMap::GetTileAt(unsigned int h, unsigned int w)
{
	if (h < levelHeight && w < levelWidth)
	{
		return tileMap.at(h).at(w)->collidable;
	}
	else return NULL;
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
	//Read In Map Height And Width
	inFile >> levelWidth;
	inFile >> levelHeight;

	vector<Tile*> tempTile;
	int temp;
	int x = 0, y = 0;
	while (!inFile.eof())
	{
		//Read In Type Of File
		inFile >> temp;

		//Create Tiles
		switch (temp)
		{
		case 0:
			//Blank Tile
			tempTile.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			
			break;
		case 1:
			//Ground Tile
			tempTile.push_back(new Tile(mRenderer, "Images/Ground.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, true, false));
			
			break;
		case 2:
			//Bricks
			tempTile.push_back(new Tile(mRenderer, "Images/BrickNew.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, true, true));
			
			break;
		case 3:
			//Create Blank Tile
			tempTile.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			
			//Assign Position Variable For Game Objects
			marioPos = Vector2D(x * TILE_WIDTH, (y * TILE_HEIGHT) - 16);
			break;
		case 4:
			//Create Blank Tile
			tempTile.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			
			//Create Luigi
			luigiPos = Vector2D(x * TILE_WIDTH, (y * TILE_HEIGHT) - 16);
			break;
		case 5:
			//Create Blank Tile
			tempTile.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			
			//Create Koopa
			koopaPos.push_back(Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT));
			break;
		case 6:
			//Create Blank Tile
			tempTile.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			
			//Create PowBlock
			powBlockPos.push_back(Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT));
			break;
		case 7:
			//Create Blank Tile
			tempTile.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			
			//Create Coin
			coinPos.push_back(Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT));
			break;
		case 8:
			//Create Blank Tile
			
			tempTile.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			//Create Win Flag
			flagPos = Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT);
			break;
		case 9:
			//Create Unbreakable Tile
			tempTile.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, true, false));
			
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
			tileMap.push_back(tempTile);
			//std::cerr << tempTile.size() << std::endl;
			tempTile.clear();
			//std::cerr << tempTile.size() << "   " << tileType.size() << std::endl;
		}
	}

	inFile.close();
}

