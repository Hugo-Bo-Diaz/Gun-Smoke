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
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

#define PATH_DURATION 1000
#define BULLET_INTERVAL 500
#define SPAWN_INTERVAL 2000

Enemy_Boss::Enemy_Boss(int x, int y) : Enemy(x, y)
{
	walking.PushBack({ 3, 196, 19, 32 });
	walking.PushBack({ 23, 196, 19, 32 });
	walking.PushBack({ 43, 196, 19, 32 });
	walking.speed = 0.1f;

	crouch_moving.PushBack({ 63, 196, 21, 29 });
	crouch_moving.PushBack({ 87, 196, 21, 30 });
	crouch_moving.PushBack({ 109, 196, 20, 29 });
	crouch_moving.speed = 0.1f;

	to_crouch.PushBack({ 131, 196, 18, 29 });
	to_crouch.PushBack({ 150, 196, 21, 21 });
	to_crouch.speed = 0.1f;

	shooting_front.PushBack({ 174, 196, 18, 35 });
	shooting_front.loop = false;

	shooting_left.PushBack({ 195, 196, 17, 34 });
	shooting_left.loop = false;

	shooting_down_left.PushBack({ 109, 196, 20, 29 });
	shooting_down_left.loop = false;
	 
	shooting_down_right.PushBack({ 63, 196, 21, 29 });
	shooting_down_right.loop = false;

	shooting_right.PushBack({ 216, 196, 17, 33 });
	shooting_right.loop = false;

	animation = &walking;
	srand(time(NULL));

	collider = App->collision->AddCollider({ 0, 0, 18, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	col = App->collision->AddCollider({ 0, 0, 18, 10 }, COLLIDER_TYPE::COLLIDER_ENEMY_BASE, (Module*)App->enemies);

	App->audio->StopMusic();
	App->audio->PlayMusic("gunsmoke/Gunsmoke_04.ogg");
	hit_audio = App->audio->LoadFx("gunsmoke/boss_hit.wav");
	audio_boss_death = App->audio->LoadFx("gunsmoke/boss_death.wav");

	original_pos.y = y;
	path_dest.y = position.y;
	path_dest.x = position.x;

	boss = true;
	squares = 4;

	App->enemies->boss_alive = true;

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
		App->audio->PlayFx(hit_audio);
	}

	if (App->enemies->OnScreenEnemies() < 7)
	{
		int pos_x;
		int pos_y;

		ENEMY_TYPES type;
		int random_loc = value_between(0, 1);
		int random_enemy = value_between(0,1);
		if (random_loc == 0)
		{
			pos_x = -10;
			pos_y = value_between(110,160) - 2776; //140
		}
		else if (random_loc == 1)
		{
			pos_x = value_between(100,110);//100
			pos_y = -2825;
		}
		if (random_enemy == 0)
		{
			if (random_loc == 1)
			{type = COOKIEBOSS;}
			else
			{type = BROWNCOOKIE;}
		}
		else if (random_enemy == 1)
		{
			if (random_loc == 1)
			{type = MECHBOSS;}
			else
			{type = MECH;}
		}

		if (SDL_GetTicks() > timer_spawn || App->enemies->OnScreenEnemies() < 4)
		{
			App->enemies->AddEnemy(type, pos_x, pos_y);
			timer_spawn = SDL_GetTicks() + SPAWN_INTERVAL;
		}
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
						&&	(path_dest.y < 120 - 2776 && path_dest.y > -2776)) // not out of zone -2976 -> final 
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
			if (moving == false)
			{
				bool path_valid = false;
				//select new path
				while (!path_valid)
				{
					path_dest.x = value_between(position.x - 25, position.x + 25);
					path_dest.y = value_between(position.y - 25, position.y + 25);

					if ((path_dest.x < 160 && path_dest.x > 70)
						&& (path_dest.y < 120 - 2776 && path_dest.y > -2776)) // not out of zone -2976 -> final 
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
			}

			//move towards path
			position.x = path_from.x + (path_dest.x - path_from.x) * (int)elapsed / PATH_DURATION;
			position.y = path_from.y + (path_dest.y - path_from.y) * (int)elapsed / PATH_DURATION;

			collider->SetPos(position.x, position.y+1000);
			

		}
		break;
	}
	//move collider
	col->SetPos(position.x, position.y + 17);

}
Enemy_Boss::~Enemy_Boss()
{
	App->audio->PlayFx(audio_boss_death);

	if (App->player->destroyed == false)
	{
		App->player->score += App->player->lifes * 10000;

		App->particles->AddParticle(App->particles->boss_death, position.x, position.y, COLLIDER_NONE);
		App->player->death_time = SDL_GetTicks() + 3000;
	}
	//App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_gameover);

	App->audio->UnLoadFx(audio_boss_death);
	App->audio->UnLoadFx(hit_audio);
}

