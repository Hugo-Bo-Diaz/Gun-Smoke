#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleBarrel.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Barrel.h"


ModuleBarrel::ModuleBarrel()
{
	for (uint i = 0; i < MAX_BARRELS; ++i)
		barrels[i] = nullptr;
}

// Destructor
ModuleBarrel::~ModuleBarrel()
{
}

bool ModuleBarrel::Start()
{

	sprites = App->textures->Load("gunsmoke/barrels.png");

	return true;
}

update_status ModuleBarrel::PreUpdate()
{
	// check camera position to decide what to spawn
	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleBarrel::Update()
{
	for (uint i = 0; i < MAX_BARRELS; ++i)
		if (barrels[i] != nullptr)
		{
			barrels[i]->Draw();
		}

	return UPDATE_CONTINUE;
}

update_status ModuleBarrel::PostUpdate()
{
	// check camera position to decide what to spawn
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleBarrel::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for (uint i = 0; i < MAX_BARRELS; ++i)
	{
		if (barrels[i] != nullptr)
		{
			delete barrels[i];
			barrels[i] = nullptr;
		}
	}

	return true;
}

void ModuleBarrel::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_BARRELS; ++i)
	{
		if (barrels[i] != nullptr && barrels[i]->GetCollider() == c1)
		{
			if (c2->type == COLLIDER_PLAYER_BASE)
			{
				barrels[i]->OnCollision();
			}
			break;
		}
	}
}

void ModuleBarrel::AddBarrel(int x, int y, POWERUP_TYPE type)
{

	uint i = 0;
	for (; barrels[i] != nullptr && i < MAX_BARRELS; ++i);
	{
		if (i != MAX_BARRELS)
		{
			barrels[i] = new Barrel(x, y, type);
		}
	}
}