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
	SDL_Texture* graphics;
};

#endif // !_MODULENEOGEO_
