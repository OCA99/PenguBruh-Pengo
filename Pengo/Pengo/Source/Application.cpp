#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "SceneIntro.h"
#include "SceneIntermission.h"
#include "SceneMenu.h"
#include "ScenePoints.h"
#include "SceneLevel.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "SceneLevel3.h"
#include "SceneLevel4.h"
#include "SceneLevel5.h"
#include "SceneLevel6.h"
#include "SceneLevel7.h"
#include "SceneLevel8.h"
#include "SceneLevel9.h"
#include "SceneLevel10.h"
#include "SceneLevel11.h"
#include "SceneLevel12.h"
#include "SceneLevel13.h"
#include "SceneLevel14.h"
#include "SceneLevel15.h"
#include "SceneLevel16.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
//#include "ModuleCollisions.h"
#include "ModuleBlocks.h"
#include "ModuleWalls.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"
#include "ModuleDebug.h"
#include "ModuleUI.h"
#include "Score.h"
#include "ModuleStars.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	textures =		new ModuleTextures(true);
	modules[3] =	audio =			new ModuleAudio(true);

	modules[4] =	sceneIntro =	new SceneIntro(true);
	modules[5] = intermission = new SceneIntermission(false);
	modules[6] =	blocks =		new ModuleBlocks(false);
	modules[7] =	walls =			new ModuleWalls(false);
	modules[8] = enemies = new ModuleEnemies(false);	//Enemies start disabled	
	modules[9] =	player = new ModulePlayer(false);	//Player starts disabled
	//modules[9] =	collisions =	new ModuleCollisions(true);
	modules[10] =	sceneMenu = new SceneMenu(false);
	modules[11] = scenePoints = new ScenePoints(false);
	modules[12] = ui = new ModuleUI(false);
	modules[13] =	fonts =			new ModuleFonts(true);
	modules[14] =	fade =			new ModuleFadeToBlack(true);
	modules[15] =	sceneLevel_1 =	new SceneLevel1(false);	
	//modules[13] = sceneLevel_1 = new SceneLevel1(false);	
	modules[16] = sceneLevel_2 = new SceneLevel2(false);	
	modules[17] = sceneLevel_3 = new SceneLevel3(false);	
	modules[18] = sceneLevel_4 = new SceneLevel4(false);	
	modules[19] = sceneLevel_5 = new SceneLevel5(false);	
	modules[20] = sceneLevel_6 = new SceneLevel6(false);	
	modules[21] = sceneLevel_7 = new SceneLevel7(false);	
	modules[22] = sceneLevel_8 = new SceneLevel8(false);	
	modules[23] = sceneLevel_9 = new SceneLevel9(false);	
	modules[24] = sceneLevel_10 = new SceneLevel10(false);	
	modules[25] = sceneLevel_11 = new SceneLevel11(false);	
	modules[26] = sceneLevel_12 = new SceneLevel12(false);
	modules[27] = sceneLevel_13 = new SceneLevel13(false);
	modules[28] = sceneLevel_14 = new SceneLevel14(false);
	modules[29] = sceneLevel_15 = new SceneLevel15(false);
	modules[30] = sceneLevel_16 = new SceneLevel16(false);//Gameplay scene starts disabled
	modules[31] =	debug =		  new ModuleDebug(true);
	modules[32] = particles = new ModuleParticles(true);
	modules[33] = stars = new ModuleStars(true);
	modules[34] = score = new Score(true);
	modules[35] = render = new ModuleRender(true);

}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

#include <iostream>

Update_Status Application::Update()
{
	frameStart = SDL_GetTicks();

	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	frameTime = SDL_GetTicks() - frameStart;

	if (frameDelay > frameTime) {
		SDL_Delay(frameDelay - frameTime);
	}

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
