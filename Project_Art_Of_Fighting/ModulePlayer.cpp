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
	punch.PushBack({ 488, 350, 58, 106 }, -29, -41, 2, { 0, 0 }, {20, -20});
	punch.PushBack({ 546, 350, 89 , 106 },  -29,-41 ,3, { 0, 0 }, { 25, -25 });
	punch.PushBack({ 488, 350, 58, 106 },  -29,-41 ,3, { 0, 0 }, { 25, -25 });
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
	jump.loop = false;
	jump.PushBack({ 0, 503, 60, 83 }, -29,-18,4);
	jump.PushBack({ 60, 456, 66 , 130 }, -29, -65, 5, { 0,-8 });
	jump.PushBack({ 126, 471, 62, 113 }, -29, -58, 7, { 0,-4 });
	jump.PushBack({ 188, 474, 57 , 110 }, -26, -58, 3, { 0,-4 });
	jump.PushBack({ 245, 492, 52 , 92 }, -26, -58,9 );
	jump.PushBack({ 245, 492, 52 , 92 }, -26, -58, 5, { 0,+2 });
	jump.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 13, { 0,+5 });
	jump.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, {0, 0});
	jump.speed = 0.9f;	
		 
	//jump forward animation (arcade sprite sheet)
	jump_forward.loop = false;
	jump_forward.PushBack({ 0, 503, 60, 83 }, -29,-18,4);
	jump_forward.PushBack({ 60, 456, 66 , 130 }, -29, -65, 5, { 3,-8 });
	jump_forward.PushBack({ 126, 471, 62, 113 }, -29, -58, 7, { 3,-4 });
	jump_forward.PushBack({ 188, 474, 57 , 110 }, -26, -58, 3, { 3,-3 });
	jump_forward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 10, {2,+1});
	jump_forward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 5, { 2,+2 });
	jump_forward.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 12, { 2,+5 });
	jump_forward.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, {0, 0});
	jump_forward.speed = 0.9f;

	//jump backward animation (arcade sprite sheet)
	jump_backward.loop = false;
	jump_backward.PushBack({ 0, 503, 60, 83 }, -29, -18, 4);
	jump_backward.PushBack({ 60, 456, 66 , 130 }, -29, -65, 5, { -3,-8 });
	jump_backward.PushBack({ 126, 471, 62, 113 }, -29, -58, 7, { -3,-4 });
	jump_backward.PushBack({ 188, 474, 57 , 110 }, -26, -58, 3, { -3,-3 });
	jump_backward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 10, { -2,+1 });
	jump_backward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 5, { -2,+2 });
	jump_backward.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 12, { -2,+5 });
	jump_backward.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, { 0, 0 });
	jump_backward.speed = 0.9f;

	//falling animation
	fall.loop = false;
	fall.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 12, { 0,+5 });


	//Recover animation
	recover.loop = false;
	recover.PushBack({ 0, 503, 60, 83 }, -29, -18, 3, { 0, 0 });
	recover.speed = 0.5f;

	//jump + kick animation (arcade sprite sheet)

	jumpkick.PushBack({ 562,146,57,89 }, -32, -55, 2);
	jumpkick.PushBack({ 619,149,96,86 }, -40, -48, 4);
	jumpkick.PushBack({ 562,146,57,89 }, -32, -55, 4);
	jumpkick.loop = false;
	jumpkick.speed = 0.5f;
	
	//jump + punch animation (arcade sprite sheet)

	jumppunch.PushBack({ 715,141,66,94 }, -38, -55,3 );
	jumppunch.PushBack({ 781,157,86,78 }, -38, -55, 4);
	jumppunch.PushBack({ 715,141,66,94 }, -38, -55, 4);
	jumppunch.speed = 0.5f;
	jumppunch.loop = false;
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
	Player_Health_Value = 126;
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/ryo_sprite_sheet.png"); // arcade version
	pivotTexture = App->textures->Load("Assets/red_square.png"); // arcade version
	punchfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_punch.wav");
	kickfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kick.wav");
	kooukenfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kooken.wav");
	jumpfx = App->audio->Load_effects("Assets/Audio/FX/Jump.wav");
	if (PlayerNumber == 1) 
	{
		player_collider = App->collision->AddCollider({ { pivot_player.x,pivot_player.y,70,109 },{ 0,0 },{ 0, 0 } }, COLLIDER_PLAYER_COLLISION, App->player1);
		HitColider = App->collision->AddCollider({ {200, 200, 30, 10,}, {0, 0}, {0, 0}}, COLLIDER_PLAYER_HIT);
		HitColider->Enabled = false;
	}
		
	if (PlayerNumber == 2) 
	{
		player_collider = App->collision->AddCollider({ { pivot_player.x,pivot_player.y,35,109 },{ 0,0 },{ 0, 0 } }, COLLIDER_ENEMY_COLLISION, App->player2);
		//HitColider = App->collision->AddCollider({ { 200, 200, 10, 10, },{ 0, 0 },{ 0, 0 } }, COLLIDER_ENEMY_SHOT, App->player2);
		pivot_player.x += 200;
	}

	

	return ret;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	//Player1 Input
	if (PlayerNumber == 1 && App->player1->Player_Health_Value > 0) 
	{

		states(speed);
		//Move right
		if (App->input->keyboard_state[SDL_SCANCODE_D] == KEY_REPEAT) last_input = IN_RIGHT_DOWN;
		if (App->input->keyboard_state[SDL_SCANCODE_D] == KEY_UP) last_input = IN_RIGHT_UP;
		
		//Move Left
		if (App->input->keyboard_state[SDL_SCANCODE_A] == KEY_REPEAT) last_input = IN_LEFT_DOWN;
		if (App->input->keyboard_state[SDL_SCANCODE_A] == KEY_UP) last_input = IN_LEFT_UP;
		
		//Crouch
		if (App->input->keyboard_state[SDL_SCANCODE_S] == KEY_REPEAT) last_input = IN_CROUCH_DOWN;
		if (App->input->keyboard_state[SDL_SCANCODE_S] == KEY_UP) 
		{
			last_input = IN_CROUCH_UP;
			crouch.ResetCurrentFrame();
		}

		//Punch weak
		if (App->input->keyboard_state[SDL_SCANCODE_E] == KEY_DOWN)	last_input = IN_PUNCH;
		
		//kick weak
		if (App->input->keyboard_state[SDL_SCANCODE_R] == KEY_DOWN)	last_input = IN_KICK;
		
		//Ko'ou Ken
		if (App->input->keyboard_state[SDL_SCANCODE_F] == KEY_DOWN)	last_input = IN_KOOU_KEN;

		//Jump
		if (App->input->keyboard_state[SDL_SCANCODE_W] == KEY_DOWN) last_input = IN_JUMP_DOWN;



		//Check duration of animation and reset state when it finishes
		if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1 && current_state != ST_IDLE && current_state != ST_CROUCH)
		{
			if (current_animation == &recover) {
				last_input = IN_RECOVER_FINISH;
			}
			else {
				last_input = IN_ATTACK_FINISH;
			}
		}



		//DEBUG CONTROLS, Direct win/lose when pressing I or O
		if (App->input->keyboard_state[SDL_SCANCODE_I] == KEY_DOWN && player_collider->type == COLLIDER_NONE && !App->fade->IsFading)
		{
			Deal_Damage(*App->player1, 200);
		}		
		
		if (App->input->keyboard_state[SDL_SCANCODE_O] == KEY_DOWN && player_collider->type == COLLIDER_NONE && !App->fade->IsFading)
		{
			Deal_Damage(*App->player2, 200);
		}

		//God Mode
		if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_PLAYER_COLLISION)
		{

			player_collider->type = COLLIDER_NONE;
			timer = SDL_GetTicks();
			LOG("\nGod Mode ON");
		}
		if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_NONE && SDL_GetTicks() != timer)
		{

			player_collider->type = COLLIDER_PLAYER_COLLISION;
			LOG("\nGod Mode OFF");
		}

	}


	if (PlayerNumber == 2) 
	{
	
		//Player 2 Input

	}
	

	// Draw everything --------------------------------------
	RectSprites r = current_animation->GetCurrentFrame();

	if (PlayerNumber == 1) 
	{
		player_collider->rect.x = pivot_player.x;
		player_collider->rect.h = 87;
		player_collider->rect.w = 32;

		//Full body Colider
		//player_collider->rect = r.rect;
	}
	if(HitColider)
		HitColider->SetPos(pivot_player.x + r.DamagePosition.x, pivot_player.y + r.DamagePosition.y);

	if (current_state == ST_NEUTRAL_JUMP || current_state == ST_NEUTRAL_JUMP_PUNCH ||  current_state == ST_FALL || current_state == ST_NEUTRAL_JUMP_KICK) 
	{
		iPoint p = jump.GetDisplacementFrame();
		pivot_player += p;
		if (jump.GetDisplacementFramePos() == jump.GetLastFrame() - 5)
		{
			jump.ResetDisplacement();
			pivot_player.y = 150;
			last_input = IN_RECOVER;
		}

	}	
	
	if (current_state == ST_FORWARD_JUMP || current_state == ST_FORWARD_JUMP_PUNCH ||  current_state == ST_FORWARD_FALL || current_state == ST_FORWARD_JUMP_KICK) 
	{
		iPoint p = jump_forward.GetDisplacementFrame();
		pivot_player += p;
		if (jump_forward.GetDisplacementFramePos() == jump_forward.GetLastFrame() - 5)
		{
			jump_forward.ResetDisplacement();
			pivot_player.y = 150;
			last_input = IN_RECOVER;
		}

	}	
	if (current_state == ST_BACKWARD_JUMP || current_state == ST_BACKWARD_JUMP_PUNCH ||  current_state == ST_BACKWARD_FALL || current_state == ST_BACKWARD_JUMP_KICK) 
	{
		iPoint p = jump_backward.GetDisplacementFrame();
		pivot_player += p;
		if (jump_backward.GetDisplacementFramePos() == jump_backward.GetLastFrame() - 5)
		{
			jump_backward.ResetDisplacement();
			pivot_player.y = 150;
			last_input = IN_RECOVER;
		}

	}
	App->render->Blit(graphics, pivot_player.x + r.offset.x, pivot_player.y + r.offset.y, &r, 1, PlayerNumber);
	if (PlayerNumber == 1) 
	{
		player_collider->SetPos(pivot_player.x - 15 + r.displacement.x, pivot_player.y - 22 + r.displacement.y);
		//Full body colider
		//player_collider->SetPos(pivot_player.x + r.offset.x, pivot_player.y + r.offset.y);
	}
	if (PlayerNumber == 2) 
	{
		player_collider->SetPos(pivot_player.x + r.offset.x + 20, pivot_player.y + r.offset.y);
	}
	//App->render->Blit(pivotTexture, pivot_player.x - pivotRect.rect.w, pivot_player.y - pivotRect.rect.h, &pivotRect, 1, PlayerNumber);
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

	if (HitColider)
		HitColider->to_delete = true;


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

		CurrentColider = c2;
	}

	//Hit Detection
	if (c2->type == COLLIDER_ENEMY_HIT && c2->Enabled) 
	{
		Deal_Damage(*App->player1, 20);
		c2->Enabled = false;
	}
	if (c2->type == COLLIDER_PLAYER_HIT && c2->Enabled)
	{
		Deal_Damage(*App->player2, 20);
		c2->Enabled = false;
	}


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
		case IN_CROUCH_DOWN: state = ST_CROUCH; break;
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
		case IN_JUMP_DOWN: state = ST_FORWARD_JUMP; break;
		case IN_UNKNOWN: state = ST_IDLE; break;
		case IN_CROUCH_DOWN: state = ST_CROUCH; break;
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
		case IN_JUMP_DOWN: state = ST_BACKWARD_JUMP; break;
		case IN_UNKNOWN: state = ST_IDLE; break;
		case IN_CROUCH_DOWN: state = ST_CROUCH; break;
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
		case IN_PUNCH: state = ST_NEUTRAL_JUMP_PUNCH; break;
		case IN_KICK: state = ST_NEUTRAL_JUMP_KICK; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		}
		break;
	case ST_FORWARD_JUMP:
		switch (last_input)
		{
		case IN_PUNCH: state = ST_FORWARD_JUMP_PUNCH; break;
		case IN_KICK: state = ST_FORWARD_JUMP_KICK; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		}
		break;
	case ST_FORWARD_JUMP_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_FORWARD_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		}
		break;
	case ST_FORWARD_JUMP_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_FORWARD_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		}
		break;
	case ST_BACKWARD_JUMP:
		switch (last_input)
		{
		case IN_PUNCH: state = ST_BACKWARD_JUMP_PUNCH; break;
		case IN_KICK: state = ST_BACKWARD_JUMP_KICK; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		}
		break;
	case ST_BACKWARD_JUMP_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_BACKWARD_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		}
		break;
	case ST_BACKWARD_JUMP_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_BACKWARD_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		}
		break;
	case ST_KOOU_KEN:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_NEUTRAL_JUMP_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		}
		break;
	case ST_NEUTRAL_JUMP_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_FALL; break;
		case IN_JUMP_FINISH: state = ST_IDLE; break;
		case IN_RECOVER: state = ST_RECOVER; break;
		}
		break;
	case ST_FALL:
		switch (last_input)
		{
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_PUNCH: state = ST_NEUTRAL_JUMP_PUNCH; break;
		case IN_KICK: state = ST_NEUTRAL_JUMP_KICK; break;
		}
		break;
	case ST_FORWARD_FALL:
		switch (last_input)
		{
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_PUNCH: state = ST_FORWARD_JUMP_PUNCH; break;
		case IN_KICK: state = ST_FORWARD_JUMP_KICK; break;
		}
		break;
	case ST_BACKWARD_FALL:
		switch (last_input)
		{
		case IN_RECOVER: state = ST_RECOVER; break;
		case IN_PUNCH: state = ST_BACKWARD_JUMP_PUNCH; break;
		case IN_KICK: state = ST_BACKWARD_JUMP_KICK; break;
		}
		break;
	case ST_RECOVER:
		switch (last_input)
		{
		case IN_RECOVER_FINISH: state = ST_IDLE; break;
		}
		break;
	case ST_CROUCH:
		switch (last_input)
		{
		case IN_CROUCH_UP: state = ST_IDLE; break;
		case IN_PUNCH: state = ST_CROUCH_PUNCH; break;
		//case IN_KICK: state = ST_CROUCH_KICK; break; //Pending to do animations
		case IN_UNKNOWN: state = ST_IDLE; break;
		}
		break;
	case ST_CROUCH_PUNCH:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_CROUCH;  break;
		}
		break;	
	case ST_CROUCH_KICK:
		switch (last_input)
		{
		case IN_ATTACK_FINISH: state = ST_CROUCH;  break;
		}
		break;	
	}

	last_input = IN_UNKNOWN;
	
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
			HitColider->Enabled = true;
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
		LOG("KICK");
		break;
	case ST_NEUTRAL_JUMP:
		if (current_animation != &jump)
		{
			jump.ResetCurrentFrame();
			current_animation = &jump;
			App->audio->Play_chunk(jumpfx);
		}
		LOG("NEUTRAL JUMP");
		break;
	case ST_KOOU_KEN:
		if (current_animation != &koouKen)
		{
			koouKen.ResetCurrentFrame();
			App->particles->AddParticle(App->particles->pre_koouKen, pivot_player.x, pivot_player.y, COLLIDER_NONE, 50);
			App->particles->AddParticle(App->particles->koouKen, pivot_player.x, pivot_player.y, COLLIDER_PLAYER_HIT, 600, 30);
			current_animation = &koouKen;
			App->audio->Play_chunk(kooukenfx);
		}
		break;
	case ST_NEUTRAL_JUMP_PUNCH:
		if (current_animation != &jumppunch)
		{
			jumppunch.ResetCurrentFrame();
			current_animation = &jumppunch;
			App->audio->Play_chunk(punchfx);
		}
		LOG("NEUTRAL JUMP PUNCH");
		break;	
	case ST_NEUTRAL_JUMP_KICK:
		if (current_animation != &jumpkick)
		{
			jumpkick.ResetCurrentFrame();
			current_animation = &jumpkick;
			App->audio->Play_chunk(kickfx);
		}
		LOG("NEUTRAL JUMP KIcK");
		break;	
	case ST_FORWARD_JUMP:
		if (current_animation != &jump_forward)
		{
			jump_forward.ResetCurrentFrame();
			current_animation = &jump_forward;
			App->audio->Play_chunk(jumpfx);
		}
		LOG("FORWARD JUMP");
		break;
	case ST_FORWARD_JUMP_KICK:
		if (current_animation != &jumpkick)
		{
			jumpkick.ResetCurrentFrame();
			current_animation = &jumpkick;
			App->audio->Play_chunk(kickfx);
		}
		LOG("FORWARD JUMP KICK");
		break;	
	case ST_FORWARD_JUMP_PUNCH:
		if (current_animation != &jumppunch)
		{
			jumppunch.ResetCurrentFrame();
			current_animation = &jumppunch;
			App->audio->Play_chunk(punchfx);
		}
		LOG("FORWARD JUMP PUNCH");
		break;
	case ST_BACKWARD_JUMP:
		if (current_animation != &jump_backward)
		{
			jump_backward.ResetCurrentFrame();
			current_animation = &jump_backward;
			App->audio->Play_chunk(jumpfx);
		}
		LOG("BACKWARD JUMP");
		break;
	case ST_BACKWARD_JUMP_PUNCH:
		if (current_animation != &jumppunch)
		{
			jumppunch.ResetCurrentFrame();
			current_animation = &jumppunch;
			App->audio->Play_chunk(punchfx);
		}
		LOG("BACKWARD JUMP PUNCH");
		break;
	case ST_BACKWARD_JUMP_KICK:
		if (current_animation != &jumpkick)
		{
			jumpkick.ResetCurrentFrame();
			current_animation = &jumpkick;
			App->audio->Play_chunk(kickfx);
		}
		LOG("BACKWARD JUMP KICK");
		break;
	case ST_FALL:
		if (current_animation != &fall) {
			fall.ResetCurrentFrame();
			current_animation = &fall;
		}
		LOG("FALL");
		break;
	case ST_FORWARD_FALL:
		if (current_animation != &fall) {
			fall.ResetCurrentFrame();
			current_animation = &fall;
		}
		LOG("FALL");
		break;
	case ST_BACKWARD_FALL:
		if (current_animation != &fall) {
			fall.ResetCurrentFrame();
			current_animation = &fall;
		}
		LOG("FALL");
		break;
	case ST_RECOVER:
		if (current_animation != &recover) {
			recover.ResetCurrentFrame();
			current_animation = &recover;
		}
		LOG("RECOVER");
		break;
	case ST_CROUCH:
		if (current_animation != &crouch) {
			current_animation = &crouch;
		}
		LOG("CROUCH");
		break;	
	case ST_CROUCH_PUNCH:
		if (current_animation != &crouch_punch) 
		{
			crouch_punch.ResetCurrentFrame();
			current_animation = &crouch_punch;
			App->audio->Play_chunk(punchfx);
		}
		LOG("CROUCH PUNCH");
		break;	
	case ST_CROUCH_KICK:
		if (current_animation != &crouch_kick) {
			crouch_kick.ResetCurrentFrame();
			current_animation = &crouch_kick;
		}
		LOG("CROUCH KICK");
		break;
	}
	current_state = state;

}


