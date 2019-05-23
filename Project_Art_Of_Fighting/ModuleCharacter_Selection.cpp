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

	selector1.PushBack({ 0,194,28,31 });
	selector1.PushBack({ 500,500,28,31 });
	selector1.speed = 0.8f;

	selector2.PushBack({ 28,194,28,31 });
	selector2.PushBack({ 500,500,28,31 });
	selector2.speed = 0.8f;

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

	ryo_other.rect.x = 112;
	ryo_other.rect.y = 128;
	ryo_other.rect.w = 128;
	ryo_other.rect.h = 123;

	john_other.rect.x = 256;
	john_other.rect.y = 0;
	john_other.rect.w = 128;
	john_other.rect.h = 128;


	int x = 0, y = 281, w = 50, h = 32;
	for (int i=0; i <= 15; i++) {
		vs.PushBack({ x,y,w,h });
		y += 32;
	}
	vs_final.PushBack({ 0,729,w,h });
	vs.loop = false;
	vs.speed = 0.5f;
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
	graphics = App->textures->Load("Assets/character_selection.png");
	App->input->Paused = false;
	tick1 = SDL_GetTicks();
	no_zero = true;
	return true;
}
update_status ModuleScreenSelection::Update() {
	if (selected == false) {
		if (no_zero == true) {
			time_int = (10000 + (tick1 - tick2)) / 1000;
		}
		sprintf_s(time_char, 10, "%.0i", time_int);


		choose();
		draw();
		move();
		timer();
	}
	else { //Quan clicas intro

		if (timer_init == false) {
			tick1 = SDL_GetTicks();
			timer_init = true;
		}
		tick2 = SDL_GetTicks();
		//VS//
		if (tick2 - tick1 > 1200) {
			App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 25, (SCREEN_HEIGHT / 2) - 16, &vs.GetCurrentFrame());
			if (vs.GetCurrentFramePos() == vs.GetLastFrame() - 1) {
				App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 25, (SCREEN_HEIGHT / 2) - 16, &vs_final.GetCurrentFrame());
			}
		}

		//character image animation
		
		characters_enter();



		if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN) {
			App->fade->FadeToBlack(App->character_selection, App->scene_john);
		}
	} 

	return UPDATE_CONTINUE;
}
bool ModuleScreenSelection::CleanUp() {
	App->textures->Unload(graphics);
	return true;
}
void ModuleScreenSelection::move() {
	if ((App->input->keyboard_state[SDL_SCANCODE_D] == KEY_DOWN)) {
		if (SELECTOR_1 == 1) {
			X_SELECTOR_1 = (SCREEN_WIDTH / 2) + 28;
			Y_SELECTOR_1 = (SCREEN_HEIGHT / 2) + 75;
			SELECTOR_1 = 2;
		}

	}
	if ((App->input->keyboard_state[SDL_SCANCODE_A] == KEY_DOWN)) {
		if (SELECTOR_1 == 2) {
			X_SELECTOR_1 = (SCREEN_WIDTH / 2) - 28;
			Y_SELECTOR_1 = (SCREEN_HEIGHT / 2) + 47;
			SELECTOR_1 = 1;
		}

	}


	if ((App->input->keyboard_state[SDL_SCANCODE_L] == KEY_DOWN)) {
		if (SELECTOR_2 == 1) {
			X_SELECTOR_2 = (SCREEN_WIDTH / 2) + 28;
			Y_SELECTOR_2 = (SCREEN_HEIGHT / 2) + 78;
			SELECTOR_2 = 2;
		}
	}
	if ((App->input->keyboard_state[SDL_SCANCODE_J] == KEY_DOWN)) {
		if (SELECTOR_2 == 2) {
			X_SELECTOR_2 = (SCREEN_WIDTH / 2) - 28;
			Y_SELECTOR_2 = (SCREEN_HEIGHT / 2) + 50;
			SELECTOR_2 = 1;
		}
	}
}
void ModuleScreenSelection::timer() {
	if (time_int <= 0) {
		tick1 = 0;
		tick2 = 0;
		no_zero = false;
		App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 - 32, 2, "0");
		App->fade->FadeToBlack(App->character_selection, App->scene_john);
		selected = true;
	}
	tick2 = SDL_GetTicks();
}
void ModuleScreenSelection::draw() {
	App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 56, (SCREEN_HEIGHT / 2) + 50, &characters); 
	App->render->Blit(graphics, (SCREEN_WIDTH / 2) - 56, (SCREEN_HEIGHT / 2) + 50, &not_available); 
	App->render->Blit(graphics, X_SELECTOR_1, Y_SELECTOR_1, &selector1.GetCurrentFrame());
	App->render->Blit(graphics, X_SELECTOR_2, Y_SELECTOR_2, &selector2.GetCurrentFrame());
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 83, 15, 1, "vs mode select player"); 
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 16, SCREEN_HEIGHT / 2 - 40, 2, "time");
	App->fonts->BlitText((SCREEN_WIDTH / 2) - 8, SCREEN_HEIGHT / 2 - 32, 2, "0");
	App->fonts->BlitText((SCREEN_WIDTH / 2), SCREEN_HEIGHT / 2 - 32, 2, time_char);
}
void ModuleScreenSelection::choose() {

	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN) {
		selected = true;
		//App->fade->FadeToBlack(App->character_selection, App->scene_todo, 0.7f);
	}

	//RYO
	if (SELECTOR_1 == 1) {
		App->render->Blit(graphics, 35, 15, &imageSelection1, 1.0f, 2);
		App->render->Blit(graphics, 77, 140, &name2, 1.0f, 1);
		if (SELECTOR_2 == 1) {
			App->render->Blit(graphics, SCREEN_WIDTH - 163, 15, &ryo_other, 1.0f, 1);
			App->render->Blit(graphics, 44 + SCREEN_WIDTH - 165, 140, &name2, 1.0f, 1);
		}
	}
	else if (SELECTOR_2==1) {
		App->render->Blit(graphics, SCREEN_WIDTH - 165, 15, &imageSelection1, 1.0f, 1);
		App->render->Blit(graphics, 44 + SCREEN_WIDTH - 165, 140, &name2, 1.0f, 1);
	}

	

	//JOHN
	if (SELECTOR_1==2) {
		App->render->Blit(graphics, 35, 10, &imageSelection2, 1.0f, 1);
		App->render->Blit(graphics, 70, 140, &name1, 1.0f, 1);
		if (SELECTOR_2==2) {
			App->render->Blit(graphics, SCREEN_WIDTH - 165, 10, &john_other, 1.0f, 1);
			App->render->Blit(graphics, 35 + SCREEN_WIDTH - 165, 140, &name1, 1.0f, 1);
		}
	}
	else if (SELECTOR_2==2) {
		App->render->Blit(graphics, SCREEN_WIDTH - 165, 10, &imageSelection2, 1.0f, 2);
		App->render->Blit(graphics, 35+ SCREEN_WIDTH - 165, 140, &name1, 1.0f, 1);
	}

}
void ModuleScreenSelection::characters_enter() {
	if (SELECTOR_1 == 1) {
		if (x_image1 == 20) {
			App->render->Blit(graphics, x_image1, 20, &imageSelection1, 1, 2);
		}
		else {
			x_image1 += 10;
			App->render->Blit(graphics, x_image1, 20, &imageSelection1, 1, 2);
		}
		if (tick2 - tick1 > 50) {
			if (x_name1 >= 58) {
				App->render->Blit(graphics, x_name1, 145, &name2);
			}
			else {
				x_name1 += 10;
				App->render->Blit(graphics, x_name1, 145, &name2);
			}
		}
	}

	if (SELECTOR_1 == 2) {
		if (x_image1 == 20) {
			App->render->Blit(graphics, x_image1, 15, &imageSelection2, 1, 1);
		}
		else {
			x_image1 += 10;
			App->render->Blit(graphics, x_image1, 15, &imageSelection2, 1, 1);
		}
		if (tick2 - tick1 > 50) {
			if (x_name1 >= 58) {
				App->render->Blit(graphics, x_name1 - 5, 145, &name1);
			}
			else {
				x_name1 += 10;
				App->render->Blit(graphics, x_name1 - 5, 145, &name1);
			}
		}
	}
	if (tick2 - tick1 > 2400) {
		if (SELECTOR_2 == 2) {
			if (x_image2 <= (SCREEN_WIDTH / 2) + 50) {
				App->render->Blit(graphics, x_image2, 15, &imageSelection2, 1, 2);
			}
			else {
				x_image2 -= 10;
				App->render->Blit(graphics, x_image2, 15, &imageSelection2, 1, 2);
			}
			if (tick2 - tick1 > 2500) {
				if (x_image2 <= (SCREEN_WIDTH / 2) + 70) {
					App->render->Blit(graphics, x_name2 - 50, 145, &name1);
				}
				else {
					x_name2 -= 10;
					App->render->Blit(graphics, x_name2 - 50, 145, &name1);
				}
			}
		}

		if (SELECTOR_2 == 1) {
			if (x_image2 <= (SCREEN_WIDTH / 2) + 50) {
				App->render->Blit(graphics, x_image2, 15, &imageSelection1, 1, 1);
			}
			else {
				x_image2 -= 10;
				App->render->Blit(graphics, x_image2, 15, &imageSelection1, 1, 1);
			}
			if (tick2 - tick1 > 2400) {
				if (x_image2 <= (SCREEN_WIDTH / 2) + 70) {
					App->render->Blit(graphics, x_name2+10, 145, &name2);
				}
				else {
					x_name2 -= 10;
					App->render->Blit(graphics, x_name2+10, 145, &name2); 
				}
			}
		}
	}
}