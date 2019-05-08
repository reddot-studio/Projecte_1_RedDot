#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "Application.h"

struct Mix_Music;
struct Mix_Chunk;
struct SDL_Texture;
struct RectSprites;

class Scene
{
public:
	Scene() {};
	~Scene() {};

	virtual void Start() = 0;

	Mix_Music * todo_music = nullptr;
	Mix_Chunk * fightfx = NULL;
	SDL_Texture* graphics = nullptr;
	RectSprites rect_background;

private:

};

#endif // !__SCENE_H__
