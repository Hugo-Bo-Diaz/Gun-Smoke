#include "Application.h"
#include "Enemy_Boss.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleTextures.h"
#include <stdlib.h>
#include <time.h>
#include <cmath>
#include "Moduleplayer.h"
#include "SDL/include/SDL_timer.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#define PATH_DURATION 1000
#define BULLET_INTERVAL 500


Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	walking.PushBack({ 14, 1011, 19, 28 });
	walking.PushBack({ 54, 1010, 19, 29 });
	walking.PushBack({ 94, 1011, 19, 29 });
	walking.speed = 0.1f;

	crouch_moving.PushBack({ 131, 1013, 23, 25 });
	crouch_moving.PushBack({ 173, 1012, 21, 27 });
	crouch_moving.PushBack({ 214, 1012, 20, 26 });
	crouch_moving.speed = 0.1f;

	to_crouch.PushBack({ 254, 1012, 18, 25 });
	to_crouch.PushBack({ 293, 1019, 21, 20 });
	to_crouch.speed = 0.1f;

	shooting_front.PushBack({413, 1010, 20, 29});
	shooting_front.loop = false;

	shooting_left.PushBack({ 371, 1010, 21, 29 });
	shooting_left.loop = false;

	shooting_down_left.PushBack({ 333, 1010, 20, 29 });
	shooting_down_left.loop = false;
	 
	shooting_down_right.PushBack({ 335, 1052, 18, 29});
	shooting_down_right.loop = false;

	shooting_right.PushBack({ 377, 1053, 20, 28 });
	shooting_right.loop = false;

	animation = &walking;
	srand(time(NULL));

	collider = App->collision->AddCollider({ 0, 0, 18, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	col = App->collision->AddCollider({ 0, 0, 18, 10 }, COLLIDER_TYPE::COLLIDER_ENEMY_BASE, (Module*)App->enemies);

	hp_bar = App->textures->Load("gunsmoke/boss_hp_bar.png");

	section.x = 0;
	section.h = 8;
	section.w = 22;
	section.y = 0;

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
	int prev_squares = squares;
	if (hp <= 3)
	{
		squares = 1;
	}
	else if (hp <= 6)
	{
		squares = 2;
	}
	else if (hp <= 9)
	{
		squares = 3;
	}
	if (prev_squares != squares)
	{
		state = BOSS_CROUCHED;
		timer_crouch = SDL_GetTicks() + value_between(3000, 6000);
	}
	if (App->enemies->OnScreenEnemies() < 10)
	{
		int pos_x;
		int pos_y;
		ENEMY_TYPES type;
		int random_loc = value_between(0, 1);
		int random_enemy = value_between(0,1);
		if (random_loc == 0)
		{
			pos_x = -10;
			pos_y = 160 - 2776;
		}
		else if (random_loc == 1)
		{
			pos_x = 100;
			pos_y = -3000;
		}
		if (random_enemy == 0)
		{
			type = BROWNCOOKIE;
		}
		else if (random_enemy == 1)
		{
			type = MECH;
		}
		App->enemies->AddEnemy(type, pos_x,pos_y);
	}

	switch (state)
	{
	case BOSS_MOVING:
		{
			animation = &walking;
			if (moving == false)
			{
				bool path_valid = false;
				//select new path
				while (!path_valid)
				{
					path_dest.x = value_between(position.x - 50, position.x + 50);
					path_dest.y = value_between(position.y - 50, position.y + 50);

					if	(	(path_dest.x < 160		  && path_dest.x > 70   )
						&&	(path_dest.y < 140 - 2776 && path_dest.y > -2776)) // not out of zone -2976 -> final 
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

			collider->SetPos(position.x, position.y);
			col->SetPos(position.x, position.y + 17);


		}
		break;
		case BOSS_SHOOTING:
		{
			if (SDL_GetTicks() > next_shot && shots_fired > 0 )
			{
				float bullet_angle = atan2(App->player->position.y - position.y, App->player->position.x - position.x)*180/M_PI +180;
				if (bullet_angle < 216 )
				{
					App->particles->AddParticle(App->particles->boss_shot_r, position.x, position.y, COLLIDER_ENEMY_SHOT);
				}
				else if (bullet_angle >= 216 && bullet_angle < 252)
				{
					App->particles->AddParticle(App->particles->boss_shot_dr, position.x, position.y, COLLIDER_ENEMY_SHOT);
				}
				else if (bullet_angle >= 252 && bullet_angle < 288)
				{
					App->particles->AddParticle(App->particles->boss_shot_d, position.x, position.y, COLLIDER_ENEMY_SHOT);
				}
				else if (bullet_angle >= 288 && bullet_angle < 324)
				{
					App->particles->AddParticle(App->particles->boss_shot_dl, position.x, position.y, COLLIDER_ENEMY_SHOT);
				}
				else if (bullet_angle > 360)
				{
					App->particles->AddParticle(App->particles->boss_shot_l, position.x, position.y, COLLIDER_ENEMY_SHOT);
				}
				shots_fired -= 1;
				next_shot = SDL_GetTicks() + BULLET_INTERVAL;
			}
			if (shots_fired == 0)
			{
				state = BOSS_MOVING;
			}
			collider->SetPos(position.x, position.y);
			col->SetPos(position.x, position.y + 17);

		}
		break;
		case BOSS_CROUCHED:
		{
			animation = &crouch_moving;
			if (SDL_GetTicks() > timer_crouch)// crouching is over
			{
				state = BOSS_MOVING;
			}
			collider->SetPos(position.x, position.y+1000);
			col->SetPos(position.x, position.y + 17 +1000);

		}
		break;
	}
	//move collider
		for (int i = 0; i < squares; ++i)
		{
			App->render->Blit(hp_bar,25*i, 100, &section);
		}

}
Enemy_Boss::~Enemy_Boss()
{
	if (App->player->destroyed == false)
	{
		App->player->score += App->player->lifes*10000;
	}
	App->particles->AddParticle(App->particles->cookiedeath, position.x, position.y, COLLIDER_NONE);
}
