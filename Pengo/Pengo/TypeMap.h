#pragma once

#include <map>
#include <string>
#include <functional>
#include <iostream>

template<typename G>
class TypeMap {

public:

	TypeMap() {};
	~TypeMap() {};

	template<typename O>
	void registerType(const std::string name) {
		(*types)[name] = []() { return new O; };
	}

	G* getObject(const std::string name) {
		return (*types)[name]();
	}

private:
	std::map<std::string, std::function<G * ()>>* types = new std::map<std::string, std::function<G *()>>();
};