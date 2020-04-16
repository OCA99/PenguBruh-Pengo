#pragma once

#include <vector>
#include <map>
#include "TypeMap.h"
#include "GameObject.h"
#include "CSVReader.h"
#include "GridManager.h"

class Scene
{
public:
	Scene();
	~Scene();

	void init();
	void update();
	void render();
	void clean();

	static std::map<std::string, Scene*>* CreateScenesFromCSV(CSV* data, TypeMap<GameObject>* prefabs);

	std::vector<GameObject*> objects;
private:
	GridManager* gridManager = nullptr;
};