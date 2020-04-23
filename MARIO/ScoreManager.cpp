#include <fstream>
#include <iostream>
#include "ScoreManager.h"

ScoreManager::ScoreManager()
{
	LoadScore();
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::IncreaseScore(int scoreAdd)
{
	score += scoreAdd;
}

void ScoreManager::LoadScore()
{
	std::ifstream inFile;
	inFile.open("Score/score.txt");

	inFile >> highScore;

	std::cerr << highScore << std::endl;

	inFile.close();
}

void ScoreManager::WriteScore(int writeScore)
{
	if (score > highScore)
	{
		std::ofstream outFile;
		outFile.open("Score/score.txt");

		outFile << writeScore;
		std::cerr << "wrote" << std::endl;
		outFile.close();
	}
}
