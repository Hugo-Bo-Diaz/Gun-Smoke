#include "Application.h"
#include "Enemy_CookieBoss.h"
#include "ModuleCollision.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Moduleplayer.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleParticles.h"

#define PATH_DURATION 500
#define BULLET_INT_MIN 700
#define BULLET_INT_MAX 1000


Enemy_CookieBoss::Enemy_CookieBoss(int x, int y) : Enemy(x, y)
{

	animations[4].PushBack({ 330, 467, 21, 26 });
	animations[4].PushBack({ 10, 509, 22, 27 });
	animations[4].PushBack({ 51, 507, 24, 27 });
	animations[4].speed = 0.1f;

	animations[5].PushBack({ 214, 507, 17, 27 });
	animations[5].PushBack({ 257, 509, 14, 27 });
	animations[5].PushBack({ 297, 507, 14, 27 });
	animations[5].speed = 0.1f;

	animations[6].PushBack({ 135, 427, 20, 27 });
	animations[6].PushBack({ 257, 427, 17, 27 });
	animations[6].PushBack({ 296, 427, 19, 27 });
	animations[6].speed = 0.1f;

	animations[7].PushBack({ 135, 427, 20, 27 });
	animations[7].PushBack({ 257, 427, 17, 27 });
	animations[7].PushBack({ 296, 427, 19, 27 });
	animations[7].speed = 0.1f;

	animations[0].PushBack({ 18, 468, 15, 25 });
	animations[0].PushBack({ 175, 427, 16, 26 });
	animations[0].PushBack({ 336, 428, 15, 26 });
	animations[0].speed = 0.1f;

	animations[1].PushBack({ 93, 467, 19, 27 });
	animations[1].PushBack({ 130, 468, 17, 26 });
	animations[1].PushBack({ 175, 467, 17, 25 });
	animations[1].speed = 0.1f;

	animations[2].PushBack({ 214, 467, 18, 26 });
	animations[2].PushBack({ 255, 468, 18, 26 });
	animations[2].PushBack({ 294, 467, 18, 26 });
	animations[2].speed = 0.1f;

	animations[3].PushBack({ 330, 467, 21, 26 });
	animations[3].PushBack({ 10, 509, 22, 27 });
	animations[3].PushBack({ 51, 507, 24, 27 });
	animations[3].speed = 0.1f;

	animation = &animations[6];
	srand(time(NULL));

	collider = App->collision->AddCollider({ 0, 0, 18, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	col = App->collision->AddCollider({ 0, 0, 18, 10 }, COLLIDER_TYPE::COLLIDER_ENEMY_BASE, (Module*)App->enemies);

	original_pos.y = y;
	path_dest.y = position.y;
	path_dest.x = position.x;
	hp = 1;

	timer = SDL_GetTicks() + 2000;
}

int Enemy_CookieBoss::value_between(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void Enemy_CookieBoss::Move()
{
	if (SDL_GetTicks() > timer)
	{
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

		//move collider
		col->SetPos(position.x, position.y + 17);
		if (collider != nullptr)
			collider->SetPos(position.x, position.y);
	}
	else
	{
		position.y += 1;
		//look to player
		int pangle = 3 + trunc((M_PI / 8) + atan2(position.y - App->player->position.y, position.x - App->player->position.x) / (M_PI / 4));
		animation = &animations[pangle];

		//move collider
		col->SetPos(position.x, position.y + 17);
		if (collider != nullptr)
			collider->SetPos(position.x, position.y);

	}

}
Enemy_CookieBoss::~Enemy_CookieBoss()
{
	if (App->player->destroyed == false && hit == true)
	{
		App->player->score += 200;
	}

	App->particles->AddParticle(App->particles->cookiedeath, position.x, position.y, COLLIDER_NONE);
}
