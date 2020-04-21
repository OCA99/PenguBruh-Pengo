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
	virtual Update_Status Update();
	virtual Update_Status PostUpdate();
	virtual bool CleanUp();
};

#endif