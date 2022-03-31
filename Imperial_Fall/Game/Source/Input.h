#ifndef __INPUT_H__
#define __INPUT_H__

#include "Module.h"

#define MAX_KEYS 256
#define MAX_PADS 4
#define NUM_MOUSE_BUTTONS 5

struct SDL_Rect;
struct _SDL_GameController;
struct _SDL_Haptic;

enum EventWindow
{
	WE_QUIT = 0,
	WE_HIDE = 1,
	WE_SHOW = 2,
	WE_COUNT
};

enum KeyState
{
	KEY_IDLE = 0,
	KEY_DOWN,
	KEY_REPEAT,
	KEY_UP
};

struct GamePad
{
	// Input data
	bool start, back, guide;
	bool x, y, a, b, l1, r1, l3, r3;
	bool up, down, left, right;
	float l2, r2;
	float left_x, left_y, right_x, right_y, left_dz, right_dz;

	// Controller data
	bool enabled;
	int index;
	_SDL_GameController* controller;
	_SDL_Haptic* haptic;

	// Rumble controller
	int rumble_countdown;
	float rumble_strength;
};

class Input : public Module
{

public:

	Input();

	// Destructor
	virtual ~Input();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called before quitting
	bool CleanUp();

	// Check key states (includes mouse and joy buttons)
	KeyState GetKey(int id) const
	{
		return keyboard[id];
	}

	void SetKey(int id, KeyState state) const
	{
		keyboard[id] = state;
	}

	KeyState GetMouseButtonDown(int id) const
	{
		return mouseButtons[id - 1];
	}

	// Check if a certain window event happened
	bool GetWindowEvent(EventWindow ev);

	// Get mouse / axis position
	void GetMousePosition(int &x, int &y);
	void GetMouseMotion(int& x, int& y);

	// Activates SDL device funcionallity when a gamepad has been connected
	void HandleDeviceConnection(int index);

	// Deactivates SDL device funcionallity when a gamepad has been disconnected
	void HandleDeviceRemoval(int index);

	// Called at PreUpdate
	// Iterates through all active gamepads and update all input data
	void UpdateGamepadsInput();

	bool ShakeController(int id, int duration, float strength = 0.5f);
	const char* GetControllerName(int id) const;

private:
	bool windowEvents[WE_COUNT];
	KeyState*	keyboard;
	KeyState mouseButtons[NUM_MOUSE_BUTTONS];
	int	mouseMotionX;
	int mouseMotionY;
	int mouseX;
	int mouseY;

public:
	// An array to fill in all detected gamepads
	GamePad pads[MAX_PADS];
};

#endif // __INPUT_H__