#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModulePlayer.h"

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

	if (external_input(App->player->inputs) == true) {
		return update_status::UPDATE_CONTINUE;
	}
	else {
		return update_status::UPDATE_STOP;
	}

}

bool ModuleInput::external_input(p2Qeue<ryo_inputs>& inputs)
{
	static bool left = false;
	static bool right = false;
	static bool down = false;
	static bool up = false;
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

	//Escape to exit app
	if (keyboard_state[SDL_SCANCODE_ESCAPE] == KEY_DOWN)
		return false;

	//Press D to move forward
	switch (keyboard_state[SDL_SCANCODE_D])
	{
	case KEY_DOWN:
		right = true;
		break;
	case KEY_UP:
		App->player->inputs.Push(IN_RIGHT_UP);
		right = false;
		break;
	}

	//Press A to move backward
	switch (keyboard_state[SDL_SCANCODE_A])
	{
	case KEY_DOWN:
		left = true;
		break;
	case KEY_UP:
		App->player->inputs.Push(IN_LEFT_UP);
		left = false;
		break;
	}

	//Press W to jump
	switch (keyboard_state[SDL_SCANCODE_W])
	{
	case KEY_DOWN:
		up = true;
		break;
	case KEY_UP:
		up = false;
		break;
	}

	//Press S to crouch
	switch (keyboard_state[SDL_SCANCODE_S])
	{
	case KEY_DOWN:
		down = true;
		break;
	case KEY_UP:
		App->player->inputs.Push(IN_CROUCH_UP);
		down = false;
		break;
	}

	// Press E to punch
	if (keyboard_state[SDL_SCANCODE_E] == KEY_DOWN)
	{
		App->player->inputs.Push(IN_PUNCH);
	}	
	
	// Press R to kick
	if (keyboard_state[SDL_SCANCODE_R] == KEY_DOWN)
	{
		App->player->inputs.Push(IN_KICK);
	}

	// Press F to ko'ou ken
	if (keyboard_state[SDL_SCANCODE_F] == KEY_DOWN) {
		App->player->inputs.Push(IN_KOOU_KEN);
	}


	//Cheking booleans
	if (left && right)
		inputs.Push(IN_LEFT_AND_RIGHT);
	{
		if (left)
			inputs.Push(IN_LEFT_DOWN);
		if (right)
			inputs.Push(IN_RIGHT_DOWN);
	}

	if (up && down)
		inputs.Push(IN_JUMP_AND_CROUCH);
	else
	{
		if (down)
			inputs.Push(IN_CROUCH_DOWN);
		if (up)
			inputs.Push(IN_JUMP);
	}


	return true;
}
// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}
