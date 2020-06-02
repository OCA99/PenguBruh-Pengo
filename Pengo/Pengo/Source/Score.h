#pragma once

#include "Module.h"

class Score : public Module {
public:
	//Methods
	Score(bool startEnabled);
	~Score();

	void AddScore(int s);
	void SetHighscore(int s);
	int GetScore() { return score; };
	int GetHighscore() { return highscore; };
private:
	int highscore = 999;
	int score = 0;
};