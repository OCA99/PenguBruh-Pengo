#include "GridManager.h"

GridManager::GridManager() {

}

GridManager::GridManager(int _w, int _h, Vec2i _upperLeft, Vec2i _lowerRight, std::vector<GameObject*> _objects)
{
	w = _w;
	h = _h;
	upperLeft = _upperLeft;
	lowerRight = _lowerRight;
	grid = new std::vector<GameObject*>[w * h];
}

void GridManager::init() {
	grid = new std::vector<GameObject*>[w * h];
}

void GridManager::addObject(GameObject* o) {

}

std::vector<GameObject*>* GridManager::getCell(int x, int y) {
	return &grid[y * w + x];
}

GridManager::~GridManager()
{
}