#include "Application.h"
#include "ModuleDebug.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleFonts.h"

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
	App->fonts->Load("Assets/fonts/small_white_font.png", " abcdefghiklmnoprstuwy!.0123456789", 1, 8, 8, 34);

	return true;
}

update_status ModuleDebug::Update()
{
	App->fonts->BlitText(5, 2, 0, "pad 0 not detected press 1.2.3 for rumble");
	App->fonts->BlitText(5, 2, 0, "pad 0 plugged press 1.2.3 for rumble");
	App->fonts->BlitText(5, 11, 0, "buttons");
	App->fonts->BlitText(5, 20, 0,"dpad");
	App->fonts->BlitText(5, 29, 0, "left trigger"); //ficar el right i que es tradueixi de float a string.
	App->fonts->BlitText(5, 38, 0, "right thumb"); //ficar el right i que es tradueixi de float a string.


//	LOG("- ModuleDebug Update");
	return update_status::UPDATE_CONTINUE;
}

bool ModuleDebug::CleanUp()
{
	App->fonts->UnLoad(0);
	App->textures->Unload(graphic);
	LOG("- ModuleDebug CleanUp");
	return true;
}

void ModuleDebug::ShowDebug(iPoint * player)
{
	App->render->Blit(graphic,player->x,player->y,&point);
}
