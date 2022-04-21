#include "App.h"
#include "Render.h"
#include "Fonts.h"
#include "Combat_Entities.h"
#include "Combat_Manager.h"
#include "Defs.h"
#include "Log.h"
#include "Particles.h"

Combat_Entities::Combat_Entities(int health, int mana, int speed, int power, int owner, int skill1, int skill2, int skill3, int skill4)
{
	max_health = health;
	actual_health = max_health;
	max_mana = mana;
	actual_mana = max_mana;
	this->speed = speed;
	this->power = power;
	shield = 0;
	shield_turns = 0;

	alive = 1;

	entity_type = owner;

	skills[0] = SetSkill(entity_type, skill1); // read from xml
	skills[1] = SetSkill(entity_type, skill2); // read from xml
	skills[2] = SetSkill(entity_type, skill3); // read from xml
	skills[3] = SetSkill(entity_type, skill4); // read from xml
}

Combat_Entities::Combat_Entities(ENEMIES enemy)
{
	switch (enemy)
	{
	case ENEMIES::NOTHING:
		max_health = 9999999;
		actual_health = max_health;
		this->speed = 0;
		
		alive = 2;

		entity_type = -1;
		break;
	case ENEMIES::W_TEMPLAR:
		max_health = 100;
		actual_health = max_health;
		max_mana = 40;
		actual_mana = max_mana;
		this->speed = 30;
		this->power = 60;
		shield = 0;
		shield_turns = 0;

		weak_to = -1;

		alive = 1;

		entity_type = 4;

		skills[0] = SetSkill(entity_type, 0); // read from xml
		skills[1] = SetSkill(entity_type, 1); // read from xml
		skills[2] = SetSkill(entity_type, 2); // read from xml
		skills[3] = SetSkill(entity_type, 3); // read from xml
		break;
	case ENEMIES::MUSHROOM:
		max_health = 90;
		actual_health = max_health;
		max_mana = 80;
		actual_mana = max_mana;
		this->speed = 40;
		this->power = 30;
		shield = 0;
		shield_turns = 0;

		weak_to = 1;

		alive = 1;

		entity_type = 5;

		skills[0] = SetSkill(entity_type, 0); // read from xml
		skills[1] = SetSkill(entity_type, 1); // read from xml
		skills[2] = SetSkill(entity_type, 2); // read from xml
		skills[3] = SetSkill(entity_type, 3); // read from xml
		break;
	case ENEMIES::GOBLIN:
		max_health = 80;
		actual_health = max_health;
		max_mana = 50;
		actual_mana = max_mana;
		this->speed = 60;
		this->power = 50;
		shield = 0;
		shield_turns = 0;

		weak_to = 2;

		alive = 1;

		entity_type = 6;

		skills[0] = SetSkill(entity_type, 0); // read from xml
		skills[1] = SetSkill(entity_type, 1); // read from xml
		skills[2] = SetSkill(entity_type, 2); // read from xml
		skills[3] = SetSkill(entity_type, 3); // read from xml
		break;
	case ENEMIES::SKELETON:
		max_health = 50;
		actual_health = max_health;
		max_mana = 30;
		actual_mana = max_mana;
		this->speed = 35;
		this->power = 60;
		shield = 0;
		shield_turns = 0;

		weak_to = -1;

		alive = 1;

		entity_type = 7;

		skills[0] = SetSkill(entity_type, 0); // read from xml
		skills[1] = SetSkill(entity_type, 1); // read from xml
		skills[2] = SetSkill(entity_type, 2); // read from xml
		skills[3] = SetSkill(entity_type, 3); // read from xml
		break;
	case ENEMIES::R_TEMPLAR:
		max_health = 200;
		actual_health = max_health;
		max_mana = 80;
		actual_mana = max_mana;
		this->speed = 40;
		this->power = 80;
		shield = 0;
		shield_turns = 0;

		weak_to = -1;

		alive = 1;

		entity_type = 8;

		skills[0] = SetSkill(entity_type, 0); // read from xml
		skills[1] = SetSkill(entity_type, 1); // read from xml
		skills[2] = SetSkill(entity_type, 2); // read from xml
		skills[3] = SetSkill(entity_type, 3); // read from xml
		break;
	}
}

