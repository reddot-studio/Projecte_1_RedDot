#include "ModuleAudio.h"
#include "Globals.h"
#include "Application.h"

#include "SDL/include/SDL.h"
#include "SDL_Mixer/include/SDL_mixer.h"
#pragma comment(lib, "SDL_Mixer/libx86/SDL2_mixer.lib")

ModuleAudio::ModuleAudio():Module()
{
	for (int i = 0; i < MAX_CHUNKS; i++)
	{
		Chunk_Array[i] = nullptr;
	}
}
ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Init()
{
	bool ret = true;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		SDL_Log("SDL_INIT_AUDIO could not initialitze! SDL_Mix Error: %s", Mix_GetError());
		ret = false;
	}
	else
	{
		LOG("SDL_INIT AUDIO correctly initialized!");
		int flags = MIX_INIT_OGG;
		int initted = Mix_Init(flags);
		if (initted&flags != flags) {
			SDL_Log("Mix_Init: Failed to init required ogg support! SDL_Mixer Error: %s", Mix_GetError());
			SDL_Log("Mix_Init: %s\n", Mix_GetError());
			ret = false;
		}
		else
		{
			LOG("Mix_Init correctly initialized!");
			Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
			App->audio->Load("Assets/Audio/033xART OF FIGHT.ogg");
			Play(Chunk_Array[0]);
			Mix_FadeInChannel(2, Chunk_Array[0], 0, 5000);
			Mix_FadeOutChannel(2, 10000);
		}
	}
	return ret;
}

update_status ModuleAudio::PreUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp()
{
	bool ret = true;
	for (int i = 0; i < last_Chunk; i++)
	{
		Chunk_Array[i] = nullptr;
	}
	return ret;
}

Mix_Chunk * ModuleAudio::Load(const char *path)
{
	Chunk = Mix_LoadWAV(path);
	if (Chunk==NULL)
	{
		SDL_Log("Could not LOAD audio file from path: %s SDL_Mixer Error: %s", path, Mix_GetError());
		SDL_Quit();
	}
	else
	{
		Chunk_Array[last_Chunk++] = Chunk;
		LOG("Chunk path added to Chunks array!");
	}
	return Chunk;
}

bool ModuleAudio::Play(Mix_Chunk* chunk)
{
	bool ret = true;
	Mix_Volume(1, MIX_MAX_VOLUME / 6);
	if ((Mix_PlayChannel(2,chunk,1) < 2))
	{
		SDL_Log("SDL Could not play the chunk! SDL_Mixer Error: %s", Mix_GetError());
		ret = false;
	}
	else
	{
		LOG("Chunk is being played!");
	}
	return ret;
}