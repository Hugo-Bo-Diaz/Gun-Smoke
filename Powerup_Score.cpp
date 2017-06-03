#include "Powerup_Score.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Powerup.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

Powerup_Score::Powerup_Score(int x, int y)
{
	position.x = x;
	position.y = y;

	section.x = position.x;
	section.y = position.y;
	section.h = 18;
	section.w = 18;

	type = POWERUP_SCORE;
	collider = App->collision->AddCollider(section, COLLIDER_POWER_UP, (Module*)App->powerup);

}


Powerup_Score::~Powerup_Score()
{
}


void Powerup_Score::OnCollision()
{
	//INCREASE PLAYER SCORE
	App->player->score += 1000;
}

SDL_Rect Powerup_Score::Draw()
{
	if (frame == 0 || frame == 1)
	{
		return{ 337, 30, 18, 18 };
	}
}