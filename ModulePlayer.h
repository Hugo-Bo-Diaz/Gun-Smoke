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

	//POWERUPS
	/*
	0-> boots
	1-> rifle
	2-> bullets
	*/

	int powerup[3];

	int checkpoint = 0;

	int timer = 0;
	bool itstime;
	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	SDL_Texture* sprites = nullptr;
	Animation* current_animation = nullptr;

	Animation idle;
	Animation left;
	Animation right;

	Animation left_shot;
	Animation idle_shot;
	Animation right_shot;

	fPoint position;
	fPoint previous;
	Collider* col;
	Collider* col_base;
	bool destroyed = false;
	int time_z;
	int time_x;
	int time_c;
	int camera_y = 0;
	int cooldown = 0;//of the shots

	int setanim = 60;
	int lastkey=0;

	int font_score = -1;
	uint audio_shot;
	int score;
	char scores[8];

	int lifes = 3;

	bool joystick_up;
	bool joystick_down;
	bool joystick_left;
	bool joystick_right;

	int god_mode = 0;
};

#endif