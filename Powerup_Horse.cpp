#include "Powerup_Horse.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "Powerup.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"
Powerup_Horse::Powerup_Horse(int x, int y)
{
	position.x = x;
	position.y = y;

	section.x = position.x;
	section.y = position.y;
	section.h = 18;
	section.w = 18;

	type = POWERUP_HORSE;
	collider = App->collision->AddCollider(section, COLLIDER_POWER_UP, (Module*)App->powerup);

}


Powerup_Horse::~Powerup_Horse()
{
}


void Powerup_Horse::OnCollision()
{
	//INCREASE PLAYER HORSEPOWER
	if (App->player->horse == 0)
	{
	App->player->horse = 2;
	App->player->alarm_horse_sound = 7000+ SDL_GetTicks();
	App->audio->PlayFx(App->player->audio_horse, 0, 6);
	}
}

SDL_Rect Powerup_Horse::Draw()
{
	return{ 408, 5, 18, 18 };
}