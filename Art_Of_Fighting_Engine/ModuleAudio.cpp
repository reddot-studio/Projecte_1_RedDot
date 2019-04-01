
#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )



ModuleAudio::ModuleAudio() : Module() {}

ModuleAudio::~ModuleAudio() {}


bool ModuleAudio::Init()
{
	bool ret = true;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("SDL_INIT_AUDIO could not initialitze! SDL_Mix Error: %s\n", Mix_GetError());
		ret = false;
	}
	else
	{
		LOG("SDL_INIT AUDIO correctly initialized!\n");
		int flags = MIX_INIT_OGG;
		int initted = Mix_Init(flags);
		if (initted&flags != flags) {
			SDL_Log("Mix_Init: Failed to init required ogg support! SDL_Mixer Error: %s \n", Mix_GetError());
			SDL_Log("Mix_Init: %s\n", Mix_GetError());
			ret = false;
		}
		else
		{
			LOG("Mix_Init correctly initialized!");
			Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 1024);
			start_music = Load_music("Assets/Audio/041xRyukoh-no Theme.ogg");
			todo_music = Load_music("Assets/Audio/033xART OF FIGHT.ogg");
			ending_music = Load_music("Assets/Audio/042xSono hito-wa watashitachi-no kodomo kana.ogg");
			john_music = Load_music("Assets/Audio/038xKoukuu Bokaan!.ogg");
		}
	}


	return ret;
}


bool ModuleAudio::CleanUp()
{
	LOG("Cleaning music and fx!\n");

	for (unsigned int i = 0; i < last_audio; i++)
		Mix_FreeMusic(soundtrack[i]);

	for (unsigned int i = 0; i < last_effect; i++)
		Mix_FreeChunk(effects[i]);

	Mix_CloseAudio();
	Mix_Quit();

	return true;
}

Mix_Music* const ModuleAudio::Load_music(const char *path)
{
	Mix_Music* music = Mix_LoadMUS(path);
	soundtrack[last_audio++] = music;

	LOG("Loading Music\n");

	return music;
}

Mix_Chunk* const ModuleAudio::Load_effects(const char *path)
{
	Mix_Chunk* effect = Mix_LoadWAV(path);
	effects[last_effect++] = effect;

	LOG("Loading FX\n");
	
	return effect;
}

