#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2Qeue.h"

struct SDL_Texture;
struct Mix_Chunk;
enum ryo_states
{
	ST_UNKNOWN,

	ST_IDLE,
	ST_WALK_FORWARD,
	ST_WALK_BACKWARD,
	ST_JUMP_NEUTRAL,
	ST_JUMP_FORWARD,
	ST_JUMP_BACKWARD,
	ST_CROUCH,
	ST_PUNCH_STANDING,
	ST_PUNCH_NEUTRAL_JUMP,
	ST_PUNCH_FORWARD_JUMP,
	ST_PUNCH_BACKWARD_JUMP,
	ST_PUNCH_CROUCH
};

enum ryo_inputs
{
	IN_LEFT_DOWN,
	IN_LEFT_UP,
	IN_RIGHT_DOWN,
	IN_RIGHT_UP,
	IN_LEFT_AND_RIGHT,
	IN_JUMP,
	IN_CROUCH_UP,
	IN_CROUCH_DOWN,
	IN_JUMP_AND_CROUCH,
	IN_X,
	IN_JUMP_FINISH,
	IN_PUNCH_FINISH
};

class ModulePlayer : public Module
{
public:


public:
	ModulePlayer();
	~ModulePlayer();
	int num = 100;
	bool Start();
	update_status PreUpdate() override;
	update_status Update();
	bool CleanUp() override;

	bool external_input(p2Qeue<ryo_inputs>& inputs);

	ryo_states process_fsm(p2Qeue<ryo_inputs>& inputs);

	void OnCollision(Collider*, Collider*);

public:
	Mix_Chunk *punchfx = NULL;
	Mix_Chunk *kickfx = NULL;
	Mix_Chunk *kooukenfx = NULL;
	Mix_Chunk *jumpfx = NULL;


	Collider * player_collider = nullptr;

	ryo_states state = ST_IDLE;
	ryo_states current_state;
	p2Qeue<ryo_inputs> inputs;

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

	//Crouch Moves
	Animation crouch;
	Animation crouch_punch;
	Animation crouch_kick;

	//Special moves
	Animation koouKen;

	SDL_Rect ActiveScene;
	int timer;

	bool BackColision, FrontColision;
	Collider* CurrentColider;


};

#endif