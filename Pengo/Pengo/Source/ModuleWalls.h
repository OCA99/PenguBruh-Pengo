#ifndef __MODULE_WALLS_H__
#define __MODULE_WALLS_H__

#include "Module.h"

#define MAX_WALLS 160

enum class Wall_Type
{
	HORIZONTAL,
	VERTICAL
};

class Wall;
struct SDL_Texture;

class ModuleWalls : public Module
{
public:
	// Constructor
	ModuleWalls(bool startEnabled);

	// Destructor
	~ModuleWalls();

	bool Start() override;

	Update_Status PreUpdate() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

	void AddWall(Wall_Type type, int x, int y);

	void PushWall(int i);

private:

	// All spawned enemies in the scene
	Wall* walls[MAX_WALLS] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;
};

#endif // __MODULE_ENEMIES_H__