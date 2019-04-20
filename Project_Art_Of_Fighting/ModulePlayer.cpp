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

ModulePlayer::ModulePlayer(int num)
{
	PlayerNumber = num;
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
	jump.PushBack({ 60, 456, 66 , 130 }, -29, -65, 3, { 0,-8 });
	jump.PushBack({ 126, 471, 62, 113 }, -29, -48, 7, { 0,-5 });
	jump.PushBack({ 188, 474, 57 , 110 }, -29, -45, 3, { 0,-4 });
	jump.PushBack({ 245, 492, 52 , 92 }, -29, -27,9 );
	jump.PushBack({ 245, 492, 52 , 92 }, -29, -27, 5, { 0,+2 });
	jump.PushBack({ 299, 471 , 57 , 115 }, -29, -50, 12, { 0,+5 });
	jump.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, {0, 0});
	jump.speed = 0.9f;	

	//jump + kick animation (arcade sprite sheet)

	jumpkick.PushBack({ 562,146,57,89 }, -29, -65, 10, { 0,+3 }); //TODO 1: És raro pq no se com fitejarho be amb el salt, proveu, que no tinc gaire idea del pushback
	jumpkick.PushBack({ 619,149,96,86 }, -29, -48, 12, { 0,+3 });
	
	//jump + punch animation (arcade sprite sheet)

	jumppunch.PushBack({ 715,141,66,94 },0 ,0 ,4 );
	jumppunch.PushBack({ 781,157,86,78 },0 ,0 , 4);
	
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
	if(PlayerNumber == 1)
		player_collider = App->collision->AddCollider({ {pivot_player.x,pivot_player.y,70,109},{0,0}, {0, 0} }, COLLIDER_PLAYER, App->player1);
		
	if (PlayerNumber == 2) 
	{
		player_collider = App->collision->AddCollider({ { pivot_player.x,pivot_player.y,70,109 },{ 0,0 },{ 0, 0 } }, COLLIDER_ENEMY, App->player2);
		pivot_player.x += 200;
	}



	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	if (PlayerNumber == 1) {


		states(speed);
		//Old OnWall Colision Exit, DO NOt USE EVER AGAIN
		//if (CurrentColider != nullptr && BackColision && player_collider->rect.x > CurrentColider->rect.x + CurrentColider->rect.w) 
		//{
		//	BackColision = false;
		//}

		//if (CurrentColider != nullptr && FrontColision && player_collider->rect.x < CurrentColider->rect.x - player_collider->rect.w)
		//{
		//	FrontColision = false;
		//}
	}
	//Player1 Input
	if (PlayerNumber == 1) 
	{
		//Move right
		if (App->input->keyboard_state[SDL_SCANCODE_D] == KEY_REPEAT) last_input = IN_RIGHT_DOWN;	
		else if (App->input->keyboard_state[SDL_SCANCODE_D] == KEY_UP) last_input = IN_RIGHT_UP;
		
		//Move Left
		if (App->input->keyboard_state[SDL_SCANCODE_A] == KEY_REPEAT) last_input = IN_LEFT_DOWN;
		else if (App->input->keyboard_state[SDL_SCANCODE_A] == KEY_UP) last_input = IN_LEFT_UP;

		//Punch weak
		if (App->input->keyboard_state[SDL_SCANCODE_E] == KEY_DOWN)	last_input = IN_PUNCH;
		
		//kick weak
		if (App->input->keyboard_state[SDL_SCANCODE_R] == KEY_DOWN)	last_input = IN_KICK;
		
		//Ko'ou Ken
		if (App->input->keyboard_state[SDL_SCANCODE_F] == KEY_DOWN)	last_input = IN_KOOU_KEN;

		//Jump
		if (App->input->keyboard_state[SDL_SCANCODE_W] == KEY_DOWN) last_input = IN_JUMP_DOWN;

		//if (App->input->keyboard_state[SDL_SCANCODE_R] == KEY_DOWN)
		//{
		//	if (current_animation != &jumpkick)
		//	{
		//		current_state = ST_ATTACK;
		//		jumpkick.ResetCurrentFrame();
		//		current_animation = &jumpkick;
		//		App->audio->Play_chunk(kickfx);
		//	}
		//}
		//if (App->input->keyboard_state[SDL_SCANCODE_E] == KEY_DOWN)
		//{
		//	if (current_animation != &jumppunch)
		//	{
		//		current_state = ST_ATTACK;
		//		jumppunch.ResetCurrentFrame();
		//		current_animation = &jumppunch;
		//		App->audio->Play_chunk(punchfx);
		//	}
		//}




		//Check duration of animation and reset state when it finishes
		if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1 && current_state != ST_IDLE)
		{
			last_input = IN_ATTACK_FINISH;
		}


		//DEBUG CONTROLS, Direct win/lose when pressing I or O
		if (App->input->keyboard_state[SDL_SCANCODE_I] == KEY_DOWN && player_collider->type == COLLIDER_NONE)
		{
			Deal_Damage(*App->player1, 200);
		}		
		
		if (App->input->keyboard_state[SDL_SCANCODE_O] == KEY_DOWN && player_collider->type == COLLIDER_NONE)
		{
			Deal_Damage(*App->player2, 200);
		}

		//God Mode
		if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_PLAYER)
		{

			player_collider->type = COLLIDER_NONE;
			timer = SDL_GetTicks();
			LOG("\nGod Mode ON");
		}
		if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_NONE && SDL_GetTicks() != timer)
		{

			player_collider->type = COLLIDER_PLAYER;
			LOG("\nGod Mode OFF");
		}

	}


	if (PlayerNumber == 2) 
	{
	
		//Player 2 Input

	}
	

	// Draw everything --------------------------------------
	RectSprites r = current_animation->GetCurrentFrame();
	pivot_player += r.displacement;
	player_collider->rect = r.rect;
	if (current_animation == &jump) 
	{
		if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 5)
		{
			pivot_player.y = 150;
			last_input = IN_JUMP_FINISH;
		}
	}
	App->render->Blit(graphics, pivot_player.x + r.offset.x, pivot_player.y + r.offset.y, &r, 1, PlayerNumber);
	player_collider->SetPos(pivot_player.x + r.offset.x, pivot_player.y + r.offset.y);
	App->render->Blit(pivotTexture, pivot_player.x - pivotRect.rect.w, pivot_player.y - pivotRect.rect.h, &pivotRect, 1, PlayerNumber);
	return UPDATE_CONTINUE;
}

