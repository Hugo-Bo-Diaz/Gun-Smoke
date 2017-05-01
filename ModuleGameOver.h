#ifndef __MODULESCENEGAMEOVER_H__
#define __MODULESCENEGAMEOVER_H__

#include "Module.h"

struct SDL_Texture;

class ModuleGameOver : public Module
{
public:
	ModuleGameOver();
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();
	int font_score;
	int score;
	char scores[8];
	int auxiliar;
	int auxiliar2;

	int highscores[5] = { 0, 0, 0, 0, 0 };


public:

	SDL_Texture* background = nullptr;
	uint fx = 0;
};

#endif // __MODULESCENEGAMEOVER_H__
