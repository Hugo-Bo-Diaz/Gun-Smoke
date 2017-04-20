#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation left;
	Animation right;
	iPoint position;
	Collider* col;
	bool destroyed = false;
	int time_z;
	int time_x;
	int time_c;
	int cooldown = 0;//of the shots
	int font_score = -1;
	uint audio_shot;
};

#endif