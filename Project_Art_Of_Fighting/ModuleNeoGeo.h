#ifndef _MODULENEOGEO_
#define _MODULENEOGEO_

#include "Application.h"
#include "Globals.h"
#include "Module.h"
#include "ModuleTextures.h"
#include "Animation.h"
#include "ModuleDebug.h"
#include "ModuleSceneJohn.h"
#include "ModuleSceneTodo.h"
#include "ModuleCharacter_Selection.h"
#include "ModuleUI.h"
#include "ModuleCongratzScreen.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"
#include "ModuleWelcomeScreen.h"

class ModuleNeoGeo :public Module {
public:
	ModuleNeoGeo();
	~ModuleNeoGeo();
	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
	///////
	Animation neogeo;
	Animation* current_animation;
	Animation final_neogeo;
	SDL_Texture* graphics;

	int tick1 = 0, tick2 = 0;
};

#endif // !_MODULENEOGEO_
