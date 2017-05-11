#include "Application.h"
#include "Enemy_Mech.h"
#include "ModuleCollision.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Moduleplayer.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleParticles.h"

#define PATH_DURATION 500
#define BULLET_INT_MIN 2000
#define BULLET_INT_MAX 2500
#define BOMB_DELAY 12000


Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	walk.PushBack({ 333, 546, 23, 28 });
	walk.PushBack({ 374, 545, 20, 30 });
	walk.PushBack({ 412, 546, 22, 28 });
	walk.PushBack({ 456, 545, 19, 30 });
	walk.speed = 0.1f;
	animation = &walk;
	
	/*path.PushBack({ -1.0f,-0.75f }, 120);
	path.PushBack({ -1.0f,0.75f }, 100);
	path.PushBack({ -1.0f,1.25f }, 100);*/

	collider = App->collision->AddCollider({ 0, 0, 20, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	col = App->collision->AddCollider({ 0, 0, 20, 10 }, COLLIDER_TYPE::COLLIDER_ENEMY_BASE, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
	path_dest.y = position.y;
	path_dest.x = position.x;

	hp = 1;
}

int Enemy_Mech::value_between(int min, int max)
{
	return rand() % (max - min + 1) + min;
}


void Enemy_Mech::Move()
{

	if (moving == false)
	{
		bool path_valid = false;
		//select new path
		while (!path_valid)
		{
			path_dest.x = value_between(position.x - 25, position.x + 25);
			path_dest.y = value_between(position.y - 40, position.y + 20);

			if ((   abs(path_dest.x - App->player->position.x) > 20)
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
	//shoot next mine
	if (SDL_GetTicks() > next_shot)
	{
		bullet_angle = M_PI / 4 * trunc((M_PI / 8) + atan2(App->player->position.y - position.y, App->player->position.x - position.x) / (M_PI / 4));
		App->particles->AddParticle(App->particles->tnt, position.x, position.y, COLLIDER_NONE, 2, 0, 2 * sin(bullet_angle));
		bombdelay = SDL_GetTicks() + 800;

		next_shot = SDL_GetTicks() + value_between(BULLET_INT_MIN, BULLET_INT_MAX);
	}


	if (SDL_GetTicks() > bombdelay) {
		App->particles->AddParticle(App->particles->explosion, position.x, position.y + 70, COLLIDER_ENEMY_BASE, 0, 0, 0);
		bombdelay += 100000;

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

	animation = &walk;

	//move collider
	col->SetPos(position.x, position.y + 20);

}

Enemy_Mech::~Enemy_Mech()
{
	if (App->player->destroyed == false)
	{
		App->player->score += 300;
	}

	App->particles->AddParticle(App->particles->mechdeath, position.x, position.y, COLLIDER_NONE);
}