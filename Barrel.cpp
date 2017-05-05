#include "Barrel.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePowerup.h"
#include "ModuleParticles.h"

Barrel::Barrel(int x, int y, POWERUP_TYPE ptype)
{
	position.x = x;
	position.y = y;
	type = ptype;
}


Barrel::~Barrel()
{
	App->powerup->AddPowerup(position.x, position.y, type);
}


const Collider* Barrel::GetCollider() const
{
	return collider;
}

void Barrel::Draw()
{
	App->render->Blit();
}

void Barrel::OnCollision()
{
//END MY SUFFERING
}