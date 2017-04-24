#include "Application.h"
#include "Enemy_RedBird.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	fly.PushBack({216,553,16,9});

	animation = &fly;

	collider = App->collision->AddCollider({0, 0, 16, 9}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_RedBird::Shoot()
{
	/*if(going_up)
	{
		if(wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if(wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}*/

	//position.y;

	//position.y = original_y + (25.0f * sinf(wave));
	//position.x -= 1;
	int i = 5;

	for (;;) {
		if (i = 0)
		{
			App->particles->AddParticle(App->particles->shot_g, position.x + 12, position.y, COLLIDER_ENEMY_SHOT);
			int i = 5;
		}

		else i -= 1;
	}
}
