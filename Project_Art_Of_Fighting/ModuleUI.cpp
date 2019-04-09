#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneTodo.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"


ModuleUI::ModuleUI()
{
	
}

ModuleUI::~ModuleUI()
{}


bool ModuleUI::Start()
{
	LOG("Loading UI");

	//Load All UI


	return true;
}

update_status ModuleUI::Update()
{


	//Draw UI
	//if ((App->render->Blit(graphics, 0, 0, &rect_background)) == false)
	//{
	//	SDL_Log("Unable to [BLIT] texture: texture_background");
	//	return update_status::UPDATE_STOP;
	//}




	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{


	//Unload everything

	LOG("Unloading todo scene");
	return true;
}