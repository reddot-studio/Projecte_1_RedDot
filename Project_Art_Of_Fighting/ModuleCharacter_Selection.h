#ifndef _MODULECHARACTERSELECTION_
#define _MODULECHARACTERSELECTION_

#include "Application.h"
#include "Globals.h"
#include "Animation.h"
#include "Module.h"

class ModuleScreenSelection : public Module {
public:
	ModuleScreenSelection();
	~ModuleScreenSelection();
	bool Init();
	bool CleanUp();
	update_status Update();
	bool Start();
};

#endif // !_MODULECHARACTERSELECTION_
