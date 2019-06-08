#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "Character.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "Animation.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "Special_Move.h"

struct SDL_Texture;
struct Mix_Chunk;
class Special_Move;

class Character
{
public:
	Character() {};
	~Character() {};
	virtual bool Start() = 0;
	virtual bool CleanUp() = 0;

public:

	int player;
	Characters characterType;

	bool isBlocking = false;

	int colliderOffsetX;

	virtual void AddInput(inputs, float) = 0;
	virtual inputs CheckCombos() = 0;
	virtual void AddCombo(int NumberOfInputs, inputs EndState, inputs Inp...) = 0;

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
	Animation taunt;
	Animation thrown;
	Animation recharge;
	Animation ultrakick;
	Animation pose_idle_receive_standing_punch_kick_plus_jump_punch;
	Animation pose_idle_receive_jump_kick_plus_crouch_receive_jump_kick_punch;
	Animation pose_idle_receive_crouch_kick;
	Animation air_damage;

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

	//Strong Atacks
	Animation c_punch;
	Animation c_kick;

	//Textures
	SDL_Texture* graphics = nullptr;

	Mix_Chunk *punchfx = NULL;
	Mix_Chunk *kickfx = NULL;
	Mix_Chunk *kooukenfx = NULL;
	Mix_Chunk *jumpfx = NULL;
	Mix_Chunk *dmg = NULL;
	Mix_Chunk *tauntfx = NULL;


};

#endif // !__CHARACTER_H__
