#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleDebug.h"
#include"ModuleCollision.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	current_state = ST_UNKNOWN;
	pivotRect.rect = {0,0,10,10};

	//idle animation (arcade sprite sheet)
	idle.PushBack({0, 8, 66, 108}, -29, -43,2);
	idle.PushBack({ 68, 8, 67, 108}, -29, -43,2);
	idle.PushBack({ 135 , 8, 69, 108 }, -29, -43,2);
	idle.speed = 0.25f;	
	
	//crouch animation (arcade sprite sheet)
	crouch.PushBack({ 0, 503, 60, 83 }, -29, -18,2);
	crouch.PushBack({815, 43, 62, 73}, -24, -8);
	crouch.speed = 0.5f;
	crouch.loop = false;

	//crouched punch animation (arcade sprite sheet)
	crouch_punch.PushBack({ 416, 42, 53, 74 }, -19, -9, 2);
	crouch_punch.PushBack({ 469, 41,109, 75 }, -33, -10, 4);
	crouch_punch.PushBack({ 578, 41, 67, 75 }, -21, -10, 4);
	crouch_punch.speed = 0.5f;
	crouch_punch.loop = false;

	//idle animation (arcade sprite sheet)
	idle_player2.PushBack({0, 8, 66, 108}, -29, -43,2);
	idle_player2.PushBack({ 68, 8, 67, 108}, -29, -43,2);
	idle_player2.PushBack({ 135 , 8, 69, 108 }, -29, -43,2);
	idle_player2.speed = 0.25f;

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 693, 348, 58, 108 }, -21, -43,3);
	forward.PushBack({ 751, 348, 69 , 108 },-32,-43,3);
	forward.PushBack({ 820, 348, 58 , 108 },-21,-43,3);
	forward.PushBack({ 878, 348, 67 , 108 },-29,-43,3);
	forward.speed = 0.25f;	 
	
	// walk backward animation (arcade sprite sheet)
	backward.PushBack({ 577, 479, 59, 107 }, -29, -42, 3);
	backward.PushBack({ 636, 477, 54 , 109 }, -25, -44, 3);
	backward.PushBack({ 690, 478, 61 , 107 },  -32,-42 ,3);
	backward.PushBack({ 636, 477, 54 , 109 }, -25, -44, 3);
	backward.speed = 0.25f;

	// punch animation (arcade sprite sheet)
	punch.PushBack({ 488, 350, 58, 106 },  -29,-41 ,2);
	punch.PushBack({ 546, 350, 89 , 106 },  -29,-41 ,3);
	punch.PushBack({ 488, 350, 58, 106 },  -29,-41 ,3);
	punch.speed = 0.5f;
	punch.loop = false;

	// kick animation (arcade sprite sheet)
	kick.PushBack({ 669, 235, 60, 110 },  -35,-45 ,4);
	kick.PushBack({ 729, 235, 61 , 113 },  -38,-48 ,4);
	kick.PushBack({ 790, 235, 103, 113 },  -44,-48 ,8);
	kick.PushBack({ 729, 235, 61 , 113 },  -38,-48 ,4);
	kick.speed = 1.0f;	
	kick.loop = false;
	
	 //jump animation (arcade sprite sheet)
	jump.canMove = true;
	jump.loop = false;
	jump.PushBack({ 0, 503, 60, 83 }, -29,-18,4);
	jump.PushBack({ 60, 456, 66 , 130 }, -29,-65,3,0,-8);
	jump.PushBack({ 126, 471, 62, 113 }, -29,jump.frames[jump.GetLastFrame() -1 ].offset.y,7,0,-5);
	jump.PushBack({ 188, 474, 57 , 110 }, -29, jump.frames[jump.GetLastFrame() - 1].offset.y,3,0,-5);
	jump.PushBack({ 245, 492, 52 , 92 }, -29, jump.frames[jump.GetLastFrame() - 1].offset.y,9 );
	jump.PushBack({ 245, 492, 52 , 92 },  -29, jump.frames[jump.GetLastFrame() - 1].offset.y,5,0,+1);
	jump.PushBack({ 299, 471 , 57 , 115 }, -29 , jump.frames[jump.GetLastFrame() - 1].offset.y,12,0,+7);
	jump.PushBack({ 0, 503, 60, 83 }, -29,-18,5);
	jump.speed = 0.9f;	
	
	// ko'ou ken animation (arcade sprite sheet)

	koouKen.PushBack({ 178, 878, 65, 107 }, -31, -42, 4);
	koouKen.PushBack({ 864, 734, 75, 123 }, -44, -58, 6);
	koouKen.PushBack({ 243, 878, 88 , 107 }, -57, -42, 4);
	koouKen.PushBack({ 331, 878, 85, 107 }, -50, -42, 10);
	koouKen.PushBack({ 416, 878, 81 , 107 }, -46, -42, 5);
	koouKen.PushBack({ 497, 878, 102 , 107 }, -22, -42, 30);
	koouKen.speed = 0.9f;
	koouKen.loop = false;

	current_animation = &idle;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	pivot_player.x = 100;
	pivot_player.y = 150;
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/ryo_sprite_sheet.png"); // arcade version
	pivotTexture = App->textures->Load("Assets/red_square.png"); // arcade version
	punchfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_punch.wav");
	kickfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kick.wav");
	kooukenfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kooken.wav");
	jumpfx = App->audio->Load_effects("Assets/Audio/FX/Jump.wav");
	player_collider = App->collision->AddCollider({ {pivot_player.x,pivot_player.y,70,109},{0,0} }, COLLIDER_PLAYER, App->player);



	return ret;
}