Combat_Entities::Combat_Entities()
{
	skills[0] = SetSkill(-1, 0); // read from xml
	skills[1] = SetSkill(-1, 1); // read from xml
	skills[2] = SetSkill(-1, 2); // read from xml
	skills[3] = SetSkill(-1, 3); // read from xml
}

Combat_Entities::~Combat_Entities()
{

}

bool Combat_Entities::DamageEntity(int amount, SKILL_BONUS bonus)
{
	if (shield > 0)
	{
		if (bonus == SKILL_BONUS::NOTHING)
		{
			shield -= amount;

			if (shield > 0)
			{
				return true;
			}
			else
			{
				actual_health += shield;
				shield = 0;
			}
		}
		else if (bonus == SKILL_BONUS::DESTROY_SHIELD)
		{
			shield = 0;
			actual_health -= amount;
		}
		else if (bonus == SKILL_BONUS::IGNORE_SHIELD)
		{
			actual_health -= amount;
		}
		else if (bonus == SKILL_BONUS::CRITICAL)
		{
			if (actual_health <= max_health / 2)
			{
				shield -= amount * 2;

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
				shield -= amount * 0.5;

				if (shield > 0)
				{
					return true;
				}
				else
				{
					actual_health += shield;
				}
			}
		}
	}
	else
	{
		actual_health -= amount;
	}

	if (actual_health <= 0)
	{
		actual_health = 0;
		prepared_to_die = true;
		app->particles->AddParticle(app->particles->blood_smoke, position.x - 32, position.y - 35);
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
	else if (actual_mana < 0)
	{
		actual_mana = 0;
	}
}

void Combat_Entities::ShieldEntity(int amount, int turns)
{
	if (amount > shield)
	{
		shield = amount;
	}
	
	if (turns > shield_turns)
	{
		shield_turns = turns;
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

void Combat_Entities::UpdateShield()
{
	if (shield_turns > 0)
	{
		shield_turns--;
		if (shield_turns == 0)
		{
			shield = 0;
		}
	}
}

int Combat_Entities::FindBuff(BUFF buff)
{
	ListItem<BUFF>* item;

	for (item = buffs.start; item != NULL; item = item->next)
	{
		if (buff.buff_type == item->data.buff_type)
		{
			return item->data.turns;
		}
	}
	return -1;
}

void Combat_Entities::AddBuff(BUFF_TYPE type, int turns)
{
	BUFF new_buff;
	new_buff.buff_type = type;

	if (FindBuff(new_buff) == -1)
	{
		new_buff.turns = turns;
		buffs.Add(new_buff);

		// stat buffs
		if (type == BUFF_TYPE::QUICK)
		{
			SetSpeed(0);
		}
		else if (type == BUFF_TYPE::STRONG)
		{
			SetPower(0);
		}
		else if (type == BUFF_TYPE::GODMODE_STRONG)
		{
			SetGodModePower(0);
		}
	}
	else
	{
		AddBuffTurns(new_buff, turns);
	}
}

void Combat_Entities::AddBuffTurns(BUFF buff, int turns_to_add)
{
	ListItem<BUFF>* item;

	for (item = buffs.start; item != NULL; item = item->next)
	{
		if (buff.buff_type == item->data.buff_type)
		{
			item->data.turns += turns_to_add;
			if (buff.buff_type == BUFF_TYPE::QUICK || buff.buff_type == BUFF_TYPE::STRONG)
			{
				item->data.turns--;
			}
			break;
		}
	}
}

void Combat_Entities::UpdateBuffs()
{
	ListItem<BUFF>* item;

	for (item = buffs.start; item != NULL; item = item->next)
	{
		item->data.turns--;
		if (item->data.turns == 0)
		{
			// stat buffs
			if (item->data.buff_type == BUFF_TYPE::QUICK)
			{
				SetSpeed(1);
			}
			else if (item->data.buff_type == BUFF_TYPE::STRONG)
			{
				SetPower(1);
			}
			else if (item->data.buff_type == BUFF_TYPE::GODMODE_STRONG)
			{
				SetGodModePower(1);
			}

			buffs.Del(item);
		}
	}
}

void Combat_Entities::RemoveAllBuffs()
{
	ListItem<BUFF>* item;

	for (item = buffs.start; item != NULL; item = item->next)
	{
		if (item->data.buff_type == BUFF_TYPE::QUICK)
		{
			SetSpeed(1);
		}
		else if (item->data.buff_type == BUFF_TYPE::STRONG)
		{
			SetPower(1);
		}
		else if (item->data.buff_type == BUFF_TYPE::GODMODE_STRONG)
		{
			SetGodModePower(1);
		}

		buffs.Del(item);
	}
}

void Combat_Entities::RemoveGodModeBuffs()
{
	ListItem<BUFF>* item;

	for (item = buffs.start; item != NULL; item = item->next)
	{
		if (item->data.buff_type == BUFF_TYPE::GODMODE_STRONG)
		{
			if (item->data.buff_type == BUFF_TYPE::GODMODE_STRONG)
			{
				SetGodModePower(1);
			}

			buffs.Del(item);
		}
	}
}

void Combat_Entities::UpdateHealBuffs()
{
	BUFF b;

	// realx
	b.buff_type = BUFF_TYPE::RELAX;

	if (FindBuff(b) != -1)
	{
		HealEntity(max_health / 4);
	}
}

int Combat_Entities::FindDebuff(DEBUFF debuff)
{
	ListItem<DEBUFF>* item;

	for (item = debuffs.start; item != NULL; item = item->next)
	{
		if (debuff.debuff_type == item->data.debuff_type)
		{
			return item->data.turns;
		}
	}
	return -1;
}

void Combat_Entities::AddDebuff(DEBUFF_TYPE type, int turns)
{
	DEBUFF new_debuff;
	new_debuff.debuff_type = type;

	if (FindDebuff(new_debuff) == -1)
	{
		new_debuff.turns = turns;
		debuffs.Add(new_debuff);

		// stat debuffs
		if (type == DEBUFF_TYPE::ANTI_QUICK)
		{
			SetSpeed(1);
		}
		else if (type == DEBUFF_TYPE::ANTI_STRONG)
		{
			SetPower(1);
		}
	}
	else
	{
		AddDebuffTurns(new_debuff, turns);
	}
}

void Combat_Entities::AddDebuffTurns(DEBUFF debuff, int turns_to_add)
{
	ListItem<DEBUFF>* item;

	for (item = debuffs.start; item != NULL; item = item->next)
	{
		if (debuff.debuff_type == item->data.debuff_type)
		{
			item->data.turns += turns_to_add;
			if (debuff.debuff_type == DEBUFF_TYPE::ANTI_QUICK || debuff.debuff_type == DEBUFF_TYPE::ANTI_STRONG || debuff.debuff_type == DEBUFF_TYPE::STUN)
			{
				item->data.turns--;
			}
			break;
		}
	}
}

void Combat_Entities::UpdateDebuffs()
{
	ListItem<DEBUFF>* item;

	for (item = debuffs.start; item != NULL; item = item->next)
	{
		item->data.turns--;
		if (item->data.turns == 0)
		{
			// stat debuffs
			if (item->data.debuff_type == DEBUFF_TYPE::ANTI_QUICK)
			{
				SetSpeed(0);
			}
			else if (item->data.debuff_type == DEBUFF_TYPE::ANTI_STRONG)
			{
				SetPower(0);
			}

			debuffs.Del(item);
		}
	}
}

void Combat_Entities::RemoveAllDebuffs()
{
	ListItem<DEBUFF>* item;

	for (item = debuffs.start; item != NULL; item = item->next)
	{
		if (item->data.debuff_type == DEBUFF_TYPE::ANTI_QUICK)
		{
			SetSpeed(0);
		}
		else if (item->data.debuff_type == DEBUFF_TYPE::ANTI_STRONG)
		{
			SetPower(0);
		}

		debuffs.Del(item);
	}
}

void Combat_Entities::UpdateDamageDebuffs()
{
	DEBUFF b;

	// burn
	b.debuff_type = DEBUFF_TYPE::BURN;
	
	if (FindDebuff(b) != -1)
	{
		DamageEntity(max_health / 10, SKILL_BONUS::IGNORE_SHIELD);
	}
}

Skill Combat_Entities::SetSkill(int owner, int skill_number)
{
	Skill skill;
	if (owner == -1) // items
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "HP Potion";
			skill.skill_description0 = "Heal the objective.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 0;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "MP Potion";
			skill.skill_description0 = "Restore the objective and the user mana.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 1; // reload the half of the mana from the user
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::RELOAD;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Fire Jar";
			skill.skill_description0 = "Set all enemies on fire for 3 turns.";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 0;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 1;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 3;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Lightning Jar";
			skill.skill_description0 = "Break the armor of an enemy for 2 turns.";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 0;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 2;
			skill.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			skill.buff_turns = 2;
			break;
		}
	}
	else if (owner == 0) // assassin
	{
		switch (skill_number)
		{
		case 0: // initial skills
			skill.owner = owner;
			skill.skill_name = "Stab";
			skill.skill_description0 = "Low damage to a single target.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Strong Stab";
			skill.skill_description0 = "Medium damage to a single target.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Bomb";
			skill.skill_description0 = "Low damage to all targets.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Stealth";
			skill.skill_description0 = "The user obtain stealth for one turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STEALTH;
			skill.buff_turns = 1;
			break;
		case 4:
			skill.owner = owner;
			skill.skill_name = "Quick";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 10;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::QUICK;
			skill.buff_turns = 2;
			break;
		case 5: // level 2 skills
			skill.owner = owner;
			skill.skill_name = "Fast Stab";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.buff_type = BUFF_TYPE::QUICK;
			skill.buff_turns = 1;
			break;
		case 6:
			skill.owner = owner;
			skill.skill_name = "Great Bomb";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 30;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Dodge";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::DODGE;
			skill.buff_turns = 1;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Rise";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 2;
			break;
		case 9: // level 3 up root skills
			skill.owner = owner;
			skill.skill_name = "Pierce Strong Stab";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.skill_bonus = SKILL_BONUS::IGNORE_SHIELD;
			break;
		case 10:
			skill.owner = owner;
			skill.skill_name = "Great Fire Bomb";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 1;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 3;
			break;
		case 11:
			skill.owner = owner;
			skill.skill_name = "Extended Stealth";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STEALTH;
			skill.buff_turns = 2;
			break;
		case 12:
			skill.owner = owner;
			skill.skill_name = "Exausting Bomb";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_STRONG;
			skill.buff_turns = 2;
			break;
		case 13: // level 3 down root skills
			skill.owner = owner;
			skill.skill_name = "Tactic Stab";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.skill_bonus = SKILL_BONUS::CRITICAL;
			break;
		case 14:
			skill.owner = owner;
			skill.skill_name = "Spike Trap";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_QUICK;
			skill.buff_turns = 2;
			break;
		case 15:
			skill.owner = owner;
			skill.skill_name = "Ghost";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 30;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::DAMAGE_INMUNITY;
			skill.buff_turns = 1;
			break;
		case 16:
			skill.owner = owner;
			skill.skill_name = "Lightning Strong Stab";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 2;
			skill.att_strenght = 1;
			break;
		}
	}
	else if (owner == 1) // healer
	{
		switch (skill_number)
		{
		case 0: // initial skills
			skill.owner = owner;
			skill.skill_name = "Staff Blow";
			skill.skill_description0 = "Low damage to a single target.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Shield";
			skill.skill_description0 = "Give an ally a small shield during one turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Heal";
			skill.skill_description0 = "Heal a small amount of health to an ally.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Clean";
			skill.skill_description0 = "Clean all the debuffs from an ally.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 10;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.support_type = SUPPORT_TYPE::CLEAN_DEBUFFS;
			break;
		case 4:
			skill.owner = owner;
			skill.skill_name = "Attack Boost";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 2;
			break;
		case 5: // level 2 skills
			skill.owner = owner;
			skill.skill_name = "Great Shield";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 30;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 6:
			skill.owner = owner;
			skill.skill_name = "Field Heal";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Cancel";
			skill.att_effect = ATT_EFFECT::ANTI_HEAL;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.support_type = SUPPORT_TYPE::CLEAN_BUFFS;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Speed Boost";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::QUICK;
			skill.buff_turns = 2;
			break;
		case 9: // level 3 up root skills
			skill.owner = owner;
			skill.skill_name = "Give Inmortality";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 120;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::DAMAGE_INMUNITY;
			skill.buff_turns = 2;
			break;
		case 10:
			skill.owner = owner;
			skill.skill_name = "Great Heal";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 24;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 11:
			skill.owner = owner;
			skill.skill_name = "Field Clean";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 10;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.support_type = SUPPORT_TYPE::CLEAN_DEBUFFS;
			break;
		case 12:
			skill.owner = owner;
			skill.skill_name = "Field Attack Boost";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 60;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 2;
			break;
		case 13: // level 3 down root skills
			skill.owner = owner;
			skill.skill_name = "Field Shield";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 30;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 14:
			skill.owner = owner;
			skill.skill_name = "Relax";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 35;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::RELAX;
			skill.buff_turns = 3;
			break;
		case 15:
			skill.owner = owner;
			skill.skill_name = "Field Cancel";
			skill.att_effect = ATT_EFFECT::ANTI_HEAL;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.support_type = SUPPORT_TYPE::CLEAN_BUFFS;
			break;
		case 16:
			skill.owner = owner;
			skill.skill_name = "Mana Source";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 100;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::RELOAD;
			break;
		}
	}
	else if (owner == 2) // tank
	{
		switch (skill_number)
		{
		case 0: // initial skills
			skill.owner = owner;
			skill.skill_name = "Slash";
			skill.skill_description0 = "Low damage to a single target.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Heavy Slash";
			skill.skill_description0 = "Medium damage to a single target.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Taunt";
			skill.skill_description0 = "Provoke all enemies, obtain taunt for one turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 1;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Pierce Slash";
			skill.skill_description0 = "Low damage to a single target, this tactical attack ignores the enemy shield.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.skill_bonus = SKILL_BONUS::IGNORE_SHIELD;
			break;
		case 4:
			skill.owner = owner;
			skill.skill_name = "Auto-Shield";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 10;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 5: // level 2 skills
			skill.owner = owner;
			skill.skill_name = "Defensive Slash";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 6:
			skill.owner = owner;
			skill.skill_name = "Taunt Insurance";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.shield_turns = 1;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Heavy Pierce Slash";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 25;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.skill_bonus = SKILL_BONUS::IGNORE_SHIELD;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Great Auto-Shield";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 9: // level 3 up root skills
			skill.owner = owner;
			skill.skill_name = "Heavy Defensive Slash";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 30;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 10:
			skill.owner = owner;
			skill.skill_name = "Extended Taunt";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 2;
			break;
		case 11:
			skill.owner = owner;
			skill.skill_name = "Destructive Slash";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.skill_bonus = SKILL_BONUS::DESTROY_SHIELD;
			break;
		case 12:
			skill.owner = owner;
			skill.skill_name = "Extended Great Auto-Shield";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 25;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 2;
			break;
		case 13: // level 3 down root skills
			skill.owner = owner;
			skill.skill_name = "Spinning Slash";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 30;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 14:
			skill.owner = owner;
			skill.skill_name = "Statue";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 50;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 1;
			break;
		case 15:
			skill.owner = owner;
			skill.skill_name = "Spinning Pierce Slash";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.skill_bonus = SKILL_BONUS::IGNORE_SHIELD;
			break;
		case 16:
			skill.owner = owner;
			skill.skill_name = "Revive";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 80;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::REVIVE;
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
			skill.skill_description0 = "Low damage to a single target.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Rock";
			skill.skill_description0 = "Medium damage to a single target.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Fire Ball";
			skill.skill_description0 = "Low fire damage to a single target.";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Water Jet";
			skill.skill_description0 = "Low water damage to a single target.";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 3;
			skill.att_strenght = 0;
			break;
		case 4:
			skill.owner = owner;
			skill.skill_name = "Lightning";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 2;
			skill.att_strenght = 0;
			break;
		case 5: // level 2 skills
			skill.owner = owner;
			skill.skill_name = "Armor Break";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 25;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			skill.buff_turns = 2;
			break;
		case 6:
			skill.owner = owner;
			skill.skill_name = "Burning Fire Ball";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 1;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Slow Down Water Jet";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_QUICK;
			skill.buff_turns = 1;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Great Lightning";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 2;
			skill.att_strenght = 1;
			break;
		case 9: // level 3 up root skills
			skill.owner = owner;
			skill.skill_name = "Compact Rock";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 60;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 2;
			break;
		case 10:
			skill.owner = owner;
			skill.skill_name = "Burning Fire Circle";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 30;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 1;
			break;
		case 11:
			skill.owner = owner;
			skill.skill_name = "Water Splash";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 3;
			skill.att_strenght = 0;
			break;
		case 12:
			skill.owner = owner;
			skill.skill_name = "Paralyzing Bolt";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 60;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 2;
			skill.debuff_type = DEBUFF_TYPE::STUN;
			skill.buff_turns = 1;
			break;
		case 13: // level 3 down root skills
			skill.owner = owner;
			skill.skill_name = "Giant Rock";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 14:
			skill.owner = owner;
			skill.skill_name = "Magma Orb";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 3;
			break;
		case 15:
			skill.owner = owner;
			skill.skill_name = "Slow Down Water Splash";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_QUICK;
			skill.buff_turns = 1;
			break;
		case 16:
			skill.owner = owner;
			skill.skill_name = "Divine Lightning";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 2;
			skill.att_strenght = 1;
			break;
		}
	}
	else if (owner == 4) // White Templar (ENEMY)
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Lunge";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Block"; // Bloqueo de escudo (puede bloquear y evitar un ataque a sus compa�eros)
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Templar Scream"; // +5 de da�o en todos SUS ataques
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 1;
			// buff
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Fire Edge"; // Da�o medio con fuego
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 1;
			break;
		}
	}
	else if (owner == 5) // Mushroom (ENEMY)
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Punch";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Heal"; // Cura +15 de vida a quien menos vida tenga
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Heart Breaker"; // Roba +5 de vida a los PROTAGONISTAS y se los pone a los ENEMIGOS
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Bubble";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 12;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 3;
			skill.att_strenght = 0;
			break;
		}
	}
	else if (owner == 6) // Goblin (ENEMY)
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Scratch";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Great Circle"; // "Scratch" pero a 3 PROTAGONISTAS distintos en el mismo ataque******Ruben: Todos por favor, no 3*****DAVID: HAHHAHAH VALE TODOS
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 35;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Reap";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Break";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 25;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			skill.buff_turns = 2;
			break;
		}
	}
	else if (owner == 7) // Skeleton (ENEMY)
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Silence Slash";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.buff_type = BUFF_TYPE::STEALTH;
			skill.buff_turns = 1;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Auto-Shield";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 10;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Steal Life";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Slash";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 8;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		}
	}
	else if (owner == 8) // Red Templar (ENEMY)
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Berserker";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 40;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 2;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 2;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Demolish";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.buff_type = BUFF_TYPE::QUICK;
			skill.buff_turns = 2;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "I command thee, kneel!";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 25;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			skill.buff_turns = 2;
			// buff
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Recovery";	
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 0;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 2;
			skill.supp_strenght = 2;
			skill.support_type = SUPPORT_TYPE::RELOAD;
			skill.debuff_type = DEBUFF_TYPE::STUN;
			skill.buff_turns = 1;
			skill.zero_mana = true;
			break;
		}
	}

	if (skill.buff_type == BUFF_TYPE::QUICK || skill.buff_type == BUFF_TYPE::STRONG || skill.debuff_type == DEBUFF_TYPE::STUN
		|| skill.debuff_type == DEBUFF_TYPE::ANTI_STRONG || skill.debuff_type == DEBUFF_TYPE::ANTI_QUICK)
	{
		skill.buff_turns++;
	}

	return skill;
}

