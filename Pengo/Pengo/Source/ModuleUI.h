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

	void Bonus(int points);

	
	bool fx = true;
private:
	int blueFontID = -1;
	int whiteFontID = -1;
	int yellowFontID = -1;

	Animation life;
	Animation death;
	Animation egg;
	Animation eggFX;
	Animation levelFlag;
	Animation levelFlag5;
	SDL_Texture* texture = nullptr;

	bool showingBonus = false;
	int remainingBonus = 0;
	float showingCounter = 0.0f;
};

#endif