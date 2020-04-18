#pragma once

#include <vector>
#include "Vec2.h"
#include <iostream>

class GameObject;

class GridManager
{
public:
	GridManager();
	GridManager(int _w, int _h, Vec2i _upperLeft, Vec2i _lowerRight, std::vector<GameObject*> _objects);
	~GridManager();
	std::vector<GameObject*>* getCell(int x, int y);
	void init();
	void addObject(GameObject* o);
	Vec2i pixelPositionToGrid(Vec2i pos);
	bool containsObject(Vec2i position, int type);
	bool canMoveToPosition(Vec2i position);
	Vec2i gridToPixelPosition(Vec2i gridPos);
	GameObject* getObjectOfType(Vec2i position, int type);
	GameObject* getAnyBlock(Vec2i position);
	bool isPartOfGrid(Vec2i position);

	int w = 0;
	int h = 0;
	Vec2i upperLeft = Vec2i();
	Vec2i lowerRight = Vec2i();
	std::vector<GameObject*>* grid = nullptr;
private:
	int cellSize = 0;
};