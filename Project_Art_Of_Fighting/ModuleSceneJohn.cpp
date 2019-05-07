#include "Globals.h"
#include "Application.h"
#include "ModuleSceneJohn.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleCongratzScreen.h"
#include"ModuleCollision.h"
#include"ModuleUI.h"
#include "SDL/include/SDL.h"


// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneJohn::ModuleSceneJohn()
{
	//background//
		rect_background.rect.w = 557;
		rect_background.rect.h = 225;
		rect_background.rect.x = 0;
		rect_background.rect.y = 0;

	//rojo parpadeo//
	rojoParpadeo.PushBack({ 174, 224, 24, 32 });
	rojoParpadeo.PushBack({ 198,224,24,32 });
	rojoParpadeo.speed = 0.2f;


	//rotulo verde//
	rotuloVerde.PushBack({ 113,232,119,94 });
	rotuloVerde.PushBack({ 231,232,119,94 });
	rotuloVerde.PushBack({ 349,232,119,94 });
	rotuloVerde.PushBack({ 467,232,119,94 });
	rotuloVerde.PushBack({ 585,232,119,94 });
	rotuloVerde.PushBack({ 703,232,119,94 });
	rotuloVerde.PushBack({ 821,232,119,94 });
	rotuloVerde.speed = 0.2f;

	//radio//
	radio.PushBack({ 10,236,45,99 });
	radio.PushBack({ 56,236,45,99 });
	radio.speed = 0.2f;

	//szechu//
	szechu.PushBack({ 578,354,88,97 });
	szechu.PushBack({ 578,460,88,97 });
	szechu.speed = 0.2f;

	//Morado//
	morado.PushBack({ 50,274,50,43 },0,0,5);
	morado.PushBack({  0,274,50,43 }, 0, 0, 5);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 5);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 5);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 5);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 15);
	morado.speed = 0.2f;

}

ModuleSceneJohn::~ModuleSceneJohn()
{}


bool ModuleSceneJohn::Start()
{

	LOG("Loading lee scene");
	lee_music = App->audio->Load_music("Assets/Audio/038xKoukuu Bokaan!.ogg");
	if ((graphics = App->textures->Load("Assets/ChinaTown.png")) == NULL)
	{
		SDL_Log("Unable to load texture from path: /guardian.png");
		return false;
	}
	App->audio->Play_music(lee_music);

	//Screen Limits
	//BackPanel = App->collision->AddCollider({ { 0,0,25, SCREEN_HEIGHT },{ 0,0 }, {0, 0} }, COLLIDER_WALL, App->scene_john);
	//FrontPanel = App->collision->AddCollider({ { rect_background.rect.w-25, 0 , 25, SCREEN_HEIGHT },{ 0,0 } ,{ 0, 0 } }, COLLIDER_WALL, App->scene_john);
	//BackPanel->LeftRight = false;
	//FrontPanel->LeftRight = true;

	App->player1->Enable();
	App->player2->Enable();
	App->sceneUI->Enable();
	App->input->keyboard_state[SDL_SCANCODE_RETURN] = KEY_IDLE;
	return true;
}


update_status ModuleSceneJohn::Update()
{
	if ((App->render->Blit(graphics, 0, 0, &rect_background)) == false)
	{
		SDL_Log("Unable to [BLIT] texture: texture_background");
		return update_status::UPDATE_STOP;
	}
	App->input->Paused = false;
	App->render->Blit(graphics, 115, 0, &rojoParpadeo.GetCurrentFrame());

	App->render->Blit(graphics, 130, 100, &rotuloVerde.GetCurrentFrame());

	App->render->Blit(graphics, 440, 100, &radio.GetCurrentFrame());

	App->render->Blit(graphics, 315, 100, &szechu.GetCurrentFrame());

	App->render->Blit(graphics, 55, 59, &morado.GetCurrentFrame());

	if (App->input->keyboard_state[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		App->fade->FadeToBlack(App->scene_john, App->scene_congratz);
	}

	return UPDATE_CONTINUE;
}

bool ModuleSceneJohn::CleanUp()
{
	if (FrontPanel && BackPanel) 
	{
		FrontPanel->to_delete = true;
		BackPanel->to_delete = true;
	}

	App->sceneUI->Disable();
	App->audio->Unload_music(lee_music);
	App->textures->Unload(graphics);
	App->player1->Disable();
	App->player2->Disable();
	LOG("Unloading john stage");
	return true;
}