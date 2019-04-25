#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneTodo.h"
#include "ModuleSceneJohn.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleCongratzScreen.h"
#include "ModuleParticles.h"
#include "ModuleDebug.h"
#include "ModuleAudio.h"
#include "ModuleCollision.h"
#include"ModuleUI.h"
#include "ModuleFonts.h"


Application::Application()
{
	int num = 0;
	modules[num++] = window = new ModuleWindow();
	modules[num++] = render = new ModuleRender();
	modules[num++] = input = new ModuleInput();
	modules[num++] = audio = new ModuleAudio();
	modules[num++] = fonts = new ModuleFonts();
	modules[num++] = textures = new ModuleTextures();
	modules[num++] = scene_congratz = new ModuleCongratzScreen();
	modules[num++] = scene_john = new ModuleSceneJohn();
	modules[num++] = scene_todo = new ModuleSceneTodo();
	modules[num++] = player1 = new ModulePlayer(1);
	modules[num++] = player2 = new ModulePlayer(2);
	modules[num++] = particles = new ModuleParticles();
	modules[num++] = fade = new ModuleFadeToBlack();
	modules[num++] = scene_welcome = new ModuleWelcomeScreen();
	modules[num++] = debug = new ModuleDebug();
	modules[num++] = collision = new ModuleCollision();
	modules[num++] = sceneUI = new ModuleUI();
	
	
}	

Application::~Application()
{
	for(int i = NUM_MODULES-1 ; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;

	//Disable Player2 for future implementation
	//App->player2->Disable();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;
	return ret;
}