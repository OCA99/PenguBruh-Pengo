#pragma once

#include "Module.h"

class Score : public Module {
public:
	//Methods
	Score(bool startEnabled);
	~Score();

	void AddScore(int s);
	void AddScore(float s);
	void AddScore(int s, int x, int y);
	void SetHighscore(int s);
	int GetScore() { return score; };
	int GetHighscore() { return highscore; };
	void CheckAndSetHighscore();
	void ResetScore();
private:
	int highscore = 0;
	int score = 0;
	float scoreRemainder;
};