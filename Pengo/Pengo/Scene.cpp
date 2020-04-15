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

std::map<std::string, Scene*>* Scene::CreateScenesFromCSV(CSV* data, TypeMap<GameObject>* prefabs) {
	std::map<std::string, Scene*>* result = new std::map<std::string, Scene*>();
	for (std::vector<std::string> line : *data) {
		std::string name = line[0];
		if ((*result).find(name) == (*result).end()) {
			(*result)[name] = new Scene();
		}
		std::string object_type = line[1];
		GameObject* obj = prefabs->getObject(object_type);
		int x = std::stoi(line[2], nullptr);
		int y = std::stoi(line[3], nullptr);
		(*obj).position = Vec2i(x, y);
		(*result)[name]->objects.push_back(obj);

	}
	return result;
}
