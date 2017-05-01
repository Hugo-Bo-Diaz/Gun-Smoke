#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

Enemy::Enemy(int x, int y) : position(x, y)
{
	moving = false;
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
	if (col != nullptr)
		col->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

const Collider* Enemy::GetCol() const
{
	return col;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	if(collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == col && c1->type == COLLIDER_ENEMY_BASE && c2->type == COLLIDER_WALL)
	{ 
		int horiz, vert;
		if (c1->rect.x < c2->rect.x)
			horiz = c1->rect.x + c1->rect.w - c2->rect.x;
		else
			horiz = c2->rect.x + c2->rect.w - c1->rect.x;
		if (c1->rect.y < c2->rect.y)
			vert = c1->rect.y + c1->rect.h - c2->rect.y;
		else
			vert = c2->rect.y + c2->rect.h - c1->rect.y;
		if (horiz < vert)
			position.x = previous.x;
		else
			position.y = previous.y;
		moving = false;
	}
	if (c1 == collider)
	{
		//App->particles->AddParticle(App->particles->explosion, position.x, position.y);
	}
}

