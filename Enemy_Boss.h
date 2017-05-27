#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "Path.h"
#include "SDL/include/SDL_timer.h"

enum boss_state
{
	BOSS_CROUCHED,
	BOSS_SHOOTING,
	BOSS_MOVING,
	BOSS_IDLE
};

class Enemy_Boss : public Enemy
{

private:
	iPoint original_pos;
	Animation fly;
	Path path;
	//timers
	boss_state state = BOSS_CROUCHED;
	int timer_crouch = value_between(2000, 4000) + SDL_GetTicks(); //2-4 sec after spawn
	int timer_shots;
	bool crouched= true;
	int shots_fired;
	SDL_Texture* hp_bar = nullptr;
	SDL_Rect section;
	uint timer_spawn= 0 ;
	uint hit_audio;
	uint audio_boss_death;
	uint boss_death_time = -1;

public:
	Enemy_Boss(int x, int y);
	~Enemy_Boss();
	void Move();
	int value_between(int, int);
	iPoint path_dest;
	iPoint path_from;
	uint path_start;
	uint next_shot = 0;

	//anim

	Animation shooting_front;
	Animation shooting_right;
	Animation shooting_left;
	Animation shooting_down_left;
	Animation shooting_down_right;

	Animation walking;
	Animation to_crouch;
	Animation crouch_moving;

};
#endif
