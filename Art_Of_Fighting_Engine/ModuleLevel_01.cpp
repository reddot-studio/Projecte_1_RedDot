#include "ModuleLevel_01.h"

bool ModuleLevel_01::Init()
{
	posX = 0;
	background = new SDL_Rect{ posX,0,1536,768 };
	return true;
}

update_status ModuleLevel_01::PreUpdate()
{

	//Zoom test
	//background->h += 1;
	//background->y -= 1;
	//background->x-= 1;

	if (App->input->right && posX < 800) {
		posX--;
		/*background->x += SCROLL_SPEED;
		background->w -= SCROLL_SPEED;*/
	}
	if (App->input->left && posX < 0) {
		posX++;
		//background->x -= SCROLL_SPEED;
		//background->w += SCROLL_SPEED;
	}
	return update_status::UPDATE_CONTINUE;
}

update_status ModuleLevel_01::Update()
{
	App->render->Blit(App->textures->textures[0], posX, 0, App->level01->background);
	return update_status::UPDATE_CONTINUE;
}

bool ModuleLevel_01::CleanUp()
{
	LOG("\nModuleLevel_01 CleanUp");
	return update_status::UPDATE_CONTINUE;
}
