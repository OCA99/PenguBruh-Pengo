#include "GameData.h"

int GameData::score = 0;
int GameData::lives = 0;
std::vector<std::pair<std::string, int>> GameData::highScores = std::vector<std::pair<std::string, int>>();

void GameData::loadHighScores() {
	highScores.push_back(std::pair<std::string, int>("abc", 1234));
}