bool ModulePlayer::CleanUp()
{
	App->audio->Unload_effects(punchfx);
	App->audio->Unload_effects(kickfx);
	App->audio->Unload_effects(kooukenfx);
	App->audio->Unload_effects(jumpfx); 
	App->textures->Unload(graphics);
	App->textures->Unload(pivotTexture);
	if(player_collider)
		player_collider->to_delete = true;
	LOG(" - ModulePlayer CleanUp");
	return true;
}

void ModulePlayer::OnCollision(Collider * c1, Collider * c2)
{
	//Colision with wall
	if (c2->type == COLLIDER_WALL)
	{

		if(c2->rect.x < pivot_player.x) 
		{
			//BackColision = true;
			pivot_player.x = c2->rect.x + c2->rect.w + (pivot_player.x - player_collider->rect.x);
		}
		if(c2->rect.x > pivot_player.x)
		{
			//FrontColision = true;
			pivot_player.x = c2->rect.x - ((player_collider->rect.x + player_collider->rect.w) - pivot_player.x); 
		}
	}

	CurrentColider = c2;

}

player_state ModulePlayer::ControlStates()
{
	static player_state state = ST_IDLE;
	
	switch (current_state)
	{
	case ST_IDLE:
		switch (last_input)
		{
		case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
		case IN_RIGHT_DOWN: state = ST_WALK_FORWARD; break;
		case IN_JUMP_DOWN: state = ST_NEUTRAL_JUMP;	 break;
		case IN_PUNCH: state = ST_STANDING_PUNCH; break;
		case IN_KICK: state = ST_STANDING_KICK; break;
		case IN_KOOU_KEN: state = ST_KOOU_KEN; break;
		}
		break;
	case ST_WALK_FORWARD:
		switch (last_input)
		{
		case IN_RIGHT_UP: state = ST_IDLE; break;
		case IN_LEFT_DOWN: state = ST_WALK_BACKWARD; break;
		case IN_PUNCH: state = ST_STANDING_PUNCH; break;
		case IN_KICK: state = ST_STANDING_KICK; break;
		case IN_KOOU_KEN: state = ST_KOOU_KEN; break;
		}
		break;
	case ST_WALK_BACKWARD:
		switch (last_input)
		{
		case IN_LEFT_UP: state = ST_IDLE; break;
		case IN_RIGHT_DOWN: state = ST_IDLE; break;
		case IN_PUNCH: state = ST_STANDING_PUNCH; break;
		case IN_KICK: state = ST_STANDING_KICK; break;
		case IN_KOOU_KEN: state = ST_KOOU_KEN; break;
		}
		break;
	case ST_STANDING_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;

	case ST_STANDING_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_NEUTRAL_JUMP:
		switch (last_input)
		{
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_KOOU_KEN:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_CROUCH:
		break;
	default:
		break;
	}
	
	return state;
}

void ModulePlayer::states(int speed)
{
	player_state state = ControlStates();

	// Control state
	switch (state)
	{
	case ST_IDLE:
		current_animation = &idle;
		LOG("IDLE");
		break;
	case ST_WALK_FORWARD:
		pivot_player.x += speed;
		if (current_animation != &forward)
		{
			forward.ResetCurrentFrame();
			current_animation = &forward;
		}
		LOG("FORWARD");
		break;
	case ST_WALK_BACKWARD:
		pivot_player.x -= speed;
		if (current_animation != &backward)
		{
			backward.ResetCurrentFrame();
			current_animation = &backward;
		}
		LOG("BACKWARD");
		break;
	case ST_STANDING_PUNCH:
		if (current_animation != &punch)
		{
			punch.ResetCurrentFrame();
			current_animation = &punch;
			App->audio->Play_chunk(punchfx);
		}
		LOG("PUNCH");
		break;
	case ST_STANDING_KICK:
		if (current_animation != &kick)
		{
			kick.ResetCurrentFrame();
			current_animation = &kick;
			App->audio->Play_chunk(kickfx);
		}
		break;
	case ST_NEUTRAL_JUMP:
		if (current_animation != &jump)
		{
			jump.ResetCurrentFrame();
			current_animation = &jump;
			App->audio->Play_chunk(jumpfx);
		}
		break;
	case ST_KOOU_KEN:
		if (current_animation != &koouKen)
		{
			koouKen.ResetCurrentFrame();
			App->particles->AddParticle(App->particles->pre_koouKen, pivot_player.x, pivot_player.y, COLLIDER_NONE, 50);
			App->particles->AddParticle(App->particles->koouKen, pivot_player.x, pivot_player.y, COLLIDER_PLAYER_SHOT, 600, 30);
			current_animation = &koouKen;
			App->audio->Play_chunk(kooukenfx);
		}
		break;
	case ST_CROUCH:
		break;
	}
	current_state = state;

}


