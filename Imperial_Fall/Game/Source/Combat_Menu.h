#ifndef __COMBAT_MENU_H__
#define __COMBAT_MENU_H__

#include "Module.h"
#include "Menu.h"
#include "Animation.h"
#include "Point.h"

#define NUM_BUTTONS 7  //Bottones generales
#define NUM_ITEMS_BUTTONS 5
#define NUM_ENEMIES_BUTTONS 5
#define NUM_ALLIES_BUTTONS 5


struct Button;

class Combat_Menu : public Module
{
public:
	Combat_Menu();

	virtual ~Combat_Menu();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

private:

	bool in_combat = false;
	bool in_action = false;

	bool in_items = false;
	bool in_enemies = false;
	bool in_allies = false;

	SDL_Rect r;

	int chosed;
	Button general_buttons[NUM_BUTTONS];
	Button items_buttons[NUM_ITEMS_BUTTONS];
	Button enemies_buttons[NUM_ENEMIES_BUTTONS];
	Button allies_buttons[NUM_ALLIES_BUTTONS];

	Uint8 idleColorR = 18;
	Uint8 idleColorG = 188;
	Uint8 idleColorB = 13;
	Uint8 inColorR = 255;
	Uint8 inColorG = 178;
	Uint8 inColorB = 0;
	Uint8 pColorR = 255;
	Uint8 pColorG = 0;
	Uint8 pColorB = 0;

	uint win_w, win_h;

	// sound
	uint click_sound;
	uint hover_sound;

	// animation
	Animation* currentAnimation = NULL;

	Animation idleAnim;

	// positions
	fPoint action_pos[NUM_BUTTONS];
	fPoint item_pos[NUM_ITEMS_BUTTONS];
	fPoint enemy_pos[NUM_ENEMIES_BUTTONS];
	fPoint ally_pos[NUM_ALLIES_BUTTONS];

};

#endif