#pragma once

#include <vector>
#include <string>
#include <utility>

class GameData {
public:
	static int score;
	static int lives;
	static std::vector<std::pair<std::string, int>> highScores;

	static void loadHighScores();
};