update_status ModulePlayer::PreUpdate()
{
	int speed = 1;

	////OnWall Colision Exit
	//if (CurrentColider != nullptr && BackColision && player_collider->rect.x > CurrentColider->rect.x + CurrentColider->rect.w)
	//{
	//	BackColision = false;
	//}

	//if (CurrentColider != nullptr && FrontColision && player_collider->rect.x < CurrentColider->rect.x - player_collider->rect.w)
	//{
	//	FrontColision = false;
	//}

	//Move right
	if (App->input->keyboard_state[SDL_SCANCODE_D] == KEY_REPEAT && state == ST_IDLE && !FrontColision)
	{
		pivot_player.x += speed;
		inputs.Push(IN_RIGHT_DOWN);
	}
	else {
		inputs.Push(IN_RIGHT_UP);
	}

	//Move Left
	if (App->input->keyboard_state[SDL_SCANCODE_A] == KEY_REPEAT && state == ST_IDLE && !BackColision)
	{
		pivot_player.x -= speed;
		inputs.Push(IN_LEFT_DOWN);
	}
	else {
		inputs.Push(IN_LEFT_UP);
	}

	//Punch weak
	if (App->input->keyboard_state[SDL_SCANCODE_E] == KEY_DOWN)
	{
		inputs.Push(IN_X);

	}

	////kick weak
	//if (App->input->keyboard_state[SDL_SCANCODE_R] == KEY_DOWN && state == ST_IDLE)
	//{
	//	if (current_animation != &kick)
	//	{
	//		state = ST_PUNCH_STANDING;
	//		kick.ResetCurrentFrame();
	//		current_animation = &kick;
	//		App->audio->Play_chunk(kickfx);
	//	}
	//}

	////Jump
	if (App->input->keyboard_state[SDL_SCANCODE_W] == KEY_DOWN)
	{
		inputs.Push(IN_JUMP);
	}

	////Ko'ou Ken
	//if (App->input->keyboard_state[SDL_SCANCODE_F] == KEY_DOWN && state == ST_IDLE)
	//{
	//	if (current_animation != &koouKen)
	//	{
	//		state = ST_PUNCH_STANDING;
	//		koouKen.ResetCurrentFrame();
	//		App->particles->AddParticle(App->particles->pre_koouKen, pivot_player.x, pivot_player.y, COLLIDER_NONE, 50);
	//		App->particles->AddParticle(App->particles->koouKen, pivot_player.x, pivot_player.y, COLLIDER_PLAYER_SHOT, 600);
	//		current_animation = &koouKen;
	//		App->audio->Play_chunk(kooukenfx);
	//	}

	//}



	//Check states and set to Idle
	//if (App->input->keyboard_state[SDL_SCANCODE_A] == key_state::KEY_IDLE
	//	&& App->input->keyboard_state[SDL_SCANCODE_D] == key_state::KEY_IDLE && state != ST_PUNCH_STANDING && state != ST_JUMP_NEUTRAL)
	//	current_animation = &idle;


	////God Mode
	//if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_PLAYER)
	//{

	//	player_collider->type = COLLIDER_NONE;
	//	timer = SDL_GetTicks();
	//	LOG("\nGod Mode ON");
	//}
	//if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_NONE && SDL_GetTicks() != timer)
	//{

	//	player_collider->type = COLLIDER_PLAYER;
	//	LOG("\nGod Mode OFF");
	//}

	while (external_input(inputs))
	{
		//Check duration of animation and reset state when it finishes

		ryo_states state = process_fsm(inputs);

		if (state != current_state)
		{
			switch (state)
			{
			case ST_IDLE:
				current_animation = &idle;
				LOG("IDLE\n");
				break;
			case ST_WALK_FORWARD:

				if (current_animation != &forward)
				{
					forward.ResetCurrentFrame();
					current_animation = &forward;
				}
				LOG("FORWARD >>>\n");
				break;
			case ST_WALK_BACKWARD:
				if (current_animation != &backward)
				{
					backward.ResetCurrentFrame();
					current_animation = &backward;
				}
				LOG("BACKWARD <<<\n");
				break;
			case ST_JUMP_NEUTRAL:
				if (current_animation != &jump)
				{
					jump.ResetCurrentFrame();
					current_animation = &jump;
					App->audio->Play_chunk(jumpfx);
				}
				LOG("JUMPING NEUTRAL ^^^^\n");
				break;
			case ST_JUMP_FORWARD:
				LOG("JUMPING FORWARD ^^>>\n");
				break;
			case ST_JUMP_BACKWARD:
				LOG("JUMPING BACKWARD ^^<<\n");
				break;
			case ST_CROUCH:
				LOG("CROUCHING ****\n");
				break;
			case ST_PUNCH_CROUCH:
				LOG("PUNCH CROUCHING **++\n");
				break;
			case ST_PUNCH_STANDING:
				if (current_animation != &punch)
				{
					punch.ResetCurrentFrame();
					current_animation = &punch;
					App->audio->Play_chunk(punchfx);
				}
				LOG("PUNCH STANDING ++++\n");
				break;
			case ST_PUNCH_NEUTRAL_JUMP:
				LOG("PUNCH JUMP NEUTRAL ^^++\n");
				break;
			case ST_PUNCH_FORWARD_JUMP:
				LOG("PUNCH JUMP FORWARD ^>>+\n");
				break;
			case ST_PUNCH_BACKWARD_JUMP:
				LOG("PUNCH JUMP BACKWARD ^<<+\n");
				break;

			}
			current_state = state;

		}
		return update_status::UPDATE_CONTINUE;
	}
}


