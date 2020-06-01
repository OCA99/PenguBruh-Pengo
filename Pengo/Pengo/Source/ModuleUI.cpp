#include "ModuleUI.h"

#include "Application.h"
#include "ModuleFonts.h"

#include "SDL/include/SDL_render.h"

ModuleUI::ModuleUI(bool startEnabled) : Module(startEnabled)
{
}

ModuleUI::~ModuleUI()
{
}

#include <iostream>

bool ModuleUI::Init() {

	return true;
}

bool ModuleUI::Start() {
	char lookupTable[] = { "0123456789.,\"!'-©ABCDEFGHIJKLMNOPQRSTUVWXYZ.    " };
	whiteFontID = App->fonts->Load("assets/sprites/Fonts/white.png", lookupTable, 3);
	return true;
}

bool ModuleUI::CleanUp() {
	return true;
}

Update_Status ModuleUI::PreUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::Update()
{
	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleUI::PostUpdate()
{
	return Update_Status::UPDATE_CONTINUE;
}