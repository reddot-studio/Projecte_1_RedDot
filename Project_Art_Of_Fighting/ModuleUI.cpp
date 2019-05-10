#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleUI.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"
#include "ModuleFonts.h"
#include <stdio.h>



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
	App->player1->Player_Health_Value_p1 = 126;
	App->player2->Player_Health_Value_p2 = 126;
	
	App->fonts->Load("Assets/fonts/timer.png", "1234567890", 1, 12, 20, 10);
	timer = 60;
	time[0] = 0;

	//Animation winPOint
	winpoint.PushBack({ 0,161,15,15 });
	winpoint.PushBack({ 15,161,15,15 });
	winpoint.PushBack({ 30,161,15,15 });
	winpoint.PushBack({ 30,161,15,15 });
	winpoint.PushBack({ 15,161,15,15 });
	winpoint.PushBack({ 0,161,15,15 });
	winpoint.speed = 0.2f;
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
	if (tick2 - tick1 <= 4000)
	{
		RendPosition = { { 0, 0, 32, 24 },{ 0, 0 } ,{ 0, 0 } };
		App->render->Blit(TimerTexture, SCREEN_WIDTH / 2 - RendPosition.rect.w / 2, 8, &RendPosition, 0);
		App->fonts->BlitText(SCREEN_WIDTH / 2 - 13, 10, 1, "60", 2);
		tick3 = SDL_GetTicks();
	}
	else
	{

		RendPosition = { { 0, 0, 32, 24 },{ 0, 0 } ,{ 0, 0 } };
		App->render->Blit(TimerTexture, SCREEN_WIDTH / 2 - RendPosition.rect.w / 2, 8, &RendPosition, 0);
		if (timer > 0 && App->player1->win_check==false && App->player2->win_check == false)
		{
			timer_float = 60000 - (tick2 - tick3);
			timer = timer_float / 1000;
		}
		else
		{
			if(App->player1->win_check == false && App->player2->win_check == false)
			time_over = true;
		}

		//timer to string time and it will work ********************************************************************

		if (timer >= 10)
		{
			sprintf_s(time, 10, "%d", timer);
			App->fonts->BlitText(SCREEN_WIDTH / 2 - 13, 10, 1, time, 2);
		}
		else
		{
			timer = timer_float / 1000;
			sprintf_s(time, 10, "%d", timer);
			App->fonts->BlitText(SCREEN_WIDTH / 2 - 13, 10, 1, "0", 2);
			App->fonts->BlitText(SCREEN_WIDTH / 2 + 1, 10, 1, time, 2);
		}

	}
	tick2 = SDL_GetTicks();



	//Player 1 Health
	//Render order is really important
	RendPosition = { { 0, 0, 126, 6 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player2->Player_Health_BG_Empty, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 17, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);
	RendPosition = { { 0, 0, App->player2->Player_Health_Value_p2, 6 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player2->Player_Health, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 17, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);
	RendPosition = { { 0, 0, 128, 8 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player2->Player_Health_BG, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 16, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);



	//Player 2 Health BackGround
	RendPosition = { { 0, 0, 126, 6 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player1->Player_Health_BG_Empty, (SCREEN_WIDTH / 2) + 17, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);
	RendPosition = { { 0, 0, App->player1->Player_Health_Value_p1, 6 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player1->Player_Health, (SCREEN_WIDTH / 2 ) + 17, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);
	RendPosition = { { 0, 0, 128, 8 },{ 0, 0 } ,{ 0, 0 } };
	App->render->Blit(App->player1->Player_Health_BG, (SCREEN_WIDTH / 2) + 16, 20 - (RendPosition.rect.h / 2), &RendPosition, 0);


	//WinPoints
	if (App->player1->Player_Health_Value_p1 == 0 || (time_over==true&& App->player2->Player_Health_Value_p2 > App->player1->Player_Health_Value_p1)) {
		counter1++;
	}
	if(counter1 > 0 ) { 
		App->render->Blit(win_points, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 17, 28 - (RendPosition.rect.h / 2), &current_animation->GetCurrentFrame(), 0);
		if (counter1 == 2) {
			App->render->Blit(win_points, (SCREEN_WIDTH / 2 - RendPosition.rect.w) - 2, 28 - (RendPosition.rect.h / 2), &current_animation->GetCurrentFrame(), 0);
		}
	}
	if (App->player2->Player_Health_Value_p2 == 0 || (time_over == true && App->player1->Player_Health_Value_p1 > App->player2->Player_Health_Value_p2)) {
		counter2++;
	}
	if (counter2 > 0) {
		App->render->Blit(win_points, (SCREEN_WIDTH / 2) + 130, 28 - (RendPosition.rect.h / 2), &current_animation->GetCurrentFrame(), 0);
		if (counter2 == 2) 
		{
			App->render->Blit(win_points, (SCREEN_WIDTH / 2) + 110, 28 - (RendPosition.rect.h / 2), &current_animation->GetCurrentFrame(), 0);
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
		App->fonts->UnLoad(0);
	

	LOG("Unloading todo scene");
	return true;
}