// Update: draw background
update_status ModulePlayer::Update()
{
	if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1 && current_state != ST_IDLE){
		switch (current_state)
		{
		case ST_JUMP_NEUTRAL:
			inputs.Push(IN_JUMP_FINISH);
			break;
		case ST_PUNCH_STANDING:
			inputs.Push(IN_PUNCH_FINISH);
			break;
		}

	}
	//if (App->input->keyboard_state[SDL_SCANCODE_S] == KEY_REPEAT && state == CAN_MOVE)
	//{
	//	state = CROUCH;
	//	current_animation = &crouch;
	//	//App->render->camera.x -= speed + 0.7;
	//}

	//else if (App->input->keyboard_state[SDL_SCANCODE_S] == KEY_REALESE) {
	//	crouch.ResetCurrentFrame();
	//	state = CAN_MOVE;
	//}
	//if (App->input->keyboard_state[SDL_SCANCODE_S] == KEY_REPEAT && App->input->keyboard_state[SDL_SCANCODE_E] == KEY_PRESSED && state == CROUCH)
	//{
	//	crouch_punch.ResetCurrentFrame();
	//	state = CROUCH;
	//	current_animation = &crouch_punch;
	//	//App->render->camera.x -= speed + 0.7;
	//}

	


	// Draw everything --------------------------------------
	RectSprites r = current_animation->GetCurrentFrame();
	App->render->Blit(graphics, pivot_player.x + r.offset.x, pivot_player.y + r.offset.y, &r);
	App->player->player_collider->SetPos(pivot_player.x - 29, pivot_player.y-43);
	//RectSprites r1 = idle_player2.GetCurrentFrame();
	//App->render->Blit(graphics, 700,290 , &r1);
	App->render->Blit(pivotTexture, pivot_player.x - pivotRect.rect.w, pivot_player.y - pivotRect.rect.h, &pivotRect);
	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	App->textures->Unload(graphics);
	App->textures->Unload(pivotTexture);
	if(App->player->player_collider)
		App->player->player_collider->to_delete = true;
	LOG(" - ModulePlayer CleanUp");
	return true;
}

