#ifndef _MODULECHARACTERSELECTION_
#define _MODULECHARACTERSELECTION_

#include "Application.h"
#include "Globals.h"
#include "Animation.h"
#include "Module.h"
#include "ModuleTextures.h"

class ModuleScreenSelection : public Module {
public:
	ModuleScreenSelection();
	~ModuleScreenSelection();
	bool Init();
	bool CleanUp();
	update_status Update();
	bool Start();

	SDL_Texture* selector1;
	SDL_Texture* selector2;
};

#endif // !_MODULECHARACTERSELECTION_
