#include "Application.h"
#include "Enemy_Boss.h"
#include "ModuleCollision.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Moduleplayer.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleParticles.h"

#define PATH_DURATION 1000
#define BULLET_INTERVAL 300


Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
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

	hp = 12;
}

int Enemy_Boss::value_between(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void Enemy_Boss::Move()
{
	switch (state)
	{
	case BOSS_MOVING:
		{
			if (moving == false)
			{
				bool path_valid = false;
				//select new path
				while (!path_valid)
				{
					path_dest.x = value_between(position.x - 50, position.x + 50);
					path_dest.y = value_between(position.y - 50, position.y + 50);

					if	(	(path_dest.x < 160		  && path_dest.x > 70   )
						&&	(path_dest.y < 160 - 2776 && path_dest.y > -2776)) // not out of zone -2976 -> final 
					{
						path_valid = true;
					}
				}
				path_from = position;
				moving = true;
				path_start = SDL_GetTicks();
			}

			//shoot next bullet

			//check destination
			uint elapsed = SDL_GetTicks() - path_start;
			if (elapsed > PATH_DURATION)//if he got there
			{
				elapsed = PATH_DURATION;
				moving = false;
				if (value_between(0, 1) == 1)//roll a 2-sided dice
				{
					state = BOSS_SHOOTING;
					shots_fired = value_between(3, 6);
					timer_shots = 0;
				}
			}

			//move towards path
			position.x = path_from.x + (path_dest.x - path_from.x) * (int)elapsed / PATH_DURATION;
			position.y = path_from.y + (path_dest.y - path_from.y) * (int)elapsed / PATH_DURATION;

		}
		break;
		case BOSS_SHOOTING:
		{
			if (SDL_GetTicks() > next_shot && shots_fired > 0 )
			{
				float bullet_angle = atan2(App->player->position.y - position.y, App->player->position.x - position.x)*180/M_PI +180;
				if (bullet_angle < 240 )
				{
					App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y, COLLIDER_ENEMY_SHOT, 0,0,1);
				}
				if (bullet_angle >= 240 && bullet_angle < 300)
				{
					App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y, COLLIDER_ENEMY_SHOT, 0, 0, 1);
				}
				if (bullet_angle > 360)
				{
					App->particles->AddParticle(App->particles->enemy_bullet, position.x, position.y, COLLIDER_ENEMY_SHOT, 0, 0, 1);
				}
				shots_fired -= 1;
				next_shot = SDL_GetTicks() + BULLET_INTERVAL;
			}
			if (shots_fired == 0)
			{
				state = BOSS_MOVING;
			}
		}
		break;
		case BOSS_CROUCHED:
		{
			if (SDL_GetTicks() > timer_crouch)// crouching is over
			{
				state = BOSS_MOVING;
			}

		}
		break;

	}
	//move collider
	collider->SetPos(position.x, position.y);
	col->SetPos(position.x, position.y + 17);

}
Enemy_Boss::~Enemy_Boss()
{
	if (App->player->destroyed == false)
	{
		App->player->score += 200;
	}
	App->particles->AddParticle(App->particles->cookiedeath, position.x, position.y, COLLIDER_NONE);
}
