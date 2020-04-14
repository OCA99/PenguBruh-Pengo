#include "Scene.h"
#include "Player.h"


Scene::Scene( )
{
	objects = std::vector<GameObject*>();
	prefabs = new TypeMap<GameObject>();
	prefabs->registerType<Player>("player");
	objects.push_back(prefabs->getObject("player"));
}

Scene::~Scene()
{}

void Scene::init()
{
	for (GameObject* o : objects)
	{
		o->init();

	}
}

void Scene::update()
{
	for (GameObject *o : objects)
	{
		o->update();
	}
}

void Scene::render()
{
	for (GameObject* o : objects)
	{
		o->render();
	}
}

void Scene::clean()
{
	for (GameObject* o : objects)
	{
		o->clean();
	}
}
