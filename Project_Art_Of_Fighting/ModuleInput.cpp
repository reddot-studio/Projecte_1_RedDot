#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
}

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

	for (int i = 4; i < 285; i++)
	{
		keyboard_state[i] = KEY_NONE;
	}
	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{

	SDL_PumpEvents();

	keyboard = SDL_GetKeyboardState(NULL);

	for (int i = 4; i < 285; i++)
	{
		if (keyboard[i]) {
			if (keyboard_state[i] == KEY_PRESSED || keyboard_state[i] == KEY_REPEAT) {
				keyboard_state[i] = KEY_REPEAT;
			}
			else {
				keyboard_state[i] = KEY_PRESSED;
			}
		}
		else if (keyboard_state[i] == KEY_PRESSED || keyboard_state[i] == KEY_REPEAT) {
			keyboard_state[i] = KEY_REALESE;
		}
		else {
			keyboard_state[i] = KEY_NONE;
		}
	}


	if(keyboard_state[SDL_SCANCODE_ESCAPE] == KEY_PRESSED)
		return update_status::UPDATE_STOP;

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
