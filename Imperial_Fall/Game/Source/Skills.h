#ifndef __SKILLS_H__
#define __SKILLS_H__

#include <string>
using namespace std;

enum class ATT_EFFECT
{
	EMPTY = -1,
	PHYSIC,
	FIRE,
	LIGHTNING,
	WATER,
	ANTI_HEAL
};

enum class SUPP_EFFECT
{
	EMPTY = -1,
	HEAL,
	BUFF
};

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
	CLEAN_DEBUFFS,
	CLEAN_BUFFS,
	RELOAD,
	REVIVE
};

enum class BUFF_TYPE // self
{
	NOTHING = 0,
	STEALTH,
	DODGE,
	DAMAGE_INMUNITY,
	DEBUFF_INMUNITY,
	TAUNT,
	QUICK,
	STRONG,
	RELAX, // progresive heal
	GODMODE_STRONG
};

enum class DEBUFF_TYPE
{
	NOTHING = 0,
	BURN,
	DEF_REDUCC,
	STUN,
	ANTI_QUICK,
	ANTI_STRONG
};

enum class SKILL_BONUS
{
	NOTHING = 0,
	IGNORE_SHIELD,
	DESTROY_SHIELD,
	CRITICAL // if objective have more than his half health the attack hit half, else hit double
};

struct Skill
{
public:
	int owner; // 0 --> assassin, 1 --> tank, 2 --> healer, 3 --> wizard

	const char* skill_name = "name";
	ATT_EFFECT att_effect = ATT_EFFECT::EMPTY;
	SUPP_EFFECT supp_effect = SUPP_EFFECT::EMPTY;
	int mana_cost = 0;
	// enemy objective
	ENEMY_OBJECTIVE enemy_objective = ENEMY_OBJECTIVE::NOTHING;
	// ally objective
	ALLY_OBJECTIVE ally_objective = ALLY_OBJECTIVE::NOTHING;
	// 0 --> physic, 1 --> fire, 2 --> lightning, 3 --> water
	int element = 0;
	// 0 --> low damage, 1 --> mid damage, 2 --> high damage
	int att_strenght = -1;
	// 0 --> low damage, 1 --> mid damage, 2 --> high damage
	int supp_strenght = -1;

	// specific

	// support type
	SUPPORT_TYPE support_type = SUPPORT_TYPE::NOTHING;
	int shield_turns = 0;
	// buff type
	BUFF_TYPE buff_type = BUFF_TYPE::NOTHING;
	DEBUFF_TYPE debuff_type = DEBUFF_TYPE::NOTHING;
	int buff_turns = 0;
	// skill bonus
	SKILL_BONUS skill_bonus = SKILL_BONUS::NOTHING;

	// no mana skill, used in enemy AI
	bool zero_mana = false;
};

#endif