#ifndef __ENEMY_BROWNCOOKIE_H__
#define __ENEMY_BROWNCOOKIE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_BrownCookie : public Enemy 
{

private:
	iPoint original_pos;
	Animation fly;
	Path path;
	
public:
	Enemy_BrownCookie(int x, int y);
	~Enemy_BrownCookie();
	void Move();
	int value_between(int,int);
	iPoint path_dest;
	iPoint path_from;
	uint path_start;
	uint next_shot=0;
	//anim
	Animation animations[8];
};
#endif
