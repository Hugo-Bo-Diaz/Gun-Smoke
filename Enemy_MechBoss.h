#ifndef __ENEMY_MECHBOSS_H__
#define __ENEMY_MECHBOSS_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_MechBoss : public Enemy
{

private:
	iPoint original_pos;
	Animation walk;
	Animation thrw;
	Path path;
	uint bombdelay;
	uint timer;
public:
	Enemy_MechBoss(int x, int y);
	~Enemy_MechBoss();
	void Move();
	int value_between(int, int);
	iPoint path_dest;
	iPoint path_from;
	uint path_start;
	uint next_shot = 0;
	float bullet_angle = 0;
};
#endif