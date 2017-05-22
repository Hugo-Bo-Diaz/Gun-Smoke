#ifndef __ENEMY_STABBY_H__
#define __ENEMY_STABBY_H__

#include "Enemy.h"
#include "Path.h"
#include "SDL/include/SDL_timer.h"

class Enemy_Stabby : public Enemy
{

private:
	iPoint original_pos;
	Animation fly;
	Path path;

public:
	Enemy_Stabby(int x, int y);
	~Enemy_Stabby();
	void Move();
	int value_between(int, int);
	iPoint path_dest;
	iPoint path_from;
	uint path_start;
	uint next_shot = 0;
	uint jump = 0;
	uint gravity = 1;
	Animation horizontal;
	Animation up;
	Animation down;
	Animation floor;
};
#endif
