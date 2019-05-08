#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Animation.h"

struct SDL_Texture;
struct Mix_Chunk;

class Character
{
public:
	Character();
	~Character() {};
	virtual bool Start() { return true; };
	virtual bool CleanUp() { return true; };

public:

	int player;

	bool isBlocking = false;

	int specialDmg;
	//Basic moves
	Animation idle;
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

	Animation pose_idle_receive_standing_punch_kick_plus_jump_punch;
	Animation pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch;
	Animation pose_idle_receive_crouch_kick;
	Animation pose_idle_receive_crouch_punch;

	Animation pose_crouch_receive_standing_crouch_kick;
	Animation pose_crouch_receive_crouch_punch;

	Animation exitBlock;

	Animation pose_jump_receive_dmg; //Not sure for prototype

	//Crouch Moves
	Animation crouch;
	Animation crouch_punch;
	Animation crouch_kick;

	//Special moves
	Animation koouKen;

	//Blocking moves
	Animation standing_block;
	Animation crouch_block;

	//Textures
	SDL_Texture* graphics = nullptr;

	Mix_Chunk *punchfx = NULL;
	Mix_Chunk *kickfx = NULL;
	Mix_Chunk *kooukenfx = NULL;
	Mix_Chunk *jumpfx = NULL;
	Mix_Chunk *dmg = NULL;


};

#endif // !__CHARACTER_H__
