#include "GridManager.h"

#include "GameObject.h"

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
	o->gridPosition = pixelPositionToGrid(o->position);
	o->gridManager = this;
	getCell(o->gridPosition.x, o->gridPosition.y)->push_back(o);
}

Vec2i GridManager::pixelPositionToGrid(Vec2i pos) {
	int x = pos.x - upperLeft.x;
	int y = pos.y - upperLeft.y;
	cellSize = (lowerRight.x - upperLeft.x) / w;
	int gridX = x / cellSize;
	int gridY = y / cellSize;
	return Vec2i(gridX, gridY);
}

bool GridManager::containsObject(Vec2i position, int type) {
	for (GameObject* o : *getCell(position.x, position.y)) {
		if (o->type == type) {
			return true;
		}
	}
	return false;
}

bool GridManager::canMoveToPosition(Vec2i position) {
	// 2 = Block, 3 = Diamond
	if (position.x > w - 1 || position.x < 0) return false;
	if (position.y > h - 1 || position.y < 0) return false;
	if (containsObject(position, 2) || containsObject(position, 3)) return false;
	return true;
}

std::vector<GameObject*>* GridManager::getCell(int x, int y) {
	return &grid[y * w + x];
}

Vec2i GridManager::gridToPixelPosition(Vec2i gridPos) {
	int x = gridPos.x * cellSize + upperLeft.x;
	int y = gridPos.y * cellSize + upperLeft.y;
	return Vec2i(x, y);
}


GridManager::~GridManager()
{
}