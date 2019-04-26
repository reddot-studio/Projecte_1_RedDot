#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
struct Mix_Music;

class ModuleUI : public Module
{
public:
	ModuleUI();
	~ModuleUI();
	bool Start();
	update_status Update();
	bool CleanUp();


public:


	RectSprites RendPosition;

	SDL_Texture* TimerTexture;
	int timer;
	float timer_float;
	int tick1 = 0, tick2 = 0;
	char* time;

};

#endif // __MODULESCENEKEN_H__