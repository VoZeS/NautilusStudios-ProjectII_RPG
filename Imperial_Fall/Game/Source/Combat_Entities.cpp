#include "Combat_Entities.h"
#include "Defs.h"
#include "Log.h"

Combat_Entities::Combat_Entities(int health, int mana, int speed, int power, int owner)
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

	skills[0] = SetSkill(entity_type, 0); // read from xml
	skills[1] = SetSkill(entity_type, 1); // read from xml
	skills[2] = SetSkill(entity_type, 2); // read from xml
	skills[3] = SetSkill(entity_type, 3); // read from xml
}

Combat_Entities::Combat_Entities(ENEMIES enemy)
{
	switch (enemy)
	{
	case ENEMIES::NOTHING:
		this->speed = 0;
		
		alive = 2;
		break;
	case ENEMIES::TEMPLAR:
		max_health = 100;
		actual_health = max_health;
		max_mana = 40;
		actual_mana = max_mana;
		this->speed = 30;
		this->power = 60;
		shield = 0;
		shield_turns = 0;

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

		alive = 1;

		entity_type = 5;

		skills[0] = SetSkill(entity_type, 0); // read from xml
		skills[1] = SetSkill(entity_type, 1); // read from xml
		skills[2] = SetSkill(entity_type, 2); // read from xml
		skills[3] = SetSkill(entity_type, 0); // read from xml
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

		alive = 1;

		entity_type = 6;

		skills[0] = SetSkill(entity_type, 0); // read from xml
		skills[1] = SetSkill(entity_type, 1); // read from xml
		skills[2] = SetSkill(entity_type, 2); // read from xml
		skills[3] = SetSkill(entity_type, 0); // read from xml
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

		alive = 1;

		entity_type = 7;

		skills[0] = SetSkill(entity_type, 0); // read from xml
		skills[1] = SetSkill(entity_type, 1); // read from xml
		skills[2] = SetSkill(entity_type, 2); // read from xml
		skills[3] = SetSkill(entity_type, 0); // read from xml
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
		
	}
	else
	{
		actual_health -= amount;
	}

	if (actual_health <= 0)
	{
		actual_health = 0;
		alive = 0;
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

void Combat_Entities::ShieldEntity(int amount, int turns)
{
	shield += amount;
	shield_turns += turns;
}

void Combat_Entities::HealEntity(int amount)
{
	actual_health += amount;

	if (actual_health > max_health)
	{
		actual_health = max_health;
	}
}


void Combat_Entities::CleanEntity()
{
	// remove debuffs
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
			buff.turns += turns_to_add;
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
			buffs.Del(item);
		}
	}
}

void Combat_Entities::RemoveAllBuffs()
{
	ListItem<BUFF>* item;

	for (item = buffs.start; item != NULL; item = item->next)
	{
		buffs.Del(item);
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
			debuff.turns += turns_to_add;
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
			debuffs.Del(item);
		}
	}
}

void Combat_Entities::RemoveAllDebuffs()
{
	ListItem<BUFF>* item;

	for (item = buffs.start; item != NULL; item = item->next)
	{
		buffs.Del(item);
	}
}

void Combat_Entities::UpdateDamageDebuffs()
{
	DEBUFF b;

	// burn
	b.debuff_type = DEBUFF_TYPE::BURN;
	
	if (FindDebuff(b) != -1)
	{
		DamageEntity(max_health / 10, SKILL_BONUS::NOTHING);
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
			skill.anim_effect = ANIM_EFFECT::HEAL;
			skill.mana_cost = 0;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "MP Potion";
			skill.anim_effect = ANIM_EFFECT::HEAL;
			skill.mana_cost = 0;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::RELOAD;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Fire Granade";
			skill.anim_effect = ANIM_EFFECT::FIRE;
			skill.mana_cost = 0;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 1;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Lightning Knife";
			skill.anim_effect = ANIM_EFFECT::LIGHTNING;
			skill.mana_cost = 0;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 2;
			skill.att_strenght = 1;
			break;
		}
	}
	else if (owner == 0) // assassin
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Stab";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Strong Stab";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Bomb";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Stealth";
			skill.anim_effect = ANIM_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STEALTH;
			skill.buff_turns = 1;
			break;
		}
	}
	else if (owner == 1) // healer
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Staff Blow";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Shield";
			skill.anim_effect = ANIM_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.buff_turns = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Heal";
			skill.anim_effect = ANIM_EFFECT::HEAL;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Clean";
			skill.anim_effect = ANIM_EFFECT::HEAL;
			skill.mana_cost = 10;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.support_type = SUPPORT_TYPE::CLEAN;
			break;
		}
	}
	else if (owner == 2) // tank
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Slash";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Heavy Slash";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Taunt";
			skill.anim_effect = ANIM_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 1;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Pierce Slash";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.skill_bonus = SKILL_BONUS::IGNORE_SHIELD;
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
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Rock";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Fire Ball";
			skill.anim_effect = ANIM_EFFECT::FIRE;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Water Jet";
			skill.anim_effect = ANIM_EFFECT::WATER;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 3;
			skill.att_strenght = 0;
			break;
		}
	}
	else if (owner == 4) // Templar (ENEMY)
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Lunge";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Block"; // Bloqueo de escudo (puede bloquear y evitar un ataque a sus compañeros)
			skill.anim_effect = ANIM_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Templar Scream"; // +5 de daño en todos SUS ataques
			skill.anim_effect = ANIM_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			// buff
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Fire Edge"; // Daño medio con fuego
			skill.anim_effect = ANIM_EFFECT::FIRE;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 1;
			break;
		}
	}
	else if (owner == 5) // EnemyHealer (ENEMY)
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Punch";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Heal"; // Cura +15 de vida a quien menos vida tenga
			skill.anim_effect = ANIM_EFFECT::HEAL;
			skill.mana_cost = 30;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "HeartBreaker"; // Roba +5 de vida a los PROTAGONISTAS y se los pone a los ENEMIGOS
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.supp_strenght = 0;
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
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Multiple Scratch"; // "Scratch" pero a 3 PROTAGONISTAS distintos en el mismo ataque******Ruben: Todos por favor, no 3*****DAVID: HAHHAHAH VALE TODOS
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 35;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Reap";
			skill.anim_effect = ANIM_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
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
		skill.anim_effect = ANIM_EFFECT::PHYSIC;
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
		skill.anim_effect = ANIM_EFFECT::BUFF;
		skill.mana_cost = 10;
		skill.ally_objective = ALLY_OBJECTIVE::SELF;
		skill.element = 0;
		skill.supp_strenght = 0;
		skill.support_type = SUPPORT_TYPE::SHIELD;
		skill.buff_turns = 1;
		break;
	case 2:
		skill.owner = owner;
		skill.skill_name = "Steal Life";
		skill.anim_effect = ANIM_EFFECT::PHYSIC;
		skill.mana_cost = 20;
		skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
		skill.ally_objective = ALLY_OBJECTIVE::SELF;
		skill.element = 0;
		skill.att_strenght = 0;
		skill.supp_strenght = 0;
		break;
	}
	}
	return skill;
}
