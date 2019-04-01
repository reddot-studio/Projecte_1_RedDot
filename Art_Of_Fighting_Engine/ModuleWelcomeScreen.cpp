#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneTodo.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "SDL/include/SDL.h"

ModuleWelcomeScreen::ModuleWelcomeScreen()
{
	rect_background.rect.x = 0;
	rect_background.rect.y = 569;
	rect_background.rect.w = 550;
	rect_background.rect.h = 224;

	coin.PushBack({ 0,797,95,16});
	coin.PushBack({ 103,797,95,16});
	coin.speed = 0.1f;
	
}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{}

bool ModuleWelcomeScreen::Start()
{

	LOG("Loading intro scene");
	if ((graphics = App->textures->Load("Assets/backgrounds_karuta_guardian.png")) == NULL)
	{
		SDL_Log("Could not load image from path! SDL_Error: %s", SDL_GetError());
		return false;
	}
	
	if(Mix_PlayMusic(App->audio->start_music,1)==-1)
		SDL_Log("%s",SDL_GetError());
	App->player->Disable();

	return true;
}


update_status ModuleWelcomeScreen::Update()
{

	if ((App->render->Blit(graphics, -95, 0, &rect_background)) == false)
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
		return update_status::UPDATE_STOP;
	}
	App->render->Blit(graphics, 136, 150, &coin.GetCurrentFrame());

	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_PRESSED)
	{
		
		App->fade->FadeToBlack(App->scene_welcome, App->scene_todo, App->audio->todo_music);
	}



	
	return update_status::UPDATE_CONTINUE;
}


bool ModuleWelcomeScreen::CleanUp()
{
	App->player->Enable();
	App->textures->Unload(graphics);

	LOG("Unloading todo scene");
	return true;
}