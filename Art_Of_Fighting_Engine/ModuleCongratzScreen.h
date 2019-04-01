#ifndef _ModuleCongratzScreen_H_
#define _ModuleCongratzScreen_H_

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

class ModuleCongratzScreen :public Module {
public:
	ModuleCongratzScreen();
	~ModuleCongratzScreen();

	bool Start();
	update_status Update();
	bool CleanUp();
public:
	SDL_Texture* graphics = nullptr;
	RectSprites rect_background;

};

#endif