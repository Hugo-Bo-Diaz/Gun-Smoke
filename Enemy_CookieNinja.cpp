#include "Application.h"
#include "Enemy_CookieNinja.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Moduleplayer.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleParticles.h"

#define PATH_DURATION 500
#define BULLET_INT_MIN 1300
#define BULLET_INT_MAX 2000

#define PATH_1 1500
#define PATH_2 2000
#define PATH_3 2800


Enemy_CookieNinja::Enemy_CookieNinja(int x, int y) : Enemy(x, y)
{
	animations[4].PushBack({ 145, 83, 16, 28 });
	animations[4].PushBack({ 164, 83, 18, 28 });
	animations[4].PushBack({ 185, 83, 20, 28 });
	animations[4].speed = 0.1f;

	animations[5].PushBack({ 208, 83, 17, 28 });
	animations[5].PushBack({ 227, 83, 13, 28 });
	animations[5].PushBack({ 241, 83, 13, 28 });
	animations[5].speed = 0.1f;

	animations[6].PushBack({ 10, 113, 17, 30 });
	animations[6].PushBack({ 34, 113, 17, 30 });
	animations[6].PushBack({ 56, 113, 17, 30 });
	animations[6].speed = 0.1f;

	animations[7].PushBack({ 7, 51, 21, 30 });
	animations[7].PushBack({ 30, 51, 20, 30 });
	animations[7].PushBack({ 81, 114, 19, 30 });
	animations[7].speed = 0.1f;

	animations[0].PushBack({ 143, 51, 15, 30 });
	animations[0].PushBack({ 164, 51, 13, 30 });
	animations[0].PushBack({ 185, 51, 16, 30 });
	animations[0].speed = 0.1f;

	animations[1].PushBack({ 206, 51, 19, 29 });
	animations[1].PushBack({ 227, 51, 17, 30 });
	animations[1].PushBack({ 245, 51, 16, 30 });
	animations[1].speed = 0.1f;

	animations[2].PushBack({ 7, 83, 21, 28 });
	animations[2].PushBack({ 30, 83, 21, 28 });
	animations[2].PushBack({ 53, 83, 21, 29 });
	animations[2].speed = 0.1f;

	animations[3].PushBack({ 75, 83, 21, 28 });
	animations[3].PushBack({ 97, 83, 22, 28 });
	animations[3].PushBack({ 120, 83, 24, 28 });
	animations[3].speed = 0.1f;

	jumping.PushBack({ 103, 114, 25, 27, });

	animation = &jumping;
	srand(time(NULL));

	collider = App->collision->AddCollider({ 0, 0, 18, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	col = App->collision->AddCollider({ 0, 0, 18, 10 }, COLLIDER_TYPE::COLLIDER_ENEMY_BASE, (Module*)App->enemies);
	jump = SDL_GetTicks();

	original_pos.y = y;
	path_dest.y = position.y;
	path_dest.x = position.x;
	hp = 1;

}

int Enemy_CookieNinja::value_between(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void Enemy_CookieNinja::Move()
{
	if (SDL_GetTicks() > jump + PATH_3)
	{
		ignore_walls = false;
		if (moving == false)
		{
			bool path_valid = false;
			//select new path
			while (!path_valid)
			{
				path_dest.x = value_between(position.x - 25, position.x + 25);
				path_dest.y = value_between(position.y - 25, position.y + 25);

				if ((abs(path_dest.x - App->player->position.x) > 20)
					|| (abs(path_dest.y - App->player->position.y) > 20)) // not near player
				{
					if (path_dest.x > 0
						&& path_dest.x < SCREEN_WIDTH)// not out of screen(x)
					{
						path_valid = true;
					}
				}
			}
			path_from = position;
			moving = true;
			path_start = SDL_GetTicks();

		}

		//shoot next bullet
		if (SDL_GetTicks() > next_shot)
		{
			float bullet_angle = M_PI / 4 * trunc((M_PI / 8) + atan2(App->player->position.y - position.y, App->player->position.x - position.x) / (M_PI / 4));
			App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y, COLLIDER_ENEMY_SHOT, 0, 2 * cos(bullet_angle), 2 * sin(bullet_angle));
			next_shot = SDL_GetTicks() + value_between(BULLET_INT_MIN, BULLET_INT_MAX);
		}

		//check destination
		uint elapsed = SDL_GetTicks() - path_start;
		if (elapsed > PATH_DURATION)
		{
			elapsed = PATH_DURATION;
			moving = false;
		}

		//move towards path
		position.x = path_from.x + (path_dest.x - path_from.x) * (int)elapsed / PATH_DURATION;
		position.y = path_from.y + (path_dest.y - path_from.y) * (int)elapsed / PATH_DURATION;

		//look to player
		int pangle = 3 + trunc((M_PI / 8) + atan2(position.y - App->player->position.y, position.x - App->player->position.x) / (M_PI / 4));
		animation = &animations[pangle];

	}

	else if (SDL_GetTicks() > jump + PATH_2)
	{
		ignore_walls = true;
		position.x++;
		position.y++;
	}

	else if (SDL_GetTicks() > jump + PATH_1)
	{
		ignore_walls = true;
		position.x++;
	}

	else
	{
		ignore_walls = true;
		position.x;
	}

	//move collider
	col->SetPos(position.x, position.y + 17);
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

}
Enemy_CookieNinja::~Enemy_CookieNinja()
{
	if (App->player->destroyed == false && hit == true)
	{
		App->player->score += 200;
		App->enemies->Playsound(1);
	}

	App->particles->AddParticle(App->particles->cookiedeath, position.x, position.y, COLLIDER_NONE);
}
