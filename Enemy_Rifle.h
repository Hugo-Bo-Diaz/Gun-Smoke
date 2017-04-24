#ifndef __ENEMY_RIFLE_H__
#define __ENEMY_RIFLE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Rifle : public Enemy
{

private:
	iPoint original_pos;
	Animation fly;
	Path path;
public:
	Enemy_Rifle(int x, int y);
	void Move();
	void Shoot();
};
#endif
