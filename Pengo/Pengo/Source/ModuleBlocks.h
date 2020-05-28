#ifndef __MODULE_BLOCKS_H__
#define __MODULE_BLOCKS_H__

#include "Module.h"

#define MAX_BLOCKS 160

enum class Block_Type
{
	NO_TYPE,
	NORMAL,
	DIAMOND,
	EGG
};

class Block;
struct SDL_Texture;

class ModuleBlocks : public Module
{
public:
	// Constructor
	ModuleBlocks(bool startEnabled);

	// Destructor
	~ModuleBlocks();

	bool Start() override;

	Update_Status PreUpdate() override;

	Update_Status Update() override;

	Update_Status PostUpdate() override;

	bool CleanUp() override;

	void AddBlock(Block_Type type, int x, int y);

	bool BlockInGridPosition(int x, int y);

	void PushBlock(int fromx, int fromy, int x, int y);

	void DestroyBlock(int x, int y);

	bool PositionInMap(int x, int y);

	void HatchNextEgg();

	bool DestructibleByEnemy(int x, int y);

	void BreakBlock(int x, int y);

private:

	// All spawned enemies in the scene
	Block* blocks[MAX_BLOCKS] = { nullptr };

	// The enemies sprite sheet
	SDL_Texture* texture = nullptr;
};

#endif // __MODULE_ENEMIES_H__