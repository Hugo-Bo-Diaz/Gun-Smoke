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
#include "ModuleSceneSpace.h"
#include "ModuleEnemies.h"
#include "SDL/include/SDL_timer.h"

#include<stdio.h>
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

#define HORSE_AUDIO_DURATION 7000

ModulePlayer::ModulePlayer()
{
	powerup[0] = 0;
	powerup[1] = 0;
	powerup[2] = 0;

	// idle animation (just the ship)
	idle.PushBack({ 4, 8, 19, 29 });
	idle.PushBack({ 25, 8, 20, 29 });
	idle.PushBack({ 48, 8, 19, 29 });
	idle.PushBack({ 70, 8, 20, 29 });
	idle.PushBack({ 91, 8, 21, 29 });
	idle.speed = 0.2f;

	// move left
	left.PushBack({ 24, 73, 16, 26 });
	left.PushBack({ 4, 74, 17, 29 });
	left.PushBack({ 242, 72, 17, 30 });
	left.PushBack({ 219, 72, 17, 30 });
	left.PushBack({ 194, 72, 21, 30 });
	left.speed = 0.2f;

	// Move right
	right.PushBack({ 218, 7, 16, 26 });
	right.PushBack({ 237, 8, 17, 29 });
	right.PushBack({ 1, 39, 17, 30 });
	right.PushBack({ 23, 39, 17, 30 });
	right.PushBack({ 45, 39, 21, 30 });
	right.speed = 0.2f;

	// shoot idle animation (just the ship)
	idle_shot.PushBack({ 114, 8, 19, 29 });
	idle_shot.PushBack({ 135, 8, 19, 29 });
	idle_shot.PushBack({ 155, 8, 19, 29 });
	idle_shot.PushBack({ 176, 8, 19, 29, });
	idle_shot.PushBack({ 197, 8, 19, 29 });
	idle_shot.speed = 0.2f;

	// shoot left
	right_shot.PushBack({ 172, 72, 19, 30 });
	right_shot.PushBack({ 150, 72, 17, 29 });
	right_shot.PushBack({ 130, 72, 17, 30 });
	right_shot.PushBack({ 109, 72, 17, 30 });
	right_shot.PushBack({ 88, 72, 17, 30 });
	right_shot.speed = 0.2f;

	// shoot right
	left_shot.PushBack({ 69, 39, 19, 30 });
	left_shot.PushBack({ 93, 39, 17, 29 });
	left_shot.PushBack({ 113, 39, 17, 30 });
	left_shot.PushBack({ 134, 39, 17, 30 });
	left_shot.PushBack({ 155, 39, 17, 30 });
	left_shot.speed = 0.2f;

	//horse walk
	horse_walk.PushBack({ 1, 106, 24, 35 });
	horse_walk.PushBack({ 26, 106, 24, 35 });
	horse_walk.PushBack({ 52, 106, 24, 37 });
	horse_walk.speed = 0.2f;

	//horse jump
	horse_transition.PushBack({ 242, 110, 16, 30 });
	horse_transition.PushBack({ 233, 110, 18, 30 });
	horse_transition.PushBack({ 206, 110, 16, 30 });
	horse_transition.PushBack({ 187, 110, 17, 30 });
	horse_transition.PushBack({ 168, 110, 18, 26 });
	horse_transition.PushBack({ 144, 110, 23, 18 });
	horse_transition.loop = false;
	horse_transition.speed = 0.2f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("gunsmoke/player.png");
	sprites = App->textures->Load("gunsmoke/powerups.png");

	alarm_horse_sound = 0;
	horse = 0;

	destroyed = false;
	switch (checkpoint)
	{
	case 0:
		{
			position.x = 120;
			position.y = 200;
			camera_y = 0;
			App->render->camera.y = 0 * SCREEN_SIZE;
		}
		break;
	case 1:
		{
			position.x = 120;
			position.y = -984;
			camera_y = -1100;
			App->render->camera.y = -1100*SCREEN_SIZE;
		} break;
	case 2:
		{
			position.x = 120;
			position.y = -1976;
			camera_y = -2176;
			App->render->camera.y = -2176 * SCREEN_SIZE;
		} break;
	default:
		{
			position.x = 120;
			position.y = 200;
			camera_y = 0;
			App->render->camera.y = 0 * SCREEN_SIZE;
		}
		break;
	}

	if (powerup[0]>0)
	{powerup[0] -= 1;}
	if (powerup[1] > 0)
	{powerup[1] -= 1;}
	if (powerup[2] > 0)
	{powerup[2] -= 1;}

	App->particles->powerup_activated = true;

	audio_shot = App->audio->LoadFx("gunsmoke/shotfx.wav");
	audio_horse = App->audio->LoadFx("gunsmoke/horse_ride.wav");

	font_score = App->fonts->Load("fonts/font.png", "0123456789abcdefghijklmnopqrstuvwxyz", 1);
	col = App->collision->AddCollider({(int)position.x, (int)position.y, 19, 28}, COLLIDER_PLAYER, this);
	col_base= App->collision->AddCollider({ (int)position.x, (int)position.y+18, 17, 9 }, COLLIDER_PLAYER_BASE,this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->audio->UnLoadFx(audio_shot);
	App->audio->UnLoadFx(audio_horse);
	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_score);
	App->audio->Stop_horse_sound();

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

	if (position.y*SCREEN_SIZE < -1976*SCREEN_SIZE && checkpoint == 1)
	{
		checkpoint = 2;
		LOG("------------SECOND CHECKPOINT REACHED------------")
	}
	if (position.y*SCREEN_SIZE < -984*SCREEN_SIZE && checkpoint == 0)
	{
		checkpoint = 1;
		LOG("------------FIRST CHECKPOINT REACHED------------")

	}
	if (App->render->camera.y == (-2814 * SCREEN_SIZE))
		position.y;// Automatic movement

	else if (itstime && destroyed == false && horse_jump == -1)
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

	float speed = 1 + powerup[0]*0.12;

	joystick_left = 0;
	joystick_right = 0;

	if (destroyed == false && horse_jump == -1)
	{

		if (App->input->controller_1.left_joystick.x > 0.25)
		{
			joystick_right = 1;
		}
		if (App->input->controller_1.left_joystick.x < -0.25)
		{
			joystick_left = 1;
		}

		joystick_down = 0;
		joystick_up = 0;

		if (App->input->controller_1.left_joystick.y > 0.25)
		{
			joystick_down = 1;
		}
		if (App->input->controller_1.left_joystick.y < -0.25)
		{
			joystick_up = 1;
		}


		if ((App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT || joystick_up || App->input->controller_1.w_button) && camera_y < position.y)
		{
			position.y -= speed;
		}

		if ((App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT || joystick_down || App->input->controller_1.s_button) && camera_y + SCREEN_HEIGHT - 5 > position.y + 32)
		{
			position.y += speed;
		}

		if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT || joystick_right || App->input->controller_1.d_button) && App->render->camera.x + SCREEN_WIDTH > position.x + 19)
		{
			position.x += speed;
			if (current_animation != &right)
			{
				right.Reset();
				current_animation = &right;
			}

		}

		if ((App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT || joystick_left || App->input->controller_1.a_button) && App->render->camera.x < position.x)
		{
			position.x -= speed;
			if (current_animation != &left)
			{
				left.Reset();
				current_animation = &left;
			}

		}



		if ((App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE)
			&& (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) && joystick_left == false && joystick_right == false)
		{
			current_animation = &idle;
		}
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT
			&& App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && joystick_left == false && joystick_right == false)
		{
			current_animation = &idle;
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


		if (App->input->keyboard[SDL_SCANCODE_J] == KEY_STATE::KEY_DOWN || App->input->controller_1.z_button)
		{
			time_z = 5;
		}

		if (App->input->keyboard[SDL_SCANCODE_K] == KEY_STATE::KEY_DOWN || App->input->controller_1.x_button || App->input->controller_1.x2_button)
		{
			time_x = 5;
		}

		if (App->input->keyboard[SDL_SCANCODE_L] == KEY_STATE::KEY_DOWN || App->input->controller_1.c_button)
		{
			time_c = 5;
		}


		if (time_z > 0)
		{
			time_z -= 1;
			current_animation = &left_shot;
		}

		if (time_z == 0)
		{
			press_z = false;
		}
		else { press_z = true; }



		if (time_x > 0)
		{
			time_x -= 1;
			current_animation = &idle_shot;
		}

		if (time_x == 0)
		{
			press_x = false;
		}
		else { press_x = true; }



		if (time_c > 0)
		{
			time_c -= 1;
			current_animation = &right_shot;
		}

		if (time_c == 0)
		{
			press_c = false;
		}
		else { press_c = true; }

		//combined shots
		if (press_z && press_x&& cooldown < 5)
		{
			App->particles->AddParticle(App->particles->shot_l_up, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shot_l_down, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
			time_z = 0; time_x = 0;
			cooldown = COOLDOWN;
			App->audio->PlayFx(audio_shot);
			setanim = 30;
			lastkey = 0;

		}

		if (press_x && press_c&& cooldown < 5)
		{
			App->particles->AddParticle(App->particles->shot_r_up, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shot_r_down, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
			time_z = 0; time_x = 0;
			cooldown = COOLDOWN;
			App->audio->PlayFx(audio_shot);
			setanim = 30;
			lastkey = 2;
		}

		if (press_z && press_c&& cooldown < 5)
		{
			App->particles->AddParticle(App->particles->shot_r, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shot_l, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
			time_z = 0; time_x = 0;
			cooldown = COOLDOWN;
			App->audio->PlayFx(audio_shot);
			setanim = 30;
			lastkey = 1;
		}

		//simple shots
		if (press_z && time_z != 0 && cooldown == 0 && (App->input->keyboard[SDL_SCANCODE_J] || App->input->controller_1.z_button))
		{
			App->particles->AddParticle(App->particles->shot_l, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shot_l, position.x + 2, position.y + 10, COLLIDER_PLAYER_SHOT);
			cooldown = COOLDOWN;
			App->audio->PlayFx(audio_shot);
			setanim = 30;
			lastkey = 0;
		}
		if (press_x && time_x != 0 && cooldown == 0 && (App->input->keyboard[SDL_SCANCODE_K] || App->input->controller_1.x_button || App->input->controller_1.x2_button))
		{
			App->particles->AddParticle(App->particles->laser, position.x + 12, position.y, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->laser, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
			cooldown = COOLDOWN;
			App->audio->PlayFx(audio_shot);
			setanim = 30;
			lastkey = 1;
		}
		if (press_c && time_c != 0 && cooldown == 0 && (App->input->keyboard[SDL_SCANCODE_L] || App->input->controller_1.c_button))
		{
			App->particles->AddParticle(App->particles->shot_r, position.x + 12, position.y + 10, COLLIDER_PLAYER_SHOT);
			App->particles->AddParticle(App->particles->shot_r, position.x + 2, position.y, COLLIDER_PLAYER_SHOT);
			cooldown = COOLDOWN;
			App->audio->PlayFx(audio_shot);
			setanim = 30;
			lastkey = 2;

		}
		if (setanim > 0)
		{
			setanim -= 1;
		}

		if (setanim != 0)//means the player has shot in X time so the sprites will be the walking ones
		{

			if (lastkey == 2)
			{
				current_animation = &left_shot;
			}

			if (lastkey == 1)
			{
				current_animation = &idle_shot;
			}

			if (lastkey == 0)
			{
				current_animation = &right_shot;
			}

		}
	}
	if (horse_jump != -1 && position.x > SCREEN_WIDTH / 2)
	{
		god_mode = 1;
		col->rect = { (int)position.x + god_mode * 250, (int)position.y, 19, 28 };
		col_base->rect = { (int)position.x + 1 + god_mode * 250 , (int)position.y + 18, 17, 9 };
		//App->particles->AddParticle(App->particles->horse_appearance, SCREEN_WIDTH / 2, position.y, COLLIDER_NONE);
		if (SDL_GetTicks() + 1000 > horse_jump && position.x > SCREEN_WIDTH / 2)
		{
		position.x -= 1;
		position.y -= 1;
		current_animation = &horse_transition;
		}
		if (SDL_GetTicks() + 3000 > horse_jump)
		{
			god_mode = 0;
		}
	}

	if (horse == 0)
	{
		col->rect = { (int)position.x + god_mode*250, (int)position.y, 19, 28 };
		col_base->rect = { (int)position.x+1 + god_mode*250 , (int)position.y + 18, 17, 9 };

//		col->SetPos(position.x + god_mode * 250, position.y);
	//	col_base->SetPos(position.x + 1 + god_mode * 250, position.y + 18);
	}

	/*else if (SDL_GetTicks() > death_time && death_time != -1 && destroyed == false)
	{

		horse_jump = false;
	}*/

	else if (SDL_GetTicks() > horse_jump && horse_jump != -1)// || horse > 0)
	{
		col->rect = { (int)position.x-1 +god_mode*250, (int)position.y, 20, 36 };
		col_base->rect = { (int)position.x+god_mode*250, (int)position.y + 16, 18, 20 };
		current_animation = &horse_walk;
		horse_jump = -1;
	}

	else if (horse > 0 && horse_jump == -1)
	{
		col->rect = { (int)position.x - 1 + god_mode * 250, (int)position.y, 20, 36 };
		col_base->rect = { (int)position.x + god_mode * 250, (int)position.y + 16, 18, 20 };
		current_animation = &horse_walk;
	}
	// Draw everything --------------------------------------
	
	sprintf_s(scores, 8, "%7d", score);
	App->fonts->BlitText(8,8,font_score,scores);

	if(destroyed == false)
		App->render->Blit(graphics, (int)position.x, (int)position.y, &(current_animation->GetCurrentFrame()));

	//Draw HUD(lifes / powerups)---------------------------------

	for (uint i = 0; i < lifes; i++)
	{
		SDL_Rect rect = { 150, 11, 8, 8 };
		App->render->Blit(sprites, i * 8, 256-8 +camera_y, &rect);
	}

	for (uint i = 0; i < powerup[0]; i++)
	{
		SDL_Rect rect = { 150, 36, 8, 8 };
		App->render->Blit(sprites, i * 8+ 8*6, 256 - 8 + camera_y, &rect);
	}

	for (uint i = 0; i < powerup[1]; i++)
	{
		SDL_Rect rect = { 172, 35, 8, 8 };
		App->render->Blit(sprites, i * 8 + 8 * 12, 256 - 8 + camera_y, &rect);
	}

	if (App->input->keyboard[SDL_SCANCODE_G] == KEY_DOWN)
	{
		switch (god_mode)
		{
		case 0:
		{god_mode = 1;
		break;
		}

		case 1:
		{
			god_mode = 0;
			break;
		}
		}
	}

	if (horse > 0 && SDL_GetTicks() > alarm_horse_sound && alarm_horse_sound != -1)
	{
		//horse_jump = true;
		//death_time = SDL_GetTicks() + 3000;
		App->audio->PlayFx(audio_horse, 0, 6);
		alarm_horse_sound = SDL_GetTicks() + 5000;
	}

	if (horse == 0)
	{
		App->audio->Stop_horse_sound();
		alarm_horse_sound = -1;
	}

	if (SDL_GetTicks() > death_time && death_time != -1 && destroyed == true)
	{
	//	death_time = SDL_GetTicks();

		if (lifes != 0)
		{
			App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_transit, 0.3f);
			death_time = -1;
			//death = false;
		}
		else
		{
			lifes = 3;
			LOG("OUT OF LIFES");
			App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_gameover);
			death_time = -1;
			//death = false;
		}
	}
	if (App->input->keyboard[SDL_SCANCODE_N]== KEY_STATE::KEY_REPEAT)
	{
		App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_gameover);
	}
	if (App->input->keyboard[SDL_SCANCODE_M] == KEY_STATE::KEY_REPEAT)
	{
		lifes -= 1;
		App->particles->AddParticle(App->particles->player_death, position.x, position.y, COLLIDER_NONE);
		death_time = SDL_GetTicks() + 3000;
		destroyed = true;

	}

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	//death_time = SDL_GetTicks();

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
			vert = c1->rect.y + c1->rect.h - c2->rect.y;
		else
			vert = c2->rect.y + c2->rect.h - c1->rect.y;

		if (horiz < vert)
			position.x = previous.x;
		else
		{
			position.y = previous.y;

			if (c2->rect.x >= SCREEN_WIDTH / 2 && camera_y + SCREEN_HEIGHT - 5 < position.y + 32)
				position.x = (c2->rect.x - c1->rect.w);

			else if (c2->rect.x < SCREEN_WIDTH / 2 && camera_y + SCREEN_HEIGHT - 5 < position.y + 32)
				position.x = (c2->rect.x + c2->rect.w);
		}
	}

	if (c1 == col && c2->type == COLLIDER_ENEMY_SHOT
		&& destroyed == false && App->fade->IsFading() == false)
	{
		if (horse == 0)
		{
			lifes -= 1;


			if (destroyed == false)
			{
				App->particles->AddParticle(App->particles->player_death, position.x, position.y, COLLIDER_NONE);

				death_time = SDL_GetTicks() + 3000;
				//death_time = -1;
			}

			else death = false;
			/*if (lifes != 0)
			{
				if (SDL_GetTicks() > death_time + 3000)
				{
					App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_transit, 0.3f);
				}
			}
			else
			{
				lifes = 3;
				LOG("OUT OF LIFES");
				if (SDL_GetTicks() > death_time + 3000)
				{
					App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_gameover);
				}
			}*/
			destroyed = true;
		}
		else
		{
			horse -= 1;
			if (horse == 0)
			{
				App->particles->AddParticle(App->particles->horse_death, position.x-20, position.y, COLLIDER_NONE);

			}
		}

	}
	if (c1 == col_base && c2->type == COLLIDER_ENEMY_BASE 
		&& destroyed == false && App->fade->IsFading() == false)
	{
		lifes -= 1;

		if (destroyed == false)
		{
			App->particles->AddParticle(App->particles->player_death, position.x, position.y, COLLIDER_NONE);
			death_time = SDL_GetTicks() + 3000;
		}

		else death = false;
		/*if (lifes != 0)
		{

			if (SDL_GetTicks() > death_time + 3000)
			{
				App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_transit, 0.3f);
			}
		}
		else
		{
			lifes = 3;
			LOG("OUT OF LIFES");
			if (SDL_GetTicks() > death_time + 3000)
			{
				App->fade->FadeToBlack((Module*)App->scene_space, (Module*)App->scene_gameover);
			}
		}*/

			destroyed = true;
	}

}