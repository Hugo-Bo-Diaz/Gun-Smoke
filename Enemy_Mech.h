#ifndef __ENEMY_MECH_H__
#define __ENEMY_MECH_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Mech : public Enemy
{

private:
	iPoint original_pos;
	Animation walk_left;
	Animation walk_right;
	Path path;
public:
	Enemy_Mech(int x, int y);
	void Move();
};
#endif