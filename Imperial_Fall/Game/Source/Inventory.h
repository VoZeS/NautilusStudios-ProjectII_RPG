#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Module.h"
#include "Animation.h"

#define NUM_GEAR_BUTTONS 4

struct Button;
struct Cursor;

class Inventory : public Module
{
public:
	Inventory(bool enabled);

	virtual ~Inventory();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

public:
	bool hide = true;
	

private:
	Cursor cursor;

	// book
	Animation* book;
	Animation open;
	Animation page1;
	Animation page2;
	Animation page3;
	Animation page4;
	Animation page5;
	Animation pass_page1_2;
	Animation pass_page2_3;
	Animation pass_page3_4;
	Animation pass_page4_5;
	Animation pass_page5_4;
	Animation pass_page4_3;
	Animation pass_page3_2;
	Animation pass_page2_1;
	Animation close;

	SDL_Texture* book_tex;

	int book_pos; // 0 --> open, 1 --> page1, 2 --> page2, 3 --> page3, 4 --> page4, 5 --> page5, 6 --> close
	int text_cd;
	bool count;
	bool show_info;

	// display
	void DisplayHero(int n);
	SDL_Texture* whitemark_128x128;
	SDL_Texture* whitemark_250x70;
	SDL_Texture* hero_tex;

	// buttons
	int chosed;
	Button skill_button;
	Button gear_buttons[NUM_GEAR_BUTTONS];

	// sound
	uint click_sound;
	uint hover_sound;
	bool hover_playing = false;
	bool InAnyButton();
	
};

#endif