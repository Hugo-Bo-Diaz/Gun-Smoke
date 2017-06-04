#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	explosion.anim.PushBack({ 22, 46, 31, 31 });
	explosion.anim.PushBack({ 55, 46, 31, 31 });
	explosion.anim.PushBack({ 94, 46, 31, 31 });
	explosion.anim.PushBack({ 134, 46, 31, 31 });
	explosion.anim.PushBack({ 175, 46, 31, 31 });
	explosion.anim.PushBack({ 214, 45, 31, 31 });
	explosion.anim.PushBack({ 254, 46, 31, 31 });
	explosion.anim.PushBack({ 297, 46, 31, 31 });
	explosion.anim.PushBack({ 333, 43, 31, 31 }); //333 43 = +3x-100y
	explosion.anim.PushBack({ 373, 46, 31, 31 });	
	explosion.anim.loop = false;
	explosion.anim.speed = 0.15f;

	laser.anim.PushBack({ 131, 37, 2, 4 });
	laser.anim.PushBack({339, 131, 5, 6 });
	laser.anim.PushBack({361, 129, 11, 10});
	laser.anim.speed = 0.0f;
	laser.speed.y = -4;
	laser.life = SHOT_LIFE;

	//fixed up this point
	shot_l.anim.PushBack({ 174, 38, 3, 3 });
	shot_l.anim.PushBack({ 339, 131, 5, 6 });
	shot_l.anim.PushBack({ 361, 129, 11, 10 });
	shot_l.anim.speed = 0.0f;
	shot_l.speed.y = -3;
	shot_l.speed.x = -3;
	shot_l.life = SHOT_LIFE;

	shot_l_up.anim.PushBack({ 149, 37, 3, 4 });
	shot_l_up.anim.PushBack({ 339, 131, 5, 6 });
	shot_l_up.anim.PushBack({ 361, 129, 11, 10 });
	shot_l_up.anim.speed = 0.0f;
	shot_l_up.speed.y = -4;
	shot_l_up.speed.x = -2;
	shot_l_up.life = SHOT_LIFE;

	shot_l_down.anim.PushBack({ 196, 38, 4, 3 });
	shot_l_down.anim.PushBack({ 339, 131, 5, 6 });
	shot_l_down.anim.PushBack({ 361, 129, 11, 10 });
	shot_l_down.anim.speed = 0.0f;
	shot_l_down.speed.y = -3;
	shot_l_down.speed.x = -3;
	shot_l_down.life = SHOT_LIFE;

	shot_r.anim.PushBack({ 178, 38, 3, 3 });
	shot_r.anim.PushBack({ 339, 131, 5, 6 });
	shot_r.anim.PushBack({ 361, 129, 11, 10 });
	shot_r.anim.speed = 0.0f;
	shot_r.speed.y = -3;
	shot_r.speed.x = +3;
	shot_r.life = SHOT_LIFE;

	shot_r_down.anim.PushBack({ 201, 38, 4, 3 });
	shot_r_down.anim.PushBack({ 339, 131, 5, 6 });
	shot_r_down.anim.PushBack({ 361, 129, 11, 10 });
	shot_r_down.anim.speed = 0.0f;
	shot_r_down.speed.y = -3;
	shot_r_down.speed.x = 3;
	shot_r_down.life = SHOT_LIFE;

	shot_r_up.anim.PushBack({ 154, 37, 3, 4 });
	shot_r_up.anim.PushBack({ 339, 131, 5, 6 });
	shot_r_up.anim.PushBack({ 361, 129, 11, 10 });
	shot_r_up.anim.speed = 0.0f;
	shot_r_up.speed.y = -4;
	shot_r_up.speed.x = 2;
	shot_r_up.life = SHOT_LIFE;

	shot_g.anim.PushBack({ 316, 12, 10, 10 });
	shot_g.anim.speed = 0.0f;
	shot_g.speed.y = +5;
	shot_g.life = SHOT_LIFE;    

	end_of_bullet.anim.PushBack({ 249, 36, 5, 6 });
	end_of_bullet.anim.PushBack({ 271, 34, 11, 10 });
	end_of_bullet.anim.loop = false;
	end_of_bullet.life = 200;
	end_of_bullet.anim.speed = 0.1f;

	hitmarker.anim.PushBack({ 195, 20, 2, 2 }); //1
	hitmarker.anim.PushBack({ 217, 18, 6, 6 }); //2
	hitmarker.anim.PushBack({ 214, 17, 8, 8 }); //3
	hitmarker.anim.loop = false;
	hitmarker.life = 200;
	hitmarker.anim.speed = 0.1f;

	enemy_bullet.anim.PushBack({ 262, 16, 4, 4 });
	enemy_bullet.anim.PushBack({ 262, 16, 10, 10 });
	enemy_bullet.anim.loop = false;
	enemy_bullet.life = 750;

	enemy_bullet.anim.PushBack({ 262, 16, 4, 4 });
	enemy_bullet.anim.PushBack({ 262, 16, 10, 10 });
	enemy_bullet_2.anim.loop = false;
	enemy_bullet_2.life = 1500;

	tnt.anim.PushBack({ 406, 19, 8, 6 });
	tnt.anim.PushBack({ 380, 17, 10, 9 });
	tnt.anim.PushBack({ 354, 14, 13, 13 });
	tnt.anim.PushBack({ 380, 17, 10, 9 });
	tnt.anim.PushBack({ 406, 19, 8, 6 });
	tnt.anim.PushBack({ 432, 22, 7, 3 });
	tnt.anim.loop = false;
	tnt.anim.speed = 0.15f;

	mechdeath.anim.PushBack({ 22, 94, 30, 34 });
	mechdeath.anim.PushBack({ 53, 94, 26, 30 });
	mechdeath.anim.PushBack({ 84, 94, 26, 29 });
	mechdeath.anim.PushBack({ 113, 94, 32, 26 });
	mechdeath.anim.PushBack({ 0, 0, 0, 0 });
	mechdeath.anim.PushBack({ 113, 94, 32, 26 });
	mechdeath.anim.PushBack({ 0, 0, 0, 0 });
	mechdeath.anim.PushBack({ 113, 94, 32, 26 });

	mechdeath.anim.loop = false;
	mechdeath.anim.speed = 0.2f;

	cookiedeath.anim.PushBack({ 191, 102, 24, 28 });
	cookiedeath.anim.PushBack({ 216, 102, 25, 27 });
	cookiedeath.anim.PushBack({ 243, 102, 27, 22 });
	cookiedeath.anim.PushBack({ 281, 102, 27, 22 });
	cookiedeath.anim.PushBack({ 0, 0, 0, 0 });
	cookiedeath.anim.PushBack({ 281, 102, 27, 22 });
	cookiedeath.anim.PushBack({ 0, 0, 0,0 });
	cookiedeath.anim.PushBack({ 281, 102, 27, 22 });
	cookiedeath.anim.loop = false;
	cookiedeath.anim.speed = 0.2f;

	boss_shot_d.anim.PushBack({ 68, 36, 2, 4 });
	boss_shot_d.life = 1000;
	boss_shot_d.speed.y = 5;
	boss_shot_d.anim.loop = false;


	boss_shot_dl.anim.PushBack({ 88, 36, 2, 5 });
	boss_shot_dl.life = 1000;
	boss_shot_dl.speed.y = 4;
	boss_shot_dl.speed.x = -1;
	boss_shot_dl.anim.loop = false;

	boss_shot_dr.anim.PushBack({ 52, 36, 2, 5 });
	boss_shot_dr.life = 1000;
	boss_shot_dr.speed.y = 4;
	boss_shot_dr.speed.x = 1;
	boss_shot_dr.anim.loop = false;

	boss_shot_l.anim.PushBack({ 108, 36, 2, 4 });
	boss_shot_l.life = 1000;
	boss_shot_l.speed.y = 3;
	boss_shot_l.speed.x = -3;
	boss_shot_l.anim.loop = false;

	boss_shot_r.anim.PushBack({ 34, 36, 2, 4 });
	boss_shot_r.life = 1000;
	boss_shot_r.speed.y = 3;
	boss_shot_r.speed.x = 3;
	boss_shot_r.anim.loop = false;

	barrel_broken.anim.PushBack({ 23, 11, 16, 16 });
	barrel_broken.anim.PushBack({ 47, 11, 16, 16 });
	barrel_broken.anim.PushBack({ 70, 11, 16, 16 });
	barrel_broken.anim.PushBack({ 95, 11, 16, 16 });
	barrel_broken.anim.PushBack({ 119, 11, 16, 16 });
	barrel_broken.anim.PushBack({ 143, 11, 15, 16 });
	barrel_broken.anim.PushBack({ 169, 11, 14, 16 });
	barrel_broken.life = 800;
	barrel_broken.anim.speed = 0.15f;
	barrel_broken.anim.loop = false;

	sniperdeath_l.anim.PushBack({ 27, 141, 17, 14 });
	sniperdeath_l.anim.PushBack({ 52, 138, 17, 16 });
	sniperdeath_l.anim.PushBack({ 80, 138, 11, 13 });
	sniperdeath_l.anim.PushBack({ 101, 141, 13, 10 });
	
	sniperdeath_l.anim.loop = false;
	sniperdeath_l.anim.speed = 0.1f;

	sniperdeath_r.anim.PushBack({ 190, 141, 17, 14 });
	sniperdeath_r.anim.PushBack({ 165, 138, 17, 16 });
	sniperdeath_r.anim.PushBack({ 143, 138, 11, 13 });
	sniperdeath_r.anim.PushBack({ 120, 141, 13, 10 });
	sniperdeath_r.anim.loop = false;
	sniperdeath_r.anim.speed = 0.1f;

	stabbydeath.anim.PushBack({ 351, 95, 21, 21 });
	stabbydeath.anim.PushBack({ 380, 98, 21, 24 });
	stabbydeath.anim.PushBack({ 408, 100, 31, 18 });

	stabbydeath.anim.loop = false;
	stabbydeath.anim.speed = 0.1f;

	player_death.anim.PushBack({ 19, 263, 14, 29 });
	player_death.anim.PushBack({ 58, 263, 16, 29 });
	player_death.anim.PushBack({ 95, 263, 21, 29 });
	player_death.anim.PushBack({ 135, 263, 23, 29 });
	player_death.anim.PushBack({ 172, 263, 27, 29 });
	player_death.anim.PushBack({ 212, 263, 31, 29 });
	player_death.anim.PushBack({ 252, 263, 31, 29 });

	player_death.anim.loop = false;
	player_death.anim.speed = 0.11f;
	player_death.life = 3500;

	boss_death.anim.PushBack({ 350, 131, 22, 32 });
	boss_death.anim.PushBack({ 375, 131, 24, 26 });
	
	boss_death.anim.loop = false;
	boss_death.anim.speed = 0.05f;
	boss_death.life = 4000;


	horse_appearance.anim.PushBack({ 22, 168, 15, 34 });
	horse_appearance.anim.PushBack({ 38, 168, 15, 31 });
	horse_appearance.anim.PushBack({ 54, 168, 15, 36 });

	horse_appearance.anim.speed = 0.2f;
	horse_appearance.speed.y = -1;
	horse_appearance.life = 4000;


	horse_death.anim.PushBack({ 70, 168, 16, 34 });
	horse_death.anim.PushBack({ 87, 168, 17, 32 });
	horse_death.anim.PushBack({ 106, 169, 18, 33 });
	horse_death.anim.PushBack({ 125, 169, 18, 33 });
	horse_death.anim.PushBack({ 146, 169, 21, 35 });

	horse_death.anim.loop = false;
	horse_death.anim.speed = 0.1f;
	horse_death.life = 1000;

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("gunsmoke/particles.png");
	tnt_sound = App->audio->LoadFx("gunsmoke/tnt_explosion.wav");
	// Load particles fx particle

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles /n");
	App->textures->Unload(graphics);

	// Unload fx

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	if (powerup_activated == true)
	{
		shot_l.life =		SHOT_LIFE + App->player->powerup[1] * 32;
		shot_l_down.life =	SHOT_LIFE + App->player->powerup[1] * 32;
		shot_l_up.life =	SHOT_LIFE + App->player->powerup[1] * 32;
		shot_r.life =		SHOT_LIFE + App->player->powerup[1] * 32;
		shot_r_down.life =	SHOT_LIFE + App->player->powerup[1] * 32;
		shot_r_up.life =	SHOT_LIFE + App->player->powerup[1] * 32;
		laser.life =		SHOT_LIFE + App->player->powerup[1] * 32;

		powerup_activated = false;
	}

	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
			//p = nullptr;    //WE CHANGED THIS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			active[i] = nullptr;
		}
		else if(SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if(p->fx_played == false)
			{
				p->fx_played = true;
			}
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, int xspeed, int yspeed, bool explosion_sound)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (xspeed != 100)
			{			
				p->speed.x = xspeed;
			}
			if (yspeed != 100)
			{
				p->speed.y = yspeed;
			}			
			
			if (explosion_sound)
			{
				App->audio->PlayFx(tnt_sound);
			}
			if(collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;

			break;
		}
	}
}

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if(active[i] != nullptr && active[i]->collider == c1)
		{
			App->particles->AddParticle(App->particles->hitmarker, active[i]->position.x - 4, active[i]->position.y-4, COLLIDER_PARTICLE, 0);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : 
anim(p.anim), position(p.position), speed(p.speed),
fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{

	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	bool ret = true;

	if(life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
		{
			if (collider != nullptr && collider->type == COLLIDER_PLAYER_SHOT)
			{
				App->particles->AddParticle(App->particles->end_of_bullet, position.x-4, position.y-4, COLLIDER_PARTICLE, 0);
			}

			ret = false;
		}
	}
	else
		if(anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}

