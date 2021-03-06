#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include "Module.h"
#include "Animation.h"

#define PAGE_SPEED 0.15f

#define NUM_ITEMS_BUTTONS_INV 4
#define NUM_ITEMS_SELECT_BUTTONS 8
#define NUM_GEAR_BUTTONS 4
#define NUM_GEAR_SELECT_BUTTONS 4
#define NUM_SKILL_TREE_BUTTONS 17
#define NUM_SKILL_INTERACT_BUTTONS 4

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
	
	void BlockAll();
	void UnlockAll();
	void ResetItems();
	void ResetGear();
	void ResetSkills();
	int GetItemUses(int n);
	// user: 0 --> assassin, 1 --> healer, 2 --> tank, 3 --> wizard
	// piece: 0 --> helmet, 1 --> chestplate, 2 --> boots, 3 --> weapon
	// user: 0 --> unequiped, 1 --> level 1, 2 --> level 2, 3 --> level 3, 4 --> level 4
	Gear GetGearPiece(int user, int piece, int level);
	int SumGearStats(int user, int stat); // stat: 0 --> health, 1 --> mana, 2 --> speed, 3 --> power

	// a --> user, if a == 4 --> item
	// e --> piece of gear, or whitch item
	// i --> level of gear
	void UnlockObject(const char* aei);
	void EquipGear(const char* aei);
	void EquipAllMaxGear(); // cheat only
	void UnlockSkill(int owner, int skill);
	void AddSkillPoint(int owner, int amount);

	SDL_Texture* items_tex;
	SDL_Texture* gear_tex;
	SDL_Texture* unknow_tex;
	SDL_Texture* accept_tex;
	SDL_Texture* misc;

	// coins
	int GetCoins();
	void AddCoins(int amount);

	// xp
	void AddXP(int owner, int amount);

	// description
	bool in_description;
	Skill desc_skill;

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
	SDL_Texture* arrows_tex;
	Animation* left_arrow;
	Animation* right_arrow;
	Animation l_arrow;
	Animation r_arrow;
	SDL_Texture* skill_tree_tex;
	Animation* skill_page;
	Animation open_skill;
	Animation close_skill;

	int book_pos; // 0 --> open, 1 --> page1, 2 --> page2, 3 --> page3, 4 --> page4, 5 --> page5, 6 --> close
	int info_cd;
	bool count;
	bool show_info;
	int page_display; // 1 --> page1, 2 --> page2, 3 --> page3, 4 --> page4, 5 --> page5
	int page_gear[4];
	bool in_skill_tree;

	// display
	void DisplayHero(int n);
	SDL_Texture* whitemark_128x128;
	SDL_Texture* whitemark_150x150;
	SDL_Texture* whitemark_250x70;
	SDL_Texture* whitemark_800x150;
	SDL_Texture* hero_tex;
	void DisplayItems();
	void DisplayGear(int n);
	void DisplayGearHover(int user, int piece, int level);
	void SaveItemChange(int n, int change);
	bool CheckItemEquiped(int n);
	bool CheckItemUnlocked(int n);
	void SaveGearChange(int n, int change, SUB_INV submenu);
	bool CheckGearUnlocked(int user, int piece, int level);
	bool CheckSkillUnlocked(int owner, int skill);
	bool CheckSkillPoints(int owner, int skill);
	void DisplaySkillPoints(int owner);
	bool CheckSkillEquiped(int owner, int skill);
	void SaveSkillChange(int owner, int skill_slot, int skill_to_insert);

	// buttons
	int chosed;
	Button skill_button;
	Button items_buttons[NUM_ITEMS_BUTTONS_INV];
	Button items_select_buttons[NUM_ITEMS_SELECT_BUTTONS];
	int item_submenu; // indica que item se cambia
	Button gear_buttons[NUM_GEAR_BUTTONS];
	Button gear_select_buttons[NUM_GEAR_SELECT_BUTTONS];
	Button skill_tree_buttons[NUM_SKILL_TREE_BUTTONS];
	Button skill_interact_buttons[NUM_SKILL_INTERACT_BUTTONS];
	SUB_INV submenu;

	// sound
	uint click_sound;
	uint hover_sound;
	uint equip_sound;
	uint unequip_sound;
	uint open_book_sound;
	uint pass_page_sound;
	uint earn_coins_sound;
	uint spend_coins_sound;
	uint earn_point_sound;
	bool hover_playing = false;
	bool InAnyButton();

	// skill tree
	Skill GetSkillForInv(int owner, int skill);
	Skill GetItemForInv(int skill);
	int GetSkillParent(int skill);
	int GetSkillPoints(int skill);
	int skill_win; // 0 --> disabled, 1 --> what to equip, 2 --> unlock skill, 2 --> dont have points
	int skill_saved;
	SDL_Rect GetSkillRect(int skill, bool unlocked); // 1 to 4
	int GetSkillBySlot(int owner, int slot);
	SDL_Texture* skill_image0; // assassin
	SDL_Texture* skill_image1; // healer
	SDL_Texture* skill_image2; // tank
	SDL_Texture* skill_image3; // wizard

	SDL_Texture* inventory;

	// coins
	void DisplayCoins();
	SDL_Texture* coin;
	int coins_obtained;
	int coins_cd;
	SDL_Texture* whitemark_500x70;
	
};

#endif