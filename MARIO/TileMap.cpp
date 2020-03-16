#include "TileMap.h"
#include "GameScreen.h"

TileMap::TileMap(vector<Tile*> tiles, SDL_Renderer* renderer, std::string imagePath, GameScreen* screen)
{
	mRenderer = renderer;
	tempScreen = screen;
	LoadLevel(imagePath);
	std::cerr << "hello" << std::endl;
}

TileMap::~TileMap()
{
	//Delete Vectors
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
	//Read In Map Height And Width
	inFile >> levelWidth;
	inFile >> levelHeight;

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
			tileMap.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			break;
		case 1:
			//Ground Tile
			tileMap.push_back(new Tile(mRenderer, "Images/Ground.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, true, false));
			break;
		case 2:
			//Bricks
			tileMap.push_back(new Tile(mRenderer, "Images/BrickNew.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, true, true));
			break;
		case 3:
			//Create Blank Tile
			tileMap.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			//Create Mario

			//Assign Position Variable For Game Objects
			tempScreen->CreateMario(Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT));
			break;
		case 4:
			//Create Blank Tile
			tileMap.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			//Create Luigi
			tempScreen->CreateLuigi(Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT));
			break;
		case 5:
			//Create Blank Tile
			tileMap.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			//Create Koopa
			tempScreen->CreateKoopa(Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), FACING_LEFT, KOOPA_SPEED);
			break;
		case 6:
			//Create Blank Tile
			tileMap.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			//Create PowBlock
			break;
		case 7:
			//Create Blank Tile
			tileMap.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			//Create Coin
			tempScreen->CreateCoin(Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT));
			break;
		case 8:
			//Create Blank Tile
			tileMap.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, false, false));
			//Create Win Flag
			break;
		case 9:
			//Create Unbreakable Tile
			tileMap.push_back(new Tile(mRenderer, "Images/Blank.png", Vector2D(x * TILE_WIDTH, y * TILE_HEIGHT), false, true, false));
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

