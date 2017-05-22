#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePowerup.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"
#include "Powerup.h"
#include "Powerup_Boots.h"
#include "Powerup_Rifle.h"


ModulePowerup::ModulePowerup()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		powerups[i] = nullptr;
}

// Destructor
ModulePowerup::~ModulePowerup()
{
}

bool ModulePowerup::Start()
{

	sprites = App->textures->Load("gunsmoke/powerups.png");
	audio_pickup = App->audio->LoadFx("gunsmoke/powerup.wav");

	return true;
}

update_status ModulePowerup::PreUpdate()
{
	// check camera position to decide what to spawn
	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModulePowerup::Update()
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
		if (powerups[i] != nullptr)
		{
			SDL_Rect section = powerups[i]->Draw();
			App->render->Blit(sprites, powerups[i]->position.x, powerups[i]->position.y, &section);
		}

	return UPDATE_CONTINUE;
}

update_status ModulePowerup::PostUpdate()
{
	// check camera position to decide what to spawn
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModulePowerup::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);
	App->audio->UnLoadFx(audio_pickup);
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr)
		{
			delete powerups[i];
			powerups[i] = nullptr;
		}
	}

	return true;
}

bool ModulePowerup::AddPowerup(int x, int y, POWERUP_TYPE type)
{
	bool ret = false;
	uint i = 0;
	for (; powerups[i] != nullptr && i < MAX_POWERUPS; ++i);
	{
		if (i != MAX_POWERUPS)
		{
			switch (type)
			{
			case POWERUP_TYPE::POWERUP_BOOTS:
				powerups[i] = new Powerup_Boots(x, y);
				ret = true;
				break;

			case POWERUP_TYPE::POWERUP_RIFLE:
                powerups[i] = new Powerup_Rifle(x, y);
				ret = true;
				break;

			case POWERUP_TYPE::POWERUP_BULLETS:
				//powerups[i] = new Powerup_Bullets(x, y);
				ret = true;
				break;

			}
		}
	}
	return ret;
}

void ModulePowerup::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_POWERUPS; ++i)
	{
		if (powerups[i] != nullptr && powerups[i]->GetCollider() == c1 )
		{
			if (c2->type == COLLIDER_PLAYER)
			{
				powerups[i]->OnCollision();
				App->audio->PlayFx(audio_pickup);
				delete powerups[i];
				powerups[i] = nullptr;
			}
			break;
		}
	}
}