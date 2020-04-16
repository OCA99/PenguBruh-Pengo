#include "Scene.h"


Scene::Scene( )
{
	objects = std::vector<GameObject*>();
	gridManager = new GridManager();
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
		if (line[1] == "manager") {
			(*result)[name]->gridManager->w = std::stoi(line[3], nullptr);
			(*result)[name]->gridManager->h = std::stoi(line[4], nullptr);
			int xi = std::stoi(line[5], nullptr);
			int yi = std::stoi(line[6], nullptr);
			int xf = std::stoi(line[7], nullptr);
			int yf = std::stoi(line[8], nullptr);
			(*result)[name]->gridManager->upperLeft = Vec2i(xi, yi);
			(*result)[name]->gridManager->lowerRight = Vec2i(xf, yf);
			(*result)[name]->gridManager->init();
			continue;
		}
		std::string object_type = line[2];
		GameObject* obj = prefabs->getObject(object_type);
		int x = std::stoi(line[3], nullptr);
		int y = std::stoi(line[4], nullptr);
		(*obj).position = Vec2i(x, y);
		(*result)[name]->objects.push_back(obj);
		if (line[1] == "grid_object") {
			(*result)[name]->gridManager->addObject(obj);
		}
	}
	return result;
}
