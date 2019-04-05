#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;
class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();
	int num = 100;
	bool Start();
	update_status Update();
	bool CleanUp() override;

public:
	Mix_Chunk *punchfx = NULL;
	Mix_Chunk *kickfx = NULL;
	Mix_Chunk *kooukenfx = NULL;
	Mix_Chunk *jumpfx = NULL;
	enum player_state
	{
		IDLE = 0,
		ATTACK,
		CAN_MOVE,
		JUMP,
		CROUCH,
	};

	Collider * player_collider = nullptr;

	player_state state = IDLE;
	Animation* current_animation;
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
};

#endif