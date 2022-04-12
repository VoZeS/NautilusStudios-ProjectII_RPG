#ifndef __COMBAT_ENTITIES_H__
#define __COMBAT_ENTITIES_H__

#include "Skills.h"
#include "Animation.h"
#include "List.h"
#include "Point.h"

enum class ENEMIES
{
	NOTHING = 0,
	W_TEMPLAR,
	MUSHROOM,
	GOBLIN,
	SKELETON,
	R_TEMPLAR
};

struct BUFF {
	BUFF_TYPE buff_type;
	uint turns = 0;
};

struct DEBUFF {
	DEBUFF_TYPE debuff_type;
	uint turns = 0;
};

class Combat_Entities
{
public:
	Combat_Entities(int health, int mana, int speed, int power, int owner, int skill1, int skill2, int skill3, int skill4);
	Combat_Entities(ENEMIES enemy);
	Combat_Entities();
	~Combat_Entities();

	// 0 --> dead, 1 --> alive, 2 --> no exist
	int GetEntityState()
	{
		return alive;
	}

	bool DamageEntity(int amount, SKILL_BONUS bonus);
	void ReloadMana(int amount = 0);
	void ShieldEntity(int amount, int turns);
	void HealEntity(int amount);
	void CleanDebuffedEntity();
	void CleanBuffedEntity();

	int CheckMana()
	{
		return actual_mana;
	}

	// get stats
	int GetMaxHealth()
	{
		return max_health;
	}

	int GetActualHealth()
	{
		return actual_health;
	}

	int GetMaxMana()
	{
		return max_mana;
	}

	int GetActualMana()
	{
		return actual_mana;
	}

	int GetSpeed()
	{
		return speed;
	}

	// n == 0 --> more speed, n == 1 --> less speed
	void SetSpeed(int n)
	{
		if (n == 0)
		{
			speed *= 2;
		}
		else
		{
			speed /= 2;
		}
	}

	int GetPower()
	{
		return power;
	}

	// n == 0 --> more power, n == 1 --> less power
	void SetPower(int n)
	{
		if (n == 0)
		{
			power *= 1.5f;
		}
		else
		{
			power /= 1.5f;
		}
	}

	int GetShield()
	{
		return shield;
	}

	void DestroyShield()
	{
		shield = 0;
	}

	int GetWeakness()
	{
		return weak_to;
	}

	void Revive()
	{
		alive = 1;
	}

	void UpdateShield();

	int GetType()
	{
		return entity_type;
	}

	Skill GetSkill(int pos)
	{
		return skills[pos];
	}

	// Buffs
	int FindBuff(BUFF buff); // return turns remaning or -1 if entity don't have that buff
	void AddBuff(BUFF_TYPE type, int turns);
	void AddBuffTurns(BUFF buff, int turns_to_add);
	void UpdateBuffs();
	void RemoveAllBuffs();
	List<BUFF> GetBuffList()
	{
		return buffs;
	}
	void UpdateHealBuffs();

	// Debuffs
	int FindDebuff(DEBUFF debuff); // return turns remaning or -1 if entity don't have that buff
	void AddDebuff(DEBUFF_TYPE type, int turns);
	void AddDebuffTurns(DEBUFF debuff, int turns_to_add);
	void UpdateDebuffs();
	void RemoveAllDebuffs();
	List<DEBUFF> GetDebuffList()
	{
		return debuffs;
	}
	void UpdateDamageDebuffs();

	Animation* current_anim = NULL;
	iPoint position = { 0, 0 };
	bool prepared_to_die = false;
	void KillEntity()
	{
		alive = 0;
		prepared_to_die = false;
	}

private:
	Skill SetSkill(int owner, int skill_number);

	int actual_health;
	int max_health;
	int actual_mana;
	int max_mana;
	int speed;
	int power;
	int shield;
	int shield_turns;

	// -1 --> nothing, 0 --> physic, 1 --> fire, 2 --> lightning, 3 --> water
	int weak_to = -1;

	int alive; // 0 --> dead, 1 --> alive, 2 --> no exist
	// 0 --> assassin, 1 --> tank, 2 --> healer, 3 --> wizard, 4 --> white templar, 5 --> mushroom, 6 --> goblin, 7 --> skeleton
	// 8 --> red templar
	int entity_type;

	Skill skills[4];

	List<BUFF> buffs;
	List<DEBUFF> debuffs;
};

#endif