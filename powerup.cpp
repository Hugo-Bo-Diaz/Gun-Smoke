#include "powerup.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"




Powerup::~Powerup()
{
	if (collider != nullptr)
		collider->to_delete = true;
}


const Collider* Powerup::GetCollider() const
{
	return collider;
}

