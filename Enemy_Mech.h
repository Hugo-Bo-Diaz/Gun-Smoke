#ifndef __ENEMY_MECH_H__
#define __ENEMY_MECH_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Mech : public Enemy
{

private:
	iPoint original_pos;
	Animation walk;
	Animation thrw;
	Path path;
public:
	Enemy_Mech(int x, int y);
	~Enemy_Mech();
	void Move();
	int value_between(int, int);
	iPoint path_dest;
	iPoint path_from;
	uint path_start;
	uint next_shot = 0;
	float bullet_angle = 0;
};
#endif