#ifndef __MODULESCENETODO_H__
#define __MODULESCENETODO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;
struct Mix_Music;
class ModuleSceneTodo : public Module
{
public:
	ModuleSceneTodo();
	~ModuleSceneTodo();
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Mix_Music * todo_music = nullptr;
	SDL_Texture* graphics = nullptr;
	RectSprites rect_background;
};

#endif // __MODULESCENEKEN_H__