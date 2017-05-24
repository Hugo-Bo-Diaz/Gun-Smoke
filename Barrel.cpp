#include "Barrel.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePowerup.h"
#include "ModuleParticles.h"
#include "ModuleBarrel.h"

Barrel::Barrel(int x, int y, POWERUP_TYPE ptype)
{
	position.x = x;
	position.y = y;
	type = ptype;

	section.x = 0;
	section.y = 0;
	section.w = 20;
	section.h = 20;
	collider = App->collision->AddCollider({position.x,position.y,20,20},COLLIDER_BARREL,(Module*)App->barrel);
}


Barrel::~Barrel()
{
	if (hp == 0)
	{
		App->powerup->AddPowerup(position.x, position.y, type);
		App->particles->AddParticle(App->particles->barrel_broken,position.x,position.y);
	}
	if (collider != nullptr)
	{
		collider->to_delete = true;
	}
}


const Collider* Barrel::GetCollider() const
{
	return collider;
}

void Barrel::Draw()
{
	App->render->Blit(App->barrel->sprites, position.x, position.y, &section);
}

void Barrel::OnCollision()
{

	/*if (type != POWERUP_NULL)
	{
		App->powerup->AddPowerup(position.x,position.y,type);
	}*/

//END MY SUFFERING
}