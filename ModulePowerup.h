#ifndef __ModulePowerup_H__
#define __ModulePowerup_H__

#include "Module.h"
#include "Powerup_Boots.h"

#define MAX_POWERUPS 20

class Powerup;

class ModulePowerup : public Module
{
public:

	ModulePowerup();
	~ModulePowerup();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddPowerup(int x, int y, POWERUP_TYPE type);

private:

	//void SpawnPowerup(const EnemyInfo& info);

private:

	Powerup* powerups[MAX_POWERUPS];
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__