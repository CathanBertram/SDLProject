#pragma once
#include <fstream>
#include <vector>
#include "Tile.h"

class Tile;
class GameScreen;

class TileMap
{
public:
	TileMap(vector<vector<Tile*> > tiles, SDL_Renderer* renderer, std::string imagePath);
	~TileMap();

	int GetTileAt(unsigned int h, unsigned int w);

	void ChangeTileAt(unsigned int h, unsigned int w, unsigned int newValue);

	void LoadLevel(std::string levelToLoad);

	vector<vector<Tile*> > tileMap;
	vector<vector<int> > tileType;

	int GetLevelHeight() { return levelHeight; }
	int GetLevelWidth() { return levelWidth; }

	Vector2D GetMarioPos() { return marioPos; }
	Vector2D GetLuigiPos() { return luigiPos; }
	Vector2D GetFlagPos() { return flagPos; }
	Vector2D GetKoopaPos(int i) { return koopaPos[i]; }
	Vector2D GetPowBlockPos(int i) { return powBlockPos[i]; }
	Vector2D GetCoinPos(int i) { return coinPos[i]; }
	Vector2D GetQuestionPos(int i) { return questionPos[i]; }

	int GetKoopaSize() { return koopaPos.size(); }
	int GetPowBlockSize() { return powBlockPos.size(); }
	int GetCoinSize() { return coinPos.size(); }
	int GetQuestionSize() { return questionPos.size(); }

private:
	SDL_Renderer* mRenderer;
	int levelWidth;
	int levelHeight;

	Vector2D marioPos;
	Vector2D luigiPos;
	Vector2D flagPos;

	vector<Vector2D> koopaPos;
	vector<Vector2D> powBlockPos;
	vector<Vector2D> coinPos;
	vector<Vector2D> questionPos;
};

