#ifndef __POWERUP_RIFLE_H__
#define __POWERUP_RIFLE_H__

#include "powerup.h"
class Powerup_Rifle : public Powerup
{
public:

	Powerup_Rifle(int x, int y);
	~Powerup_Rifle();

	virtual void OnCollision();
	virtual SDL_Rect Draw();
};
#endif //__POWERUP_RIFLE_H__
