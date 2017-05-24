#ifndef __ENEMY_REDBIRD_H__
#define __ENEMY_REDBIRD_H__

#include "Enemy.h"

class Enemy_RedBird : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation right_up_up;
	Animation right_up_down;
	Animation building_right;
	Animation right_down_up;
	Animation right_down_down;

	Animation left_up_up;
	Animation left_up_down;
	Animation building_left;
	Animation left_down_up;
	Animation left_down_down;

public:

	Enemy_RedBird(int x, int y);

	void Move();
	int value_between(int, int);
	uint next_shot;
	~Enemy_RedBird();
};

#endif // __ENEMY_REDBIRD_H__