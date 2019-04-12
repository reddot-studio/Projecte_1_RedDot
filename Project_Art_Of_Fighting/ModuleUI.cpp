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
	TimerTexture = App->textures->Load("Assets/UI_Sprites/Timer.png");
	Player_1_Health = App->textures->Load("Assets/UI_Sprites/Health.png");
	Player_2_Health = App->textures->Load("Assets/UI_Sprites/Health.png");
	RendPosition = { { 0, 0, 32, 24 },{ 0, 0 },{ 0, 0 } };

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

	//Needs To sTop on fail bliT
	//Timer renderer
	RendPosition = { { 0, 0, 32, 24 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(TimerTexture, SCREEN_WIDTH / 2 - RendPosition.rect.w / 2, 8, &RendPosition, 0);
	//Player 1 Health
	RendPosition = { {0, 0, 128, 8}, {0, 0} ,{ 0, 0 } };
	App->render->Blit(Player_1_Health, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 16, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);
	//Player 2 Health
	RendPosition = { { 0, 0, 128, 8 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(Player_2_Health, (SCREEN_WIDTH / 2) + 16, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);




	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{


	//Unload everything
	App->textures->Unload(TimerTexture);
	App->textures->Unload(Player_1_Health);
	App->textures->Unload(Player_2_Health);

	LOG("Unloading todo scene");
	return true;
}