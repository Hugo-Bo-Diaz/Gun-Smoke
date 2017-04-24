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
#include "ModuleFonts.h"
// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneSpace::ModuleSceneSpace()
{}

ModuleSceneSpace::~ModuleSceneSpace()
{}

// Load assets
bool ModuleSceneSpace::Start()
{
	LOG("Loading space scene");
	
	App->audio->PlayMusic("gunsmoke/Gunsmoke_06.ogg");

	background = App->textures->Load("gunsmoke/map1.png");
	font_score = App->fonts->Load("fonts/font.png", "0123456789abcdefghijklmnopqrstuvwxyz", 1);

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();
	
	// Colliders ---
	//App->collision->AddCollider({ -10, 260, 20, -2820 }, COLLIDER_WALL);
	App->collision->AddCollider({ 117, 105, 23, 21 }, COLLIDER_WALL); // POZO Nº1
	App->collision->AddCollider({ 0, -152, 44, 363 }, COLLIDER_WALL); //EDIFICIO A
	App->collision->AddCollider({ 44, -124, 20, 347 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -98, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 160, -668, 68, 627 }, COLLIDER_WALL); // EDIFICIO B

	//App->collision->AddCollider({ 160, -668, 68, 627 }, COLLIDER_DESTINY); //

	// Enemies GunMen ---
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 68, -73);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 102, -157);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 1, -222);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 24, -280);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 24, -362);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 111, -392);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 24, -451);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 77, -502);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 24, -606);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 33, -666);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 60, -666);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 85, -666);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 95, -770);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 200, -800);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 77, -840);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 200, -880);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 75, -905);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 6, -950);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 100, -995);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 105, -1085); 
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 105, -1150);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 105, -1240);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 8, -1335);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 8, -1365);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 105, -1345);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 77, -1490);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 160, -1595);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 130, -1690); 
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 200, -1910);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 85, -2010);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 5, -2140);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 75, -2140);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 130, -2180);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 183, -2341);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 75, -2450);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 183, -2505);
	App->enemies->AddEnemy(ENEMY_TYPES::BROWNCOOKIE, 100, -2620);
	
	// Enemies Sniper ---
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8, - 132);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -420);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -600);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -1090);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8, -1250);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8, -1440);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8, -1700);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -2175);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -2365);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -2560);

	// Enemies BomberMen ---
	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 31, -733);
	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 120, -770);
	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 95, -2280);
	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 50, -2535);

	// Enemies Rifle ---
	App->enemies->AddEnemy(ENEMY_TYPES::RIFLE, 130, -1810);
	App->enemies->AddEnemy(ENEMY_TYPES::RIFLE, 190, -1810);
	App->enemies->AddEnemy(ENEMY_TYPES::RIFLE, 50, -2140);


	//App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 120, -80);
	
	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");
	App->audio->StopMusic();
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
	if (App->render->camera.y == (-2814 * SCREEN_SIZE))
		App->render->camera.y -= 0 * SCREEN_SIZE;

	else App->render->camera.y -= 1 * SCREEN_SIZE;

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, -2814, NULL);

	App->fonts->BlitText(10, 0, font_score, "gunman-1");
	App->fonts->BlitText(80, 0, font_score, "hi-score");


	return UPDATE_CONTINUE;
}