#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

struct SDL_Texture;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp() override;

public:

	enum player_state
	{
		IDLE = 1,
		ATTACK,
		CAN_MOVE,
		JUMP,
	};

	player_state state = IDLE;
	Animation* current_animation;
	SDL_Texture* graphics = nullptr;
	iPoint position;

	//Basic Moves
	Animation idle;
	Animation forward;
	Animation backward;
	Animation punch;
	Animation kick;
	Animation jump;

	//Special moves
	Animation koouKen;
};

#endif