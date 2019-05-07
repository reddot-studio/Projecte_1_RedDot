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
	Animation rojoParpadeo;
	Animation rotuloVerde;
	Animation radio;
	Animation szechu;
	Animation morado;
public:
	ModuleSceneJohn();
	~ModuleSceneJohn();
	Mix_Music* lee_music;
	bool Start() override;
	update_status Update()override;
	bool CleanUp();

	Collider* BackPanel;
	Collider* FrontPanel;

};

#endif

