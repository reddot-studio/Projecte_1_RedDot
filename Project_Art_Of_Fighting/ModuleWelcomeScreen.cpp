#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneTodo.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleSceneJohn.h"
#include "ModuleSceneTodo.h"
#include "ModuleCongratzScreen.h"
#include "ModuleFadeToBlack.h"
#include "ModuleWelcomeScreen.h"
#include"ModuleUI.h"
#include "SDL_mixer/include/SDL_mixer.h"
#include "ModuleFonts.h"



ModuleWelcomeScreen::ModuleWelcomeScreen()
{
	//logo transition//
	//c1
	logo_transition.PushBack({ 0,0,309,232 });
	logo_transition.PushBack({ 0,232,309,232 });
	logo_transition.PushBack({ 0,464,309,232 });
	logo_transition.PushBack({ 0,696,309,232 });
	logo_transition.PushBack({ 0,928,309,232 });
	logo_transition.PushBack({ 0,1160,309,232 });
	logo_transition.PushBack({ 0,1392,309,232 });
	logo_transition.PushBack({ 0,1624,309,232 });
	//c2
	logo_transition.PushBack({ 309,0,309,232 });
	logo_transition.PushBack({ 309,232,309,232 });
	logo_transition.PushBack({ 309,464,309,232 });
	logo_transition.PushBack({ 309,696,309,232 });
	logo_transition.PushBack({ 309,928,309,232 });
	logo_transition.PushBack({ 309,1160,309,232 });
	logo_transition.PushBack({ 309,1392,309,232 });
	logo_transition.PushBack({ 309,1624,309,232 });
	//c3
	logo_transition.PushBack({ 618,0,309,232 });
	logo_transition.PushBack({ 618,232,309,232 });
	logo_transition.PushBack({ 618,464,309,232 });
	logo_transition.PushBack({ 618,696,309,232 });
	logo_transition.PushBack({ 618,928,309,232 });
	logo_transition.PushBack({ 618,1160,309,232 });
	logo_transition.PushBack({ 618,1392,309,232 });
	logo_transition.PushBack({ 618,1624,309,232 });
	logo_transition.PushBack({ 618,1624,309,232 });
	logo_transition.PushBack({ 618,1624,309,232 });

	//c4
	logo_transition.PushBack({ 927,0,309,232 });
	logo_transition.PushBack({ 927,232,309,232 });
	logo_transition.PushBack({ 927,464,309,232 });
	logo_transition.PushBack({ 927,696,309,232 });
	logo_transition.PushBack({ 927,928,309,232 });
	logo_transition.PushBack({ 927,1160,309,232 });
	logo_transition.PushBack({ 927,1392,309,232 });
	logo_transition.PushBack({ 927,1624,309,232 });
	//c5
	logo_transition.PushBack({ 1236,0,309,232 });
	logo_transition.PushBack({ 1236,232,309,232 });
	logo_transition.PushBack({ 1236,464,309,232 });
	logo_transition.PushBack({ 1236,696,309,232 });
	logo_transition.PushBack({ 1236,928,309,232 });
	logo_transition.PushBack({ 1236,1160,309,232 });
	logo_transition.PushBack({ 1236,1392,309,232 });
	logo_transition.PushBack({ 1236,1624,309,232  });
	//c6
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.PushBack({ 1545,0,309,232 });
	logo_transition.speed = 0.4f;

	//Final_logo
	final_logo.PushBack({ 1609,244,216,130 });


	insert_coin.PushBack({ 1574,1100,140,10 });
	insert_coin.PushBack({ 1574,1133,140,10 });
	insert_coin.speed = 0.07f;
	

	snk.rect = { 1547,1141,77,25 };

	//TODO 1 WELCOMESCR: CREATE ANIMATION FOR BLACK RECT
	black.rect = { 100,150,120,10 };
	current_animation = &logo_transition;
}

ModuleWelcomeScreen::~ModuleWelcomeScreen()
{}

bool ModuleWelcomeScreen::Init()
{
	App->scene_john->Disable();
	App->scene_todo->Disable();
	App->scene_congratz->Disable();
	App->sceneUI->Disable();
	return true;
}

bool ModuleWelcomeScreen::Start()
{

	LOG("Loading intro scene");
	if ((graphics = App->textures->Load("Assets/WelcomeScreen.png")) == NULL)
	{
		SDL_Log("Could not load image from path! SDL_Error: %s", SDL_GetError());
		return false;
	}
	start_music = App->audio->Load_music("Assets/Audio/041xRyukoh-no Theme.ogg");
	App->audio->Play_music(start_music);

	//Load fonts
	App->fonts->Load("Assets/fonts/small_orange_font.png", " abcdefghiklmnoprstuwy!.0123456789", 1, 8, 8, 34);

	App->player1->Disable();
	App->player2->Disable();

	return true;
}


update_status ModuleWelcomeScreen::Update()
{

	if (current_animation->GetCurrentFramePos() == current_animation->GetLastFrame() -1)
	{
		finish_animation = 1;
		current_animation = &final_logo;
	}
	else
	{
		App->render->Blit(graphics, 25, 0, &current_animation->GetCurrentFrame());
	}
	
	if (finish_animation == 1) {
		App->render->Blit(graphics, 60, 180, &snk);

		App->render->Blit(graphics, 89, 12, &current_animation->GetCurrentFrame());
		
		App->fonts->BlitText(61, 205, 0, "snk home entertainment, inc.!1992");
		App->fonts->BlitText(130, 150, 0, "push start button");
		App->render->Blit(graphics, 130, 150, &insert_coin.GetCurrentFrame());
	}


	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_welcome, App->scene_todo);
		App->input->Enable();
	}


	if (App->input->keyboard_state[SDL_SCANCODE_0] == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_welcome, App->scene_congratz);
	}
	return update_status::UPDATE_CONTINUE;
}


bool ModuleWelcomeScreen::CleanUp()
{
	App->audio->Unload_music(start_music);
	App->textures->Unload(graphics);
	
	App->fonts->UnLoad(0);

	LOG("Unloading welcome scene");
	return true;
}