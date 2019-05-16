#ifndef _MODULECHARACTERSELECTION_
#define _MODULECHARACTERSELECTION_

#include "Application.h"
#include "Globals.h"
#include "Animation.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "SDL/include/SDL.h"
#include "RectSprites.h"



class ModuleScreenSelection : public Module {
public:
	ModuleScreenSelection();
	~ModuleScreenSelection();
	bool Init();
	bool CleanUp();
	update_status Update();
	bool Start();
	void move();
	void timer();
	void draw();
	void choose();

	SDL_Rect back;
	RectSprites selector1;
	RectSprites selector2;
	RectSprites imageSelection1;
	RectSprites imageSelection2;
	RectSprites characters;
	SDL_Renderer* background;
	SDL_Texture* graphics;

	int X_SELECTOR_1 = ((SCREEN_WIDTH / 2) - 28);
	int Y_SELECTOR_1 = ((SCREEN_HEIGHT / 2) + 17);
	int X_SELECTOR_2 = ((SCREEN_WIDTH / 2) - 0);
	int Y_SELECTOR_2 = ((SCREEN_HEIGHT / 2) + 20);

	int s1_pos_x = 2;
	int s2_pos_x = 3;
	int s1_pos_y = 1;
	int s2_pos_y = 1;


	int tick1 = 0, tick2 = 0;
	char time_char[10];
	int time_int;
	bool no_zero;
};

#endif // !_MODULECHARACTERSELECTION_
