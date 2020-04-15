#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using CSV = std::vector<std::vector<std::string>>;

inline std::vector<std::string> getLineAndSplit(std::istream& file) {
	std::vector<std::string> result;
	std::string line;
	std::getline(file, line);

	std::stringstream lineStream(line);
	std::string cell;

	while (std::getline(lineStream, cell, ','))
	{
		result.push_back(cell);
	}
	return result;
}

inline CSV* readCSV(std::string path) {
	CSV* result = new CSV();

	std::ifstream file(path);

	while (file.peek() != EOF) {
		(*result).push_back(getLineAndSplit(file));
	}

	return result;
}