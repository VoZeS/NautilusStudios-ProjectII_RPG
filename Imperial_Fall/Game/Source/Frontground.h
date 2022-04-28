#ifndef __FRONTGROUND_H__
#define __FRONTGROUND_H__

#include "Module.h"
#include "Animation.h"

enum class ENEMIES;

enum class MOVE_TO
{
	NOTHING = -1,
	LOGO_SCENE,
	SCENE_TOWN1,
	SCENE_TOWN2,
	SCENE_FOREST,
	SCENE_BATTLEFIELD,
	SCENE_DUNGEON,
	SCENE_OUTSIDE,
	SCENE_INSIDE,
	TOWN1_SCENE,
	TOWN1_TOWN2,
	TOWN1_OUTSIDE,
	TOWN1_COMBAT,
	TOWN2_SCENE,
	TOWN2_TOWN1,
	TOWN2_FOREST,
	TOWN2_BATTLEFIELD,
	TOWN2_DUNGEON,
	TOWN2_COMBAT,
	FOREST_SCENE,
	FOREST_TOWN2,
	FOREST_COMBAT,
	BATTLEFIELD_SCENE,
	BATTLEFIELD_TOWN2,
	BATTLEFIELD_COMBAT,
	DUNGEON_SCENE,
	DUNGEON_TOWN2,
	DUNGEON_COMBAT,
	OUTSIDE_SCENE,
	OUTSIDE_TOWN1,
	OUTSIDE_INSIDE,
	OUTSIDE_COMBAT,
	INSIDE_SCENE,
	INSIDE_OUTSIDE,
	INSIDE_COMBAT,
	FROM_COMBAT,
	RESET_COMBAT,
	COMBAT_FINALCOMBAT
};

class Frontground : public Module
{
public:
	Frontground(bool enabled);

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

	int GetA()
	{
		return a;
	}

	bool FadeToBlack();

	bool FadeFromBlack();

	bool FadeInCombat(ENEMIES enemies[], std::string rew); // start combat


	ENEMIES enemies_to_fight[4];
	std::string reward = "999"; // default

	ENEMIES GetEnemiesToFight(int n)
	{
		return enemies_to_fight[n];
	}

	bool ReturnToField(); // end combat
	void SaveDirection();
	void MovePlayer();

	bool ResetCombat();

	void ReturnStartScreen();

	MOVE_TO move_to = MOVE_TO::NOTHING;

	void SetController();

private:
	SDL_Rect r;
	Uint8 a;

	bool go_black = false;
	bool return_black = false;
	int fade_speed = 4;

	int direction = -1; // 0 --> down, 1 --> up, 2 --> right, 3 --> left

	// cutscene
	uint letlengh = 0;
	int letter_cd = 0;
	bool fix = true;

public:
	// controller
	bool controller = false;

	// god mode
	bool godmode = false;

	// fast combat
	bool fast_combat = false;

	// 0 --> scene, 1 --> town1, 2 --> town2, 3 --> forest, 4 --> battlefield, 5 --> dungeon, 6 --> outside, 7 --> inside
	int current_level = 0;

	// adventure phase
	int adventure_phase = 0;

	// is there a save
	bool first_time = false;
	void SetFirstTime(bool state)
	{
		pugi::xml_document saveGame;
		pugi::xml_parse_result result = saveGame.load_file(STARTED_FILENAME);

		saveGame.child("started").child("first_time").attribute("value").set_value(state);

		saveGame.save_file(STARTED_FILENAME);
	}

	void SaveStartUp();
};

#endif
