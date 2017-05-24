#include "Application.h"
#include "Enemy_Stabby.h"
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

#define PATH_1 2500
#define PATH_2 3000
#define PATH_3 3800
#define PATH_4 4000 
#define PATH_5 4500 
#define PATH_6 5000 
#define PATH_7 5100 
#define PATH_8 5900 
#define PATH_9 8000

Enemy_Stabby::Enemy_Stabby(int x, int y) : Enemy(x, y)
{

	horizontal.PushBack({ 450, 586, 22, 24, });
	up.PushBack({ 411, 584, 22, 26, });
	down.PushBack({ 372, 587, 19, 25, });
	floor.PushBack({ 336, 589, 20, 24, });


	animation = &horizontal;
	srand(time(NULL));

	collider = App->collision->AddCollider({ 0, 0, 22, 26 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	col = App->collision->AddCollider({ 0, 0, 22, 9 }, COLLIDER_TYPE::COLLIDER_ENEMY_BASE, (Module*)App->enemies);
	jump = SDL_GetTicks();

	original_pos.y = y;
	path_dest.y = position.y;
	path_dest.x = position.x;

	hp = 2;

}

int Enemy_Stabby::value_between(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

void Enemy_Stabby::Move()
{

	//move collider
	col->SetPos(position.x, position.y + 16);
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (SDL_GetTicks() > jump + PATH_9)
	{

	}

	else if (SDL_GetTicks() > jump + PATH_8)
	{
		animation = &horizontal;
		collider->SetPos(position.x + 500, position.y);
		col->SetPos(position.x + 500, position.y + 16);
		ignore_walls = true;
		position.x--;
	}

	else if (SDL_GetTicks() > jump + PATH_7)
	{
		animation = &up;
		collider->SetPos(position.x + 500, position.y);
		col->SetPos(position.x + 500, position.y + 16);
		ignore_walls = true;
		position.x--;
		position.y--;
	}

	else if (SDL_GetTicks() > jump + PATH_6)
	{
		animation = &floor;
		ignore_walls = true;
		//position.x--;
	}

	else if (SDL_GetTicks() > jump + PATH_5)
	{
		animation = &down;
		collider->SetPos(position.x + 500, position.y);
		col->SetPos(position.x + 500, position.y + 16);
		ignore_walls = true;
		position.x--;
		position.y++;
	}

	else if (SDL_GetTicks() > jump + PATH_4)
	{
		animation = &up;
		collider->SetPos(position.x + 500, position.y);
		col->SetPos(position.x + 500, position.y + 16);
		ignore_walls = true;
		position.x--;
		position.y--;
	}

	else if (SDL_GetTicks() > jump + PATH_3)
	{
		animation = &floor;
		ignore_walls = true;
		//position.x--;
		//	position.y--;
	}

	else if (SDL_GetTicks() > jump + PATH_2)
	{
		animation = &down;
		collider->SetPos(position.x + 500, position.y);
		col->SetPos(position.x + 500, position.y + 16);
		ignore_walls = true;
		position.x--;
		position.y++;
	}

	else if (SDL_GetTicks() > jump + PATH_1)
	{
		animation = &horizontal;
		collider->SetPos(position.x + 500, position.y);
		col->SetPos(position.x + 500, position.y + 16);
		ignore_walls = true;
		position.x--;
	}

	else
	{
		animation = &floor;
		collider->SetPos(position.x + 500, position.y);
		col->SetPos(position.x + 500, position.y + 16);
		ignore_walls = true;
		position.x;
	}

}
Enemy_Stabby::~Enemy_Stabby()
{
	if (App->player->destroyed == false && hit == true)
	{
		App->player->score += 200;
	}

	App->particles->AddParticle(App->particles->stabbydeath, position.x, position.y, COLLIDER_NONE);
}
