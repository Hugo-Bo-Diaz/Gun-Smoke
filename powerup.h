#ifndef __Powerup_H__
#define __Powerup_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Powerup
{
private:

	Collider* collider = nullptr;
	Collider* col = nullptr;

public:
	Powerup(int x, int y);
	~Powerup();

	iPoint position;
	SDL_Rect section;
	SDL_Texture* texture;

	const Collider* GetCollider() const;
	const Collider* GetCol() const;

	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* c1, Collider* c2) {};
};


#endif // Powerup_H_
