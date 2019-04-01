#ifndef _ModuleWelcomeScreen_H_
#define _ModuleWelcomeScreen_H_

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
struct SDL_Texture;

class ModuleWelcomeScreen : public Module {
public:
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();

	bool Start();
	update_status Update();

	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	RectSprites rect_background;
	Animation coin;
};



#endif
