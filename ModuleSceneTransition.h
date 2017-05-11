#ifndef __MODULESCENETRANSITION_H__
#define __MODULESCENETRANSITION_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneTransition : public Module
{
public:
	ModuleSceneTransition();
	~ModuleSceneTransition();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* background = nullptr;
	uint fx = 0;
};

#endif // __MODULESCENETRANSITION