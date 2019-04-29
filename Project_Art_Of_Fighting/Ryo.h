#ifndef __RYO_H__
#define __RYO_H__

#include "Character.h"
#include "Application.h"
#include "ModuleTextures.h"

struct SDL_Texture;

class Ryo : public Character
{
public:
	Ryo();
	~Ryo();
	bool Start();
};

#endif // !__RYO_H__
