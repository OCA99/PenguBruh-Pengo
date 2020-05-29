
#include "Score.h"


Score::Score(){
	m_score = 0;
}

Score::~Score(){}

void Score::SumPoints(Score &score, int points) {
	score.m_score += points;

}