#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleSceneSpace.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneSpace::ModuleSceneSpace()
{}

ModuleSceneSpace::~ModuleSceneSpace()
{}

// Load assets
bool ModuleSceneSpace::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("gunsmoke/map1.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	
	// Colliders ---
	App->collision->AddCollider({ 117, 105, 23, 21 }, COLLIDER_WALL); // POZO Nº1
	App->collision->AddCollider({ 0, -124, 60, 363 }, COLLIDER_WALL); //EDIFICIO A
	App->collision->AddCollider({ 160, -668, 68, 627 }, COLLIDER_WALL); // EDIFICIO B
	//App->collision->AddCollider({0, 0, 3930, 16}, COLLIDER_WALL);
	//App->collision->AddCollider({1375, 0, 111, 96}, COLLIDER_WALL);
	//App->collision->AddCollider({1375, 145, 111, 96}, COLLIDER_WALL);

	// Enemies ---
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 120, -80);

	//App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 120, -80);

	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 625, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 640, 80);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 665, 80);
	
	// TODO 1: Add a new wave of red birds
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 800, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 825, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 840, 120);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 865, 120);

	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 700, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 715, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 730, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 745, 100);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 760, 100);


	
	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);

	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	// Move camera forward -----------------------------
	App->render->camera.y -= 1 * SCREEN_SIZE;

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, -2814, NULL);
	
	return UPDATE_CONTINUE;
}