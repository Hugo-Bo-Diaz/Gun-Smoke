#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "Enemy_RedBird.h"
#include "Enemy_BrownCookie.h"
#include "Enemy_CookieNinja.h"
#include "Enemy_CookieBoss.h"
#include "Enemy_MechBoss.h"
#include "Enemy_Mech.h"
#include "Enemy_Rifle.h"
#include "Enemy_Boss.h"

#define SPAWN_MARGIN 650

ModuleEnemies::ModuleEnemies()
{
	section.x = 0;
	section.h = 8;
	section.w = 22;
	section.y = 0;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	sprites = App->textures->Load("gunsmoke/enemies.png");
	boss_alive = false;
	section.x = 425;
	section.y = 2032;
	section.w = 22;
	section.h = 8;

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if(queue[i].y * SCREEN_SIZE > App->render->camera.y + (App->render->camera.h * SCREEN_SIZE) - SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].y * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) 
		{ 
			enemies[i]->previous = enemies[i]->position;
			enemies[i]->Move();
		};

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Draw(sprites);
	if (boss_alive)
	{
		for (uint i = 0; i < MAX_ENEMIES; ++i)
		{
			if (enemies[i] != nullptr && enemies[i]->boss == true)
			{
				int squares = enemies[i]->squares;
				for (int i = 0; i < squares; ++i)
				{
					App->render->Blit(sprites, 5 + 25*i, -2795, &section);
				}
			}
		}
	}


	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to de-spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			if(enemies[i]->position.y * SCREEN_SIZE > (App->render->camera.y) + 495)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.y * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			{
				queue[i].type = ENEMY_TYPES::NO_TYPE;
			}
		}
	}


	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for(; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch(info.type)
		{
			case ENEMY_TYPES::REDBIRD:
			enemies[i] = new Enemy_RedBird(info.x,info.y);
			break;

			case ENEMY_TYPES::BROWNCOOKIE:
			enemies[i] = new Enemy_BrownCookie(info.x, info.y);
			break;

			case ENEMY_TYPES::COOKIENINJA:
			enemies[i] = new Enemy_CookieNinja(info.x, info.y);
			break;

			case ENEMY_TYPES::MECH:
			enemies[i] = new Enemy_Mech(info.x, info.y);
			break;

			case ENEMY_TYPES::RIFLE:
			enemies[i] = new Enemy_Rifle(info.x, info.y);
			break;

			case ENEMY_TYPES::BOSS:
			enemies[i] = new Enemy_Boss(info.x, info.y);
			break;

			case ENEMY_TYPES::COOKIEBOSS:
			enemies[i] = new Enemy_CookieBoss(info.x, info.y);
			break;

			case ENEMY_TYPES::MECHBOSS:
			enemies[i] = new Enemy_MechBoss(info.x, info.y);
			break;


		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if ((enemies[i] != nullptr) && ((enemies[i]->GetCollider() == c1) || (enemies[i]->GetCol() == c1)))
		{
			enemies[i]->OnCollision(c1, c2);
			if (c2->type == COLLIDER_PLAYER_SHOT)
			{
				enemies[i]->hp -= 1;
				enemies[i]->hit = true;
				if (enemies[i]->hp == 0)
				{
					delete enemies[i];
					enemies[i] = nullptr;
				}
			}
			break;
		}
	}
}

int ModuleEnemies::OnScreenEnemies()
{
	int ret = 0;
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			ret++;
		}
	}
	return ret;
}