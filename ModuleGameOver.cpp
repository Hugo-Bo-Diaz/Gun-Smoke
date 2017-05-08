#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleGameOver.h"
#include "ModuleFonts.h"
#include "ModulePlayer.h"

#include <stdio.h>


ModuleGameOver::ModuleGameOver()
{}

ModuleGameOver::~ModuleGameOver()
{}

// Load assets
bool ModuleGameOver::Start()
{
	LOG("Loading Game Over Scene");

	background = App->textures->Load("gunsmoke/start.png");
	for (int i = 0; i < 5; i++)
	{
		highscores[i] = 0;
	}

	App->render->camera.x = App->render->camera.y = 0;

	font_score = App->fonts->Load("fonts/font.png", "0123456789abcdefghijklmnopqrstuvwxyz", 1);

	if (App->player->score > highscores[4])
		highscores[4] = App->player->score;

	App->player->score = 0;
	
	for (int i = 1; i < 5; i++)
	{
		for (int i = 1; i < 5; i++)
		{
			if (highscores[i] > highscores[i - 1])
			{
				auxiliar = highscores[i];
				auxiliar2 = highscores[i - 1];
				highscores[i - 1] = auxiliar;
				highscores[i] = auxiliar2;
			}
		}
	}
	return true;
}

// UnLoad assets
bool ModuleGameOver::CleanUp()
{
	LOG("Unloading space scene");

	 App->fonts->UnLoad(font_score);
	App->textures->Unload(background);

	return true;
}

// Update: draw background
update_status ModuleGameOver::Update()
{
	App->render->Blit(background, 0, 0, NULL);

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN && App->fade->IsFading() == false)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_intro);
	}

	for (int i = 0; i < 5; i++)
	{
		sprintf_s(scores, 8, "%7d", highscores[i]);

		App->fonts->BlitText(81, 144 + i * 16, font_score, scores);

	}


	return UPDATE_CONTINUE;
}
