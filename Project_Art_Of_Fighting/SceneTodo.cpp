#include "SceneTodo.h"

SceneTodo::SceneTodo()
{
	rect_background.rect.w = 556;
	rect_background.rect.h = 224;
	rect_background.rect.x = 0;
	rect_background.rect.y = 338;


}

void SceneTodo::Start()
{
	todo_music = App->audio->Load_music("Assets/Audio/033xART OF FIGHT.ogg");
	fightfx = App->audio->Load_effects("Assets/Audio/FX/Fight.wav");
	graphics = App->textures->Load("Assets/backgrounds_karuta_guardian.png");

}
