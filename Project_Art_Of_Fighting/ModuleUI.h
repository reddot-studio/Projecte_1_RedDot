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

	SDL_Texture* Player1;
	SDL_Texture* Player_1_Health;
	SDL_Texture* Player_1_Spirit;

	SDL_Texture* Player2;
	SDL_Texture* Player_2_Health;
	SDL_Texture* Player_2_Spirit;

};

#endif // __MODULESCENEKEN_H__