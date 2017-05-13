#ifndef __ENEMY_COOKIENINJA_H__
#define __ENEMY_COOKIENINJA_H__

#include "Enemy.h"
#include "Path.h"
#include "SDL/include/SDL_timer.h"

class Enemy_CookieNinja : public Enemy
{

private:
	iPoint original_pos;
	Animation fly;
	Path path;

public:
	Enemy_CookieNinja(int x, int y);
	~Enemy_CookieNinja();
	void Move();
	int value_between(int, int);
	iPoint path_dest;
	iPoint path_from;
	uint path_start;
	uint next_shot = 0;
	uint jump = 0;
	uint gravity = 1;
	Animation animations[8];
	Animation jumping; //377 468 23 25
};
#endif
