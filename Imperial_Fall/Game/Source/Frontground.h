#ifndef __FRONTGROUND_H__
#define __FRONTGROUND_H__

#include "Module.h"

enum class ENEMIES;

class Frontground : public Module
{
public:
	Frontground();

	virtual ~Frontground();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void SetA_Black()
	{
		a = 255;
	}

	void SetA_Null()
	{
		a = 0;
	}

	bool FadeToBlack(int dest_level); // if -1 --> no level change

	bool FadeFromBlack(int dest_level); // if -1 --> no level change

	bool FadeInCombat(ENEMIES enemies[]); // start combat


	ENEMIES enemies_to_fight[4];

	bool FadeOutCombat();

	ENEMIES GetEnemiesToFight(int n)
	{
		return enemies_to_fight[n];
	}

	bool ReturnToField(); // end combat

	bool ResetCombat();

	void SetPressE_Hide(bool hide)
	{
		press_e_hide = hide;
	}

	int GetCombatState()
	{
		return in_combat;
	}

	bool town1_to_town2 = false,
		town2_to_town1 = false,
		forest_to_town2 = false,
		battlefield_to_town2 = false,
		dungeon_to_town2 = false,
		town1_to_outside = false,
		inside_to_outside = false,
		outside_to_town1 = false;

private:
	SDL_Rect r;
	Uint8 a;

	bool go_black = false;
	bool return_black = false;
	int fade_speed = 4;

	int destination_level = -1;

	SDL_Texture* press_e;
	bool press_e_hide = true;

	int in_combat = 0; // 0 --> no combat, 1 --> entering combat, 2 --> in combat, 3 --> exiting combat, 4 --> restart combat
	int  restart = 0; // 0 --> desactivado, 1 --> activado, 2 --> proceso
};

#endif
