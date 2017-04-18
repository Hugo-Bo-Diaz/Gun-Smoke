#include "Application.h"
#include "Enemy_Mech.h"
#include "ModuleCollision.h"


Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	walk_left.PushBack({ 5,72,21,22 });
	walk_left.PushBack({ 5,72,21,22 });
	walk_left.PushBack({ 5,72,21,22 });

	walk_right.PushBack({ 5,72,21,22 });
	walk_right.PushBack({ 5,72,21,22 });
	walk_right.PushBack({ 5,72,21,22 });

	animation = &walk_left;
	
	path.PushBack({ -1.0f,-0.75f }, 120);
	path.PushBack({ -1.0f,0.75f }, 100);
	path.PushBack({ -1.0f,1.25f }, 100);

	collider = App->collision->AddCollider({ 0, 0, 21, 22 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Mech::Move()
{
	if (position.x < 50)
	{
		animation = &walk_right;
	}
	position = original_pos + path.GetCurrentPosition();
}