#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17



class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleSceneSpace;
class ModuleGameOver;
class ModuleSceneIntro;
class ModulePlayer;
class ModuleFadeToBlack;
class ModuleCollision;
class ModuleEnemies;
class ModuleFonts;
class ModuleAudio;
class ModulePowerup;
class ModuleBarrel;
class ModuleSceneTransition;
class Module;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneSpace* scene_space;
	ModuleGameOver* scene_gameover;
	ModuleSceneIntro* scene_intro;
	ModuleCollision* collision;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleParticles* particles;
	ModuleEnemies* enemies;
	ModuleFonts* fonts;
	ModuleAudio* audio;
	ModulePowerup * powerup;
	ModuleBarrel* barrel;
	ModuleSceneTransition* scene_transit;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__