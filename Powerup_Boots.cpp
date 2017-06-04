#include "Powerup_Boots.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Powerup.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Powerup_Boots::Powerup_Boots(int x, int y)
{
	position.x = x;
	position.y = y;

	section.x = position.x;
	section.y = position.y ;
	section.h = 18;
	section.w = 18;

	type = POWERUP_BOOTS;
	collider = App->collision->AddCollider(section, COLLIDER_POWER_UP,(Module*)App->powerup);

}


Powerup_Boots::~Powerup_Boots()
{
}


void Powerup_Boots::OnCollision() 
{
	//INCREASE PLAYER POWERS
	App->player->powerup[0] += 1;
}

SDL_Rect Powerup_Boots::Draw()
{
	if (frame == 0 || frame == 1)
	{
		return{ 0, 0, 21, 18 };
	}
	else
	{
		return{ 0, 21, 21, 18 };
	}
}