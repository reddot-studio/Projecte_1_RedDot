#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "ModuleRender.h"

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
	bool left = false;
	bool right = false;
	const Uint8 *keyboard = nullptr;
};

#endif // __ModuleInput_H__