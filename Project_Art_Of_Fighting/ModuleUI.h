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
	SDL_Texture* win_points;
	SDL_Texture* TimerTexture;
	int timer;
	float timer_float;
	int tick1 = 0, tick2 = 0;
	char* time;
	Animation winpoint;
	Animation* current_animation;
	int counter1 = 0, counter2 = 0;
};

#endif // __MODULESCENEKEN_H__