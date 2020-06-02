#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"

#include "Animation.h"

#define DYNAMIC_TEXT_LEN 5

struct SDL_Texture;

class ModuleUI : public Module
{
public:
	//Constructor
	ModuleUI(bool startEnabled);

	//Destructor
	~ModuleUI();

	bool Init();

	bool Start();

	bool CleanUp();

	Update_Status PreUpdate() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	void intToString(char* buffer, int k);

	void RenderDynamicText(char* text, int x, int y, int fontIndex, bool inverse);

private:
	int blueFontID = -1;
	int whiteFontID = -1;

	Animation life;
	SDL_Texture* texture = nullptr;
};

#endif