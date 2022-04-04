#ifndef __COMBAT_ENTITIES_H__
#define __COMBAT_ENTITIES_H__

#include "Skills.h"
#include "Animation.h"
#include "List.h"

enum class ENEMIES
{
	TEMPLAR = 0,
	HEALER,
	GOBLIN,
	SKELETON
};

struct BUFF {
	BUFF_TYPE buff_type;
	uint turns = 0;
};

class Combat_Entities
{
public:
	Combat_Entities(int health, int mana, int speed, int power, int owner);
	Combat_Entities(ENEMIES enemy);
	~Combat_Entities();

	bool GetEntityState()
	{
		return alive;
	}

	bool DamageEntity(int amount);
	void ReloadMana(int amount = 0);
	void ShieldEntity(int amount);
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
	void AddTurns(BUFF buff, int turns_to_add);
	void UpdateBuffs();
	void RemoveAllBuffs();
	List<BUFF> GetBuffList()
	{
		return buffs;
	}

	Animation* current_anim = NULL;

private:
	Skill SetSkill(int owner, int skill_number);

	int actual_health;
	int max_health;
	int actual_mana;
	int max_mana;
	int speed;
	int power;
	int shield;

	bool alive;
	int entity_type; // 0 --> assassin, 1 --> tank, 2 --> healer, 3 --> wizard, 4 --> Templar, 5 --> EnemyHealer, 6 --> Goblin

	Skill skills[4];

	List<BUFF> buffs;
};

#endif