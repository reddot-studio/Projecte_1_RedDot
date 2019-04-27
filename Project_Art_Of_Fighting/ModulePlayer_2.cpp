#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer_2.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleDebug.h"
#include "ModuleUI.h"
#include"ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer_2::ModulePlayer_2()
{
	for (int i = 0; i < 3; i++)
	{
		HurtColliders[i] = nullptr;
	}

	pivotRect.rect = { 0,0,10,10 };

	//Rect Colliders
	SDL_Rect rect1 = { -10,-40,25,20 };
	SDL_Rect rect2 = { -20,-20,45,60 };
	SDL_Rect rect3 = { -25,40,50,30 };

	//Jump Colliders
	SDL_Rect head_jump_collider = { -10,-55,25,20 };
	SDL_Rect body_jump_collider = { -20,-40,45,60 };
	SDL_Rect legs_jump_collider = { -25,10,50,30 };

	//Jump Punch Colliders
	SDL_Rect head_jumppunch_collider = { -10,-55,25,20 };
	SDL_Rect body_jumppunch_collider = { -25,-44,35,60 };
	SDL_Rect legs_jumppunch_collider = { -30,5,37,30 };


	//Jump Kick Colliders
	SDL_Rect head_jumpkick_collider = { -10,-50,25,20 };
	SDL_Rect body_jumpkick_collider = { -25,-44,35,45 };
	SDL_Rect legs_jumpkick_collider = { -30,-5,47,30 };

	//Crouch Rect Colliders
	SDL_Rect head_crouch_collider = { -10,-8,25,20 };
	SDL_Rect body_crouch_collider = { -20,8,50,58 };

	//Crouch Punch Rect Colliders
	SDL_Rect head_crouchPunch_collider = { 5,-8,25,20 };
	SDL_Rect body_crouchPunch_collider = { -10,8,50,58 };

	//Recover Colliders
	SDL_Rect head_recover_collider = { -10,-19,25,27 };
	SDL_Rect body_recover_collider = { -29,8,55,58 };

	//Kick Colliders
	SDL_Rect head_kick_collider = { -30,-50,25,20 };
	SDL_Rect body_kick_collider = { -30,-30,33,60 };
	SDL_Rect legs_kick_collider = { -27,30,30,40 };

	//Hit Collider
	SDL_Rect hit_punch_colllider = { 20,-25,43,10 };
	SDL_Rect hit_kick_collider = { 5,-45,60,40 };

	//idle animation (arcade sprite sheet)
	idle.PushBack({ 0, 8, 66, 108 }, -29, -43, 2, rect1, rect2, rect3);
	idle.PushBack({ 68, 8, 67, 108 }, -29, -43, 2, rect1, rect2, rect3);
	idle.PushBack({ 135 , 8, 69, 108 }, -29, -43, 2, rect1, rect2, rect3);
	idle.speed = 0.25f;

	//crouch animation (arcade sprite sheet)
	crouch.PushBack({ 0, 503, 60, 83 }, -29, -18, 2, head_crouch_collider, body_crouch_collider);
	crouch.PushBack({ 815, 43, 62, 73 }, -24, -8, 2, head_crouch_collider, body_crouch_collider);
	crouch.speed = 0.5f;
	crouch.loop = false;

	//crouched punch animation (arcade sprite sheet)
	crouch_punch.PushBack({ 416, 42, 53, 74 }, -19, -9, 2, { -5,-8,25,20 }, body_crouchPunch_collider);
	crouch_punch.PushBack({ 469, 41,109, 75 }, -33, -10, 4, head_crouchPunch_collider, body_crouchPunch_collider, {}, { 30,5,43,10 });
	crouch_punch.PushBack({ 578, 41, 67, 75 }, -21, -10, 4, { -5,-8,25,20 }, body_crouchPunch_collider);
	crouch_punch.speed = 0.5f;
	crouch_punch.damage = 20;
	crouch_punch.loop = false;

	//crouched kick animation (arcade sprite sheet)
	crouch_kick.PushBack({ 867,169,55,66 }, -24, -1, 3, { -5,-8,25,20 }, body_crouchPunch_collider); //TODO PLAYER 1: Implementar state i input + establir colliders
	crouch_kick.PushBack({ 0,280,127,68 }, -50, -3, 4, { -5, -8, 25, 20 }, body_crouchPunch_collider, {}, { 10, 40, 70, 23 });
	crouch_kick.speed = 0.5f;
	crouch_kick.damage = 20;
	crouch_kick.loop = false;

	// walk forward animation (arcade sprite sheet)
	forward.PushBack({ 693, 348, 58 , 108 }, -21, -43, 3, rect1, rect2, rect3);
	forward.PushBack({ 751, 348, 69 , 108 }, -32, -43, 3, rect1, rect2, rect3);
	forward.PushBack({ 820, 348, 58 , 108 }, -21, -43, 3, rect1, rect2, rect3);
	forward.PushBack({ 878, 348, 67 , 108 }, -29, -43, 3, rect1, rect2, rect3);
	forward.speed = 0.25f;

	// walk backward animation (arcade sprite sheet)
	backward.PushBack({ 577, 479, 59 , 107 }, -29, -42, 3, rect1, rect2, rect3);
	backward.PushBack({ 636, 477, 54 , 109 }, -25, -44, 3, rect1, rect2, rect3);
	backward.PushBack({ 690, 478, 61 , 107 }, -32, -42, 3, rect1, rect2, rect3);
	backward.PushBack({ 636, 477, 54 , 109 }, -25, -44, 3, rect1, rect2, rect3);
	backward.speed = 0.25f;

	// punch animation (arcade sprite sheet)
	punch.PushBack({ 488, 350, 58, 106 }, -29, -41, 2, rect1, rect2, rect3, hit_punch_colllider);
	punch.PushBack({ 546, 350, 89 , 106 }, -29, -41, 3, rect1, rect2, rect3, hit_punch_colllider);
	punch.PushBack({ 488, 350, 58, 106 }, -29, -41, 3, rect1, rect2, rect3, hit_punch_colllider);
	punch.speed = 0.5f;
	punch.loop = false;
	punch.damage = 20;

	// kick animation (arcade sprite sheet)
	kick.PushBack({ 669, 235, 60, 110 }, -35, -45, 4, head_kick_collider, body_kick_collider, legs_kick_collider);
	kick.PushBack({ 729, 235, 61 , 113 }, -38, -48, 4, head_kick_collider, body_kick_collider, legs_kick_collider, hit_kick_collider);
	kick.PushBack({ 790, 235, 103, 113 }, -44, -48, 8, head_kick_collider, body_kick_collider, legs_kick_collider, hit_kick_collider);
	kick.PushBack({ 729, 235, 61 , 113 }, -38, -48, 4, head_kick_collider, body_kick_collider, legs_kick_collider, hit_kick_collider);
	kick.speed = 1.0f;
	kick.damage = 30;
	kick.loop = false;

	//jump animation (arcade sprite sheet)
	jump.loop = false;
	jump.PushBack({ 0, 503, 60, 83 }, -29, -18, 4, head_recover_collider, body_recover_collider);
	jump.PushBack({ 60, 456, 66 , 130 }, -29, -65, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0, -8 });
	jump.PushBack({ 126, 471, 62, 113 }, -29, -58, 7, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0,-4 });
	jump.PushBack({ 188, 474, 57 , 110 }, -26, -58, 3, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0,-4 });
	jump.PushBack({ 245, 492, 52 , 92 }, -26, -58, 9, head_jump_collider, body_jump_collider, legs_jump_collider);
	jump.PushBack({ 245, 492, 52 , 92 }, -26, -58, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0,+2 });
	jump.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 13, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 0,+5 });
	jump.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, head_jump_collider, body_jump_collider, legs_jump_collider);
	jump.speed = 0.9f;

	//jump forward animation (arcade sprite sheet)
	jump_forward.loop = false;
	jump_forward.PushBack({ 0, 503, 60, 83 }, -29, -18, 4, head_recover_collider, body_recover_collider);
	jump_forward.PushBack({ 60, 456, 66 , 130 }, -29, -65, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 3,-8 });
	jump_forward.PushBack({ 126, 471, 62, 113 }, -29, -58, 7, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 3,-4 });
	jump_forward.PushBack({ 188, 474, 57 , 110 }, -26, -58, 3, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 3,-3 });
	jump_forward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 10, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 2,+1 });
	jump_forward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 2,+2 });
	jump_forward.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 12, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { 2,+5 });
	jump_forward.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, head_jump_collider, body_jump_collider, legs_jump_collider, { 0, 0 });
	jump_forward.speed = 0.9f;

	//jump backward animation (arcade sprite sheet)
	jump_backward.loop = false;
	jump_backward.PushBack({ 0, 503, 60, 83 }, -29, -18, 4, head_recover_collider, body_recover_collider);
	jump_backward.PushBack({ 60, 456, 66 , 130 }, -29, -65, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -3,-8 });
	jump_backward.PushBack({ 126, 471, 62, 113 }, -29, -58, 7, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -3,-4 });
	jump_backward.PushBack({ 188, 474, 57 , 110 }, -26, -58, 3, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -3,-3 });
	jump_backward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 10, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -2,+1 });
	jump_backward.PushBack({ 245, 492, 52 , 92 }, -26, -58, 5, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -2,+2 });
	jump_backward.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 12, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,0 }, { -2,+5 });
	jump_backward.PushBack({ 0, 503, 60, 83 }, -29, -18, 6, head_jump_collider, body_jump_collider, legs_jump_collider);
	jump_backward.speed = 0.9f;

	//falling animation
	fall.loop = false;
	fall.PushBack({ 299, 471 , 57 , 115 }, -25, -55, 12, head_jump_collider, body_jump_collider, legs_jump_collider, { 0,+5 });


	//Recover animation
	recover.loop = false;
	recover.PushBack({ 0, 503, 60, 83 }, -29, -18, 3, head_recover_collider, body_recover_collider, { 0, 0 });
	recover.speed = 0.5f;

	//jump + kick animation (arcade sprite sheet)

	jumpkick.PushBack({ 562,146,57,89 }, -32, -55, 2, head_jumpkick_collider, body_jumpkick_collider, legs_jumpkick_collider);
	jumpkick.PushBack({ 619,149,96,86 }, -40, -48, 4, head_jumpkick_collider, body_jumpkick_collider, legs_jumpkick_collider, { 10,10,45,30 });
	jumpkick.PushBack({ 562,146,57,89 }, -32, -55, 4, head_jumpkick_collider, body_jumpkick_collider, legs_jumpkick_collider);
	jumpkick.loop = false;
	jumpkick.damage = 20;
	jumpkick.speed = 0.5f;

	//jump + punch animation (arcade sprite sheet)

	jumppunch.PushBack({ 715,141,66,94 }, -38, -55, 3, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumppunch.PushBack({ 781,157,86,78 }, -38, -55, 4, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider, { 5,-20,45,25 });
	jumppunch.PushBack({ 715,141,66,94 }, -38, -55, 4, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumppunch.speed = 0.5f;
	jumppunch.damage = 20;
	jumppunch.loop = false;
	// ko'ou ken animation (arcade sprite sheet)

	koouKen.PushBack({ 178, 878, 65, 107 }, -31, -42, 4, rect1, rect2, rect3);
	koouKen.PushBack({ 864, 734, 75, 123 }, -44, -58, 6, rect1, rect2, rect3);
	koouKen.PushBack({ 243, 878, 88 , 107 }, -57, -42, 4, rect1, rect2, rect3);
	koouKen.PushBack({ 331, 878, 85, 107 }, -50, -42, 10, rect1, rect2, rect3);
	koouKen.PushBack({ 416, 878, 81 , 107 }, -46, -42, 5, rect1, rect2, rect3);
	koouKen.PushBack({ 497, 878, 102 , 107 }, -22, -42, 30, rect1, rect2, rect3);
	koouKen.speed = 0.9f;
	koouKen.loop = false;

	//win animation
	win.PushBack({ 820 ,1140,50,112 }, 0, 0, 0);
	win.PushBack({ 875 ,1148,66,104 }, 0, 0, 0);

	//defeat animation
	defeat.PushBack({ 508 ,1023,66,110 }, 0, 0, 0);
	defeat.PushBack({ 582 ,1045,64,88 }, 0, 0, 0);
	defeat.PushBack({ 649 ,1069,60,64 }, 0, 0, 0);


	//DAMAGES
	pose_idle_receive_standing_punch_kick_plus_jump_punch.PushBack({ 478 ,1254,69,112 }, 0, 0, 0);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.PushBack({ 547,1253,81,113 }, 0, 0, 0);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.PushBack({ 478 ,1254,69,112 }, 0, 0, 0);

	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 745,1144,64,109 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 586,1144,68,108 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 446,1138,60,114 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 0,1283,112,83 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 230,1288,108,78 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 118,1263,97,103 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 230,1288,108,78 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 358,1325,118,42 }, 0, 0, 0);
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 815, 43, 62, 73 }, -24, -8, 2);// getting up == crouch animation
	pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch.PushBack({ 0, 503, 60, 83 }, -29, -18, 2);

	pose_idle_receive_crouch_kick.PushBack({ 745,1144,64,109 }, 0, 0, 0);
	pose_idle_receive_crouch_kick.PushBack({ 586,1144,68,108 }, 0, 0, 0);

	pose_idle_receive_crouch_punch.PushBack({ 119,1146,55,106 }, 0, 0, 0);
	pose_idle_receive_crouch_punch.PushBack({ 247,1149,46,158 }, 0, 0, 0);

	pose_crouch_receive_standing_crouch_kick.PushBack({ 299,1178,73,73 }, 0, 0, 0);

	pose_crouch_receive_crouch_punch.PushBack({ 376,1177,65,75 }, 0, 0, 0);
	pose_crouch_receive_crouch_punch.PushBack({ 299,1178,73,73 }, 0, 0, 0);

	//EFFECTS
	//starhit animation
	starhit.PushBack({ 975 ,885,18,23 }, 0, 0, 0);
	starhit.PushBack({ 1008 ,879,29,36 }, 0, 0, 0);

	//impact floor animation
	impactfloor.PushBack({ 977 ,923,16,12 }, 0, 0, 0);
	impactfloor.PushBack({ 1013 ,922,18,15 }, 0, 0, 0);
	impactfloor.PushBack({ 973 ,951,24 ,21 }, 0, 0, 0);
	impactfloor.PushBack({ 1011 ,948,24,24 }, 0, 0, 0);

	//vomit animation
	vomit.PushBack({ 983 ,1042,11,12 }, 0, 0, 0);
	vomit.PushBack({ 1002 ,1042,18,13 }, 0, 0, 0);
	vomit.PushBack({ 986 ,1068,10,7 }, 0, 0, 0);
	vomit.PushBack({ 1010 ,1067,5,5 }, 0, 0, 0);

	//blood animation
	blood.PushBack({ 962 ,1155,6,6 }, 0, 0, 0);
	blood.PushBack({ 959 ,1175,48,17 }, 0, 0, 0);
	blood.PushBack({ 961 ,1204,43,16 }, 0, 0, 0);
	blood.PushBack({ 960 ,1224,49,16 }, 0, 0, 0);

	current_animation = &idle;
}

