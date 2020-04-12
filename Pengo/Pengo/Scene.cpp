#include "Scene.h"

Scene::Scene( )
{
	objects = std::vector<GameObject*>();
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
