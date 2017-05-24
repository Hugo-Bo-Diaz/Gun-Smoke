#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneTransition.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneTransition::ModuleSceneTransition()
{}

ModuleSceneTransition::~ModuleSceneTransition()
{}

// Load assets
bool ModuleSceneTransition::Start()
{
	LOG("Loading space intro");

	background = App->textures->Load("gunsmoke/map1.png");

	App->render->camera.x = App->render->camera.y = 0;

	return true;
}

// UnLoad assets
bool ModuleSceneTransition::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background);

	return true;
}

// Update: draw background
update_status ModuleSceneTransition::Update()
{
	//App->render->Blit(background, 0, 0, NULL);

	App->fade->FadeToBlack(this, (Module*)App->scene_space,0.3f);

	return UPDATE_CONTINUE;
}