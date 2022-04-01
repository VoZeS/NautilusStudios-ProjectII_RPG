#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"

#define NUM_PAUSE_BUTTONS 4
#define NUM_MENU_BUTTONS 4
#define NUM_DEAD_BUTTONS 2
#define NUM_SETTINGS_BUTTONS 4

struct Button {
	SDL_Rect rect = { 0, 0, 220, 70 };
	SDL_Texture* tex = NULL;
	SDL_Texture* alt_tex = NULL;
	


	int state = 0; // 0->idle, 1->above, 2->pressed
};

class Menu : public Module
{
public:
	Menu();

	virtual ~Menu();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	bool GetGameState();

	bool dead;

	bool lose;

	SDL_Texture* torch_fire = NULL;
	SDL_Rect PauseMenuHUD;
	SDL_Rect r;
	bool intro;
	bool paused;
	bool settings;
	bool vsync;
	bool fullscreen;
	bool credits;

private:
	

	int xbarra = 135;
	int xbarra2 = 135;
	bool slider;
	bool slider2;

	int chosed;
	Button pause_buttons[NUM_PAUSE_BUTTONS];
	Button menu_buttons[NUM_MENU_BUTTONS];
	Button dead_buttons[NUM_DEAD_BUTTONS];
	Button settings_buttons[NUM_SETTINGS_BUTTONS];
	Button lose_button;

	SDL_Texture* gameOver = NULL;
	SDL_Texture* cat = NULL;

	Uint8 idleColorR = 18;
	Uint8 idleColorG = 188;
	Uint8 idleColorB = 13;
	Uint8 inColorR = 255;
	Uint8 inColorG = 178;
	Uint8 inColorB = 0;
	Uint8 pColorR = 255;
	Uint8 pColorG = 0;
	Uint8 pColorB = 0;

	int load_cd = 120;
	bool loading = false;

	uint win_w, win_h;
	
	bool started = false;
	int save_cd = 50;
	bool saving = false;

	// sound
	uint click_sound;
	uint hover_sound;

};

#endif