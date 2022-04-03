#ifndef __COMBAT_ENTITIES_H__
#define __COMBAT_ENTITIES_H__

#include "Skills.h"

enum class ENEMIES
{
	SKELLETON,
	GOBLIN,
	TEMPLAR
};

class Combat_Entities
{
public:
	Combat_Entities(int health, int mana, int speed, int power, int owner);
	Combat_Entities(ENEMIES enemy);

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
	int entity_type; // 0 --> assassin, 1 --> tank, 2 --> healer, 3 --> wizard, 4 --> enemy

	Skill skills[4];
};

#endif