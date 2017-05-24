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
	right_up_up.PushBack({ 341, 987, 11, 12 });
	right_up_down.PushBack({ 298, 988, 14, 11 });
	building_left.PushBack({216,972,16,9});
	right_down_up.PushBack({ 218, 991, 14, 10 });
	right_down_down.PushBack({ 179, 988, 16, 12 });

	left_up_up.PushBack({ 136, 968, 11, 12 });
	left_up_down.PushBack({ 176, 969, 14, 11 });
	building_right.PushBack({ 256,990,16,9 });
	left_down_up.PushBack({ 256, 972, 14, 10 });
	left_down_down.PushBack({ 296, 969, 13, 12 });

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
		float bullet_angle = M_PI / 8 * trunc((M_PI / 8) + atan2(App->player->position.y - position.y, App->player->position.x - position.x) / (M_PI / 8));
		App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y, COLLIDER_ENEMY_SHOT, 0, 3 * cos(bullet_angle), 3 * sin(bullet_angle));
		next_shot = SDL_GetTicks() + value_between(BULLET_INT_MIN, BULLET_INT_MAX);
	}
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
		int angle = trunc((M_PI / 8) + atan2(App->player->position.y - position.y, App->player->position.x - position.x) / (M_PI / 8));
		switch (angle)
		{
		case -2:
			animation = &left_up_up;
			break;
		case -1:
			animation = &left_up_down;
			break;
		case 0:
			animation = &building_left;
			break;
		case 1:
			animation = &left_down_up;
			break;
		case 2:
			animation = &left_down_down;
			break;
		case 6:
			animation = &right_down_down;
			break;
		case 7:
			animation = &right_down_up;
			break;
		case 8:
			animation = &building_right;
			break;
		case -7:
			animation = &right_up_down;
			break;
		case -6:
			animation = &right_up_up;
			break;
		default:
			break;
		}
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

	if (position.x > SCREEN_WIDTH / 2)
		App->particles->AddParticle(App->particles->sniperdeath_r,position.x,position.y);

	else
		App->particles->AddParticle(App->particles->sniperdeath_l, position.x, position.y);
}