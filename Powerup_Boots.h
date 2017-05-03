#ifndef __POWERUP_BOOTS_H__
#define __POWERUP_BOOTS_H__

#include "powerup.h"
class Powerup_Boots : public Powerup
{
public:

	Powerup_Boots(int x, int y);
	~Powerup_Boots();

	virtual void OnCollision();
	virtual SDL_Rect Draw();
};
#endif //__POWERUP_BOOTS_H__
