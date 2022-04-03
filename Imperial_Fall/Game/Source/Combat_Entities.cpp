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

	entity_type = owner;

	skills[0] = SetSkill(entity_type, 0); // read from xml
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
	if (amount == 0)
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
	else if (actual_mana < 0)
	{
		actual_mana = 0;
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
			stab.element = 0;
			stab.strenght = 0;

			return stab;
			break;
		}
	}
	else if (owner == 1)
	{
		switch (skill_number)
		{
		case 0:
			Skill slash;
			slash.owner = owner;
			slash.skill_name = "Stab";
			slash.mana_cost = 10;
			slash.objective = true;
			slash.attack_type = true;
			slash.element = 0;
			slash.strenght = 0;

			return slash;
			break;
		}
	}
	else if (owner == 2)
	{
		switch (skill_number)
		{
		case 0:
			Skill staff_blow;
			staff_blow.owner = owner;
			staff_blow.skill_name = "Stab";
			staff_blow.mana_cost = 10;
			staff_blow.objective = true;
			staff_blow.attack_type = true;
			staff_blow.element = 0;
			staff_blow.strenght = 0;

			return staff_blow;
			break;
		}
	}
	else if (owner == 3)
	{
		switch (skill_number)
		{
		case 0:
			Skill stone;
			stone.owner = owner;
			stone.skill_name = "Stab";
			stone.mana_cost = 10;
			stone.objective = true;
			stone.attack_type = true;
			stone.element = 0;
			stone.strenght = 0;

			return stone;
			break;
		}
	}
	else
	{
		switch (skill_number)
		{
		case 0:
			Skill punch;
			punch.owner = owner;
			punch.skill_name = "Stab";
			punch.mana_cost = 10;
			punch.objective = true;
			punch.attack_type = true;
			punch.element = 0;
			punch.strenght = 0;

			return punch;
			break;
		}
	}
}