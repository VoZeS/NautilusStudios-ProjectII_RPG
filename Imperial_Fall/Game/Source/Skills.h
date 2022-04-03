#ifndef __SKILLS_H__
#define __SKILLS_H__

#include <string>
using namespace std;

enum class OBJECTIVE
{
	ONE_ENEMY = 0,
	ALL_ENEMY,
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
	// objective
	OBJECTIVE objective = OBJECTIVE::ONE_ENEMY;
	// 0 --> physic, 1 --> fire, 2 --> lightning, 3 --> water
	int element = 0;
	// 0 --> low damage, 1 --> mid damage, 2 --> high damage
	int strenght = 0;

	// specific

	// support type
	SUPPORT_TYPE support_type = SUPPORT_TYPE::NOTHING;
	// buff type
	BUFF_TYPE buff_type = BUFF_TYPE::NOTHING;
};

#endif