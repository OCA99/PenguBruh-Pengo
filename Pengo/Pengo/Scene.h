#pragma once

#include <vector>
#include <map>
#include "TypeMap.h"
#include "GameObject.h"


class Player;

class Scene
{
public:
	Scene();
	~Scene();

	void init();
	void update();
	void render();
	void clean();

	std::vector<GameObject*> objects;
private:
	TypeMap<GameObject>* prefabs;
};