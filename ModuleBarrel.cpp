#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleBarrel.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
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
	hurt_sound = App->audio->LoadFx("gunsmoke/barrel_hit.wav");

	return true;
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


// Called before quitting
bool ModuleBarrel::CleanUp()
{
	LOG("Freeing all barrels");

	App->textures->Unload(sprites);
	App->audio->UnLoadFx(hurt_sound);

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
			if (c2->type == COLLIDER_PLAYER_SHOT)
			{
				if (barrels[i]->hp > 0)
				{
					App->audio->PlayFx(hurt_sound);
					barrels[i]->hp -= 1;
				}
				else
				{
				barrels[i]->OnCollision();
				delete barrels[i];
				barrels[i] = nullptr;
				}

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