#include "ModuleCharacter_Selection.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneTodo.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleRender.h"
#include "RectSprites.h"
#include "ModuleFonts.h"
#include <stdio.h>
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "John.h"

ModuleScreenSelection::ModuleScreenSelection() {
	back.w = SCREEN_WIDTH;
	back.h = SCREEN_HEIGHT;
	back.x = 0;
	back.y = 0;

	characters.rect.x = 0;
	characters.rect.y = 142;
	characters.rect.w = 112;
	characters.rect.h = 56;

	selector1.rect.x = 0;
	selector1.rect.y = 198;
	selector1.rect.h = 31;
	selector1.rect.w = 28;

	selector2.rect.x = 28;
	selector2.rect.y = 198;
	selector2.rect.h = 31;
	selector2.rect.w = 28;
}
ModuleScreenSelection::~ModuleScreenSelection() {

}

bool ModuleScreenSelection::Init() {
	SDL_SetRenderDrawColor(background,0, 0, 0, 255);
	SDL_RenderFillRect(background, &back);
	SDL_RenderPresent;
	graphics = App->textures->Load("Assets/character_selection.png");
	return true;
}
bool ModuleScreenSelection::Start() {
	App->input->Paused = false;
	tick1 = SDL_GetTicks();
	no_zero = true;
	return true;
}
update_status ModuleScreenSelection::Update() {

	if (no_zero == true) {
		time_int = (10000 + (tick1 - tick2)) / 1000;
	}

	sprintf_s(time_char, 10, "%.0i", time_int);

	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->character_selection, App->scene_todo);
	}
	
	draw();
	move();
	timer();
	

	return UPDATE_CONTINUE;
}
bool ModuleScreenSelection::CleanUp() {

	return true;
}

void ModuleScreenSelection::move() {
	if ((App->input->keyboard_state[SDL_SCANCODE_D] == KEY_DOWN)) {
		if (s1_pos_x < 4) {
			X_SELECTOR_1 += 28;
			s1_pos_x++;
		}
	}
	if ((App->input->keyboard_state[SDL_SCANCODE_A] == KEY_DOWN)) {
		if (s1_pos_x > 1) {
			X_SELECTOR_1 -= 28;
			s1_pos_x--;
		}
	}
	if ((App->input->keyboard_state[SDL_SCANCODE_S] == KEY_DOWN)) {
		if (s1_pos_y < 2) {
			Y_SELECTOR_1 += 28;
			s1_pos_y++;
		}
	}
	if ((App->input->keyboard_state[SDL_SCANCODE_W] == KEY_DOWN)) {
		if (s1_pos_y > 1) {
			Y_SELECTOR_1 -= 28;
			s1_pos_y--;
		}
	}


	if ((App->input->keyboard_state[SDL_SCANCODE_L] == KEY_DOWN)) {
		if (s2_pos_x < 4) {
			X_SELECTOR_2 += 28;
			s2_pos_x++;
		}
	}
	if ((App->input->keyboard_state[SDL_SCANCODE_J] == KEY_DOWN)) {
		if (s2_pos_x > 1) {
			X_SELECTOR_2 -= 28;
			s2_pos_x--;
		}
	}
	if ((App->input->keyboard_state[SDL_SCANCODE_K] == KEY_DOWN)) {
		if (s2_pos_y < 2) {
			Y_SELECTOR_2 += 28;
			s2_pos_y++;
		}
	}
	if ((App->input->keyboard_state[SDL_SCANCODE_I] == KEY_DOWN)) {
		if (s2_pos_y > 1) {
			Y_SELECTOR_2 -= 28;
			s2_pos_y--;
		}
	}
}
void ModuleScreenSelection::timer() {
	if (time_int <= 0) {
		tick1 = 0;
		tick2 = 0;
		no_zero = false;
		App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 - 32, 1, "0");
		App->fade->FadeToBlack(App->character_selection, App->scene_welcome);
	}
	tick2 = SDL_GetTicks();
}
void ModuleScreenSelection::draw() {
	App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 56, (SCREEN_HEIGHT / 2) + 20, &characters); //Print Characters
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 83, 20, 0, "vs mode select player"); //Imprimir font de adalt. bug. no carga la font.
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 16, SCREEN_HEIGHT / 2 - 40, 1, "time");
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 8, SCREEN_HEIGHT / 2 - 32, 1, "0");
	App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 - 32, 1, time_char);
	App->render->Blit(graphics, X_SELECTOR_1, Y_SELECTOR_1, &selector1);
	App->render->Blit(graphics, X_SELECTOR_2, Y_SELECTOR_2, &selector2);
}