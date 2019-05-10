#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_joystick.h"

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

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{

		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	SDL_Joystick * joy;
	if (SDL_NumJoysticks() > 0) {
		joy = SDL_JoystickOpen(0);
		if (joy) {
			LOG("\nOpened Joystick 0");
		}
	}

	

	for (int i = 4; i < 285; i++)
	{
		keyboard_state[i] = KEY_IDLE;
	}

	int num = SDL_NumJoysticks();
	for (int i = 0; i < num; ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) {
				break;
			}
			else {
				SDL_Log("Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}
	if (SDL_GameControllerGetAttached(controller)) {
		LOG("TRUE")
	}
	else {
		LOG("FALSE");
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	
	float horizontalAxis = (float)SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
	Uint8 num = SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A);
	horizontalAxis /= 32767;
	if (horizontalAxis > 0.1f) {
		rightAxis = true;
		leftAxis = false;
	}
	if (horizontalAxis < -0.1f) {
		leftAxis = true;
		rightAxis = false;
	}
	else {
		rightAxis = false;
		rightAxis = false;
	}
	if (rightAxis) {
		LOG("Right axis true");
	}
	else {
		LOG("Right axis false");
	}	
	if (leftAxis) {
		LOG("Left axis true");
	}
	else {
		LOG("Left axis false");
	}
	SDL_Log("Button: %d", num);
	if (Paused) {
		SDL_PumpEvents();
	}

	if (!Paused) 
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


		if (keyboard_state[SDL_SCANCODE_ESCAPE] == KEY_DOWN)
			return update_status::UPDATE_STOP;

	}

	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{

	for (int i = 4; i < 285; i++)
	{
		keyboard_state[i] = KEY_IDLE;
	}
	Paused = true;
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
