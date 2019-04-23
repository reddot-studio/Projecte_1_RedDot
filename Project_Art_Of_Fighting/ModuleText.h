#ifndef _MODULETEXT_
#define _MODULETEXT_

#include "Module.h"
#include "Globals.h"

class ModuleText : public Module {
public:
	ModuleText();
	~ModuleText();
	bool Start();
	update_status Update();
	bool CleanUp();

};

#endif // !_MODULETEXT_
