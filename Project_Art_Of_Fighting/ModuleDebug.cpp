#include "Application.h"
#include "ModuleDebug.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"
#include <stdio.h>

bool ModuleDebug::Init()
{
	square_pos.x = 0;
	square_pos.y = 0;

	point.rect = { 0,0,10,10 };

	graphic = App->textures->Load("Assets/red_square.png");
	LOG("\n\nModuleDebug Init");

	return true;
}
bool ModuleDebug::Start() {
	return true;
}

update_status ModuleDebug::Update()
{
	if (App->input->keyboard_state[SDL_SCANCODE_F2] == KEY_DOWN){     //F2== amagar o enseñar debug
		debug = !debug;
	}
	if (debug == false)
		return update_status::UPDATE_CONTINUE;

	App->fonts->BlitText(5, 2, 2, "pad 0 not detected press 1.2.3 for rumble");
	App->fonts->BlitText(5, 11, 2, "pad 0 plugged press 1.2.3 for rumble");
	App->fonts->BlitText(5, 20, 2, "buttons");
	App->fonts->BlitText(5, 29, 2,"dpad");
	App->fonts->BlitText(5, 38, 2, "left trigger"); //ficar el right i que es tradueixi de float a string.
	App->fonts->BlitText(5, 50, 2, "right thumb"); //ficar el right i que es tradueixi de float a string.
	App->fonts->BlitText(5, 59, 2, "hor asis"); //ficar el right i que es tradueixi de float a string.

	if (App->input->GetHorizontalAxis() > App->input->deathZone)
	sprintf_s(time, 10, "%.2f", App->input->GetHorizontalAxis());
	else if (App->input->GetHorizontalAxis() < -App->input->deathZone) {
		sprintf_s(time, 10, "%.2f", App->input->GetHorizontalAxis());
	}
	if (App->input->GetHorizontalAxis() > App->input->deathZone || App->input->GetHorizontalAxis() < -App->input->deathZone) {
		App->fonts->BlitText(85, 50, 1, time);
	} //ficar el right i que es tradueixi de float a string.
	else
	{
		App->fonts->BlitText(85, 50, 2, "0.0");
	}


//	LOG("- ModuleDebug Update");
	return update_status::UPDATE_CONTINUE;
}

bool ModuleDebug::CleanUp()
{
	App->textures->Unload(graphic);
	LOG("- ModuleDebug CleanUp");
	return true;
}

void ModuleDebug::ShowDebug(iPoint * player)
{
	/*App->render->Blit(graphic,player->x,player->y,&point);*/
}
