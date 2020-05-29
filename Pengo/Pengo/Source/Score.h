#pragma once


class Score {
public:
	int m_score;

private:
	int highscore;
	int lastscore;
public:
	//Methods
	Score();
	~Score();

	void SumPoints(Score& score, int points);

};