void Combat_Entities::DisplayStatus(int cx, int cy)
{
	int i = 0;
	SDL_Rect rect;

	if (buffs.Count() > 0)
	{
		ListItem<BUFF>* item;

		for (item = buffs.start; item != NULL; item = item->next)
		{
			switch (item->data.buff_type)
			{
			case BUFF_TYPE::STEALTH:
				rect = { 32, 64, 32, 32 };
				break;
			case BUFF_TYPE::DODGE:
				rect = { 0, 64, 32, 32 };
				break;
			case BUFF_TYPE::DAMAGE_INMUNITY:
				rect = { 64, 32, 32, 32 };
				break;
			case BUFF_TYPE::DEBUFF_INMUNITY:
				rect = { 96, 32, 32, 32 };
				break;
			case BUFF_TYPE::TAUNT:
				rect = { 96, 0, 32, 32 };
				break;
			case BUFF_TYPE::QUICK:
				rect = { 96, 64, 32, 32 };
				break;
			case BUFF_TYPE::STRONG:
				rect = { 32, 96, 32, 32 };
				break;
			case BUFF_TYPE::RELAX:
				rect = { 32, 32, 32, 32 };
				break;
			case BUFF_TYPE::GODMODE_STRONG:
				rect = { 64, 96, 32, 32 };
				break;
			default:
				break;
			}

			app->render->DrawRectangle({ cx + (32 * i) + 1, cy + 1, 30, 30 }, 104, 193, 4, 200);
			app->render->DrawTexture(app->combat_manager->status_effects, cx + (32 * i), cy, &rect);
			i++;
		}
	}

	if (debuffs.Count() > 0)
	{
		ListItem<DEBUFF>* item;

		for (item = debuffs.start; item != NULL && i < MAX_EFFECTS_DISPLAYED; item = item->next)
		{
			switch (item->data.debuff_type)
			{
			case DEBUFF_TYPE::BURN:
				rect = { 0, 32, 32, 32 };
				break;
			case DEBUFF_TYPE::DEF_REDUCC:
				rect = { 32, 0, 32, 32 };
				break;
			case DEBUFF_TYPE::STUN:
				rect = { 0, 0, 32, 32 };
				break;
			case DEBUFF_TYPE::ANTI_QUICK:
				rect = { 64, 64, 32, 32 };
				break;
			case DEBUFF_TYPE::ANTI_STRONG:
				rect = { 0, 96, 32, 32 };
				break;
			default:
				break;
			}

			app->render->DrawRectangle({ cx + (32 * i) + 1, cy + 1, 30, 30 }, 193, 56, 4, 200);
			app->render->DrawTexture(app->combat_manager->status_effects, cx + (32 * i), cy, &rect);
			i++;
		}
	}
}

