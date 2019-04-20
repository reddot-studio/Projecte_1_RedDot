#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

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

struct SDL_Texture;
struct Mix_Chunk;

enum player_state
{	ST_UNKNOWN,
	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,
	ST_STANDING_PUNCH,
	ST_STANDING_KICK,
	ST_NEUTRAL_JUMP,
	ST_NEUTRAL_JUMP_PUNCH,
	ST_NEUTRAL_JUMP_KICK,
	ST_FORWARD_JUMP,
	ST_BACKWARD_JUMP,
	ST_FORWARD_JUMP_PUNCH,
	ST_FORWARD_JUMP_KICK,
	ST_BACKWARD_JUMP_PUNCH,
	ST_BACKWARD_JUMP_KICK,
	ST_KOOU_KEN,
	ST_FALL,
	ST_FORWARD_FALL,
	ST_BACKWARD_FALL,
	ST_RECOVER,
	ST_CROUCH,
};

enum inputs
{
	IN_UNKNOWN,
	IN_LEFT_UP,
	IN_LEFT_DOWN,
	IN_RIGHT_UP,
	IN_RIGHT_DOWN,
	IN_JUMP_DOWN,
	IN_PUNCH,
	IN_KICK,
	IN_KOOU_KEN,
	IN_JUMP_FINISH,
	IN_ATTACK_FINISH,
	IN_RECOVER_FINISH,
	IN_RECOVER,
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(int num);
	~ModulePlayer();
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
	

	//Crouch Moves
	Animation crouch;
	Animation crouch_punch;
	Animation crouch_kick;

	//Special moves
	Animation koouKen;

	SDL_Rect ActiveScene;
	int timer;

	//bool BackColision, FrontColision;
	Collider* CurrentColider;

	//PlayerStats
	int Player_Health_Value;

	void Deal_Damage(ModulePlayer& Enemy, int AttackDamage)
	{
		if (Enemy.Player_Health_Value - AttackDamage <= 0) 
		{
			LOG("\n Someone died");
			Enemy.Player_Health_Value = 0;

			Module *CurrentScene = nullptr;

			if (App->scene_todo->IsEnabled())
				CurrentScene = App->scene_todo;
			if (App->scene_john->IsEnabled())
				CurrentScene = App->scene_john;

			App->fade->FadeToBlack(CurrentScene, App->scene_congratz);

		}
		else
		{
			Enemy.Player_Health_Value -= AttackDamage;
		}
	}

	int PlayerNumber;
	SDL_Texture* Player_texture;
	SDL_Texture* Player_Health_BG;
	SDL_Texture* Player_Health_BG_Empty;
	SDL_Texture* Player_Health;
	SDL_Texture* Player_Spirit;

};

#endif