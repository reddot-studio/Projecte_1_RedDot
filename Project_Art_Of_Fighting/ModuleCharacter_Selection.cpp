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
	characters.rect.y = 138;
	characters.rect.w = 112;
	characters.rect.h = 56;

	selector1.rect.x = 0;
	selector1.rect.y = 194;
	selector1.rect.h = 31;
	selector1.rect.w = 28;

	selector2.rect.x = 28;
	selector2.rect.y = 194;
	selector2.rect.h = 31;
	selector2.rect.w = 28;

	imageSelection1.rect.x = 0;
	imageSelection1.rect.y = 0;
	imageSelection1.rect.w = 128;
	imageSelection1.rect.h = 123;

	imageSelection2.rect.x = 128;
	imageSelection2.rect.y = 0;
	imageSelection2.rect.w = 128;
	imageSelection2.rect.h = 128;

	name1.rect.x = 0;
	name1.rect.y = 123;
	name1.rect.w = 58;
	name1.rect.h = 15;

	name2.rect.x = 58;
	name2.rect.y = 123;
	name2.rect.w = 44;
	name2.rect.h = 15;

	not_available.rect.x = 0;
	not_available.rect.y = 225;
	not_available.rect.w = 112;
	not_available.rect.h = 56;
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


	choose();
	draw();
	move();
	timer();
	

	return UPDATE_CONTINUE;
}
bool ModuleScreenSelection::CleanUp() {
	//App->textures->Unload(graphics);
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
		App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 - 32, 2, "0");
		App->fade->FadeToBlack(App->character_selection, App->scene_welcome);
	}
	tick2 = SDL_GetTicks();
}
void ModuleScreenSelection::draw() {
	App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 56, (SCREEN_HEIGHT / 2) + 50, &characters); //Print Characters
	App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 56, (SCREEN_HEIGHT / 2) + 50, &not_available); //Print Characters
	App->render->Blit(graphics, X_SELECTOR_1, Y_SELECTOR_1, &selector1);
	App->render->Blit(graphics, X_SELECTOR_2, Y_SELECTOR_2, &selector2);
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 83, 15, 1, "vs mode select player"); //Imprimir font de adalt. bug. no carga la font.
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 16, SCREEN_HEIGHT / 2 - 40, 2, "time");
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 8, SCREEN_HEIGHT / 2 - 32, 2, "0");
	App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 - 32, 2, time_char);
}
void ModuleScreenSelection::choose() {
	if (((s1_pos_x == 2 && s2_pos_x == 4) || (s1_pos_x == 4 && s2_pos_x == 2)) && App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN) {
		if ((s1_pos_y == 1 && s2_pos_y == 2) || (s1_pos_y == 2 && s2_pos_y == 1)) {
			App->fade->FadeToBlack(App->character_selection, App->scene_john);
		}
	}
	//RYO
	if (s1_pos_x == 2 && s1_pos_y == 1) {
		App->render->Blit(graphics, 35, 15, &imageSelection1, 1.0f, 2);
		App->render->Blit(graphics, 77, 140, &name2, 1.0f, 1);
		if (s2_pos_x == 2 && s2_pos_y == 1) {
			App->render->Blit(graphics, SCREEN_WIDTH - 163, 15, &imageSelection1, 1.0f, 1);
			App->render->Blit(graphics, 44 + SCREEN_WIDTH - 165, 140, &name2, 1.0f, 1);
		}
	}
	else if (s2_pos_x == 2 && s2_pos_y == 1) {
		App->render->Blit(graphics, SCREEN_WIDTH - 165, 15, &imageSelection1, 1.0f, 1);
		App->render->Blit(graphics, 44 + SCREEN_WIDTH - 165, 140, &name2, 1.0f, 1);
	}


	//JOHN
	if (s1_pos_x == 4 && s1_pos_y == 2) {
		App->render->Blit(graphics, 35, 10, &imageSelection2, 1.0f, 1);
		App->render->Blit(graphics, 70, 140, &name1, 1.0f, 1);
		if (s2_pos_x == 4 && s2_pos_y == 2) {
			App->render->Blit(graphics, SCREEN_WIDTH - 165, 10, &imageSelection2, 1.0f, 2);
			App->render->Blit(graphics, 35 + SCREEN_WIDTH - 165, 140, &name1, 1.0f, 1);
		}
	}
	else if (s2_pos_x == 4 && s2_pos_y == 2) {
		App->render->Blit(graphics, SCREEN_WIDTH - 165, 10, &imageSelection2, 1.0f, 2);
		App->render->Blit(graphics, 35+ SCREEN_WIDTH - 165, 140, &name1, 1.0f, 1);
	}
}