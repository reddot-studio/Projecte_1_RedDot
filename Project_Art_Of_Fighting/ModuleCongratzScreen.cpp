#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleCongratzScreen.h"
#include "SDL/include/SDL.h"

ModuleCongratzScreen::ModuleCongratzScreen()
{
	rect_background.rect.x = 682;
	rect_background.rect.y = 338;
	rect_background.rect.w = 304;
	rect_background.rect.h = 224;
}

ModuleCongratzScreen::~ModuleCongratzScreen(){}

bool ModuleCongratzScreen::Start()
{

	LOG("Loading congratz scene");
	if ((graphics = App->textures->Load("Assets/backgrounds_karuta_guardian.png")) == NULL)
	{
		SDL_Log("Could not load image from path! SDL_Error: %s", SDL_GetError());
		return false;
	}	
	ending_music = App->audio->Load_music("Assets/Audio/042xSono hito-wa watashitachi-no kodomo kana.ogg");
	App->audio->Play_music(ending_music);
	return true;
}

update_status ModuleCongratzScreen::Update()
{
	if ((App->render->Blit(graphics, 40, 0, &rect_background)) == false)
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
		return update_status::UPDATE_STOP;
	}
	

	return update_status::UPDATE_CONTINUE;
}

bool ModuleCongratzScreen::CleanUp()
{
	App->textures->Unload(graphics);
	LOG("Unloading congratz scene");
	return true;
}