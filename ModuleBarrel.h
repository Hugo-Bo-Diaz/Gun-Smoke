#ifndef __ModuleBarrel_H__
#define __ModuleBarrel_H__

#include "Module.h"
#include "Powerup.h"

#define MAX_BARRELS 20

class Barrel;

class ModuleBarrel : public Module
{
public:

	ModuleBarrel();
	~ModuleBarrel();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

private:

	void AddBarrel(int x, int y, POWERUP_TYPE type);

private:

	Barrel* barrels[MAX_BARRELS];
	SDL_Texture* sprites;
};

#endif // __ModuleEnemies_H__