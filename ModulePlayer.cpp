#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"

#include<stdio.h>
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
	position.x = 120;
	position.y = 200;
	camera_y = 0;
	
	audio_shot = App->audio->LoadFx("gunsmoke/shotfx.wav");

	font_score = App->fonts->Load("fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);
	font_score = App->fonts->Load("fonts/font.png", "0123456789abcdefghijklmnopqrstuvwxyz", 1);
	col = App->collision->AddCollider({position.x, position.y, 19, 28}, COLLIDER_PLAYER, this);
	col_base= App->collision->AddCollider({ position.x, position.y+18, 17, 9 }, COLLIDER_PLAYER_BASE,this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->audio->UnLoadFx(audio_shot);
	App->textures->Unload(graphics);
	if (col != nullptr)
		col->to_delete = true;

	return true;
}

update_status ModulePlayer::PreUpdate()
{
	previous = position;
	return UPDATE_CONTINUE;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	if (App->render->camera.y == (-2814 * SCREEN_SIZE))
		position.y;// Automatic movement

	else if (itstime)
	{
		position.y -= 1;
		camera_y -= 1;
		itstime = false;
	}

	if (timer < 1)
	{
		timer++;
	}
	else
	{
		timer = 0;
	}

	if (timer == 1)
	{
		itstime = true;
	}
	else
	{
		itstime = false;
	}



	int speed = 1;

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && camera_y < position.y)
	{
		position.y -= speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && camera_y + SCREEN_HEIGHT - 5 > position.y + 32)
	{
		position.y += speed;
	}

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT &&
		App->render->camera.x + SCREEN_WIDTH > position.x + 19)
	{
		position.x += speed;
		if(current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
	}

	if(App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && App->render->camera.x < position.x)
	{
		position.x -= speed;
		if(current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
	}
	/*

	  z x c
	z n d l    0 1 2 3 4 5
	x X n d
	c X X n

	*/

	bool press_z = false;
	bool press_x = false;
	bool press_c = false;
	if (cooldown > 0)
	{
		cooldown -= 1;
	}


	if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN)
	{time_z= 5;}

	if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN)
	{time_x = 5;}

	if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN)
	{time_c = 5;}


	if (time_z > 0)
	{
		time_z -= 1;
	}

	if (time_z == 0)
	{press_z = false;}
	else { press_z = true; }



	if (time_x > 0)
	{
		time_x -= 1;
	}

	if (time_x == 0)
	{press_x = false;}
	else { press_x = true; }



	if (time_c > 0)
	{
		time_c -= 1;
	}

	if (time_c == 0)
	{press_c = false;}
	else { press_c = true; }

	//combined shots
	if (press_z && press_x&& cooldown < 5)
	{
		App->particles->AddParticle(App->particles->shot_l_up, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->shot_l_down, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
		time_z = 0; time_x = 0;
		cooldown = COOLDOWN;
		App->audio->PlayFx(audio_shot);
	}

	if (press_x && press_c&& cooldown < 5)
	{
		App->particles->AddParticle(App->particles->shot_r_up, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->shot_r_down, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
		time_z = 0; time_x = 0;
		cooldown = COOLDOWN;
		App->audio->PlayFx(audio_shot);
	}

	if (press_z && press_c&& cooldown < 5)
	{
		App->particles->AddParticle(App->particles->shot_r, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->shot_l, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
		time_z = 0; time_x = 0;
		cooldown = COOLDOWN;
		App->audio->PlayFx(audio_shot);
	}

	//simple shots
	if (press_z && time_z !=0 && cooldown == 0 && App->input->keyboard[SDL_SCANCODE_J])
	{
		App->particles->AddParticle(App->particles->shot_l, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->shot_l, position.x + 2, position.y + 10, COLLIDER_PLAYER_SHOT);
		cooldown = COOLDOWN;
		App->audio->PlayFx(audio_shot);

	}
	if (press_x && time_x != 0 && cooldown == 0 && App->input->keyboard[SDL_SCANCODE_K])
	{
		App->particles->AddParticle(App->particles->laser, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->laser, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
		cooldown = COOLDOWN;
		App->audio->PlayFx(audio_shot);


	}
	if (press_c && time_c != 0 && cooldown == 0 && App->input->keyboard[SDL_SCANCODE_L])
	{
		App->particles->AddParticle(App->particles->shot_r, position.x + 12, position.y + 10, COLLIDER_PLAYER_SHOT);
		App->particles->AddParticle(App->particles->shot_r, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
		cooldown = COOLDOWN;
		App->audio->PlayFx(audio_shot);
	}

	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
	{
		current_animation = &idle;
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
		&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		current_animation = &idle;
	}

	col->SetPos(position.x, position.y);
	col_base->SetPos(position.x+1, position.y+18);

	// Draw everything --------------------------------------
	if(destroyed == false)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	sprintf_s(scores, 8, "%7d", score);
	App->fonts->BlitText(8,8,font_score,scores);

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if(c1 == col_base && c1->type == COLLIDER_PLAYER_BASE && c2->type == COLLIDER_WALL && destroyed == false && App->fade->IsFading() == false)
	{
		/*if ((c1->rect.x + c1->rect.w) - c2->rect.x < abs(2))
			position.x = (c2->rect.x - c1->rect.w);

		else if ((c2->rect.x + c2->rect.w) - c1->rect.x < abs(2))
			position.x = (c2->rect.x + c2->rect.w);

		else if ((c1->rect.y - c1->rect.h) - c2->rect.y > abs(2))
			position.y = (c2->rect.y + c1->rect.h);

		else if ((c2->rect.y - c2->rect.h) - c1->rect.y > abs(2))
			position.y = (c2->rect.y - c2->rect.h);*/

		int horiz, vert;
		if (c1->rect.x < c2->rect.x)
			horiz = c1->rect.x + c1->rect.w - c2->rect.x;
		else 
			horiz = c2->rect.x + c2->rect.w - c1->rect.x;
		if (c1->rect.y < c2->rect.y)
			vert =c1->rect.y + c1->rect.h - c2->rect.y;
		else 
			vert = c2->rect.y + c2->rect.h - c1->rect.y;
		if (horiz < vert)
			position.x = previous.x;
		else 
			position.y = previous.y;
	}

	if (c1 == col && c2->type == COLLIDER_ENEMY_SHOT
		&& destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_intro);

		destroyed = true;
	}
	if (c1 == col_base && c2->type == COLLIDER_ENEMY_BASE 
		&& destroyed == false && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_intro);

		destroyed = true;
	}


}