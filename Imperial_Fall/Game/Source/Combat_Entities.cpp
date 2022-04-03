#include "Combat_Entities.h"
#include "Defs.h"
#include "Log.h"

Combat_Entities::Combat_Entities(int health, int mana, int speed, int power, int owner)
{
	actual_health = health;
	max_health = health;
	actual_mana = mana;
	max_mana = mana;
	this->speed = speed;
	this->power = power;
	shield = 0;

	alive = true;

	entity_type = owner;

	skills[0] = SetSkill(entity_type, 0); // read from xml
	skills[1] = SetSkill(entity_type, 1); // read from xml
	skills[2] = SetSkill(entity_type, 2); // read from xml
	skills[3] = SetSkill(entity_type, 3); // read from xml
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
		actual_health = 0;
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
	Skill skill;
	if (owner == 0) // assassin
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Stab";
			skill.mana_cost = 10;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Strong Stab";
			skill.mana_cost = 20;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Bomb";
			skill.mana_cost = 20;
			skill.objective = true;
			skill.attack_type = false;
			skill.element = 0;
			skill.strenght = 0;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Stealth";
			skill.mana_cost = 20;
			skill.objective = false;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		}
	}
	else if (owner == 1) // tank
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Slash";
			skill.mana_cost = 10;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Heavy Slash";
			skill.mana_cost = 20;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Taunt";
			skill.mana_cost = 20;
			skill.objective = false;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Pierce Slash";
			skill.mana_cost = 15;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		}
	}
	else if (owner == 2) // healer
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Staff Blow";
			skill.mana_cost = 10;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Shield";
			skill.mana_cost = 20;
			skill.objective = false;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Heal";
			skill.mana_cost = 15;
			skill.objective = false;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Clean";
			skill.mana_cost = 10;
			skill.objective = false;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		}
	}
	else if (owner == 3) // wizard
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Stone";
			skill.mana_cost = 10;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Rock";
			skill.mana_cost = 20;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Fire Ball";
			skill.mana_cost = 10;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 1;
			skill.strenght = 0;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Water Jet";
			skill.mana_cost = 10;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 3;
			skill.strenght = 0;
			break;
		}
	}
	else
	{
		switch (skill_number) // enemies
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Punch";
			skill.mana_cost = 10;
			skill.objective = true;
			skill.attack_type = true;
			skill.element = 0;
			skill.strenght = 0;
			break;
		}
	}

	return skill;
}