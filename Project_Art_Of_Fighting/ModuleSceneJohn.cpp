#include "Globals.h"
#include "Application.h"
#include "ModuleSceneJohn.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCongratzScreen.h"
#include"ModuleCollision.h"
#include "SDL/include/SDL.h"


// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneJohn::ModuleSceneJohn()
{
	//background//
		rect_background.rect.w = 540;
		rect_background.rect.h = 224;
		rect_background.rect.x = 0;
		rect_background.rect.y = 0;

	//helicopter//
	idle.PushBack({ 627, 0, 397, 47 });
	idle.PushBack({ 627,61,397,47 });
	idle.speed = 0.2f;


	//soldiers//
	soldiers.PushBack({ 113,232,119,94 });
	soldiers.PushBack({ 231,232,119,94 });
	soldiers.PushBack({ 349,232,119,94 });
	soldiers.PushBack({ 467,232,119,94 });
	soldiers.PushBack({ 585,232,119,94 });
	soldiers.PushBack({ 703,232,119,94 });
	soldiers.PushBack({ 821,232,119,94 });
	soldiers.speed = 0.2f;

	//couple//
	couple.PushBack({ 10,236,45,99 });
	couple.PushBack({ 56,236,45,99 });
	couple.speed = 0.2f;

	//soldierduo//
	soldierduo.PushBack({ 578,354,88,97 });
	soldierduo.PushBack({ 578,460,88,97 });
	soldierduo.speed = 0.2f;

	
}

ModuleSceneJohn::~ModuleSceneJohn()
{}


bool ModuleSceneJohn::Start()
{
	LOG("Loading john scene");
	john_music = App->audio->Load_music("Assets/Audio/038xKoukuu Bokaan!.ogg");
	if ((graphics = App->textures->Load("Assets/backgrounds_karuta_guardian.png")) == NULL)
	{
		SDL_Log("Unable to load texture from path: /guardian.png");
		return false;
	}
	App->audio->Play_music(john_music);

	//Screen Limits
	//ScreenLimits[0] = App->collision->AddCollider({ { 0-10,0,10, SCREEN_HEIGHT },{ 0,0 } }, COLLIDER_WALL, App->scene_john);
	//ScreenLimits[1] = App->collision->AddCollider({ {rect_background.rect.w, 0 , 10, SCREEN_HEIGHT },{ 0,0 } }, COLLIDER_WALL, App->scene_john);
	
	App->player->Enable();
	return true;
}


update_status ModuleSceneJohn::Update()
{
	if ((App->render->Blit(graphics, 0, 0, &rect_background)) == false)
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
		return update_status::UPDATE_STOP;
	}
	App->render->Blit(graphics, 115, 0, &idle.GetCurrentFrame());

	App->render->Blit(graphics, 130, 100, &soldiers.GetCurrentFrame());

	App->render->Blit(graphics, 440, 100, &couple.GetCurrentFrame());

	App->render->Blit(graphics, 315, 100, &soldierduo.GetCurrentFrame());

	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_john, App->scene_congratz);
	}

	return UPDATE_CONTINUE;
}

bool ModuleSceneJohn::CleanUp()
{

	App->audio->Unload_music(john_music);
	App->textures->Unload(graphics);
	App->player->Disable();
	LOG("Unloading john stage");
	return true;
}