#ifndef __MODULESCENE_H__
#define __MODULESCENE_H__

#include "Module.h"
#include "Globals.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleRender.h"
#include "Scene.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleUI.h"

struct Mix_Music;
struct SDL_Texture;
struct SDL_Rect;
struct Mix_Chunk;



class ModuleScene : public Module {
public:


	ModuleScene();
	~ModuleScene() {};

	Mix_Music* lee_music;
	bool Start() override;
	update_status Update()override;
	bool CleanUp();

	Collider* BackPanel;
	Collider* FrontPanel;

	Scene * currentScene = nullptr;
};

#endif