ModulePlayer_2::~ModulePlayer_2()
{}

// Load assets
bool ModulePlayer_2::Start()
{
	pivot_player.x = 90;
	pivot_player.y = 150;
	Player_Health_Value_p2 = 126;
	LOG("Loading player textures");
	bool ret = true;
	graphics = App->textures->Load("Assets/ryo_sprite_sheet.png"); // arcade version
	pivotTexture = App->textures->Load("Assets/red_square.png"); // arcade version
	punchfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_punch.wav");
	kickfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kick.wav");
	kooukenfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kooken.wav");
	jumpfx = App->audio->Load_effects("Assets/Audio/FX/Jump.wav");
	dmg = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_dmg.wav");

	player_collider = App->collision->AddCollider({ { pivot_player.x * 2,pivot_player.y,35,109 },{ 0,0 },{ 0, 0 } }, COLLIDER_ENEMY_COLLISION, App->player2);
	HurtColliders[0] = App->collision->AddCollider({ { 0,0,50,50 },{ 0,0 },{ 0,0 } }, COLLIDER_ENEMY_HURT, App->player2);
	HurtColliders[1] = App->collision->AddCollider({ { 0,0,50,50 },{ 0,0 },{ 0,0 } }, COLLIDER_ENEMY_HURT, App->player2);
	HurtColliders[2] = App->collision->AddCollider({ { 50,50,50,50 },{ 0,0 },{ 0,0 } }, COLLIDER_ENEMY_HURT, App->player2);
	HitCollider = App->collision->AddCollider({ { 50,50,50,50 },{ 0,0 },{ 0,0 } }, COLLIDER_ENEMY_HIT);
	HitCollider->Enabled = false;
	pivot_player.x += 200;
	Side = 2;
	Enemy = App->player1;
	tick1 = SDL_GetTicks();
	return ret;
}

