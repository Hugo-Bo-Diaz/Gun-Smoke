#include "Application.h"
#include "Enemy_Rifle.h"
#include "ModuleCollision.h"


Enemy_Rifle::Enemy_Rifle(int x, int y) : Enemy(x, y)
{
	fly.PushBack({ 215,210,16,27 });

	animation = &fly;

	/*path.PushBack({0, 0.5f }, 50);
	path.PushBack({ -0.5f, 0.5f }, 70);
	path.PushBack({ 0.5f, 0.5f }, 30);
	path.PushBack({ 0.5f, 0.5f }, 100);
	path.PushBack({ 0, 0.5f }, 500);*/

	//path.PushBack({-1.0f,0.75f }, 100);
	//path.PushBack({-1.0f,1.25f }, 100);

	collider = App->collision->AddCollider({ 0, 0, 16, 27 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_Rifle::Move()
{
	position = original_pos + path.GetCurrentPosition();
}

/*void Enemy_BrownCookie::Shoot()
{

App->particles->AddParticle(App->particles->shot_g, position.x + 12, position.y, COLLIDER_ENEMY_SHOT);
//position = original_pos + path.GetCurrentPosition();
}*/