void Combat_Entities::DisplayStatusDescription(int cx, int cy)
{
	int i = 0;
	SDL_Rect rect;
	std::string description0;
	std::string description1;
	const char* res;

	if (buffs.Count() > 0)
	{
		ListItem<BUFF>* item;

		for (item = buffs.start; item != NULL; item = item->next)
		{
			switch (item->data.buff_type)
			{
			case BUFF_TYPE::STEALTH:
				rect = { 32, 64, 32, 32 };
				description0 = "Stealth, makes the enemy unable to target the user with";
				description1 = "single target skills.";
				break;
			case BUFF_TYPE::DODGE:
				rect = { 0, 64, 32, 32 };
				description0 = "Dodge, the user avoid multi-target attacks.";
				description1 = "";
				break;
			case BUFF_TYPE::DAMAGE_INMUNITY:
				rect = { 64, 32, 32, 32 };
				description0 = "Damage Inmunity, the user can't take damage.";
				description1 = "";
				break;
			case BUFF_TYPE::DEBUFF_INMUNITY:
				rect = { 96, 32, 32, 32 };
				description0 = "Debuff Inmunity, the user can't obtain debuffs.";
				description1 = "";
				break;
			case BUFF_TYPE::TAUNT:
				rect = { 96, 0, 32, 32 };
				description0 = "Taunt, the user provoke enemies. Enemies single target";
				description1 = "attacks will hit the user.";
				break;
			case BUFF_TYPE::QUICK:
				rect = { 96, 64, 32, 32 };
				description0 = "Quick, increases 2 times the user speed.";
				description1 = "";
				break;
			case BUFF_TYPE::STRONG:
				rect = { 32, 96, 32, 32 };
				description0 = "Strong, increases 1.5 times the user power.";
				description1 = "";
				break;
			case BUFF_TYPE::RELAX:
				rect = { 32, 32, 32, 32 };
				description0 = "Relax, each turn the user will be healed by a 25%";
				description1 = "of this max health.";
				break;
			case BUFF_TYPE::GODMODE_STRONG:
				rect = { 64, 96, 32, 32 };
				description0 = "Power of the Gods, increases 5 times the user power.";
				description1 = "Only the real gods can use it.";
				break;
			default:
				break;
			}

			app->render->DrawRectangle({ cx + 1, cy + ((64 + 25) * i) + 1, 30, 30 }, 104, 193, 4, 200);
			app->render->DrawTexture(app->combat_manager->status_effects, cx, cy + ((64 + 25) * i), &rect);
			res = description0.c_str();
			app->fonts->BlitText(cx + 33, cy + ((64 + 25) * i), app->fonts->textFont1, res);
			res = description1.c_str();
			app->fonts->BlitText(cx + 33, cy + ((64 + 25) * i) + 32, app->fonts->textFont1, res);
			i++;
		}
	}

	if (debuffs.Count() > 0)
	{
		ListItem<DEBUFF>* item;

		for (item = debuffs.start; item != NULL && i < MAX_EFFECTS_DISPLAYED; item = item->next)
		{
			switch (item->data.debuff_type)
			{
			case DEBUFF_TYPE::BURN:
				rect = { 0, 32, 32, 32 };
				description0 = "Burn, the user takes a 10% of his max health";
				description1 = "as damage each turn.";
				break;
			case DEBUFF_TYPE::DEF_REDUCC:
				rect = { 32, 0, 32, 32 };
				description0 = "Defense Reduction, user will receive extra damage from";
				description1 = "physic damage.";
				break;
			case DEBUFF_TYPE::STUN:
				rect = { 0, 0, 32, 32 };
				description0 = "Stun, user is unable to act.";
				description1 = "";
				break;
			case DEBUFF_TYPE::ANTI_QUICK:
				rect = { 64, 64, 32, 32 };
				description0 = "Slow, decreases by 50% the user speed.";
				description1 = "";
				break;
			case DEBUFF_TYPE::ANTI_STRONG:
				rect = { 0, 96, 32, 32 };
				description0 = "Weak, decreases by 30% the user power.";
				description1 = "";
				break;
			default:
				break;
			}

			app->render->DrawRectangle({ cx + 1, cy + ((64 + 25) * i) + 1, 30, 30 }, 193, 56, 4, 200);
			app->render->DrawTexture(app->combat_manager->status_effects, cx, cy + ((64 + 25) * i), &rect);
			res = description0.c_str();
			app->fonts->BlitText(cx + 33, cy + ((64 + 25) * i), app->fonts->textFont1, res);
			res = description1.c_str();
			app->fonts->BlitText(cx + 33, cy + ((64 + 25) * i) + 32, app->fonts->textFont1, res);
			i++;
		}
	}
}