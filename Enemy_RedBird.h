#ifndef __ENEMY_REDBIRD_H__
#define __ENEMY_REDBIRD_H__

#include "Enemy.h"

class Enemy_RedBird : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation building_right;
	Animation building_left;

public:

	Enemy_RedBird(int x, int y);

	void Move();
	int value_between(int, int);
	uint next_shot;
	~Enemy_RedBird();
};

#endif // __ENEMY_REDBIRD_H__