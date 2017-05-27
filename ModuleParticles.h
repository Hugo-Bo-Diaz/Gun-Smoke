#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

#define MAX_ACTIVE_PARTICLES 500

struct SDL_Texture;
struct Collider;
enum COLLIDER_TYPE;

struct Particle
{
	Collider* collider = nullptr;
	Animation anim;
	uint fx = 0;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	uint tnt_sound;

	void AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type = COLLIDER_NONE, Uint32 delay = 0, int xspeed = 100, int yspeed = 100, bool explosion_sound = false);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

public:

	bool powerup_activated = false;

	Particle explosion;
	Particle laser;
	Particle shot_l;
	Particle shot_r;
	Particle shot_g;

	Particle shot_r_up;
	Particle shot_r_down;

	Particle shot_l_up;
	Particle shot_l_down;
	Particle end_of_bullet;
	Particle hitmarker;

	Particle enemy_bullet;
	Particle enemy_bullet_2;

	Particle tnt;

	Particle mechdeath;
	Particle cookiedeath;
	Particle sniperdeath_l;
	Particle sniperdeath_r;
	Particle stabbydeath;

	Particle boss_shot_l;
	Particle boss_shot_dl;
	Particle boss_shot_d;
	Particle boss_shot_dr;
	Particle boss_shot_r;

	Particle barrel_broken;

	Particle player_death;
	Particle boss_death;
	Particle horse_appearance;
};

#endif // __MODULEPARTICLES_H__