#ifndef __COMBAT_MANAGER_H__
#define __COMBAT_MANAGER_H__

#include "Module.h"
#include "Menu.h"
#include "Animation.h"
#include "Point.h"
#include "Combat_Entities.h"

#define CASTING_TIME 1 // in seconds

class Combat_Entities;

class Combat_Manager : public Module
{
public:
	Combat_Manager(bool enabled);

	virtual ~Combat_Manager();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	void SetOrder();
	bool InArray(Combat_Entities* array[], int length, Combat_Entities* check);

	void UpdateHUD();

	Combat_Entities* GetActualEntity()
	{
		return turn_order[turn];
	}

	Combat_Entities* GetEnemyByNumber(int n)
	{
		return enemies[n];
	}

	Combat_Entities* GetAllyByNumber(int n)
	{
		return allies[n];
	}

	Combat_Entities* GetItemList()
	{
		return items;
	}

	void UseSkill(Combat_Entities* user, Skill skill, Combat_Entities* objective);

	void UpdateBuffs();

	void EnemyTurn(Combat_Entities* user);

	int GetInAnimation()
	{
		return in_animation;
	}

	void SetInAnimation(int n)
	{
		in_animation = n;
	}

	void SetEntitiesPositions();

	// 0 --> normal, 1 --> win, 2 --> lose
	int CheckCombatState();

	void HeroesStats(int& health, int& mana, int& speed, int& power, int owner, int& skill1, int& skill2, int& skill3, int& skill4);

private:
	bool preupdatedone = false;

	bool in_action = false;

	bool pass_turn = false;

	Combat_Entities* turn_order[8];
	int turn = -1;
	
	Combat_Entities* allies[4] = { NULL };
	Combat_Entities* enemies[4] = { NULL };
	Combat_Entities* items = NULL;

	int animation_cd = 0;
	int in_animation = 0; // 0 --> no, 1 --> starting, 2 --> in

	void KillPreparedEntities();

	int enemies_loops = 0;

	// xml
	bool LoadHeroesStats();
	pugi::xml_document heroes_statsFile;
	pugi::xml_node heroes_stats;

	// textures
	SDL_Texture* heroes_icons = NULL;
	SDL_Texture* enemies_icons = NULL;
	SDL_Texture* turn_icon = NULL;
	SDL_Texture* dead_icon = NULL;
	SDL_Texture* whitemark_64x64 = NULL;

	// enemy casting skill
	bool casting = false;
	int casting_time = 0;
};

#endif