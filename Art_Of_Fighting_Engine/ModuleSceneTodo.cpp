#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneTodo.h"
#include "ModuleInput.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneJohn.h"
#include "ModuleWelcomeScreen.h"
#include "SDL/include/SDL.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneTodo::ModuleSceneTodo()
{
	rect_background.rect.w = 556;
	rect_background.rect.h = 224;
	rect_background.rect.x = 0;
	rect_background.rect.y = 338;
}

ModuleSceneTodo::~ModuleSceneTodo()
{}

// Load assets
bool ModuleSceneTodo::Start()
{
	LOG("Loading todo scene");
	
	graphics = App->textures->Load("Assets/backgrounds_karuta_guardian.png");
	App->player->Enable();

	return true;
}

// UnLoad assets
bool ModuleSceneTodo::CleanUp()
{
	App->player->Disable();
	App->textures->Unload(graphics);
	LOG("Unloading todo scene");
	return true;
}

// Update: draw background
update_status ModuleSceneTodo::Update()
{

	// Draw everything --------------------------------------
	if ((App->render->Blit(graphics, 0, 0, &rect_background)) == false)
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
		return update_status::UPDATE_STOP;
	}
	
	
		if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_PRESSED)
		{
		
			App->fade->FadeToBlack(App->scene_todo, App->scene_john, App->audio->john_music);
		}
	// TODO 2: make so pressing SPACE the HONDA stage is loaded

	return UPDATE_CONTINUE;
}