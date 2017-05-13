#ifndef __ENEMY_COOKIEBOSS_H__
#define __ENEMY_COOKIEBOSS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_CookieBoss : public Enemy
{

private:
	iPoint original_pos;
	Animation fly;
	Path path;

public:
	Enemy_CookieBoss(int x, int y);
	~Enemy_CookieBoss();
	void Move();
	int value_between(int, int);
	iPoint path_dest;
	iPoint path_from;
	uint path_start;
	uint next_shot = 0;
	uint timer;
	//anim
	Animation animations[8];
};
#endif
