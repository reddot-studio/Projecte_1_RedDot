#ifndef __MODULESCENEJOHN_H__
#define __MODULESCENEJOHN_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct Mix_Music;
struct SDL_Texture;
struct SDL_Rect;

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
	Mix_Music* john_music;
	bool Start() override;
	update_status Update()override;
	bool CleanUp();
};

#endif

