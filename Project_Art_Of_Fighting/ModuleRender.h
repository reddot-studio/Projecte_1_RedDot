#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"
#include "RectSprites.h"

struct SDL_Renderer;
struct SDL_Texture;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, RectSprites* section, float speed = 1.0f, int FacingPosition = 1);
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a,bool use_camera = true, float speed = 1.0f);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
	int speed = SCREEN_SIZE;
	int CurrentSceneLenght;

	Collider* CameraLimitL;
	Collider* CameraLimitR;


};

#endif //__ModuleRenderer_H__