#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleSlowdown.h"
#include "ModuleRender.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"
#include "SDL/include/SDL_log.h"

ModuleSlowdown::ModuleSlowdown()
{
}

ModuleSlowdown::~ModuleSlowdown()
{}

// Load assets
bool ModuleSlowdown::Start()
{
	return true;
}

// Update: draw background
update_status ModuleSlowdown::PostUpdate()
{
	if (slowing_down)
	{
		UpdateSlowdown();
	}

	return UPDATE_CONTINUE;
}
void ModuleSlowdown::StartSlowdown(int duration, int magnitude)
{
	slowdown_timer = 0;
	slowdown_duration = duration;
	slowdown_magnitude = magnitude;
	slowing_down = true;
	this->magnitude = 0;
}

void ModuleSlowdown::UpdateSlowdown()
{
	if (slowdown_timer <= slowdown_duration) {
		slowdown_timer++;
		time = (float)slowdown_timer / slowdown_duration;
		if (magnitude <= 60) {
			magnitude = slowdown_magnitude * time *2;
		}
		else {
			magnitude = slowdown_magnitude * time/2;
		}
		SDL_Delay(magnitude);
		SDL_Log("Time: %0.2f Magnitude: %i",time, magnitude);
	}
	else {
		slowing_down = false;
	}
}
