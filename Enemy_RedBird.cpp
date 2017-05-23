#include "Application.h"
#include "Enemy_RedBird.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Moduleplayer.h"
#include "SDL/include/SDL_timer.h"

#define PATH_DURATION 500
#define BULLET_INT_MIN 700
#define BULLET_INT_MAX 1000

int Enemy_RedBird::value_between(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	building_left.PushBack({216,972,16,9});
	building_right.PushBack({ 256,990,16,9 });
	
	if(position.x > SCREEN_WIDTH / 2)
		animation = &building_right;

	else
		animation = &building_left;

	collider = App->collision->AddCollider({0, 0, 16, 9}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	
	hp = 1;
	if (position.x == 8 && position.y == 29 - 2806)
	{
		App->enemies->position_1 = false;
	}
	if (position.x == 200 && position.y == 60 - 2806)
	{
		App->enemies->position_2 = false;
	}
	if (position.x == 200 && position.y == 160 - 2806)
	{
		App->enemies->position_3 = false;
	}
}

void Enemy_RedBird::Move()
{
	if (SDL_GetTicks() > next_shot)
	{
		float bullet_angle = M_PI / 4 * trunc((M_PI / 8) + atan2(App->player->position.y - position.y, App->player->position.x - position.x) / (M_PI / 4));
		App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y, COLLIDER_ENEMY_SHOT, 0, 2 * cos(bullet_angle), 2 * sin(bullet_angle));
		next_shot = SDL_GetTicks() + value_between(BULLET_INT_MIN, BULLET_INT_MAX);
	}
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
}
Enemy_RedBird::~Enemy_RedBird()
{
	if (App->enemies->boss_alive)
	{
		if (position.x == 8 && position.y == 29 - 2806)
		{
			App->enemies->position_1 = true;
		}
		if (position.x == 200 && position.y == 60 - 2806)
		{
			App->enemies->position_2 = true;
		}
		if (position.x == 200 && position.y == 160 - 2806)
		{
			App->enemies->position_3 = true;
		}
	}

	if (App->player->destroyed == false && hit == true)
	{
		App->player->score += 500;
		App->enemies->Playsound(1);
	}
}