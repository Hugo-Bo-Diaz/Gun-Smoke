#include "powerup.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"




Powerup::~Powerup()
{
}


const Collider* Powerup::GetCollider() const
{
	return collider;
}

