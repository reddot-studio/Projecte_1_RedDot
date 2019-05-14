#ifndef _MODULECHARACTERSELECTION_
#define _MODULECHARACTERSELECTION_

#include "Application.h"
#include "Globals.h"
#include "Animation.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"

class ModuleScreenSelection : public Module {
public:
	ModuleScreenSelection();
	~ModuleScreenSelection();
	bool Init();
	bool CleanUp();
	update_status Update();
	bool Start();

	SDL_Rect back;
	SDL_Renderer* background;
	SDL_Texture* graphics;
	SDL_Texture* selector1;
	SDL_Texture* selector2;
};

#endif // !_MODULECHARACTERSELECTION_
