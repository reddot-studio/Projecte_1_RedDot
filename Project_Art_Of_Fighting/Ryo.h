#ifndef __RYO_H__
#define __RYO_H__

#include "Character.h"

struct SDL_Texture;

class Ryo : public Character
{
public:
	Ryo(int player);
	~Ryo();
	bool Start() override;
	bool CleanUp() override;
};

#endif // !__RYO_H__
