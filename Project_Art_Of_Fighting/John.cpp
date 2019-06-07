#include "John.h"

John::John(int player)
{
	this->player = player;
	characterType = JOHN;
	specialDmg = 15;

	colliderOffsetX = -15;
	


	SDL_Rect rect1 = { 18,-40,25,20 };
	SDL_Rect rect2 = { 5,-20,45,60 };
	SDL_Rect rect3 = { 0,40,50,30 };
	

	//Jump Colliders
	SDL_Rect head_jump_collider = { 18,-55,25,20 };
	SDL_Rect body_jump_collider = { 5,-40,45,60 };
	SDL_Rect legs_jump_collider = { 0,10,50,30 };

	//Jump Punch Colliders
	SDL_Rect head_jumppunch_collider = { 18,-55,25,20 };
	SDL_Rect body_jumppunch_collider = { 10,-44,35,60 };
	SDL_Rect legs_jumppunch_collider = { 15,10,45,30 };
	

	//Jump Kick Colliders
	SDL_Rect head_jumpkick_collider = { 18,-50,25,20 };
	SDL_Rect body_jumpkick_collider = { 5,-44,35,45 };
	SDL_Rect legs_jumpkick_collider = { 0,-5,47,30 };

	//Crouch Rect Colliders
	SDL_Rect head_crouch_collider = { 20,-8,25,20 };
	SDL_Rect body_crouch_collider = { 3,8,50,52 };

	//Crouch Punch Rect Colliders
	SDL_Rect head_crouchPunch_collider = { 20,-8,25,20 };
	SDL_Rect body_crouchPunch_collider = { 3,8,50,58 };

	//Recover Colliders
	SDL_Rect head_recover_collider = { 18,-19,25,27 };
	SDL_Rect body_recover_collider = { 10,8,55,58 };

	//Kick Colliders
	SDL_Rect head_kick_collider = { -30,-50,25,20 };
	SDL_Rect body_kick_collider = { -30,-30,33,60 };
	SDL_Rect legs_kick_collider = { -27,30,30,40 };

	//Hit Collider
	SDL_Rect hit_punch_colllider = { 50,-25,43,10 };
	SDL_Rect hit_kick_collider = { 5,-45,60,40 };

	//IDLE
	idle.SetReverseOffset({ 0, -39 }, 2);
	idle.PushBack({ 0, 0, 66, 104 }, 0, -39, 2, rect1, rect2, rect3);
	idle.SetReverseOffset({ 0, -42 }, 2);
	idle.PushBack({ 129 , 0, 66, 107 }, 0, -42, 2, rect1, rect2, rect3);
	idle.SetReverseOffset({ 3, -41 }, 2);
	idle.PushBack({ 66, 0, 63, 106 }, 0, -41, 2, rect1, rect2, rect3);

	idle.speed = 0.26f;

	//WALK FORWARD
	forward.SetReverseOffset({ 0,-39 }, 5);
	forward.PushBack({ 435, 259, 67, 104 }, 0, -39, 5, rect1, rect2, rect3);
	forward.SetReverseOffset({ 2,-43 }, 5);
	forward.PushBack({ 502, 259, 63, 108 }, 2, -43, 5, rect1, rect2, rect3);
	forward.SetReverseOffset({ 2,-45 }, 5);
	forward.PushBack({ 565, 259, 61, 110 }, 2, -45, 5, rect1, rect2, rect3);
	forward.SetReverseOffset({ 0,-41 }, 5);
	forward.PushBack({ 626, 259, 63, 106 }, 0, -41, 5, rect1, rect2, rect3);
	forward.SetReverseOffset({ -2,-44 }, 5);
	forward.PushBack({ 689, 259, 69, 109 }, -2, -44, 5, rect1, rect2, rect3);
	forward.speed = 0.7f;

	//WALK BACKWARD
	backward.SetReverseOffset({ 0,-39 }, 5);
	backward.PushBack({ 435, 259, 67, 104 }, 0, -39, 5, rect1, rect2, rect3);
	backward.SetReverseOffset({ 2,-43 }, 5);
	backward.PushBack({ 502, 259, 63, 108 }, 2, -43, 5, rect1, rect2, rect3);
	backward.SetReverseOffset({ 2,-45 }, 5);
	backward.PushBack({ 565, 259, 61, 110 }, 2, -45, 5, rect1, rect2, rect3);
	backward.SetReverseOffset({ 0,-41 }, 5);
	backward.PushBack({ 626, 259, 63, 106 }, 0, -41, 5, rect1, rect2, rect3);
	backward.SetReverseOffset({ -2,-44 }, 5);
	backward.PushBack({ 689, 259, 69, 109 }, -2, -44, 5, rect1, rect2, rect3);
	backward.speed = 0.7f;

	//JUMP
	jump.loop = false;
	jump.SetReverseOffset({ -0, -39 }, 3);
	jump.PushBack({ 195,3,66,104 }, 0, -39, 3, head_jump_collider, body_jump_collider,legs_jump_collider);
	jump.SetReverseOffset({ 9, -48 }, 11);
	jump.PushBack({ 261,0,48,118 }, 9, -48, 11,head_jump_collider, body_jump_collider,legs_jump_collider, {}, { 0,-7 });
	jump.SetReverseOffset({ 9, -48 }, 3);	   	
	jump.PushBack({ 261,0,48,118 }, 9, -48, 3, head_jump_collider, body_jump_collider,legs_jump_collider, {}, { 0,-3 });
	jump.SetReverseOffset({ 0, -35 }, 8);	   	
	jump.PushBack({ 309,30,57,77 }, 0, -35, 8, head_jump_collider, body_jump_collider,legs_jump_collider);
	jump.SetReverseOffset({ 0, -35 }, 7);	   	
	jump.PushBack({ 309,30,57,77 }, 0, -35, 7, head_jump_collider, body_jump_collider,legs_jump_collider, {}, { 0,1 });
	jump.SetReverseOffset({ 9, -48 }, 14);	   	
	jump.PushBack({ 261,0,48,118 }, 9, -48, 14,head_jump_collider, body_jump_collider,legs_jump_collider, {}, { 0,6 });
	jump.speed = 0.9f;
	
	//Forward JUMP
	jump_forward.loop = false;
	jump_forward.SetReverseOffset({ 0, -39 }, 3);
	jump_forward.PushBack({ 195,3,66,104 }, 0, -39, 3, head_jump_collider, body_jump_collider, legs_jump_collider);
	jump_forward.SetReverseOffset({ 9, -48 }, 11);
	jump_forward.PushBack({ 261,0,48,118 }, 9, -48, 11,head_jump_collider, body_jump_collider, legs_jump_collider, {}, { 3,-7 });
	jump_forward.SetReverseOffset({ 9, -48 }, 3);
	jump_forward.PushBack({ 261,0,48,118 }, 9, -48, 3, head_jump_collider, body_jump_collider, legs_jump_collider, {}, { 3,-3 });
	jump_forward.SetReverseOffset({ 0, -35 }, 8);
	jump_forward.PushBack({ 309,30,57,77 }, 0, -35, 8, head_jump_collider, body_jump_collider, legs_jump_collider, {}, { 3,0 });
	jump_forward.SetReverseOffset({ 0, -35 }, 7);
	jump_forward.PushBack({ 309,30,57,77 }, 0, -35, 7, head_jump_collider, body_jump_collider, legs_jump_collider, {}, { 3,1 });
	jump_forward.SetReverseOffset({ 9, -48 }, 14);
	jump_forward.PushBack({ 261,0,48,118 }, 9, -48, 14,head_jump_collider, body_jump_collider, legs_jump_collider, {}, { 3,6 });
	jump_forward.speed = 0.9f;	

	//Backward JUMP
	jump_backward.loop = false;
	jump_backward.SetReverseOffset({ 0, -39 }, 3);
	jump_backward.PushBack({ 195,3,66,104 }, 0, -39, 3, head_jump_collider, body_jump_collider, legs_jump_collider);
	jump_backward.SetReverseOffset({ 9, -48 }, 11);
	jump_backward.PushBack({ 261,0,48,118 }, 9, -48, 11,head_jump_collider, body_jump_collider, legs_jump_collider, {}, { -3,-7 });
	jump_backward.SetReverseOffset({ 9, -48 }, 3);
	jump_backward.PushBack({ 261,0,48,118 }, 9, -48, 3, head_jump_collider, body_jump_collider, legs_jump_collider, {}, { -3,-3 });
	jump_backward.SetReverseOffset({ 0, -35 }, 8);
	jump_backward.PushBack({ 309,30,57,77 }, 0, -35, 8, head_jump_collider, body_jump_collider, legs_jump_collider, {}, { -3,0 });
	jump_backward.SetReverseOffset({ 0, -35 }, 7);
	jump_backward.PushBack({ 309,30,57,77 }, 0, -35, 7, head_jump_collider, body_jump_collider, legs_jump_collider, {}, { -3,1 });
	jump_backward.SetReverseOffset({ 9, -48 }, 14);
	jump_backward.PushBack({ 261,0,48,118 }, 9, -48, 14,head_jump_collider, body_jump_collider, legs_jump_collider, {}, { -3,6 });
	jump_backward.speed = 0.9f;

	//Recover
	recover.loop = false;
	recover.SetReverseOffset({ 0, -39 }, 3);
	recover.PushBack({ 195,3,66,104 }, 0, -39, 3,head_recover_collider,body_recover_collider);
	recover.speed = 0.5f;

	//CROUCH
	crouch.SetReverseOffset({0, -39}, 3);
	crouch.PushBack({ 195,3,66,104 }, 0, -39, 3, head_crouch_collider, body_crouch_collider);
	crouch.SetReverseOffset({ 11, -8}, 2);
	crouch.PushBack({ 498,34,58,73 },-3,-8,2,head_crouch_collider,body_crouch_collider);
	crouch.loop = false;
	crouch.speed = 0.5f;

	//CROUCH KICK
	crouch_kick.SetReverseOffset({10, -7}, 2);
	crouch_kick.PushBack({ 556,35,59,72 },-3,-7,2,{ -5,-8,25,20 },body_crouchPunch_collider);
	crouch_kick.SetReverseOffset({-34, -3}, 5);
	crouch_kick.PushBack({ 615,39,104,68 }, -4, -3, 5, { -5,-8,25,20 }, body_crouchPunch_collider, {}, { 50, 48, 50, 18 });
	crouch_kick.SetReverseOffset({9, -7}, 2);
	crouch_kick.PushBack({ 556,35,59,72 },-3,-7,2, { -5,-8,25,20 },body_crouchPunch_collider);
	crouch_kick.loop = false;
	crouch_kick.speed = 0.35f;

	//CROUCH PUNCH
	crouch_punch.SetReverseOffset({ 10, -7 }, 2);
	crouch_punch.PushBack({ 556,35,59,72 }, -3, -7, 2, { -5,-8,25,20 },body_crouchPunch_collider);
	crouch_punch.SetReverseOffset({ -34, -3 }, 5);
	crouch_punch.PushBack({ 615,39,104,68 }, -4, -3, 5, head_crouchPunch_collider, body_crouchPunch_collider, {}, { 50, 48, 50, 18 });
	crouch_punch.SetReverseOffset({ 9, -7 }, 2);
	crouch_punch.PushBack({ 556,35,59,72 }, -3, -7, 2, { -5,-8,25,20 },body_crouchPunch_collider);
	crouch_punch.loop = false;
	crouch_punch.speed = 0.35f;

	//PUNCH
	punch.SetReverseOffset({ -4,-46 }, 2);
	punch.PushBack({ 719,0,73,111 }, -3, -46, 2,rect1,rect2,rect3);
	punch.SetReverseOffset({ -39,-42 }, 2);
	punch.PushBack({ 792,0,107,107 }, -2, -42, 2, rect1, rect2, rect3,hit_punch_colllider);
	punch.SetReverseOffset({ -3,-46 }, 2);
	punch.PushBack({ 719,0,73,111 }, -3, -46, 2, rect1, rect2, rect3);
	punch.SetReverseOffset({ 0, -39 }, 4);
	punch.PushBack({ 0, 0, 66, 104 }, 0, -39, 4, rect1, rect2, rect3);
	punch.loop = false;
	punch.speed = 0.5f;
	punch.damage = 10;

	//KICK
	kick.SetReverseOffset({ 9, -48 },2 );
	kick.PushBack({ 0,128,58,113 }, -1, -48, 2, rect1, rect2, rect3);
	kick.SetReverseOffset({ 0, -49 }, 2);
	kick.PushBack({ 58,128,52,113 }, 14, -49, 2, rect1, rect2, rect3);
	kick.SetReverseOffset({ 4, -46 },2 );
	kick.PushBack({ 110,128,58,111 }, 4, -46, 2, rect1, rect2, rect3);
	kick.SetReverseOffset({ -40, -43 }, 5);
	kick.PushBack({ 168,129,105,108 }, 1, -43, 5, rect1, rect2, rect3);
	kick.SetReverseOffset({ -20, -43 }, 2);
	kick.PushBack({ 273,139,83,108 }, 3, -43, 2, rect1, rect2, rect3);
	kick.SetReverseOffset({ 3, -46 }, 2);
	kick.PushBack({ 110,128,58,111 }, 5, -46, 2, rect1, rect2, rect3);
	kick.SetReverseOffset({ 0, -49 },2 );
	kick.PushBack({ 58,128,52,113 }, 14, -49, 2, rect1, rect2, rect3);
	kick.SetReverseOffset({9, -48},2 );
	kick.PushBack({ 0,128,58,113 }, -1, -48, 2, rect1, rect2, rect3);
	kick.loop = false;
	kick.speed = 0.7f;
	kick.damage = 10;

	//KOUKEN reversed completed
	koouKen.SetReverseOffset({7, -34}, 3);
	koouKen.PushBack({ 366,149,69,98 },-10,-34, 3, rect1, rect2, rect3);
	koouKen.SetReverseOffset({7, -28}, 3);
	koouKen.PushBack({ 435,155,67,92 }, -7, -28, 3, rect1, rect2, rect3);
	koouKen.SetReverseOffset({-7, -37}, 5);
	koouKen.PushBack({ 502,145,71,101 }, 2, -37 ,5, rect1, rect2, rect3);
	koouKen.SetReverseOffset({-30, -27}, 8);
	koouKen.PushBack({ 573,155,108,92 }, -12, -27, 8, rect1, rect2, rect3);
	koouKen.loop = false;
	koouKen.speed = 0.5f;

	//FALL
	fall.loop = false;
	fall.SetReverseOffset({ 9, -48 }, 14);
	fall.PushBack({ 261,0,48,118 }, 9, -48, 14, head_jump_collider,body_jump_collider, legs_jump_collider, {}, { 0,6 });
	fall.speed = 0.5f;

	//TAUNT
	taunt.SetReverseOffset({ -23, -30 }, 3);
	taunt.PushBack({ 0,496,110,96 }, -21, -30, 3, rect1, rect2 , rect3);
	taunt.SetReverseOffset({ -17,-30 }, 3);
	taunt.PushBack({ 111,496,105,96 }, -22, -30, 3, rect1, rect2, rect3);
	taunt.SetReverseOffset({ -19,-30 }, 3);
	taunt.PushBack({ 218,496,107,96 }, -22, -30, 3, rect1, rect2, rect3);
	taunt.SetReverseOffset({ -23, -30 }, 3);
	taunt.PushBack({ 0,496,110,96 }, -21, -30, 3, rect1, rect2 , rect3);
	taunt.SetReverseOffset({ -17,-30 }, 3);
	taunt.PushBack({ 111,496,105,96 }, -22, -30, 3, rect1, rect2, rect3);
	taunt.SetReverseOffset({ -19,-30 }, 3);
	taunt.PushBack({ 218,496,107,96 }, -22, -30, 3, rect1, rect2, rect3);
	
	taunt.speed = 0.05f;
	taunt.loop = false; 
	

	//JUMP + KICK
	jumpkick.SetReverseOffset({ -4, -50 }, 2);
	jumpkick.PushBack({ 10,371,56,113 }, -4, -50, 2, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumpkick.SetReverseOffset({ -6, -50 }, 4); 
	jumpkick.PushBack({ 0,247,109,112 }, -6, -50, 4, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumpkick.SetReverseOffset({ -13, -52 }, 2);
	jumpkick.PushBack({ 116,249,91,121 }, -13, -52, 2, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumpkick.SetReverseOffset({ -4, -50 }, 2);
	jumpkick.PushBack({ 10,371,56,113 }, -4, -50, 2, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumpkick.speed = 0.45f;
	jumpkick.loop = false;
	jumpkick.damage = 10;


	//Falten frames//
	   
	//JUMP + PUNCH
	jumppunch.SetReverseOffset({7, -52}, 2);
	jumppunch.PushBack({ 10,371,56,113 },7,-52,2,head_jumppunch_collider,body_jumppunch_collider,legs_jumppunch_collider);
	jumppunch.SetReverseOffset({5, -65}, 8);
	jumppunch.PushBack({ 66,370,71,123 },5,-65,8, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumppunch.SetReverseOffset({7, -52}, 2);
	jumppunch.PushBack({ 10,371,56,113 },7,-52,2, head_jumppunch_collider, body_jumppunch_collider, legs_jumppunch_collider);
	jumppunch.speed = 0.5f;
	jumppunch.loop = false;
	jumppunch.damage = 10;

	//PUNCH + C
	c_punch.SetReverseOffset({ 15,-45 }, 3);
	c_punch.PushBack({ 320,382,48,109 },5,-45,3, rect1, rect2, rect3);
	c_punch.SetReverseOffset({ 16,-45 }, 3);
	c_punch.PushBack({ 376,382,55,109 },-4, -45, 3, rect1, rect2, rect3);
	c_punch.SetReverseOffset({ 18,-46 }, 3);
	c_punch.PushBack({ 434,382,52,110 },-3, -46, 3, rect1, rect2, rect3);	
	c_punch.SetReverseOffset({ -37,-44 }, 5);
	c_punch.PushBack({ 495 ,382,105,108 },-3, -44, 5, rect1, rect2, rect3);
	c_punch.SetReverseOffset({ 21,-47 }, 3);
	c_punch.PushBack({ 605,382,63,110 },-6, -47, 3, rect1, rect2, rect3);
	c_punch.loop = false;
	c_punch.speed = 0.6f;
	c_punch.damage = 20;


	//KICK + C
	c_kick.SetReverseOffset({ 3,-42 },2 );
	c_kick.PushBack({ 769,261, 52,107 }, 10, -42, 2, rect1, rect2, rect3);
	c_kick.SetReverseOffset({ 0,-46 }, 2);
	c_kick.PushBack({ 825,261,67,110 }, -4, -46, 2, rect1, rect2, rect3);
	c_kick.SetReverseOffset({ -40,-43 },5 );
	c_kick.PushBack({ 213,382,102,107 }, -1, -43, 5, rect1, rect2, rect3);
	c_kick.SetReverseOffset({ -1,-46 }, 2);
	c_kick.PushBack({ 140,382,67,110 }, -4, -46, 2, rect1, rect2, rect3);
	c_kick.SetReverseOffset({3,-42 }, 2);
	c_kick.PushBack({ 769,261, 52,107 }, 10, -42, 2, rect1, rect2, rect3);
	c_kick.loop = false;
	c_kick.speed = 0.05f;
	c_kick.damage = 20;

	//THROWN NOT NEEDED YET

	//thrown.PushBack({ 556,610,71,107 }, 0, -40, 3);
	//thrown.PushBack({ 635,610,102,86 }, 0, 0, 3);
	//thrown.PushBack({ 743,610,120,43 }, 0, 0, 3);
	//thrown.PushBack({ 905,610,56,106 }, 0, 0, 3);
	//thrown.PushBack({ 0,772,67,109 }, 0, 0, 3);
	//thrown.PushBack({ 84,772,72,109 }, 0, 0, 3);
	//thrown.PushBack({ 178,820,121,74 }, 0, 0, 3);
	//thrown.PushBack({ 187,772,122,45 }, 0, 0, 3);
	//thrown.speed = 0.05f;
	//thrown.loop = false; 

	 //WIN
	win.SetReverseOffset({ -17,-60 }, 3);
	win.PushBack({ 419,752,85,129 }, 0, -60, 3);
	win.SetReverseOffset({ -11,-60 }, 3);
	win.PushBack({ 508,752,79,129 }, 0, -60, 3);
	win.SetReverseOffset({ -2,-60 }, 5);
	win.PushBack({ 591,752,71, 129 }, 0, -60, 5);
	win.SetReverseOffset({ -19,-60 }, 5);
	win.PushBack({ 666,752,87 ,129 }, 0, -60, 5);
	win.speed = 0.2f;
	win.loop = false;

	//ULTRAKICK
	ultrakick.SetReverseOffset({ 3, -42 }, 2);
	ultrakick.PushBack({ 769,261, 52,107 }, 10, -42, 2);
	ultrakick.SetReverseOffset({ 6, -46 }, 3);
	ultrakick.PushBack({ 140,382,67,110 }, -5,-46 , 3);
	ultrakick.SetReverseOffset({ -33,-46 }, 3);
	ultrakick.PushBack({ 556,607,103,110 }, 0,-46 , 3);
	ultrakick.SetReverseOffset({ 6, -46 }, 3);
	ultrakick.PushBack({ 140,382,67,110 }, -5,-46 , 3);
	ultrakick.SetReverseOffset({ -40,-43 }, 3);
	ultrakick.PushBack({ 213,382,102,107 }, -1, -43, 3);
	ultrakick.SetReverseOffset({ 6, -46 }, 3);
	ultrakick.PushBack({ 140,382,67,110 }, -5, -46, 3);
	ultrakick.SetReverseOffset({ -33,-46 }, 3);
	ultrakick.PushBack({ 556,607,103,110 }, 0, -46, 3);
	ultrakick.SetReverseOffset({ 6, -46 }, 3);
	ultrakick.PushBack({ 140,382,67,110 }, -5, -46, 3);
	ultrakick.SetReverseOffset({ -40,-43 }, 3);
	ultrakick.PushBack({ 213,382,102,107 }, -1, -43, 3);
	ultrakick.SetReverseOffset({ 6, -46 }, 3);
	ultrakick.PushBack({ 140,382,67,110 }, -5, -46, 3);
	ultrakick.SetReverseOffset({ -33,-46 }, 3);
	ultrakick.PushBack({ 556,607,103,110 }, 0, -46, 3);
	ultrakick.SetReverseOffset({ 6, -46 }, 3);
	ultrakick.PushBack({ 140,382,67,110 }, -5, -46, 3);
	ultrakick.SetReverseOffset({ -40,-43 }, 3);
	ultrakick.PushBack({ 213,382,102,107 }, -1, -43, 3);
	ultrakick.SetReverseOffset({ 6, -46 }, 3);
	ultrakick.PushBack({ 140,382,67,110 }, -5, -46, 3);
	ultrakick.SetReverseOffset({ -33,-46 }, 3);
	ultrakick.PushBack({ 556,607,103,110 }, 0, -46, 3);
	ultrakick.SetReverseOffset({ 6, -46 }, 3);
	ultrakick.PushBack({ 140,382,67,110 }, -5, -46, 3);
	ultrakick.SetReverseOffset({ 15,-45 }, 3);
	ultrakick.PushBack({ 320,382,48,109 }, 5, -45, 3);
	ultrakick.SetReverseOffset({ 16,-45 }, 3);
	ultrakick.PushBack({ 376,382,55,109 }, -4, -45, 3);
	ultrakick.SetReverseOffset({ 18,-46 }, 3);
	ultrakick.PushBack({ 434,382,52,110 }, -3, -46, 3);
	ultrakick.SetReverseOffset({ -37,-44 }, 10);
	ultrakick.PushBack({ 495 ,382,105,108 },-3, -44, 3);
	ultrakick.SetReverseOffset({ 21,-47 }, 3);
	ultrakick.PushBack({ 605,382,63,110 }, -6, -47, 3);
	ultrakick.speed = 0.5f; 
	ultrakick.loop = false;

	//damage reversed completed
	pose_idle_receive_standing_punch_kick_plus_jump_punch.SetReverseOffset({6, -42}, 2);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.PushBack({ 236,261,58,107 },0 ,-42 ,2 );
	pose_idle_receive_standing_punch_kick_plus_jump_punch.SetReverseOffset({10, -42}, 2);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.PushBack({ 299,261,59,107 },-3, -42 , 2);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.SetReverseOffset({10, -42}, 2);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.PushBack({ 364,261,55,107 },0 ,-42 ,2);
	pose_idle_receive_standing_punch_kick_plus_jump_punch.loop = false;
	pose_idle_receive_standing_punch_kick_plus_jump_punch.speed = 0.3f;

	//damage in air
	air_damage.PushBack({ 677,610,93,108 },0 ,0 ,2 );
	air_damage.PushBack({ 772,657,115,60 }, 0, 0,2 );
	air_damage.PushBack({ 892,628,101,89 }, 0,0 ,2 );
	air_damage.PushBack({ 1,772,136,83 }, 0, 0, 2);
	air_damage.PushBack({ 143,785,134,70 }, 0, 0, 2);
	air_damage.PushBack({ 2,881,131,47 }, 0, 0, 2);
	
	//BLOCK
	standing_block.PushBack({338,772,60,110}, -5, -44, 5,rect1,rect2,rect3);
	standing_block.speed = 0.3f;
	standing_block.loop = false;

	//Succesfull block
	exitBlock.PushBack({ 338,772,60,110 }, -5, -44, 5, rect1, rect2, rect3);
	exitBlock.PushBack({ 338,772,60,110 }, -5, -44, 3, rect1, rect2, rect3, {}, {-2,0});
	exitBlock.speed = 0.3f;
	exitBlock.loop = false;


	//Defeat
	defeat.SetReverseOffset({-5, -45}, 3);
	defeat.PushBack({783, 772, 79, 109}, -9, -45, 3);
	defeat.SetReverseOffset({12, -16}, 3);
	defeat.PushBack({864, 801, 49, 80}, 4, -16, 3);
	defeat.SetReverseOffset({-15, -14}, 3);
	defeat.PushBack({918, 803, 78, 78}, 3, -14, 3);
	defeat.SetReverseOffset({-45, 21}, 3);
	defeat.PushBack({769, 881, 108, 44}, 2, 21, 3);
	defeat.speed = 0.2f;
	defeat.loop = false;

	//Recharge
	recharge.SetReverseOffset({ 7, -34 }, 5);
	recharge.PushBack({ 366,149,69,98 }, -10, -34, 5, rect1, rect2, rect3);
	recharge.speed = 0.5f;

	//Combos
	for (int i = 0; i < 30; i++)
	{
		Input_Queue[i].Input = IN_EMPTY;
	}

	FirstInQueue = &Input_Queue[0].Input;
	LastInQueue = &Input_Queue[0].Input;

	//falta win, defeat
}

bool John::Start()
{
	if (player == 1) {
		if (graphics == nullptr)
			graphics = App->textures->Load("Assets/john_sprite_sheet.png");
	}
	else if (player == 2) {
		if (graphics == nullptr)
			graphics = App->textures->Load("Assets/john_sprite_sheet_2.png");
	}
	if (punchfx == nullptr)
		punchfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_punch.wav");
	if (kickfx == nullptr)
		kickfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kick.wav");
	if (kooukenfx == nullptr)
		kooukenfx = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_kooken.wav");
	if (jumpfx == nullptr)
		jumpfx = App->audio->Load_effects("Assets/Audio/FX/Jump.wav");
	if (dmg == nullptr)
		dmg = App->audio->Load_effects("Assets/Audio/FX/ryo/Ryo_dmg.wav");

	//Hadouken 
	//AddCombo(6, IN_KOOU_KEN, IN_CROUCH_UP, IN_UNKNOWN, IN_RIGHT_DOWN, IN_RIGHT_UP, IN_UNKNOWN, IN_PUNCH);
	//AddCombo(4, IN_KOOU_KEN, IN_CROUCH_UP, IN_RIGHT_DOWN, IN_RIGHT_UP, IN_PUNCH);
	//AddCombo(5, IN_KOOU_KEN, IN_CROUCH_UP, IN_UNKNOWN, IN_RIGHT_DOWN, IN_RIGHT_UP, IN_PUNCH);
	AddCombo(5, IN_KOOU_KEN, IN_CROUCH_DOWN, IN_UNKNOWN, IN_RIGHT_DOWN, IN_UNKNOWN, IN_PUNCH);
	AddCombo(4, IN_KOOU_KEN, IN_CROUCH_DOWN, IN_RIGHT_DOWN, IN_UNKNOWN, IN_PUNCH);
	AddCombo(4, IN_KOOU_KEN, IN_UNKNOWN, IN_CROUCH_DOWN, IN_RIGHT_DOWN, IN_PUNCH);
	AddCombo(6, IN_KOOU_KEN, IN_UNKNOWN,IN_CROUCH_DOWN, IN_RIGHT_DOWN, IN_LEFT_DOWN ,IN_UNKNOWN, IN_PUNCH);


	return true;
}

bool John::CleanUp()
{
	if (graphics != nullptr)
	{
		App->textures->Unload(graphics);
		graphics = nullptr;
	}
	if (punchfx != nullptr)
	{
		App->audio->Unload_effects(punchfx);
		punchfx = nullptr;
	}
	if (kickfx != nullptr)
	{
		App->audio->Unload_effects(kickfx);
		kickfx = nullptr;
	}
	if (kooukenfx != nullptr)
	{
		App->audio->Unload_effects(kooukenfx);
		kooukenfx = nullptr;
	}
	if (jumpfx != nullptr)
	{
		App->audio->Unload_effects(jumpfx);
		jumpfx = nullptr;
	}
	if (dmg != nullptr)
	{
		App->audio->Unload_effects(dmg);
		dmg = nullptr;
	}
	for (int i = 0; i < SpecialLenght; i++)
	{
		if (PlayerSpecialMoves[i] != nullptr)
			delete PlayerSpecialMoves[i];
	}

	return true;
}



void John::AddCombo(int NumberOfInputs, inputs EndState, inputs Inp...)
{

	va_list args;
	va_start(args, Inp);

	Special_Move *Combo = new Special_Move();

	Combo->InputsToCompleteMovement[0] = Inp;
	for (int i = 1; i < NumberOfInputs; i++)
	{
		Combo->InputsToCompleteMovement[i] = va_arg(args, inputs);;
	}

	Combo->MovementLenght = NumberOfInputs;
	Combo->Completed_Input = EndState;
	PlayerSpecialMoves[SpecialLenght] = Combo;
	SpecialLenght++;

	va_end(args);

}

void John::AddInput(inputs Inp, float time)
{

	//Is new Input diferent from last one, check to avoid multiframed input
	if (Input_Queue[TopPosition - 1].Input != Inp)
	{
		//Then add input to queue
		//TopPosition is now greater
		//TODO: Check is queue is full to start decreasing inputs
		if (TopPosition + 1 <= 30)
		{

			Input_Queue[TopPosition].Input = Inp;
			Input_Queue[TopPosition].Time = time;
			LastInQueue = &Input_Queue[TopPosition].Input;

			if (TopPosition + 1 == IN_EMPTY)
			{
				FirstInQueue = &Input_Queue[0].Input;
			}
			else
			{
				FirstInQueue = &Input_Queue[TopPosition + 1].Input;
			}

			//SDL_Log("%d Num: %d", TopPosition, Input_Queue[TopPosition]);
			TopPosition++;




		}
		else
		{
			TopPosition = 0;
			Input_Queue[TopPosition].Input = Inp;
			Input_Queue[TopPosition].Time = time;
			LastInQueue = &Input_Queue[TopPosition].Input;
			TopPosition++;
		}

		LOG("\nA");

	}

}

inputs John::CheckCombos()
{

	int Check = TopPosition;
	int Completed = 0;
	//CheckAllCombos
	for (int i = 0; i < SpecialLenght; i++)
	{

		Check = TopPosition;
		Completed = 0;
		//Check All inputs that form the combo
		for (int j = PlayerSpecialMoves[i]->MovementLenght - 1; j >= 0; j--)
		{

			//Next move wont top out the queue
			if (Check - 1 >= 0)
			{
				if (Input_Queue[Check - 1].Input == PlayerSpecialMoves[i]->InputsToCompleteMovement[j])
				{
					if(Input_Queue[Check - 1].Time - Input_Queue[Check - 2].Time <= 400)
						Completed++;
				}

				Check--;
			}
			if (Check - 1 < 0)
			{
				Check = 30;
			}




		}

		if (Completed == PlayerSpecialMoves[i]->MovementLenght)
		{
			LOG("\n Combo Completed");

			return PlayerSpecialMoves[i]->Completed_Input;
		}

	}

	return IN_EMPTY;

}