#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "SDL\include\SDL_scancode.h"
#include "p2Qeue.h"


typedef unsigned char Uint8;
enum ryo_inputs;

class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	bool external_input(p2Qeue<ryo_inputs>& inputs);

public:
	const Uint8 *keyboard = nullptr;

	key_state keyboard_state[285];

};

#endif // __ModuleInput_H__