#ifndef __ModuleLevel_01_H__
#define __ModuleLevel_01_H__
#include "SDL_image/include/SDL_image.h"
#include "Module.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
class ModuleLevel_01 : public Module {
public:
	SDL_Rect * background = nullptr;

public:
	bool Init()		override;
	update_status PreUpdate() override;
	update_status Update() override;
	bool CleanUp()	override;

};

#endif // !__ModuleLevel_01_H__
