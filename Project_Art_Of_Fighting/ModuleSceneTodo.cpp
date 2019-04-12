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
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include"ModuleUI.h"


ModuleSceneTodo::ModuleSceneTodo()
{
	rect_background.rect.w = 556;
	rect_background.rect.h = 224;
	rect_background.rect.x = 0;
	rect_background.rect.y = 338;	
}

ModuleSceneTodo::~ModuleSceneTodo()
{}


bool ModuleSceneTodo::Start()
{
	LOG("Loading todo scene");
	todo_music = App->audio->Load_music("Assets/Audio/033xART OF FIGHT.ogg");
	App->audio->Play_music(todo_music);
	graphics = App->textures->Load("Assets/backgrounds_karuta_guardian.png");
	//App->collision->AddCollider({ {300,0,30,224},{0,0} }, COLLIDER_WALL);
	BackPanel = App->collision->AddCollider({ { 0-10,0,10, SCREEN_HEIGHT },{ 0,0 } ,{ 0, 0 } }, COLLIDER_WALL, App->scene_todo);
	FrontPanel = App->collision->AddCollider({ {rect_background.rect.w, 0 , 10, SCREEN_HEIGHT },{ 0,0 } ,{ 0, 0 } }, COLLIDER_WALL, App->scene_todo);
	App->player1->Enable();
	App->player2->Enable();
	App->sceneUI->Enable();


	return true;
}

update_status ModuleSceneTodo::Update()
{
	if ((App->render->Blit(graphics, 0, 0, &rect_background)) == false )
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
		return update_status::UPDATE_STOP;
	}
	
		if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN)
		{
			App->fade->FadeToBlack( App->scene_todo, App->scene_john);
		}
	return UPDATE_CONTINUE;
}

bool ModuleSceneTodo::CleanUp()
{
	if (FrontPanel && BackPanel)
	{
		FrontPanel->to_delete = true;
		BackPanel->to_delete = true;
	}

	App->audio->Unload_music(todo_music);
	App->textures->Unload(graphics);
	App->player1->Disable();
	App->player2->Disable();
	App->sceneUI->Disable();

	LOG("Unloading todo scene");
	return true;
}