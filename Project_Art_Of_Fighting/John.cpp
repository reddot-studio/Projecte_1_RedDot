#include "John.h"

John::John(int player)
{
	this->player = player;
	specialDmg = 15;

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

	//IDLE
	idle.SetReverseOffset({ -27,-43 }, 2);
	idle.PushBack({ 0, 0, 66, 104 }, -29, -43, 2, rect1, rect2, rect3);
	idle.SetReverseOffset({ -28,-43 }, 2);
	idle.PushBack({ 66, 0, 66, 106 }, -29, -43, 2, rect1, rect2, rect3);
	idle.SetReverseOffset({ -30,-43 }, 2);
	idle.PushBack({ 135 , 8, 69, 108 }, -29, -43, 2, rect1, rect2, rect3);


	idle.speed = 0.25f;
}
