#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "RectSprites.h"
#include "ModuleDebug.h"
#include"ModuleCollision.h"
#include "ModulePlayer_1.h"
#include "ModulePlayer_2.h"

ModuleRender::ModuleRender() : Module()
{
	camera.x = -1;
	camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	CameraLimitL = nullptr;
	CameraLimitR = nullptr;


}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);

	//Camera Limits
	CameraLimitL = App->collision->AddCollider({ {0, 0, 25, SCREEN_HEIGHT}, {0, 0}, {0, 0} }, COLLIDER_WALL);
	CameraLimitR = App->collision->AddCollider({ {SCREEN_WIDTH - 25, 0, 25, SCREEN_HEIGHT}, {0, 0}, {0, 0} }, COLLIDER_WALL);
	CameraLimitL->LeftRight = false;
	CameraLimitR->LeftRight = true;
	
	if (App->scene_john->IsEnabled() == true)
		CurrentSceneLenght = App->scene_john->rect_background.rect.w;	
	if (App->scene_todo->IsEnabled() == true)
		CurrentSceneLenght = App->scene_todo->rect_background.rect.w;


	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{

	if(App->input->keyboard_state[SDL_SCANCODE_UP] == KEY_REPEAT)
		camera.y += speed;

	if(App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
		camera.y -= speed;

	if(App->input->keyboard[SDL_SCANCODE_LEFT] == 1)
		camera.x += speed;

	if(App->input->keyboard_state[SDL_SCANCODE_RIGHT] == KEY_REPEAT)
		camera.x -= speed;
	
	CameraLimitL->rect.x = -(camera.x / speed);
	CameraLimitR->rect.x = -(((camera.x - camera.w * SCREEN_SIZE) / speed) + 25);


	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window

	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, RectSprites* section, float speed, int FacingPosition)
{
	SDL_RendererFlip facingPos;
	bool ret = true;
	SDL_Rect rect;
	rect.x = (int)(camera.x * speed) + x  * SCREEN_SIZE;
	rect.y = (int)(camera.y * speed) + y  * SCREEN_SIZE;

	if(section != NULL)
	{
		rect.w = section->rect.w;
		rect.h = section->rect.h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE;
	rect.h *= SCREEN_SIZE;

	switch (FacingPosition)
	{


	case 1:
		//Looking to right
		facingPos = SDL_FLIP_NONE;
		break;
	case 2:
		//Looking to left, player2 does NOt rotate over pivot, needs to be fixed
		facingPos = SDL_FLIP_HORIZONTAL;
		break;
	}
	if (SDL_RenderCopyEx(renderer, texture, &section->rect, &rect, 0, NULL, facingPos))
	{
		LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera,float speed)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);

	if (use_camera)
	{

		rec.x = (int)camera.x * speed + rect.x * SCREEN_SIZE;
		rec.y = (int)camera.y * speed + rect.y * SCREEN_SIZE;
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

