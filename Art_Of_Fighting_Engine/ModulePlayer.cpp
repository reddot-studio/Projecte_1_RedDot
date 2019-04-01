#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{

	int moveY = 0;
	position.x = 100;
	position.y = 220;

	// idle animation (arcade sprite sheet)
	idle.PushBack({0, 8, 66, 108});
	idle.PushBack({ 68, 8, 67, 108 });
	idle.PushBack({ 135 , 8, 69, 108 });
	idle.speed = 0.15f;

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 693, 348, 58, 108 }, 7,0,3);
	forward.PushBack({ 751, 348, 69 , 108 },  0,0 ,3);
	forward.PushBack({ 820, 348, 58 , 108 },  7,0 ,3);
	forward.PushBack({ 878, 348, 67 , 108 },  1,-1 , 3);
	forward.speed = 0.2f;	
	
	// walk backward animation (arcade sprite sheet)
	backward.PushBack({ 577, 478, 59, 108 },  0,0 ,3);
	backward.PushBack({ 636, 477, 54 , 108 },  3,0 ,3);
	backward.PushBack({ 690, 478, 61 , 108 },  0,0 ,3);
	backward.speed = 0.2f;

	// punch animation (arcade sprite sheet)
	punch.PushBack({ 488, 350, 58, 106 },  0,0 ,2);
	punch.PushBack({ 546, 350, 89 , 106 },  0,0 ,3);
	punch.PushBack({ 488, 350, 58, 106 },  0,0 ,3);
	punch.speed = 0.5f;

	// kick animation (arcade sprite sheet)
	kick.PushBack({ 669, 235, 60, 113 },  -3,0 ,4);
	kick.PushBack({ 729, 235, 61 , 113 },  -4,0 ,4);
	kick.PushBack({ 790, 235, 103, 113 },  -8,0 ,8);
	kick.PushBack({ 729, 235, 61 , 113 },  -4,0 ,5);
	kick.speed = 1.0f;	
	
	// jump animation (arcade sprite sheet)
	moveY = jump.PushBack({ 0, 503, 60, 83 },  0,moveY , 6,true);
	moveY = jump.PushBack({ 60, 456, 66 , 130 },  0,moveY , 2,true,-4);
	moveY = jump.PushBack({ 126, 471, 62, 113 },  0,moveY , 6,true,-4);
	moveY = jump.PushBack({ 188, 474, 57 , 110 },  0,moveY , 6, true,-1);
	moveY = jump.PushBack({ 245, 492, 52 , 92 },  0,moveY-5 , 12, true);
	moveY = jump.PushBack({ 245, 492, 52 , 92 },  0,moveY-5 , 4, true,+1);
	moveY = jump.PushBack({ 299, 471 , 57 , 115 },  0,moveY+10, 10, true,+3);
	moveY = jump.PushBack({ 0, 503, 60, 83 }, 0, 0, 5, true);
	jump.speed = 1.0f;	
	
	// ko'ou ken animation (arcade sprite sheet)
	koouKen.PushBack({ 178, 878, 65, 107 }, -3, 0, 4);
	koouKen.PushBack({ 864, 734, 75, 123 }, -10, 0, 6);
	koouKen.PushBack({ 243, 878, 88 , 107 }, -14, 0, 4);
	koouKen.PushBack({ 331, 878, 85, 107 }, -14, 0, 10);
	koouKen.PushBack({ 416, 878, 81 , 107 }, -8, 0, 5);
	koouKen.PushBack({ 497, 878, 102 , 107 }, 2, 0, 30);
	koouKen.speed = 0.9f;

	current_animation = &idle;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/ryo_sprite_sheet.png"); // arcade version
	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (state == CAN_MOVE) {
		current_animation = &idle;
	}

	int speed = 2;

	if (App->input->keyboard_state[SDL_SCANCODE_D] == KEY_REPEAT && state == CAN_MOVE)
	{
		current_animation = &forward;
		position.x += speed;
		App->render->camera.x -= speed + 0.7;
	}
	if (App->input->keyboard_state[SDL_SCANCODE_A] == KEY_REPEAT && state == CAN_MOVE)
	{
		current_animation = &backward;
		if (position.x > 0) 
		{
			position.x -= speed;
			App->render->camera.x += speed + 0.7;
		}
	}
	if(App->input->keyboard_state[SDL_SCANCODE_E] == KEY_PRESSED && state == CAN_MOVE)
	{
		state = ATTACK;
		current_animation = &punch;
	}
	if(App->input->keyboard_state[SDL_SCANCODE_R] == KEY_PRESSED && state == CAN_MOVE)
	{
		state = ATTACK;
		current_animation = &kick;
	}
	if(App->input->keyboard_state[SDL_SCANCODE_F] == KEY_PRESSED && state == CAN_MOVE)
	{
		state = ATTACK;
		current_animation = &koouKen;
	}
	if(App->input->keyboard_state[SDL_SCANCODE_SPACE] == KEY_PRESSED && state == CAN_MOVE)
	{
		state = ATTACK;
		current_animation = &jump;
	}

	// Draw everything --------------------------------------
	RectSprites r = current_animation->GetCurrentFrame();
	if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame () -1 && state != CAN_MOVE)
	{
		current_animation->ResetCurrentFrame();
		state = CAN_MOVE;
	}

	App->render->Blit(graphics, position.x + r.offset.x, position.y + r.offset.y - r.rect.h, &r);
	
	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	App->textures->Unload(graphics);
	return true;
}
