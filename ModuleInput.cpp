#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"

ModuleInput::ModuleInput() : Module()
{
	for(uint i = 0; i < MAX_KEYS; ++i)
		keyboard[i] = KEY_IDLE;
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	};

	if (SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER) < 0)
	{
		LOG("SDL_GAMEPAD could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		if (SDL_NumJoysticks() > 0)
		{
			Controller = SDL_GameControllerOpen(0);
			if (Controller == nullptr)
			{
				LOG("Controller couldn't be initialized SDL_Error: %s\n", SDL_GetError());
			}
			else
			{
				controller_connected == true;
			}
		}
	};

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);

	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	if(keyboard[SDL_SCANCODE_ESCAPE] || controller_1.esc_button)
		return update_status::UPDATE_STOP;

	controller_1.left_joystick.x = ((float)SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_LEFTX) / 32767.0f);
	controller_1.left_joystick.y = ((float)SDL_GameControllerGetAxis(Controller, SDL_CONTROLLER_AXIS_LEFTY) / 32767.0f);
	controller_1.x_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_A));
	controller_1.z_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_X));
	controller_1.x2_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_A));
	controller_1.c_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_B));
	controller_1.esc_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_BACK));
	controller_1.space_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_START));
	controller_1.w_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_DPAD_UP));
	controller_1.a_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT));
	controller_1.s_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN));
	controller_1.d_button = ((bool)SDL_GameControllerGetButton(Controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT));
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);
	return true;
}