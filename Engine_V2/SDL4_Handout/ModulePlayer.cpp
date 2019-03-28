#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({0, 7, 66, 101 + 7});
	idle.PushBack({66, 7, 133 - 66, 101 + 7});
	idle.PushBack({133, 7, 202-133, 101+7});
	idle.PushBack({ 66, 7, 133 - 66, 101+7 });
	idle.speed = 0.1f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
	forward.PushBack({632, 348, 689 - 632, 456 - 348});
	forward.PushBack({689, 348, 747 - 689, 456 - 348});
	forward.PushBack({747, 348, 816-747, 456-348});
	forward.PushBack({816, 348, 874 - 816, 456 - 348});
	forward.PushBack({874, 348, 941 - 874, 456 - 348});
	forward.speed = 0.11f;

	// TODO 4: Make ryu walk backwards with the correct animations
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/SpriteSheets/Ryo_SpriteSheet.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	Animation* current_animation = &idle;

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		current_animation = &forward;
		position.x += speed;
	}

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		current_animation = &forward;
		position.x -= speed;
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();

	App->render->Blit(graphics, position.x, position.y - r.h, &r);
	
	return UPDATE_CONTINUE;
}