// Update: draw background
update_status ModulePlayer_2::Update()
{

	speed = 1;
	//if (Player_Health_Value > 0)
	//{

		states(speed);
		//Move right
		if (App->input->keyboard_state[SDL_SCANCODE_KP_3] == KEY_REPEAT) last_input = IN_RIGHT_DOWN;
		if (App->input->keyboard_state[SDL_SCANCODE_KP_3] == KEY_UP) last_input = IN_RIGHT_UP;

		//Move Left
		if (App->input->keyboard_state[SDL_SCANCODE_KP_1] == KEY_REPEAT) last_input = IN_LEFT_DOWN;
		if (App->input->keyboard_state[SDL_SCANCODE_KP_1] == KEY_UP) last_input = IN_LEFT_UP;

		//Crouch
		if (App->input->keyboard_state[SDL_SCANCODE_KP_2] == KEY_REPEAT) last_input = IN_CROUCH_DOWN;
		if (App->input->keyboard_state[SDL_SCANCODE_KP_2] == KEY_UP)
		{
			last_input = IN_CROUCH_UP;
			crouch.ResetCurrentFrame();
		}

		//Punch weak
		if (App->input->keyboard_state[SDL_SCANCODE_KP_4] == KEY_DOWN)	last_input = IN_PUNCH;

		//kick weak
		if (App->input->keyboard_state[SDL_SCANCODE_KP_7] == KEY_DOWN)	last_input = IN_KICK;

		//Ko'ou Ken
		if (App->input->keyboard_state[SDL_SCANCODE_KP_0] == KEY_DOWN)	last_input = IN_KOOU_KEN;

		//Jump
		if (App->input->keyboard_state[SDL_SCANCODE_KP_5] == KEY_DOWN)	last_input = IN_JUMP_DOWN;




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

		//God Mode
		if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_ENEMY_COLLISION)
		{

			player_collider->type = COLLIDER_NONE;
			timer = SDL_GetTicks();
			LOG("\nGod Mode ON");
		}
		if (App->input->keyboard_state[SDL_SCANCODE_F5] == KEY_DOWN && player_collider->type == COLLIDER_NONE && SDL_GetTicks() != timer)
		{

			player_collider->type = COLLIDER_ENEMY_COLLISION;
			LOG("\nGod Mode OFF");
		}

		//ViewPoint
		if (player_collider->rect.x < App->player1->player_collider->rect.x)
		{
			Side = 1;
		}
		else
		{
			Side = 2;
		}

		tick2 = SDL_GetTicks();
		if (tick2 - tick1 < 4000)
		{
			App->input->Paused = true;
		}
		else
		{
			if (App->input->Paused == true && App->sceneUI->time_over == false)
			{

				App->input->Paused = false;
			}
		}

	//}


	// Draw everything --------------------------------------
	RectSprites r = current_animation->GetCurrentFrame();


	if (current_state == ST_NEUTRAL_JUMP || current_state == ST_NEUTRAL_JUMP_PUNCH || current_state == ST_FALL || current_state == ST_NEUTRAL_JUMP_KICK)
	{
		isJumping = true;
		iPoint p = jump.GetDisplacementFrame();
		pivot_player += p;
		if (jump.GetDisplacementFramePos() == jump.GetLastFrame() - 5)
		{
			jump.ResetDisplacement();
			pivot_player.y = 150;
			last_input = IN_RECOVER;
			isJumping = false;
		}

	}

	if (current_state == ST_FORWARD_JUMP || current_state == ST_FORWARD_JUMP_PUNCH || current_state == ST_FORWARD_FALL || current_state == ST_FORWARD_JUMP_KICK)
	{
		isJumping = true;
		iPoint p = jump_forward.GetDisplacementFrame();
		pivot_player += p;
		if (jump_forward.GetDisplacementFramePos() == jump_forward.GetLastFrame() - 5)
		{
			jump_forward.ResetDisplacement();
			pivot_player.y = 150;
			last_input = IN_RECOVER;
			isJumping = false;
		}

	}
	if (current_state == ST_BACKWARD_JUMP || current_state == ST_BACKWARD_JUMP_PUNCH || current_state == ST_BACKWARD_FALL || current_state == ST_BACKWARD_JUMP_KICK)
	{
		isJumping = true;
		iPoint p = jump_backward.GetDisplacementFrame();
		pivot_player += p;
		if (jump_backward.GetDisplacementFramePos() == jump_backward.GetLastFrame() - 5)
		{
			jump_backward.ResetDisplacement();
			pivot_player.y = 150;
			last_input = IN_RECOVER;
			isJumping = false;
		}

	}

	
	App->render->Blit(graphics, pivot_player.x + r.offset.x, pivot_player.y + r.offset.y, &r, 1, Side);


	if (isJumping)
	{

		player_collider->SetPos(pivot_player.x - 15, pivot_player.y - 45);

	}
	else if (current_state == ST_CROUCH || current_state == ST_CROUCH_PUNCH || current_state == ST_CROUCH_KICK)
	{
		player_collider->rect.h = 65;
		player_collider->SetPos(pivot_player.x - 15, pivot_player.y);
	}
	else
	{
		player_collider->rect.h = 90;
		player_collider->SetPos(pivot_player.x - 15, pivot_player.y - 25);
	}



	for (int i = 0; i < 3; i++)
	{
		HurtColliders[i]->SetRect(r.hurtColliders[i], current_animation->damage, pivot_player);
	}
	if (HitCollider != nullptr)
		HitCollider->SetRect(r.hitCollider, current_animation->damage, pivot_player, Side);
	//App->render->Blit(pivotTexture, pivot_player.x - pivotRect.rect.w, pivot_player.y - pivotRect.rect.h, &pivotRect, 1, PlayerNumber);
	return UPDATE_CONTINUE;
}

