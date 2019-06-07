#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"

typedef unsigned char Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	const Uint8 *keyboard = nullptr;
	Uint8 pad;
	SDL_GameController *controller[2];

	
	int effect_id;

	bool Paused = false;

	bool jump = true;

	float deathZone = 0.1f;
	float jumpZone = 0.5f;
	float crouchZone = 0.5f;

	const float GetHorizontalAxis();
	const float GetVerticalAxis();

	void StartEffect();

	key_state keyboard_state[285];
	GamePad pad_state[285];
	SDL_GameControllerButton pads_button[16];

};

#endif // __ModuleInput_H__