#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	explosion.anim.PushBack({ 22, 167, 19, 10 });
	explosion.anim.PushBack({ 54, 164, 21, 13 });
	explosion.anim.PushBack({ 92, 159, 25, 18 });
	explosion.anim.PushBack({ 130, 154, 29, 23 });
	explosion.anim.PushBack({ 171, 156, 28, 21 });
	explosion.anim.PushBack({ 211, 160, 24, 17 });
	explosion.anim.PushBack({ 248, 157, 32, 21 });
	explosion.anim.PushBack({ 328, 147, 31, 31 });
	explosion.anim.PushBack({ 369, 148, 26, 29 });
	explosion.anim.loop = false;
	explosion.anim.speed = 0.15f;

	laser.anim.PushBack({221, 131, 2, 5 });
	laser.anim.PushBack({339, 131, 5, 6 });
	laser.anim.PushBack({361, 129, 11, 10});
	laser.anim.speed = 0.0f;
	laser.speed.y = -4;
	laser.life = SHOT_LIFE;

	//fixed up this point
	shot_l.anim.PushBack({ 263, 132, 4, 4 });
	shot_l.anim.PushBack({ 339, 131, 5, 6 });
	shot_l.anim.PushBack({ 361, 129, 11, 10 });
	shot_l.anim.speed = 0.0f;
	shot_l.speed.y = -3;
	shot_l.speed.x = -3;
	shot_l.life = SHOT_LIFE;

	shot_l_up.anim.PushBack({ 239, 131, 3, 5 });
	shot_l_up.anim.PushBack({ 339, 131, 5, 6 });
	shot_l_up.anim.PushBack({ 361, 129, 11, 10 });
	shot_l_up.anim.speed = 0.0f;
	shot_l_up.speed.y = -4;
	shot_l_up.speed.x = -2;
	shot_l_up.life = SHOT_LIFE;

	shot_l_down.anim.PushBack({ 285, 132, 5, 4 });
	shot_l_down.anim.PushBack({ 339, 131, 5, 6 });
	shot_l_down.anim.PushBack({ 361, 129, 11, 10 });
	shot_l_down.anim.speed = 0.0f;
	shot_l_down.speed.y = -3;
	shot_l_down.speed.x = -3;
	shot_l_down.life = SHOT_LIFE;

	shot_r.anim.PushBack({ 268, 132, 4, 4 });
	shot_r.anim.PushBack({ 339, 131, 5, 6 });
	shot_r.anim.PushBack({ 361, 129, 11, 10 });

	shot_r.anim.speed = 0.0f;
	shot_r.speed.y = -3;
	shot_r.speed.x = +3;
	shot_r.life = SHOT_LIFE;

	shot_r_down.anim.PushBack({ 291, 132, 5, 4 });
	shot_r_down.anim.PushBack({ 339, 131, 5, 6 });
	shot_r_down.anim.PushBack({ 361, 129, 11, 10 });
	shot_r_down.anim.speed = 0.0f;
	shot_r_down.speed.y = -3;
	shot_r_down.speed.x = 3;
	shot_r_down.life = SHOT_LIFE;

	shot_r_up.anim.PushBack({ 244, 131, 3, 5 });
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

	end_of_bullet.anim.PushBack({ 339, 131, 5, 6 });
	end_of_bullet.anim.PushBack({ 361, 129, 11, 10 });
	end_of_bullet.anim.loop = false;
	end_of_bullet.life = 200;
	end_of_bullet.anim.speed = 0.1f;

	enemy_bullet.anim.PushBack({315,11,6,6});
	enemy_bullet.anim.loop = false;
	enemy_bullet.life = 750;

	enemy_bullet_2.anim.PushBack({ 315, 11, 6, 6 });
	enemy_bullet_2.anim.loop = false;
	enemy_bullet_2.life = 1500;

	tnt.anim.PushBack({ 458, 83, 8, 6 });
	tnt.anim.PushBack({ 432, 81, 10, 9 });
	tnt.anim.PushBack({ 406, 78, 13, 13 });
	tnt.anim.PushBack({ 432, 81, 10, 9 });
	tnt.anim.PushBack({ 458, 83, 8, 6 });
	tnt.anim.PushBack({ 483, 87, 7, 3 });
	tnt.anim.loop = false;
	tnt.anim.speed = 0.15f;

	mechdeath.anim.PushBack({ 16, 194, 30, 30 });
	mechdeath.anim.PushBack({ 56, 194, 29, 28 });
	mechdeath.anim.PushBack({ 96, 194, 29, 27 });
	mechdeath.anim.PushBack({ 135, 206, 32, 19 });
	
	mechdeath.anim.loop = false;
	mechdeath.anim.speed = 0.1f;

	cookiedeath.anim.PushBack({ 183, 195, 24, 24 });
	cookiedeath.anim.PushBack({ 222, 194, 26, 26 });
	cookiedeath.anim.PushBack({ 262, 200, 27, 18 });
	cookiedeath.anim.PushBack({ 302, 201, 28, 20 });

	cookiedeath.anim.loop = false;
	cookiedeath.anim.speed = 0.1f;

}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("gunsmoke/particles.png");

	// Load particles fx particle

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
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
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if(p == nullptr)
			continue;

		if(p->Update() == false)
		{
			delete p;
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay, int xspeed, int yspeed)
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
			App->particles->AddParticle(App->particles->end_of_bullet, active[i]->position.x - 4, active[i]->position.y, COLLIDER_PARTICLE, 0);
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

