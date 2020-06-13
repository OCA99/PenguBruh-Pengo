#ifndef __SCENE_LEVEL_H__
#define __SCENE_LEVEL_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel : public Module
{
public:
	SceneLevel(bool startEnabled);
	~SceneLevel();
	virtual bool Start();
	Update_Status Update();
	virtual Update_Status PostUpdate();
	virtual bool CleanUp();

protected:
	bool musicon = false;
	float timer = 0.0f;

};

#endif