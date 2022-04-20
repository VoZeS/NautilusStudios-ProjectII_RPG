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
	Combat_Menu(bool enabled);

	virtual ~Combat_Menu();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void SetAlliesTurn(bool h)
	{
		allies_turn = h;
	}

	void SetSkillPrepared(Skill skill)
	{
		skill_prepared = skill;
	}

	void SetSkillAnimation(ATT_EFFECT att_effect, SUPP_EFFECT supp_effect, int pos_x, int pos_y)
	{
		skill_att_effect = att_effect;
		skill_supp_effect = supp_effect;
		objective_pos.x = pos_x;
		objective_pos.y = pos_y;
	}

	void CancelAction()
	{
		prep_in_items = true;
		prep_in_enemies = true;
		prep_in_allies = true;
	}

	iPoint GetEntityPosition(bool ally, int n);

	void SetController()
	{
		general_buttons[0].state = 1;
		items_buttons[0].state = 1;
		enemies_buttons[0].state = 1;
		allies_buttons[0].state = 1;
	}

	// description
	bool in_description;
	int description_type = 0; // 0 --> entity, 1 --> skill
	Combat_Entities* desc_entity = NULL;
	int enemy_chosed;
	int ally_chosed;
	Skill desc_skill;
	void DisplaySkillEffects(Skill skill, int cx, int cy);

private:
	bool preupdatedone = false;
	bool updatedone = false;

	bool in_action = false;
	bool allies_turn = false;

	bool in_items = false;
	bool in_enemies = false;
	bool in_allies = false;
	int prep_in_items = 0; // 0 --> unactive, 1 --> to false, 2 --> to true
	int prep_in_enemies = 0; // 0 --> unactive, 1 --> to false, 2 --> to true
	int prep_in_allies = 0; // 0 --> unactive, 1 --> to false, 2 --> to true

	int skill_prepared_is_item = -1; // -1 --> no item, 0 --> item 0, 1 --> item 1, 2 --> item 2, 3 --> item 3

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
	Animation templarAnim;
	Animation mushroomAnim;
	Animation goblinAnim;
	Animation skeletonAnim;

	// positions
	fPoint action_pos[NUM_BUTTONS];
	fPoint item_pos[NUM_ITEMS_BUTTONS];
	fPoint enemy_pos[NUM_ENEMIES_BUTTONS];
	fPoint ally_pos[NUM_ALLIES_BUTTONS];

	// combat manager
	Skill skill_prepared;
	ATT_EFFECT skill_att_effect;
	SUPP_EFFECT skill_supp_effect;
	iPoint objective_pos;

	// textures
	SDL_Texture* assassin_texture = NULL;
	SDL_Texture* tank_texture = NULL;
	SDL_Texture* healer_texture = NULL;
	SDL_Texture* wizard_texture = NULL;
	SDL_Texture* target = NULL;
	SDL_Texture* tombstone = NULL;
	SDL_Texture* goblin = NULL;
	SDL_Texture* skeleton = NULL;
	SDL_Texture* mushroom = NULL;
	SDL_Texture* white_templar = NULL;
	SDL_Texture* red_templar = NULL;
	SDL_Texture* whitemark_400x50 = NULL;
	SDL_Texture* whitemark_110x110 = NULL;
	SDL_Texture* whitemark_128x128 = NULL;
	SDL_Texture* whitemark_800x50 = NULL;
	SDL_Texture* special_buttons = NULL;
	SDL_Texture* items = NULL;
	SDL_Texture* casting = NULL;
	SDL_Texture* skills_icons = NULL;

	void BlittAttackText(int c_x, int c_y);

	// skills fx
	// 0 --> physic, 1 --> fire, 2 --> lightning, 3 --> water, 4 --> heal, 5 --> buff
	void PlaySkillFx(int n);
	uint physic_fx;
	uint fire_fx;
	uint lightning_fx;
	uint water_fx;
	uint heal_fx;
	uint buff_fx;

};

#endif