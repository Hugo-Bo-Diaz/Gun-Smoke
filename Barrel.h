#ifndef __Barrel_H__
#define __Barrel_H__

#include "p2Point.h"
#include "Animation.h"
#include "powerup.h"
struct SDL_Texture;
struct Collider;


class Barrel
{
public:

	Barrel(int, int, POWERUP_TYPE);
	~Barrel();
	Collider* collider = nullptr;

	iPoint position;
	int hp = 6;

	POWERUP_TYPE type;

	const Collider* GetCollider() const;

	void Draw();
	void OnCollision();
	SDL_Rect section;
};


#endif // Barrel_H_
