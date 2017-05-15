#ifndef __ModuleInput_H__
#define __ModuleInput_H__

#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "SDL\include\SDL_scancode.h"
#include "SDL\include\SDL_GameController.h"

#define MAX_KEYS 300

enum KEY_STATE
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GamePad {
	p2Point<float> left_joystick;
	p2Point<float> right_joystick;
	bool z_button;
	bool x2_button;
	bool x_button;
	bool c_button;
	bool esc_button;
	bool space_button;
	bool w_button;
	bool a_button;
	bool s_button;
	bool d_button;

};


class ModuleInput : public Module
{
public:
	
	ModuleInput();
	~ModuleInput();

	bool Init();
	update_status PreUpdate();
	bool CleanUp();

public:
	KEY_STATE keyboard[MAX_KEYS];;
	SDL_GameController* Controller = nullptr;
	GamePad controller_1;
	bool controller_connected;
};

#endif // __ModuleInput_H__