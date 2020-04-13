#pragma once

#include <map>
#include "Animation.h"

template <typename K, class T>
class StateMachine {
public:
	StateMachine(std::map<K, T>* _states) {
		states = _states;
	}
	~StateMachine() {

	}
	T getCurrentValue() {
		return (*states)[currentState];
	}
	void setCurrentState(K _state) {
		currentState = _state;
	}
private:
	std::map<K, T>* states = new std::map<K, T>();
	K currentState;
};
