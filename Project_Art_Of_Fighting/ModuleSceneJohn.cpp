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
#include "ModuleDebug.h"


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
	rotuloVerde.PushBack({ 0,224,77,19 });
	rotuloVerde.PushBack({ 77,224,77,19 });
	rotuloVerde.speed = 0.1f;

	//radio//
	radio.PushBack({ 0,242,36,31 });
	radio.PushBack({ 36,242,36,31 });
	radio.PushBack({ 72,242,36,31 });
	radio.PushBack({ 108,242,36,31  });
	radio.speed = 0.1f;

	//szechu//
	szechu.PushBack({ 154,224,10,73 });
	szechu.PushBack({ 164,224,10,73 });
	szechu.speed = 0.1f;

	//Morado//
	morado.PushBack({ 50,274,50,43 },0,0,3);
	morado.PushBack({  0,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 13);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 13);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 13);
	morado.PushBack({ 50,274,50,43 }, 0, 0, 3);
	morado.PushBack({ 0,274,50,43 }, 0, 0, 13);
	morado.speed = 0.2f;

	//Cuadrado//
	cuadrado.PushBack({ 174,256,12,12 });
	cuadrado.PushBack({ 186,256,12,12 });
	cuadrado.speed = 0.05f;

	//Luz Azul//
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 13);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 13);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 13);
	luzAzul.PushBack({ 578,143,22,125 }, 0, 0, 3);
	luzAzul.PushBack({ 556,143,22,125 }, 0, 0, 13);
	luzAzul.speed = 0.2f;

	//Cartel Azul//
	cartelAzul.PushBack({ 556,12,24,131 });
	cartelAzul.PushBack({ 580,12,24,131 });
	cartelAzul.speed = 0.1f;


	//Blanco//
	blanco.PushBack({ 556,0,16,12 });
	blanco.PushBack({ 572,0,16,12 });
	blanco.speed = 0.1f;

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

	App->debug->Enable();
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

	App->render->Blit(graphics, 0, 0, &rotuloVerde.GetCurrentFrame());

	App->render->Blit(graphics, 88, 0, &radio.GetCurrentFrame());

	App->render->Blit(graphics, 195, 43, &szechu.GetCurrentFrame());

	App->render->Blit(graphics, 55, 59, &morado.GetCurrentFrame());

	App->render->Blit(graphics, 180, 102, &cuadrado.GetCurrentFrame());

	App->render->Blit(graphics, 378, 0, &luzAzul.GetCurrentFrame());

	App->render->Blit(graphics, 433, 7, &cartelAzul.GetCurrentFrame());

	App->render->Blit(graphics, 314, 114, &blanco.GetCurrentFrame());

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