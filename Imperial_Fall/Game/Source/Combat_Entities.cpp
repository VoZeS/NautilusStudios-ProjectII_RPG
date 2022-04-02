#include "Combat_Entities.h"
#include "Defs.h"
#include "Log.h"

Combat_Entities::Combat_Entities(int health, int mana, int speed, int power, int owner)
{
	actual_health = health;
	max_health = health;
	actual_mana = mana;
	max_health = health;
	this->speed = speed;
	this->power = power;
	shield = 0;

	alive = true;

	skills[0] = SetSkill(owner, 0); // read from xml
}

bool Combat_Entities::DamageEntity(int amount)
{
	if (shield > 0)
	{
		shield -= amount;

		if (shield > 0)
		{
			return true;
		}
		else
		{
			actual_health += shield;
		}
	}
	else
	{
		actual_health -= amount;
	}

	if (actual_health <= 0)
	{
		alive = false;
	}

	return true;
}

void Combat_Entities::ReloadMana(int amount)
{
	if (amount == -1)
	{
		actual_mana += max_mana / 2;
	}
	else
	{
		actual_mana += amount;
	}

	if (actual_mana > max_mana)
	{
		actual_mana = max_mana;
	}
}

void Combat_Entities::HealEntity(int amount)
{
	actual_health += amount;

	if (actual_health > max_health)
	{
		actual_health = max_health;
	}
}


void Combat_Entities::ShieldEntity(int amount)
{
	shield += amount;
}

Skill Combat_Entities::SetSkill(int owner, int skill_number)
{
	if (owner == 0)
	{
		switch (skill_number)
		{
		case 0:
			Skill stab;
			stab.owner = owner;
			stab.skill_name = "Stab";
			stab.mana_cost = 10;
			stab.objective = true;
			stab.attack_type = true;

			return stab;
			break;
		}
	}
}