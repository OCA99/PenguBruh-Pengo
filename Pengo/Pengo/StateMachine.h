#pragma once

#include <map>
#include <iterator>
#include <type_traits>

template <typename K, class T>
class StateMachine {
public:
	StateMachine(std::map<K, T>* _states) {
		states = _states;
	}
	~StateMachine() {
		if (!std::is_pointer<T>::value) return;
		std::cout << "Type is a pointer" << std::endl;
		for (auto const& x : (*states))
		{
			T value = x.second;
			delete value;
		}
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
