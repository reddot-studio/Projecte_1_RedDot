#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleCongratzScreen.h"
#include "ModuleSceneTodo.h"
#include "ModuleUI.h"
#include "SDL/include/SDL.h"
#include "ModuleFonts.h"

ModuleCongratzScreen::ModuleCongratzScreen()
{
	countback.PushBack({1858,932,80,96 });
	countback.PushBack({1968,932,80,96 });
	countback.PushBack({1859,1069,80,96 });
	countback.PushBack({1968,1069,80,96 });
	countback.PushBack({1858,1165,80,96 });
	countback.PushBack({1968,1165,80,96 });
	countback.PushBack({1858,1301,80,96 });
	countback.PushBack({1968,1301,80,96 });
	countback.PushBack({1858,1397,80,96 });
	countback.PushBack({1968,1397,80,96 });
	countback.speed = 0.015f;

	zero.PushBack({ 1968,1397,80,96 });

	rect_win.rect.x = 1547;
	rect_win.rect.y = 931;
	rect_win.rect.w = 129;
	rect_win.rect.h = 124;

	rect_lose.rect.x = 1692;
	rect_lose.rect.y = 931;
	rect_lose.rect.w = 129;
	rect_lose.rect.h = 124;

	chat_bubble.rect.x = 1547;
	chat_bubble.rect.y = 1085;
	chat_bubble.rect.w = 272;
	chat_bubble.rect.h = 48;
}

ModuleCongratzScreen::~ModuleCongratzScreen(){}

bool ModuleCongratzScreen::Start()
{
	App->sceneUI->Disable();
	LOG("Loading congratz scene");
	if ((graphics = App->textures->Load("Assets/WelcomeScreen.png")) == NULL)
	{
		SDL_Log("Could not load image from path! SDL_Error: %s", SDL_GetError());
		return false;
	}	
	ending_music = App->audio->Load_music("Assets/Audio/042xSono hito-wa watashitachi-no kodomo kana.ogg");
	App->audio->Play_music(ending_music);

	if (App->player1->Player_Health_Value <= 0) 
	{
		beat_by_2++;
		result = false;
	}
	if (App->player2->Player_Health_Value <= 0)
	{
		beat_by_1++;
		result = true;
	}

	current_animation = &countback;
	current_animation->ResetCurrentFrame();

	//Load fonts
	App->fonts->Load("Assets/fonts/big_orange_font.png", " abcdefghiklmnoprstuvwyz,:0123456789'!", 1, 8, 13, 38);
	App->fonts->Load("Assets/fonts/small_orange_font.png", " abcdefghiklmnoprstuwy!.0123456789", 1, 8, 8, 34);


	return true;
}

update_status ModuleCongratzScreen::Update()
{
	App->fonts->BlitText(220, 47, 1, "waiting for");
	App->fonts->BlitText(215, 58, 1, "a challenger");

	if ((App->render->Blit(graphics, 50, 164, &chat_bubble)) == false)
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
			return update_status::UPDATE_STOP;
	}
	switch (result)
	{
	case true:

		if ((App->render->Blit(graphics, 57.5, 40, &rect_win)) == false)
		{
			SDL_Log("Unable to [BLIT] texture: texture_background");
			return update_status::UPDATE_STOP;
		}
		App->fonts->BlitText(58.5, 173, 0, "anytime, anywhere, cross my path");
		App->fonts->BlitText(58.5, 188, 0, "again and you're mine!");

		break;
	case false:
		if ((App->render->Blit(graphics, 57.5, 40, &rect_lose)) == false)
		{
			SDL_Log("Unable to [BLIT] texture: texture_background");
			return update_status::UPDATE_STOP;
		}
		App->fonts->BlitText(58.5, 173, 0, "i'll take you on anytime,");
		App->fonts->BlitText(58.5, 188, 0, "taco breath!");


		break;
	}
	
	App->render->Blit(graphics, 220, 68.5, &current_animation->GetCurrentFrame());
 
	//When using this, coliders do not render 
	if (App->input->keyboard_state[SDL_SCANCODE_Q] == KEY_DOWN)
	{

		App->fade->FadeToBlack(App->scene_congratz, App->scene_todo);
	}

	if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame()-1)
	{	
		current_animation = &zero;
		App->fade->FadeToBlack(App->scene_congratz, App->scene_welcome);
	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleCongratzScreen::CleanUp()
{
	App->textures->Unload(graphics);
	App->audio->Unload_music(ending_music);
	App->fonts->UnLoad(0);
	App->fonts->UnLoad(1);
	LOG("Unloading congratz scene");
	return true;
}