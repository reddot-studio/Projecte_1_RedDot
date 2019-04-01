#ifndef __MODULESCENEJOHN_H__
#define __MODULESCENEJOHN_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL_rect.h"
#include "SDL_image/include/SDL_image.h"
#include "Animation.h"

class ModuleSceneJohn : public Module {
public:
	SDL_Texture * graphics = nullptr;
	RectSprites rect_background;
	Animation idle;
	Animation soldiers;
	Animation couple;
	Animation soldierduo;
public:
	ModuleSceneJohn();
	~ModuleSceneJohn();

	bool Start() override;
	update_status Update()override;
	bool CleanUp();
};

#endif

