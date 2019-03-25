#ifndef __ModuleAudio_H__
#define __ModuleAudio_H__
#include "Module.h"

#define MAX_CHUNKS 10

struct Mix_Chunk;

class ModuleAudio : public Module {
public:
	Mix_Chunk *Chunk;
	Mix_Chunk* Chunk_Array[MAX_CHUNKS];
	uint last_Chunk = 0;
public:
	ModuleAudio();
	~ModuleAudio();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

	Mix_Chunk *  Load(char const*path);
	bool Play(Mix_Chunk*chunk);

};

#endif