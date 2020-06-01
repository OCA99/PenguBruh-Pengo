
#include "Score.h"


Score::Score(bool startEnabled) : Module(startEnabled) {}

Score::~Score(){}

void Score::AddScore(int s) {
	score += s;
	if (score > 99999) score = 99999;
}

void Score::SetHighscore(int s) {
	highscore = s;
}