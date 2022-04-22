#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Module.h"
#include "Animation.h"

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
	bool hide;
	

private:
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

	// display
	void DisplayHero(int n);
	SDL_Texture* whitemark128x128;
	SDL_Texture* hero_tex;
	
};

#endif