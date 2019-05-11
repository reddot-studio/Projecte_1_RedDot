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
	App->fonts->Load("Assets/fonts/small_white_font.png", " abcdefghiklmnoprstuwy!.0123456789", 2, 8, 8, 34);
	return true;
}

update_status ModuleDebug::Update()
{

	App->fonts->BlitText(5, 2, 0, "pad 0 not detected press 1.2.3 for rumble");
	App->fonts->BlitText(5, 11, 0, "pad 0 plugged press 1.2.3 for rumble");
	App->fonts->BlitText(5, 20, 0, "buttons");
	App->fonts->BlitText(5, 29, 0,"dpad");
	App->fonts->BlitText(5, 38, 0, "left trigger"); //ficar el right i que es tradueixi de float a string.
	App->fonts->BlitText(5, 50, 0, "right thumb"); //ficar el right i que es tradueixi de float a string.
	App->fonts->BlitText(5, 59, 0, "hor asis"); //ficar el right i que es tradueixi de float a string.

	if (App->input->GetHorizontalAxis() > App->input->deathZone)
	sprintf_s(time, 10, "%.2f", App->input->GetHorizontalAxis());
	else if (App->input->GetHorizontalAxis() < -App->input->deathZone) {
		sprintf_s(time, 10, "%.2f", App->input->GetHorizontalAxis());
	}
	if (App->input->GetHorizontalAxis() > App->input->deathZone || App->input->GetHorizontalAxis() < -App->input->deathZone) {
		App->fonts->BlitText(85, 50, 0, time);
	} //ficar el right i que es tradueixi de float a string.
	else
	{
		App->fonts->BlitText(85, 50, 0, "0.0");
	}


//	LOG("- ModuleDebug Update");
	return update_status::UPDATE_CONTINUE;
}

bool ModuleDebug::CleanUp()
{
	/*App->fonts->UnLoad(0);
	App->textures->Unload(graphic);
	LOG("- ModuleDebug CleanUp");*/
	return true;
}

void ModuleDebug::ShowDebug(iPoint * player)
{
	/*App->render->Blit(graphic,player->x,player->y,&point);*/
}
