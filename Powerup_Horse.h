#ifndef __POWERUP_HORSE_H__
#define __POWERUP_HORSE_H__

#include "powerup.h"
class Powerup_Horse : public Powerup
{
public:

	Powerup_Horse(int x, int y);
	~Powerup_Horse();

	virtual void OnCollision();
	virtual SDL_Rect Draw();
};
#endif //__POWERUP_BOOTS_H__
