#pragma once

#include <vector>
#include <map>
#include "TypeMap.h"
#include "CSVReader.h"
#include "GridManager.h"

class GameObject;

class Scene
{
public:
	Scene();
	~Scene();

	void init();
	void update();
	void render();
	void clean();

	Scene& operator=(const Scene& rhs) {};

	static std::map<std::string, Scene*>* CreateScenesFromCSV(CSV* data, TypeMap<GameObject>* prefabs);

	std::vector<GameObject*> objects;
	GridManager* gridManager = nullptr;
private:
};