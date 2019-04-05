#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 14

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneTodo;
class ModuleSceneJohn;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleWelcomeScreen;
class ModuleAudio;
class ModuleCongratzScreen;
class ModuleParticles;
class ModuleDebug;
class ModuleCollision;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneTodo* scene_todo;
	ModuleSceneJohn* scene_john;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleWelcomeScreen* scene_welcome;
	ModuleAudio* audio;
	ModuleCongratzScreen* scene_congratz;
	ModuleParticles* particles;
	ModuleDebug* debug;
	ModuleCollision* collision;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__