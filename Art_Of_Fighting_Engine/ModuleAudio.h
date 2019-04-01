#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__

#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

#define MAX_MUS 20
#define MAX_FX 20

#include "Module.h"
#include "Globals.h"

class ModuleAudio : public Module
{
public:
	ModuleAudio();
	~ModuleAudio();
	Mix_Music* soundtrack[MAX_MUS];
	Mix_Chunk* effects[MAX_FX];
	uint last_audio = 0;
	uint last_effect = 0;
	Mix_Music* start_music = nullptr;
	Mix_Music* todo_music = nullptr;
	Mix_Music* john_music = nullptr;
	Mix_Music* ending_music = nullptr;

	bool Init();
	bool CleanUp();
	Mix_Music* const Load_music(const char* path);
	Mix_Chunk* const Load_effects(const char* path);
};


#endif