#include "ModuleNeoGeo.h"


ModuleNeoGeo::ModuleNeoGeo() {
	int x = 0, y = 0, w = 304, h = 224, i = 0;
	for (; i <= 97; i++) {
		neogeo.PushBack({ x,y,w,h });
		if (x <= (1824)) {
			x += 304;
		}
		else {
			y += 224;
			x = 0;
		}
	}
	neogeo.speed = 0.35f;
	neogeo.loop = false;
	final_neogeo.PushBack({ 304,2688,304,224 });
	//BUG
	current_animation = &neogeo;
}

ModuleNeoGeo::~ModuleNeoGeo() {

}

bool ModuleNeoGeo::Init() {
	App->debug->Disable();
	App->scene_john->Disable();
	App->scene_todo->Disable();
	App->scene_congratz->Disable();
	App->character_selection->Disable();
	App->sceneUI->Disable();
	App->scene_welcome->Disable();
	LOG("Loading intro scene");
	if ((graphics = App->textures->Load("Assets/neo_geo_intro.png")) == NULL)
	{
		SDL_Log("Could not load image from path! SDL_Error: %s", SDL_GetError());
		return false;
	}

	return true;
}

bool ModuleNeoGeo::Start() {
	return true;
}

update_status ModuleNeoGeo::Update() {
	if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() - 1) {
		current_animation = &final_neogeo;
	}
	App->render->Blit(graphics, (SCREEN_WIDTH/2)-160, (SCREEN_HEIGHT/2)-112, &current_animation->GetCurrentFrame());

	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN) {
		App->fade->FadeToBlack(App->neogeo, App->scene_welcome);
	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleNeoGeo::CleanUp() {
	App->textures->Unload(graphics);
	return true;
}