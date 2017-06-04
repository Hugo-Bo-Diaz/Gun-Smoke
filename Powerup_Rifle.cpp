#include "Powerup_Rifle.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Powerup.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Powerup_Rifle::Powerup_Rifle(int x, int y)
{
	position.x = x;
	position.y = y;

	section.x = position.x;
	section.y = position.y;
	section.h = 18;
	section.w = 18;

	type = POWERUP_RIFLE;
	collider = App->collision->AddCollider(section, COLLIDER_POWER_UP, (Module*)App->powerup);

}


Powerup_Rifle::~Powerup_Rifle()
{
}


void Powerup_Rifle::OnCollision()
{
	//INCREASE PLAYER POWERS
	App->player->powerup[1] += 1;
	App->particles->powerup_activated = true;
}

SDL_Rect Powerup_Rifle::Draw()
{
	if (frame == 0 || frame == 1)
	{
		return{ 44, 3, 18, 18 };
	}
	else
	{
		return{ 44, 21, 18, 18 };
	}
}