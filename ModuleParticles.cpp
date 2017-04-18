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

	explosion.anim.PushBack({274, 296, 33, 30});
	explosion.anim.PushBack({313, 296, 33, 30});
	explosion.anim.PushBack({346, 296, 33, 30});
	explosion.anim.PushBack({382, 296, 33, 30});
	explosion.anim.PushBack({419, 296, 33, 30});
	explosion.anim.PushBack({457, 296, 33, 30});
	explosion.anim.loop = false;
	explosion.anim.speed = 0.3f;

	laser.anim.PushBack({221, 138, 3, 3});
	laser.anim.PushBack({226, 138, 3, 3});
	laser.anim.PushBack({231, 138, 3, 3 });
	laser.anim.PushBack({236, 138, 3, 3 });
	laser.anim.PushBack({241, 138, 3, 3 });
	laser.anim.PushBack({246, 138, 3, 3 });
	laser.anim.PushBack({251, 138, 3, 3 });
	laser.anim.PushBack({256, 138, 3, 3 });
	laser.anim.speed = 0.4f;
	laser.speed.y = -5;
	laser.life = 3000;

	shot_l.anim.PushBack({ 221, 138, 3, 3 });
	shot_l.anim.PushBack({ 226, 138, 3, 3 });
	shot_l.anim.PushBack({ 231, 138, 3, 3 });
	shot_l.anim.PushBack({ 236, 138, 3, 3 });
	shot_l.anim.PushBack({ 241, 138, 3, 3 });
	shot_l.anim.PushBack({ 246, 138, 3, 3 });
	shot_l.anim.PushBack({ 251, 138, 3, 3 });
	shot_l.anim.PushBack({ 256, 138, 3, 3 });
	shot_l.anim.speed = 0.4f;
	shot_l.speed.y = -5;
	shot_l.speed.x = -5;
	shot_l.life = 3000;

	shot_r.anim.PushBack({ 221, 138, 3, 3 });
	shot_r.anim.PushBack({ 226, 138, 3, 3 });
	shot_r.anim.PushBack({ 231, 138, 3, 3 });
	shot_r.anim.PushBack({ 236, 138, 3, 3 });
	shot_r.anim.PushBack({ 241, 138, 3, 3 });
	shot_r.anim.PushBack({ 246, 138, 3, 3 });
	shot_r.anim.PushBack({ 251, 138, 3, 3 });
	shot_r.anim.PushBack({ 256, 138, 3, 3 });
	shot_r.anim.speed = 0.4f;
	shot_r.speed.y = -5;
	shot_r.speed.x = +5;
	shot_r.life = 3000;

	shot_g.anim.PushBack({ 316, 12, 10, 10 });
	shot_g.anim.speed = 0.4f;
	shot_g.speed.y = +5;
	shot_g.life = 3000;    
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
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
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
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
		if((SDL_GetTicks() - born) > life)
			ret = false;
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