bool ModulePlayer::external_input(p2Qeue<ryo_inputs>& inputs)
{
	if (App->input->keyboard_state[SDL_SCANCODE_D] == key_state::KEY_REPEAT && state == ST_IDLE) {
		inputs.Push(IN_RIGHT_DOWN);
	}

	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == key_state::KEY_UP) {

	}
	return true;
}

void ModulePlayer::OnCollision(Collider * c1, Collider * c2)
{
	//Colision with wall
	if (c2->type == COLLIDER_WALL)
	{

		if(c2->rect.x < 0) 
		{
			BackColision = true;
		}
		if(c2->rect.x > 0)
		{
			FrontColision = true;
		}


	}

	CurrentColider = c2;

}

ryo_states ModulePlayer::process_fsm(p2Qeue<ryo_inputs>& inputs)
{
	static ryo_states state = ST_IDLE;
	ryo_inputs last_input;

	while (inputs.Pop(last_input))
	{
		switch (state)
		{
		case ST_IDLE:
		{
			switch (last_input)
			{
			case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
			case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
			case IN_JUMP: state = ST_JUMP_NEUTRAL; break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_X: state = ST_PUNCH_STANDING; break;
			}
		}
		break;

		case ST_WALK_FORWARD:
		{
			switch (last_input)
			{
			case IN_RIGHT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			//case IN_JUMP: state = ST_JUMP_FORWARD;  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_X: state = ST_PUNCH_STANDING; break;
			}
		}
		break;

		case ST_WALK_BACKWARD:
		{
			switch (last_input)
			{
			case IN_LEFT_UP: state = ST_IDLE; break;
			case IN_LEFT_AND_RIGHT: state = ST_IDLE; break;
			//case IN_JUMP: state = ST_JUMP_BACKWARD; jump_timer = SDL_GetTicks();  break;
			case IN_CROUCH_DOWN: state = ST_CROUCH; break;
			case IN_X: state = ST_PUNCH_STANDING; break;
			}
		}
		break;

		case ST_JUMP_NEUTRAL:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
			//case IN_X: state = ST_PUNCH_NEUTRAL_JUMP; punch_timer = SDL_GetTicks(); break;
			}
		}
		break;

		case ST_JUMP_FORWARD:
		{
			switch (last_input)
			{
			//case IN_X: state = ST_PUNCH_FORWARD_JUMP; punch_timer = SDL_GetTicks(); break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
				// TODO: Add links
			}
		}
		break;

		case ST_JUMP_BACKWARD:
		{
			switch (last_input)
			{
			//case IN_X: state = ST_PUNCH_BACKWARD_JUMP; punch_timer = SDL_GetTicks(); break;
			case IN_JUMP_FINISH: state = ST_IDLE; break;
				// TODO: Add Links
			}
		}
		break;

		case ST_PUNCH_NEUTRAL_JUMP:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
				// TODO: Add Links
			}
		}
		break;

		case ST_PUNCH_FORWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
				// TODO: Add Links
			}
		}
		break;

		case ST_PUNCH_BACKWARD_JUMP:
		{
			switch (last_input)
			{
			case IN_JUMP_FINISH: state = ST_IDLE; break;
				// TODO: Add Links
			}
		}
		break;

		case ST_PUNCH_STANDING:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
				// TODO: Add Links
			}
		}
		break;

		case ST_CROUCH:
		{
			switch (last_input)
			{
			//case IN_X: state = ST_PUNCH_CROUCH;  punch_timer = SDL_GetTicks(); break;
			case IN_CROUCH_UP: state = ST_IDLE; break;
				// TODO: Add Links
			}
		}
		break;
		case ST_PUNCH_CROUCH:
		{
			switch (last_input)
			{
			case IN_PUNCH_FINISH: state = ST_IDLE; break;
				// TODO: Add Links
			}
		}
		break;
		}
	}

	return state;
}