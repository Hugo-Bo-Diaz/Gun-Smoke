#include "Application.h"
#include "Enemy_Rifle.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Moduleplayer.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleParticles.h"

#define PATH_1 1000
#define PATH_2 2000
#define PATH_3 3000

Enemy_Rifle::Enemy_Rifle(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 139, 10, 16, 30 });
	fly.PushBack({ 156, 10, 16, 29 });
	fly.PushBack({ 173, 11, 16, 28 });
	fly.PushBack({ 191, 10, 16, 27 });
	fly.PushBack({ 209, 10, 18, 29 });
	fly.speed = 0.1f;
	fly.loop = true;
	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 16, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	timer = SDL_GetTicks();
	original_pos.x = x;
	original_pos.y = y;

	hp = 3;
}

void Enemy_Rifle::Move()
{
	if (SDL_GetTicks()>timer+PATH_3)
	{ 
		position.y -= 1;
	}
	else if (SDL_GetTicks()>timer + PATH_2)
	{
		timer_2 =timer +  1000 * shots_fired;
		if (SDL_GetTicks() > timer_2 && App->player->horse_jump == -1)
		{
			float bullet_angle = M_PI / 4 * trunc((M_PI / 8) + atan2(App->player->position.y - position.y, App->player->position.x - position.x) / (M_PI / 4));
			App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y, COLLIDER_ENEMY_SHOT, 0, 4 * cos(bullet_angle), 4 * sin(bullet_angle));

			//App->particles->AddParticle(App->particles->enemy_bullet, position.x+ 8, position.y, COLLIDER_ENEMY_SHOT, 0, 0, 5);
			shots_fired++;
		}
	}
	else if (SDL_GetTicks()>timer + PATH_1)
	{
		position.y += 1;
	}

	if (SDL_GetTicks() > timer + PATH_3 + 10000)
	{
		// this means he dead
	}
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}
Enemy_Rifle::~Enemy_Rifle()
{
	if (App->player->destroyed == false && hit == true)
	{
		App->player->score += 500;
		App->enemies->Playsound(0);
	}
}