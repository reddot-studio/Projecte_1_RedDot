#include "ModuleScene.h"
#include "SceneTodo.h"


ModuleScene::ModuleScene()
{

}

bool ModuleScene::Start()
{
	if (currentScene == nullptr) {
		currentScene = new SceneTodo;
	}
	currentScene->Start();
	App->player1->Enable();
	App->player2->Enable();
	App->sceneUI->Enable();
	return true;
}

update_status ModuleScene::Update()
{
	if ((App->render->Blit(currentScene->graphics, 0, 0, &currentScene->rect_background)) == false)
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
		return update_status::UPDATE_STOP;
	}
	
	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	if (currentScene != nullptr) {
		App->audio->Unload_music(currentScene->todo_music);
		App->audio->Unload_effects(currentScene->fightfx);
		App->textures->Unload(currentScene->graphics);
	}
	App->player1->Disable();
	App->player2->Disable();
	App->sceneUI->Disable();
	if(currentScene != nullptr)
	delete currentScene;
	currentScene = nullptr;
	return true;
}
