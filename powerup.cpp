#include "powerup.h"
#include "ModuleCollision.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"


Powerup::Powerup(int x, int y)
{
	position.x = x;
	position.y = y;
}


Powerup::~Powerup()
{
	if (texture != nullptr)
	App->textures->Unload(texture);
}


const Collider* Powerup::GetCollider() const
{
	return collider;
}

const Collider* Powerup::GetCol() const
{
	return col;
}

void Powerup::Draw(SDL_Texture* sprites)
{
	if (sprites != nullptr)
		App->render->Blit(sprites, position.x, position.y, &section);
}