#pragma once
class ScoreManager
{
public:
	ScoreManager();
	~ScoreManager();

	int GetScore() { return score; }
	int GetHighScore() { return highScore; }
	void IncreaseScore(int scoreAdd);

	void LoadScore();
	void WriteScore(int writeScore);

private:
	int score;
	int highScore;
};

