#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Module.h"
#include "Animation.h"

#define PAGE_SPEED 0.15f

#define NUM_ITEMS_BUTTONS 4
#define NUM_ITEMS_SELECT_BUTTONS 8
#define NUM_GEAR_BUTTONS 4
#define NUM_GEAR_SELECT_BUTTONS 4

struct Button;
struct Cursor;

enum class SUB_INV
{
	NOTHING = 0,
	SKILL_TREE,
	ITEMS,
	HELMET,
	CHESTPLATE,
	BOOTS,
	WEAPON
};

struct Gear
{
	int health;
	int mana;
	int speed;
	int power;
};

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

	void SetTextCd(int n)
	{
		info_cd = n;
	}
	
	void ResetItems();
	void ResetGear();
	// user: 0 --> assassin, 1 --> healer, 2 --> tank, 3 --> wizard
	// piece: 0 --> helmet, 1 --> chestplate, 2 --> boots, 3 --> weapon
	// user: 0 --> unequiped, 1 --> level 1, 2 --> level 2, 3 --> level 3, 4 --> level 4
	Gear GetGearPiece(int user, int piece, int level);
	int SumGearStats(int user, int stat); // stat: 0 --> health, 1 --> mana, 2 --> speed, 3 --> power

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
	int info_cd;
	bool count;
	bool show_info;
	int page_display; // 1 --> page1, 2 --> page2, 3 --> page3, 4 --> page4, 5 --> page5
	int page_gear[4];

	// display
	void DisplayHero(int n);
	SDL_Texture* whitemark_128x128;
	SDL_Texture* whitemark_250x70;
	SDL_Texture* whitemark_800x150;
	SDL_Texture* hero_tex;
	SDL_Texture* items_tex;
	SDL_Texture* gear_tex;
	void DisplayItems();
	void DisplayGear(int n);
	void SaveItemChange(int n, int change);
	bool CheckItemEquiped(int n);
	void SaveGearChange(int n, int change, SUB_INV submenu);

	// buttons
	int chosed;
	Button skill_button;
	Button items_buttons[NUM_ITEMS_BUTTONS];
	Button items_select_buttons[NUM_ITEMS_SELECT_BUTTONS];
	int item_submenu; // indica que item se cambia
	Button gear_buttons[NUM_GEAR_BUTTONS];
	Button gear_select_buttons[NUM_GEAR_SELECT_BUTTONS];
	SUB_INV submenu;

	// sound
	uint click_sound;
	uint hover_sound;
	uint equip_sound;
	uint unequip_sound;
	bool hover_playing = false;
	bool InAnyButton();
	
};

#endif