#pragma once
#ifndef __SCENE_Points_H__
#define __SCENE_Points_H__

#include "Module.h"
#include "Application.h"
#include "ModuleUI.h"

struct SDL_Texture;

class ScenePoints : public Module
{
public:
	//Constructor
	ScenePoints(bool startEnabled);

	//Destructor
	~ScenePoints();

	void intToString(char* buffer, int k);

	void RenderDynamicText(char* text, int x, int y, int fontIndex, bool inverse);
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


private:
	int blueFontID = -1;
	int whiteFontID = -1;
	int yellowFontID = -1;
};

#endif