#ifndef __MODULE_DEBUG_H__
#define __MODULE_DEBUG_H__

#include "Module.h"


struct Collider;

class ModuleDebug : public Module
{
public:
	ModuleDebug(bool startEnabled);

	// Destructor
	~ModuleDebug();

	//Called at the beginning of the application execution
	bool Init();

	//Called when the module is activated
	//By now we will consider all modules to be permanently active
	bool Start();

	//Called at the beginning of each application loop
	Update_Status PreUpdate();

	//Called at the middle of each application loop
	Update_Status Update();

	//Called at the end of each application loop
	Update_Status PostUpdate();

	//Called at the end of the application
	bool CleanUp();

	// Switches isEnabled and calls Start() method
	void Enable();

	// Switches isEnabled and calls CleanUp() method
	void Disable();

	void BlockOnMap(int x, int y);
	void SnoBeeOnMap(int x, int y);
	void DiamondOnMap(int x, int y);
	void EggOnMap(int x, int y);
	void DestroyBlock(int x, int y);
	
	inline bool IsEnabled() const { return isEnabled; }

	int CanPut(int x, int y);
	void LevelUpDown();

	bool GMODE = 0;
	int level = 1;
	int canput = 0;
	bool ascending = 0;
	bool descending = 0;
	bool DEBUG_MODE = 0;
	bool memory = false;
	
	int levelChoose = 0;
	int whiteFontID = -1;
	int yellowFontID = -1;
	

private:
	bool isEnabled = true;
};

#endif //__MODULE_DEBUG_H__