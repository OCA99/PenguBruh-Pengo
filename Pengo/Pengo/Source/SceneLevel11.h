#ifndef __SCENE_LEVEL11_H__
#define __SCENE_LEVEL11_H__

#include "SceneLevel.h"
#include "Animation.h"

struct SDL_Texture;

class SceneLevel11 : public SceneLevel
{
public:
	//Constructor
	SceneLevel11(bool startEnabled);

	//Destructor
	~SceneLevel11();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

	// Disables the player and the enemies
	bool CleanUp();

public:
};

#endif