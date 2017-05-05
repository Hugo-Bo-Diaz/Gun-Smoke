#include "Powerup_Boots.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Powerup.h"

Powerup_Boots::Powerup_Boots(int x, int y)
{
	position.x = x;
	position.y = y;

	section.x = 24;
	section.y = 5 ;
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
}

SDL_Rect Powerup_Boots::Draw()
{
	return section;
}