bool ModulePlayer_2::CleanUp()
{
	App->audio->Unload_effects(punchfx);
	App->audio->Unload_effects(kickfx);
	App->audio->Unload_effects(kooukenfx);
	App->audio->Unload_effects(jumpfx);
	App->textures->Unload(graphics);
	App->textures->Unload(pivotTexture);

	if (player_collider != nullptr)
	{
		player_collider->to_delete = true;
	}

	if (HitCollider != nullptr)
	{
		HitCollider->to_delete = true;
	}

	for (int i = 0; i < 3; i++)
	{
		if (HurtColliders[i] != nullptr)
		{
			HurtColliders[i]->to_delete = true;
		}
	}

	LOG(" - ModulePlayer CleanUp");
	return true;
}

void ModulePlayer_2::OnCollision(Collider * c1, Collider * c2)
{

	//Is Player coliding with wall?
	if (c2->type == COLLIDER_WALL)
	{
		//Camera is not under nor over the limit
		if (-App->render->camera.x < 0)
			App->render->camera.x = 0;
		if (-App->render->camera.x > App->render->CurrentSceneLenght - 44)
			App->render->camera.x = -(App->render->CurrentSceneLenght - 44);

		//Coliding with left side of the camera?
		if (c2->LeftRight == false)
		{
			//Move camera
			if (-App->render->camera.x > 0)
				App->render->camera.x += App->render->speed;
			//Limit player inside camera
			pivot_player.x = c2->rect.x + c2->rect.w + (pivot_player.x - player_collider->rect.x);
		}

		if (c2->LeftRight == true)
		{
			//Move camera and limit player
			App->render->camera.x -= App->render->speed;
			pivot_player.x = c2->rect.x + (pivot_player.x - player_collider->rect.x) - player_collider->rect.w;
		}
	}

	//Am I coliding with an enemy?
	if (c2->type == COLLIDER_PLAYER_COLLISION && (c1->Enabled && c2->Enabled))
	{

		//Only if is moving
		if (current_state != ST_IDLE)
		{
			//When can you move the enemy? I'm coliding from the right?
			if (player_collider->rect.x + player_collider->rect.w - 5 < Enemy->player_collider->rect.x)
			{
				if (Enemy->player_collider->rect.x + Enemy->player_collider->rect.w < App->render->CameraLimitR->rect.x)
				{
					//Am i entering to the enemy by the left?
					//eNEMY REPELED BY PLAYER
					Enemy->pivot_player.x = player_collider->rect.x + player_collider->rect.w + (Enemy->pivot_player.x - Enemy->player_collider->rect.x);
				}
				else
				{
					//PLAYED REPELED BY ENEMY ON WALL COLISION
					pivot_player.x = Enemy->pivot_player.x - (Enemy->pivot_player.x - Enemy->player_collider->rect.x) - ((player_collider->rect.x + player_collider->rect.w) - pivot_player.x);
				}
			}
			else
			{
				if (Enemy->player_collider->rect.x > App->render->CameraLimitL->rect.x + App->render->CameraLimitL->rect.w)
				{
					//Am i entering to the enemy by the RIGHT?
					//PLAYER PUSHING ENEMY BACKWARDS
					Enemy->pivot_player.x = pivot_player.x - (pivot_player.x - player_collider->rect.x) - ((Enemy->player_collider->rect.x + Enemy->player_collider->rect.w) - Enemy->pivot_player.x);
				}
				else
				{
					pivot_player.x = Enemy->player_collider->rect.x + Enemy->player_collider->rect.w + (pivot_player.x - player_collider->rect.x);
				}
			}
		}


		LOG("");
	}

	//Hit Detection
	if (c2->type == COLLIDER_PLAYER_HIT && c2->Enabled)
	{

		Deal_Damage(*App->player1, c2->ColliderDamage);

		c2->Enabled = false;
	}


}

