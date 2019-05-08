#ifndef __JOHN_H__
#define __JOHN_H__

#include "Character.h"
#include "Application.h"
#include "ModuleTextures.h"

struct SDL_Texture;

class John : public Character
{
public:
	John(int player);
	~John();
	//bool Start() override;
	//bool CleanUp() override;
};

#endif // !__RYO_H__
