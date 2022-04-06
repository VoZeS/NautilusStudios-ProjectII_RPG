#ifndef __COMBAT_ENTITIES_H__
#define __COMBAT_ENTITIES_H__

#include "Skills.h"
#include "Animation.h"
#include "List.h"
#include "Point.h"

enum class ENEMIES
{
	NOTHING = -1,
	TEMPLAR,
	MUSHROOM,
	GOBLIN,
	SKELETON
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
	Combat_Entities(int owner);
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
	void CleanEntity();

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

	int GetPower()
	{
		return power;
	}

	int GetShield()
	{
		return shield;
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

	int alive; // 0 --> dead, 1 --> alive, 2 --> no exist
	int entity_type; // 0 --> assassin, 1 --> tank, 2 --> healer, 3 --> wizard, 4 --> Templar, 5 --> EnemyHealer, 6 --> Goblin

	Skill skills[4];

	List<BUFF> buffs;
	List<DEBUFF> debuffs;
};

#endif