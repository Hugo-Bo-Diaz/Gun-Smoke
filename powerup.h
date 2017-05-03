#ifndef __Powerup_H__
#define __Powerup_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

enum POWERUP_TYPE
{
	POWERUP_BOOTS,
	POWERUP_RIFLE,
	POWERUP_BULLETS,
	POWERUP_MAX
};

class Powerup
{
public:

	Powerup() {};
	~Powerup();
	Collider* collider = nullptr;

	iPoint position;
	SDL_Rect section;

	POWERUP_TYPE type;

	const Collider* GetCollider() const;

	virtual SDL_Rect Draw() {};
	virtual void OnCollision() {};
};


#endif // Powerup_H_
