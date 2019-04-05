#include "Application.h"
#include "ModuleDebug.h"
#include "ModulePlayer.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
bool ModuleDebug::Init()
{
	square_pos.x = 0;
	square_pos.y = 0;

	point.rect = { 0,0,10,10 };

	graphic = App->textures->Load("Assets/red_square.png");
	LOG("\n\nModuleDebug Init");


	return true;
}

update_status ModuleDebug::Update()
{

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
	App->render->Blit(graphic,player->x,player->y,&point);
}
