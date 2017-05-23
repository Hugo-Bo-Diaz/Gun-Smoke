#ifndef __POWERUP_SCORE_H__
#define __POWERUP_SCORE_H__

#include "powerup.h"
class Powerup_Score : public Powerup
{
public:

	Powerup_Score(int x, int y);
	~Powerup_Score();

	virtual void OnCollision();
	virtual SDL_Rect Draw();
};
#endif //__POWERUP_BOOTS_H__
