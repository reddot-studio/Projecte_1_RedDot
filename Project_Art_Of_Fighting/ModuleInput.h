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
	SDL_GameController *controller = nullptr;
	bool Paused = false;
	bool leftAxis = false;
	bool rightAxis = false;

	key_state keyboard_state[285];

};

#endif // __ModuleInput_H__