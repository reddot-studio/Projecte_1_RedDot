#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "SDL/include/SDL_joystick.h"
#include "ModulePlayer_1.h"

ModuleInput::ModuleInput() : Module()
{
}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	for (int i = 0; i < 2; i++)
	{
		controller[i] = nullptr;
	}

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
			controller[i] = SDL_GameControllerOpen(i);
			if (controller[i]) {
				break;
			}
			else {
				SDL_Log("Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (SDL_GameControllerGetAttached(controller[i])) {
			//LOG("&d TRUE",i)
		}
		else {
			//LOG("&d FALSE", i);
		}
	}


	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	if (SDL_NumJoysticks() == 2) {
		//LOG("2 PADS");
	}
	if (SDL_GameControllerGetAttached(controller[0])) {
		//LOG("TRUE")
	}
	else {
		if (SDL_NumJoysticks() > 0) {

			for (int i = 0; i < SDL_NumJoysticks(); ++i) {
				if (SDL_IsGameController(i)) {
					controller[i] = SDL_GameControllerOpen(i);
					if (controller[i]) {
						break;
					}
					else {
						SDL_Log("Could not open gamecontroller %i: %s\n", i, SDL_GetError());
					}
				}
			}
		}
		//LOG("FALSE");
	}

	if (Paused) {
		SDL_PumpEvents();
		if (App->player1->isJumping != true)
		{
			App->player1->last_input = IN_UNKNOWN;
		}
		if (App->player2->isJumping != true)
		{
			App->player2->last_input = IN_UNKNOWN;
		}

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

		if (SDL_GameControllerGetButton(controller[0], SDL_CONTROLLER_BUTTON_BACK))
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

const float ModuleInput::GetHorizontalAxis()
{
	float horizontalAxis = (float)SDL_GameControllerGetAxis(controller[0], SDL_CONTROLLER_AXIS_LEFTX);
	horizontalAxis /= 32767;

	return horizontalAxis;
}

const float ModuleInput::GetVerticalAxis()
{
	float verticalAxis = (float)SDL_GameControllerGetAxis(controller[0], SDL_CONTROLLER_AXIS_LEFTY);
	verticalAxis /= 32767;

	return verticalAxis;
}
