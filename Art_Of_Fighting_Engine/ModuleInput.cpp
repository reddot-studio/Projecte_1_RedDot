#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleLevel_01.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	keyboard = SDL_GetKeyboardState(NULL);
	// TODO 1: find out how to detect if the ESC key was pressed
	// and quit the game
	if (keyboard[SDL_SCANCODE_ESCAPE]) {
		LOG("\nESCAPE PRESSED");
		return update_status::UPDATE_STOP;
	}
	if (keyboard[SDL_SCANCODE_A]) {
		left = true;
	}
	else {
		left = false;
	}
	if (keyboard[SDL_SCANCODE_D]) {
		right = true;
	}
	else {
		right = false;
	}



	return update_status::UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}