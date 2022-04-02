#ifndef __COMBAT_ENTITIES_H__
#define __COMBAT_ENTITIES_H__

#include "Skills.h"

class Combat_Entities
{
public:
	Combat_Entities(int health, int mana, int speed, int power, int owner);

	bool GetEntityState()
	{
		return alive;
	}

	bool DamageEntity(int amount);
	void ReloadMana(int amount = -1);
	void HealEntity(int amount);
	void ShieldEntity(int amount);

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

	Skill skills[4];
};

#endif