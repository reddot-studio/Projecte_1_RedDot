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
		keyboard_state[i] = KEY_IDLE;
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
		if (keyboard[i] == 1)
		{
			if (keyboard_state[i] == KEY_IDLE)
				keyboard_state[i] = KEY_DOWN;
			else
				keyboard_state[i] = KEY_REPEAT;
		}
		else
		{
			if (keyboard_state[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard_state[i] = KEY_UP;
			else
				keyboard_state[i] = KEY_IDLE;
		}
	}


	if(keyboard_state[SDL_SCANCODE_ESCAPE] == KEY_DOWN)
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
