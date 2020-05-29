#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"

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

private:
	int blueFontID = -1;
	int whiteFontID = -1;
};

#endif