player_state ModulePlayer_2::ControlStates()
{
	static player_state state = ST_IDLE;

	switch (current_state)
	{
	case ST_IDLE:
		switch (last_input)
		{
		case IN_UNKNOWN: state = ST_IDLE; break;
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
		case IN_KICK: state = ST_CROUCH_KICK; break;
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

void ModulePlayer_2::states(int speed)
{
	player_state state = ControlStates();


	// Control state
	switch (state)
	{
	case ST_IDLE:
		current_animation = &idle;
		//if (player_collider->CheckCollision(App->player2->player_collider->rect) == false)
		//{
		//	player_collider->Enabled = true;
		//}
		player_collider->Enabled = true;
		LOG("IDLE");
		break;
	case ST_WALK_FORWARD:
		pivot_player.x += speed;
		if (current_animation != &forward && Side == 1)
		{
			forward.ResetCurrentFrame();
			current_animation = &forward;
		}
		if (current_animation != &backward && Side == 2)
		{
			backward.ResetCurrentFrame();
			current_animation = &backward;
		}
		LOG("FORWARD");
		break;
	case ST_WALK_BACKWARD:
		pivot_player.x -= speed;
		if (current_animation != &backward && Side == 1)
		{
			backward.ResetCurrentFrame();
			current_animation = &backward;
		}
		if (current_animation != &forward && Side == 2)
		{
			forward.ResetCurrentFrame();
			current_animation = &forward;
		}
		LOG("BACKWARD");
		break;
	case ST_STANDING_PUNCH:
		if (current_animation != &punch)
		{
			punch.ResetCurrentFrame();
			HitCollider->Enabled = true;
			current_animation = &punch;
			App->audio->Play_chunk(punchfx);

		}
		LOG("PUNCH");
		break;
	case ST_STANDING_KICK:
		if (current_animation != &kick)
		{
			kick.ResetCurrentFrame();
			HitCollider->Enabled = true;
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
			player_collider->Enabled = false;
		}
		LOG("NEUTRAL JUMP");
		break;
	case ST_KOOU_KEN:
		if (current_animation != &koouKen)
		{
			//Whem side == 2 does not work
			koouKen.ResetCurrentFrame();
			App->particles->AddParticle(App->particles->pre_koouKen, pivot_player.x, pivot_player.y, COLLIDER_NONE, 50);
			App->particles->AddParticle(App->particles->koouKen, pivot_player.x, pivot_player.y, COLLIDER_ENEMY_HIT, 600, 30);
			current_animation = &koouKen;
			App->audio->Play_chunk(kooukenfx);
		}
		break;
	case ST_NEUTRAL_JUMP_PUNCH:
		if (current_animation != &jumppunch)
		{
			HitCollider->Enabled = true;
			jumppunch.ResetCurrentFrame();
			current_animation = &jumppunch;
			App->audio->Play_chunk(punchfx);
			player_collider->Enabled = false;
		}
		LOG("NEUTRAL JUMP PUNCH");
		break;
	case ST_NEUTRAL_JUMP_KICK:
		if (current_animation != &jumpkick)
		{
			HitCollider->Enabled = true;
			jumpkick.ResetCurrentFrame();
			current_animation = &jumpkick;
			App->audio->Play_chunk(kickfx);
			player_collider->Enabled = false;
		}
		LOG("NEUTRAL JUMP KIcK");
		break;
	case ST_FORWARD_JUMP:
		if (current_animation != &jump_forward)
		{
			jump_forward.ResetCurrentFrame();
			current_animation = &jump_forward;
			App->audio->Play_chunk(jumpfx);
			player_collider->Enabled = false;
		}
		LOG("FORWARD JUMP");
		break;
	case ST_FORWARD_JUMP_KICK:
		if (current_animation != &jumpkick)
		{
			jumpkick.ResetCurrentFrame();
			HitCollider->Enabled = true;
			current_animation = &jumpkick;
			App->audio->Play_chunk(kickfx);
			player_collider->Enabled = false;
		}
		LOG("FORWARD JUMP KICK");
		break;
	case ST_FORWARD_JUMP_PUNCH:
		if (current_animation != &jumppunch)
		{
			HitCollider->Enabled = true;
			jumppunch.ResetCurrentFrame();
			current_animation = &jumppunch;
			App->audio->Play_chunk(punchfx);
			player_collider->Enabled = false;
		}
		LOG("FORWARD JUMP PUNCH");
		break;
	case ST_BACKWARD_JUMP:
		if (current_animation != &jump_backward)
		{
			jump_backward.ResetCurrentFrame();
			current_animation = &jump_backward;
			App->audio->Play_chunk(jumpfx);
			player_collider->Enabled = false;
		}
		LOG("BACKWARD JUMP");
		break;
	case ST_BACKWARD_JUMP_PUNCH:
		if (current_animation != &jumppunch)
		{
			HitCollider->Enabled = true;
			jumppunch.ResetCurrentFrame();
			current_animation = &jumppunch;
			App->audio->Play_chunk(punchfx);
			player_collider->Enabled = false;
		}
		LOG("BACKWARD JUMP PUNCH");
		break;
	case ST_BACKWARD_JUMP_KICK:
		if (current_animation != &jumpkick)
		{
			HitCollider->Enabled = true;
			jumpkick.ResetCurrentFrame();
			current_animation = &jumpkick;
			App->audio->Play_chunk(kickfx);
			player_collider->Enabled = false;
		}
		LOG("BACKWARD JUMP KICK");
		break;
	case ST_FALL:
		if (current_animation != &fall) {
			fall.ResetCurrentFrame();
			current_animation = &fall;
			player_collider->Enabled = false;
		}
		LOG("FALL");
		break;
	case ST_FORWARD_FALL:
		if (current_animation != &fall) {
			fall.ResetCurrentFrame();
			current_animation = &fall;
			player_collider->Enabled = false;
		}
		LOG("FALL");
		break;
	case ST_BACKWARD_FALL:
		if (current_animation != &fall) {
			fall.ResetCurrentFrame();
			current_animation = &fall;
			player_collider->Enabled = false;
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
			HitCollider->Enabled = true;
			crouch_punch.ResetCurrentFrame();
			current_animation = &crouch_punch;
			App->audio->Play_chunk(punchfx);
		}
		LOG("CROUCH PUNCH");
		break;
	case ST_CROUCH_KICK:
		if (current_animation != &crouch_kick) {
			HitCollider->Enabled = true;
			crouch_kick.ResetCurrentFrame();
			current_animation = &crouch_kick;
			App->audio->Play_chunk(kickfx);
		}
		LOG("CROUCH KICK");
		break;
	}
	current_state = state;

}

void ModulePlayer_2::Deal_Damage(ModulePlayer_1& Enemy, int AttackDamage)
{
	App->audio->Play_chunk(dmg);
	if (Enemy.Player_Health_Value_p1 - AttackDamage <= 0)
	{
		LOG("\n Someone died");
		Enemy.Player_Health_Value_p1 = 0;
		p1_win++;
		win_check = true;
		Module *CurrentScene = nullptr;

		if (App->scene_todo->IsEnabled())
			CurrentScene = App->scene_todo;

	}
	else
	{
		Enemy.Player_Health_Value_p1 -= AttackDamage;
	}
}

void ModulePlayer_2::CheckHealth(ModulePlayer_1&Enemy)
{
	
	if ((Enemy.Player_Health_Value_p1 > Player_Health_Value_p2) && App->sceneUI->time_over == true)
	{
		Player_Health_Value_p2 = 126;
		Enemy.Player_Health_Value_p1 = 126;
		App->player1->p2_win++;
	}
}



