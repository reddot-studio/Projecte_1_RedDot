#ifndef __ModulePlayer1_H__
#define __ModulePlayer1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"
#include"Application.h"
#include"ModuleFadeToBlack.h"
#include"ModuleCongratzScreen.h"
#include"ModuleSceneJohn.h"
#include"ModuleSceneTodo.h"
#include"ModulePlayer_2.h"

struct SDL_Texture;
struct Mix_Chunk;


class ModulePlayer_1 : public Module
{
public:
	ModulePlayer_1();
	~ModulePlayer_1();
	int num = 100;
	bool Start();
	update_status Update();
	bool CleanUp() override;

	void OnCollision(Collider*, Collider*);
	player_state ControlStates();
	void states(int speed);

public:
	Mix_Chunk *punchfx = NULL;
	Mix_Chunk *kickfx = NULL;
	Mix_Chunk *kooukenfx = NULL;
	Mix_Chunk *jumpfx = NULL;


	Collider * player_collider = nullptr;

	player_state current_state = ST_UNKNOWN;

	inputs last_input = IN_UNKNOWN;
	

	Animation* current_animation = nullptr;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	SDL_Texture* pivotTexture = nullptr;

	RectSprites pivotRect;
	iPoint offset;
	iPoint pivot_player;

	//Basic Moves
	Animation idle;
	Animation idle_player2;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;
	Animation jump;
	Animation fall;
	Animation recover;
	Animation jumpkick;
	Animation jumppunch;
	Animation jump_forward; 
	Animation jump_backward;
	Animation win;
	Animation defeat;
	Animation starhit;
	Animation impactfloor;
	Animation vomit;
	Animation blood;
			
	Animation pose_idle_receive_standing_punch_kick_plus_jump_punch;
	Animation pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch;
	Animation pose_idle_receive_crouch_kick;
	Animation pose_idle_receive_crouch_punch;

	Animation pose_crouch_receive_standing_crouch_kick; 
	Animation pose_crouch_receive_crouch_punch; 



	Animation pose_jump_receive_dmg; //Not sure for prototype

	
	

	//Crouch Moves
	Animation crouch;
	Animation crouch_punch;
	Animation crouch_kick;

	//Special moves
	Animation koouKen;

	SDL_Rect ActiveScene;
	int timer;
	int p2_win = 0;
	bool win_check = false;
	bool isJumping = false;

	//bool BackColision, FrontColision;
	Collider* CurrentColider = nullptr;
	Collider* HitCollider = nullptr;
	Collider* HurtColliders[3];


	//PlayerStats
	int Player_Health_Value_p1;

	void Deal_Damage(ModulePlayer_2& Enemy, int AttackDamage);

	int Side;
	SDL_Texture* Player_texture;
	SDL_Texture* Player_Health_BG;
	SDL_Texture* Player_Health_BG_Empty;
	SDL_Texture* Player_Health;
	SDL_Texture* Player_Spirit;
	int speed;

	int tick1 = 0, tick2 = 0;
};

#endif