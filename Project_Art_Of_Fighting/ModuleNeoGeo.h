#ifndef _MODULENEOGEO_
#define _MODULENEOGEO_

#include "Application.h"
#include "Globals.h"
#include "Module.h"

class ModuleNeoGeo :public Module {
public:
	ModuleNeoGeo();
	~ModuleNeoGeo();
	bool Init();
	bool Start();
	update_status Update();
	bool CleanUp();
};

#endif // !_MODULENEOGEO_
