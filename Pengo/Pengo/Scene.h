#pragma once

#include <vector>
#include "GameObject.h"

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

};