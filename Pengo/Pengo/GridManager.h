#pragma once

#include <vector>
#include "GameObject.h"
#include "Vec2.h"

class GridManager
{
public:
	GridManager();
	GridManager(int _w, int _h, Vec2i _upperLeft, Vec2i _lowerRight, std::vector<GameObject*> _objects);
	~GridManager();
	std::vector<GameObject*>* getCell(int x, int y);
	void init();
	void addObject(GameObject* o);

	int w;
	int h;
	Vec2i upperLeft;
	Vec2i lowerRight;
	std::vector<GameObject*>* grid;
private:
};