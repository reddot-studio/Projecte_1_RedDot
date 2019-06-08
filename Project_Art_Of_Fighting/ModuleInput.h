#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_scancode.h"
#include "SDL/include/SDL_gamecontroller.h"
#include "SDL/include/SDL_haptic.h"

typedef unsigned char Uint8;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	void inputGamepad(SDL_GameController *);

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	const Uint8 *keyboard = nullptr;
	SDL_GameController *controller[2];

	
	int effect_id;

	bool Paused = false;

	bool jump = true;

	float deathZone = 0.2f;
	float jumpZone = 0.7f;
	float crouchZone = 0.8f;

	const float GetHorizontalAxis();
	const float GetVerticalAxis();

	void StartEffect();

	key_state keyboard_state[285];
	GamePad gamepad;
	SDL_Haptic* haptic = nullptr;

	bool joystick_up;
	bool joystick_down;
	bool joystick_left;
	bool joystick_right;

	bool joystick_left_repeat;
	bool joystick_right_repeat;



};

#endif // __ModuleInput_H__