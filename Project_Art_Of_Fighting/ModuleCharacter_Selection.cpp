#include "ModuleCharacter_Selection.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneTodo.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"


ModuleScreenSelection::ModuleScreenSelection() {
	back.w = SCREEN_WIDTH;
	back.h = SCREEN_HEIGHT;
	back.x = 0;
	back.y = 0;
}
ModuleScreenSelection::~ModuleScreenSelection() {

}

bool ModuleScreenSelection::Init() {
	SDL_SetRenderDrawColor(background,0, 0, 0, 255);
	SDL_RenderFillRect(background, &back);
	SDL_RenderPresent;
	return true;
}
bool ModuleScreenSelection::Start() {

	return true;
}
update_status ModuleScreenSelection::Update() {
	App->input->Paused = false;
	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->character_selection, App->scene_todo);
	}

	return UPDATE_CONTINUE;
}
bool ModuleScreenSelection::CleanUp() {

	return true;
}