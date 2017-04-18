#include "Application.h"
#include "Enemy_RedBird.h"
#include "ModuleCollision.h"

Enemy_RedBird::Enemy_RedBird(int x, int y) : Enemy(x, y)
{
	fly.PushBack({0,0,18,27});
/*	fly.PushBack({38, 6, 24, 24});
	fly.PushBack({71, 6, 24, 24});
	fly.PushBack({104, 6, 24, 24});
	fly.PushBack({137, 6, 24, 24});
	fly.PushBack({170, 6, 24, 24});
	fly.PushBack({203, 6, 24, 24});
	fly.PushBack({236, 6, 24, 24});*/
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({0, 0, 18, 27}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Enemy_RedBird::Move()
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

	position.y;

	//position.y = original_y + (25.0f * sinf(wave));
	//position.x -= 1;
}
