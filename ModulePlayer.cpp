#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	// idle animation (just the ship)
	idle.PushBack({ 23, 15, 20, 32 });
	idle.PushBack({ 63, 15, 20, 32 });
	idle.PushBack({ 103, 15, 20, 32 });
	idle.PushBack({ 142, 15, 20, 32 });
	idle.PushBack({ 183, 15, 20, 32 });
	idle.speed = 0.2f;

	// move left
	left.PushBack({ 25, 95, 22, 32 });
	left.PushBack({ 65, 95, 22, 32 });
	left.PushBack({ 105, 95, 22, 32 });
	left.PushBack({ 145, 95, 22, 32 });
	left.PushBack({ 185, 95, 22, 32 });
	left.speed = 0.2f;

	// Move right
	right.PushBack({ 25, 56, 22, 32 });
	right.PushBack({ 65, 56, 22, 32 });
	right.PushBack({ 105, 56, 22, 32 });
	right.PushBack({ 145, 56, 22, 32 });
	right.PushBack({ 185, 56, 22, 32 });
	right.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("gunsmoke/player.png");

	destroyed = false;
	position.x = 150;
	position.y = 120;

	col = App->collision->AddCollider({position.x, position.y, 19, 28}, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	if (col != nullptr)
		col->to_delete = true;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	position.y -= 1; // Automatic movement

	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{
		position.y += speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if(current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if(current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->laser, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
	}

	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->shot_l, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->shot_l, position.x + 2, position.y + 10, COLLIDER_PLAYER_SHOT);
	}

	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->shot_r, position.x + 12, position.y + 10, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->shot_r, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
	   && App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
		current_animation = &idle;

	col->SetPos(position.x, position.y);

	// Draw everything --------------------------------------
	if(destroyed == false)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if(c1 == col && c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_WALL && destroyed == false && App->fade->IsFading() == false)
	{
		if ((c1->rect.x + c1->rect.w) - c2->rect.x < abs(2))
			position.x = (c2->rect.x - c1->rect.w);

		else if ((c2->rect.x + c2->rect.w) - c1->rect.x < abs(2))
			position.x = (c2->rect.x + c2->rect.w);

		/*else if ((c1->rect.y + c1->rect.h) - c2->rect.y < abs(2))
			position.y = (c2->rect.y - c1->rect.h);*/

		else if ((c2->rect.y + c2->rect.h) - c1->rect.y < abs(3))
			position.y = (c2->rect.y + c2->rect.h);
		
		//App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_intro);

	}

	if (c1 == col && (c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_ENEMY_SHOT)
		&& destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_intro);

		destroyed = true;
	}


}