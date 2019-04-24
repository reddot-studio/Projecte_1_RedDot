#ifndef _ModuleWelcomeScreen_H_
#define _ModuleWelcomeScreen_H_

#include "Module.h"
#include "Globals.h"
#include "Animation.h"

struct SDL_Texture;


class ModuleWelcomeScreen : public Module {
public:
	ModuleWelcomeScreen();
	~ModuleWelcomeScreen();

	bool Init()override;
	bool Start()override;
	update_status Update()override;

	bool CleanUp();

public:
	enum screen_state
	{
		MOVING,
		NOT_MOVING,
	};
	Animation* current_animation;
	screen_state state = MOVING;
	SDL_Texture* graphics = nullptr;
	Mix_Music* start_music = nullptr;
	RectSprites rect_background;
	Animation logo_transition;
	Animation insert_coin;
	Animation coin;
};



#endif
