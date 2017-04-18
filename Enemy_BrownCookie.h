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
	void Move();
	void Shoot();
};
#endif
