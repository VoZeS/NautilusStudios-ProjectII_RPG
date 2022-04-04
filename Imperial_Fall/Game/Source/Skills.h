#ifndef __SKILLS_H__
#define __SKILLS_H__

#include <string>
using namespace std;

enum class ENEMY_OBJECTIVE
{
	NOTHING = 0,
	ONE_ENEMY,
	ALL_ENEMY
};

enum class ALLY_OBJECTIVE
{
	NOTHING = 0,
	ONE_ALLY,
	ALL_ALLY,
	SELF
};

enum class SUPPORT_TYPE // other allies
{
	NOTHING = 0,
	HEAL,
	SHIELD,
	CLEAN,
	RELOAD,
	REVIVE
};

enum class BUFF_TYPE // self
{
	NOTHING = 0,
	STEALTH,
	TAUNT
};

struct Skill
{
public:
	int owner; // 0 --> assassin, 1 --> tank, 2 --> healer, 3 --> wizard

	const char* skill_name = "name";
	int mana_cost = 0;
	// enemy objective
	ENEMY_OBJECTIVE enemy_objective = ENEMY_OBJECTIVE::NOTHING;
	// ally objective
	ALLY_OBJECTIVE ally_objective = ALLY_OBJECTIVE::NOTHING;
	// 0 --> physic, 1 --> fire, 2 --> lightning, 3 --> water
	int element = 0;
	// 0 --> low damage, 1 --> mid damage, 2 --> high damage
	int att_strenght = 0;
	// 0 --> low damage, 1 --> mid damage, 2 --> high damage
	int supp_strenght = 0;

	// specific

	// support type
	SUPPORT_TYPE support_type = SUPPORT_TYPE::NOTHING;
	// buff type
	BUFF_TYPE buff_type = BUFF_TYPE::NOTHING;
	int buff_turns = 0; // used with shield too
};

#endif