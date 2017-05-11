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
#include "ModuleBarrel.h"
#include "ModulePowerup.h"
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

	App->barrel->Enable();
	App->powerup->Enable();

	// Colliders ---
	//App->collision->AddCollider({ -10, 260, 20, -2820 }, COLLIDER_WALL);
	App->collision->AddCollider({ 117, 105, 23, 21 }, COLLIDER_WALL); // POZOS

	App->collision->AddCollider({ 98, -927, 28, 27 }, COLLIDER_WALL);

	App->collision->AddCollider({ 117, -2008, 22, 20 }, COLLIDER_WALL);

	App->collision->AddCollider({ 0, -152, 44, 363 }, COLLIDER_WALL); //EDIFICIOS IZQ
	App->collision->AddCollider({ 44, -124, 20, 347 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -98, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 59, 0, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 61, 63, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 61, 159, 15, 19 }, COLLIDER_WALL);

	App->collision->AddCollider({ 0, -1980, 64, 1018 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -2009, 44, 29 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -1026, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -1218, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -1314, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -1410, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -1472, 12, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -1570, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -1666, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -1858, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -1954, 15, 19 }, COLLIDER_WALL);

	App->collision->AddCollider({ 0, -2320, 80, 35 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -2405, 100, 85 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -2445, 75, 40 }, COLLIDER_WALL);

	App->collision->AddCollider({ 0, -2814, 64, 122 }, COLLIDER_WALL);
	App->collision->AddCollider({ 0, -2692, 37, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 64, -2754, 15, 19 }, COLLIDER_WALL);

	App->collision->AddCollider({ 180, -698, 44, 30 }, COLLIDER_WALL); // EDIFICIOS DCH
	App->collision->AddCollider({ 160, -668, 64, 626 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -643, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -547, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 148, -449, 12, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -387, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 146, -291, 14, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -195, 15, 19 }, COLLIDER_WALL);

	App->collision->AddCollider({ 160, -1340, 64, 346 }, COLLIDER_WALL);
	App->collision->AddCollider({ 180, -1368, 44, 28 }, COLLIDER_WALL);
	App->collision->AddCollider({ 187, -994, 37, 17 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -1058, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 148, -1120, 12, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -1218, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -1314, 15, 19 }, COLLIDER_WALL);

	App->collision->AddCollider({ 160, -2813, 64, 732 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -2146, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -2338, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 148, -2434, 12, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -2530, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 146, -2626, 14, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -2722, 15, 19 }, COLLIDER_WALL);
	App->collision->AddCollider({ 145, -2814, 15, 15 }, COLLIDER_WALL);

	// Enemies GunMen ---
	if (App->player->checkpoint < 1)
	{
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
}
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
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -580);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -1090);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8, -1250);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8, -1440);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8, -1700);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -2175);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -2365);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 200, -2560);
	
	// Enemies BomberMen ---
	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 100, 30);
	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 31, -733);
	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 120, -770);
	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 95, -2280);
	App->enemies->AddEnemy(ENEMY_TYPES::MECH, 50, -2535);
	
	// Enemies Rifle ---
	App->enemies->AddEnemy(ENEMY_TYPES::RIFLE, 130, -1810);
	App->enemies->AddEnemy(ENEMY_TYPES::RIFLE, 190, -1810);
	App->enemies->AddEnemy(ENEMY_TYPES::RIFLE, 50, -2140);

	App->enemies->AddEnemy(ENEMY_TYPES::BOSS, 100, -2800);


	//App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 120, -80);
	App->barrel->AddBarrel(100,100,POWERUP_BOOTS);
	App->barrel->AddBarrel(200, 100, POWERUP_RIFLE);


	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");
	App->audio->StopMusic();
 	App->textures->Unload(background);
	App->fonts->UnLoad(font_score);

	App->powerup->Disable();
	App->barrel->Disable();

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


	else if(itstime)
	{
		App->render->camera.y -= 1 * SCREEN_SIZE;
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

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, -2814, NULL);

	App->fonts->BlitText(10, 0, font_score, "gunman1");
	App->fonts->BlitText(80, 0, font_score, "hiscore");


	return UPDATE_CONTINUE;
}

void ModuleSceneSpace::restart_level()
{
	CleanUp();
	Start();
}