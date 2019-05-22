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
#include <time.h>
#include <cstdlib>

ModuleRender::ModuleRender() : Module()
{
	camera.x = -1;
	camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;

	timer = 0.0f;
	timerSpeed = 0.2f;

	camera_offset.x = camera_offset.y = 0;

	CameraLimitL = nullptr;
	CameraLimitR = nullptr;

	srand(time(NULL));

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
	if (WIN_FULLSCREEN_DESKTOP)
	{
		SDL_RenderSetLogicalSize(renderer, 384, 224);
	}
	//Camera Limits
	CameraLimitL = App->collision->AddCollider({ {0, 0, 25, SCREEN_HEIGHT}, {0, 0}, {0, 0} }, COLLIDER_WALL);
	CameraLimitR = App->collision->AddCollider({ {SCREEN_WIDTH-25, 0, 25, SCREEN_HEIGHT}, {0, 0}, {0, 0} }, COLLIDER_WALL);
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

	//Zoom Behav
	if (App->player1->IsEnabled()) {
		int distance = App->player2->GetPosition().x - App->player1->GetPosition().x;
		SDL_Log("%i", distance);
		if (distance < 150) {
			isZoomed = true;
		}
		else {
			isZoomed = false;
		}
	}

	if (App->collision->debug)
	{
		if (App->input->keyboard_state[SDL_SCANCODE_UP] == KEY_REPEAT)
			camera.y += speed;

		if (App->input->keyboard[SDL_SCANCODE_DOWN] == 1)
			camera.y -= speed;

		if (App->input->keyboard[SDL_SCANCODE_LEFT] == 1)
			camera.x += speed;

		if (App->input->keyboard_state[SDL_SCANCODE_RIGHT] == KEY_REPEAT)
			camera.x -= speed;

	}

	//if (isZoomed) {
	//	ZoomIn();
	//}
	//else if(!isZoomed){
	//	ZoomOut();
	//}

	if (shaking)
		UpdateCameraShake();

	CameraLimitL->rect.x = -(camera.x / speed);
	CameraLimitR->rect.x = -(((camera.x - camera.w * SCREEN_SIZE) / speed)+25);


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
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, RectSprites* section, float speed, int FacingPosition, bool zoom)
{
	SDL_RendererFlip facingPos;
	bool ret = true;
	SDL_Rect rect;

	if (zoom) {
		if (isZoomed) {
			ZoomIn();
		}

		else if (!isZoomed) {
			ZoomOut();
		}
	}
	if (!zoom) {
		zoomIntensity = 1.0f;
	}
	else {
		zoomIntensity = zoomValue;
	}
	rect.x = (int)((camera.x + camera_offset.x) * speed) + x  * SCREEN_SIZE * zoomIntensity;
	rect.y = (int)((camera.y + camera_offset.y) * speed) + y  * SCREEN_SIZE * zoomIntensity;

	if(section != NULL)
	{
		rect.w = section->rect.w;
		rect.h = section->rect.h;
	}
	else
	{
		SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
	}

	rect.w *= SCREEN_SIZE * zoomIntensity;
	rect.h *= SCREEN_SIZE * zoomIntensity;

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

		rec.x = (int)((camera.x + camera_offset.x) * speed) + rect.x * SCREEN_SIZE * zoomIntensity;
		rec.y = (int)((camera.y + camera_offset.y) * speed) + rect.y * SCREEN_SIZE * zoomIntensity;
		rec.w *= SCREEN_SIZE * zoomIntensity;
		rec.h *= SCREEN_SIZE * zoomIntensity;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

void ModuleRender::StartCameraShake(int duration, float magnitude)
{
	//TODO 1: Store the data and start the shake
	shake_duration = duration;
	shake_magnitude = magnitude;
	shaking = true;
	shake_timer = 0;
}

void ModuleRender::UpdateCameraShake()
{
	//TODO 2: Update the shake timer, stop shaking if we reach the full duration
	//		  Generate a random value and set the camera offset

	if (shake_timer < shake_duration) {
		shake_timer++;
		camera_offset.x = camera_offset.y = rand() % 2 * shake_magnitude;
	}
	else {
		camera_offset.x = camera_offset.y = 0;
		shaking = false;
	}

}

void ModuleRender::ZoomIn()
{
	if (isZoomed) 
	{
		
		if (zoomValue < 1.3f)
		{
			zoomValue += 0.001f;

			if (camera.y > -200)
			{
				timer += timerSpeed;
				if (timer > 0.5f) {
					camera.y -= 2;
					timer = 0.0f;
				}
			}
		}
		SDL_Log("%0.2f", timer);
	}
	
}

void ModuleRender::ZoomOut()
{
	if (!isZoomed) {
		if (zoomValue > 1.0f) {
			zoomValue -= 0.001f;

			if (camera.y < 0) {
				timer += timerSpeed;
				if (timer > 0.5f) {
					camera.y += 2;
					timer = 0.0f;
				}
			}
		}
	}
}


