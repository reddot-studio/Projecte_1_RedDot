#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include <string>

ModuleUI::ModuleUI()
{


}

ModuleUI::~ModuleUI()
{}


bool ModuleUI::Start()
{
	LOG("Loading UI");
	tick1 = SDL_GetTicks();
	//Load All UI
	TimerTexture = App->textures->Load("Assets/UI_Sprites/Timer.png");
	win_points = App->textures->Load("Assets/UI_Sprites/indicator_fight.png");
	App->player1->Player_Health_BG = App->player2->Player_Health_BG = App->textures->Load("Assets/UI_Sprites/Health.png");
	App->player1->Player_Health = App->player2->Player_Health = App->textures->Load("Assets/UI_Sprites/Health_Value.png");
	App->player1->Player_Health_BG_Empty = App->player2->Player_Health_BG_Empty = App->textures->Load("Assets/UI_Sprites/HealthBar_Empty.png");

	//126 = player health texture lenght
	//Do same with App.player2
	App->player1->Player_Health_Value = 126;
	App->player2->Player_Health_Value = 126;
	
	App->fonts->Load("Assets/fonts/timer.png", "1234567890", 1, 12, 20, 10);
	timer = 60;
	time = "";

	//Animation winPOint
	winpoint.PushBack({ 0,161,15,15 });
	winpoint.PushBack({ 15,161,15,15 });
	winpoint.PushBack({ 30,161,15,15 });
	winpoint.speed = 4.0f;
	current_animation = &winpoint;

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
	tick2 = SDL_GetTicks();
	timer_float = (tick2 - tick1) / 100;
	timer = timer_float;
	//timer to string time and it will work ********************************************************************
	RendPosition = { { 0, 0, 32, 24 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(TimerTexture, SCREEN_WIDTH / 2 - RendPosition.rect.w / 2, 8, &RendPosition, 0);
	App->fonts->BlitText(SCREEN_WIDTH / 2 - 13, 10, 0, time,2);




	//Player 1 Health
	//Render order is really important
	RendPosition = { { 0, 0, 126, 6 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player1->Player_Health_BG_Empty, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 17, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);
	RendPosition = { { 0, 0, App->player1->Player_Health_Value, 6 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player1->Player_Health, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 17, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);
	RendPosition = { { 0, 0, 128, 8 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player1->Player_Health_BG, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 16, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);



	//Player 2 Health BackGround
	RendPosition = { { 0, 0, 126, 6 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player2->Player_Health_BG_Empty, (SCREEN_WIDTH / 2) + 17, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);
	RendPosition = { { 0, 0, App->player2->Player_Health_Value, 6 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player2->Player_Health, (SCREEN_WIDTH / 2 ) + 17, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);
	RendPosition = { { 0, 0, 128, 8 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player2->Player_Health_BG, (SCREEN_WIDTH / 2) + 16, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);


	//WinPoints
	if (App->player2->Player_Health_Value == 0) {
		counter1++;
	}
	if(counter1 > 0 ) { 
		App->render->Blit(win_points, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 17, 28 - (RendPosition.rect.h / 2), &current_animation->GetCurrentFrame());
		if (counter1 == 2) {
			App->render->Blit(win_points, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 2, 28 - (RendPosition.rect.h / 2), &current_animation->GetCurrentFrame());
		}
	}
	if (App->player1->Player_Health_Value == 0) {
		counter2++;
	}
	if (counter2 > 0) {
		App->render->Blit(win_points, (SCREEN_WIDTH / 2) + 16, 28 - (RendPosition.rect.h / 2), &current_animation->GetCurrentFrame());
		if (counter2 == 2) {
			App->render->Blit(win_points, (SCREEN_WIDTH / 2) + 31, 28 - (RendPosition.rect.h / 2), &current_animation->GetCurrentFrame());
		}
	}



	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{


	//Unload everything

		App->textures->Unload(TimerTexture);
		App->textures->Unload(App->player1->Player_Health_BG);
		App->textures->Unload(App->player1->Player_Health);
		App->textures->Unload(App->player1->Player_Health_BG_Empty);



		App->textures->Unload(App->player2->Player_Health_BG);
		App->textures->Unload(App->player2->Player_Health);
		App->textures->Unload(App->player2->Player_Health_BG_Empty);

	

	LOG("Unloading todo scene");
	return true;
}