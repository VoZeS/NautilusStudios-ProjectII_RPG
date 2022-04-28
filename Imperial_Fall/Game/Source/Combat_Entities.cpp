#include "App.h"
#include "Render.h"
#include "Fonts.h"
#include "Combat_Entities.h"
#include "Combat_Manager.h"
#include "Frontground.h"
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

	switch (owner)
	{
	case 0: weak_to = 3; break;
	case 1: weak_to = 1; break;
	case 2: weak_to = 2; break;
	case 3: weak_to = -1; break;
	}

	alive = 1;

	entity_type = owner;

	skills[0] = SetSkill(entity_type, skill1);
	skills[1] = SetSkill(entity_type, skill2);
	skills[2] = SetSkill(entity_type, skill3);
	skills[3] = SetSkill(entity_type, skill4);
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
		weak_to = -1;
		alive = 1;
		entity_type = 4;

		if (app->frontground->adventure_phase == 0)
		{
			max_health = 100;
			actual_health = max_health;
			max_mana = 50;
			actual_mana = max_mana;
			this->speed = 35;
			this->power = 60;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 0);
			skills[1] = SetSkill(entity_type, 1);
			skills[2] = SetSkill(entity_type, 2);
			skills[3] = SetSkill(entity_type, 3);
		}
		else if (app->frontground->adventure_phase == 1)
		{
			max_health = 140;
			actual_health = max_health;
			max_mana = 95;
			actual_mana = max_mana;
			this->speed = 45;
			this->power = 75;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 4);
			skills[1] = SetSkill(entity_type, 5);
			skills[2] = SetSkill(entity_type, 2);
			skills[3] = SetSkill(entity_type, 3);
		}
		else if (app->frontground->adventure_phase == 2)
		{
			max_health = 180;
			actual_health = max_health;
			max_mana = 110;
			actual_mana = max_mana;
			this->speed = 55;
			this->power = 92;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 4);
			skills[1] = SetSkill(entity_type, 5);
			skills[2] = SetSkill(entity_type, 6);
			skills[3] = SetSkill(entity_type, 7);
		}
		else if (app->frontground->adventure_phase == 3)
		{
			max_health = 220;
			actual_health = max_health;
			max_mana = 150;
			actual_mana = max_mana;
			this->speed = 65;
			this->power = 105;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 8);
			skills[1] = SetSkill(entity_type, 9);
			skills[2] = SetSkill(entity_type, 6);
			skills[3] = SetSkill(entity_type, 7);
		}
		
		break;
	case ENEMIES::MUSHROOM:
		weak_to = 1;
		alive = 1;
		entity_type = 5;

		if (app->frontground->adventure_phase == 0)
		{
			max_health = 90;
			actual_health = max_health;
			max_mana = 80;
			actual_mana = max_mana;
			this->speed = 40;
			this->power = 45;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 0);
			skills[1] = SetSkill(entity_type, 1);
			skills[2] = SetSkill(entity_type, 2);
			skills[3] = SetSkill(entity_type, 3);
		}
		else if (app->frontground->adventure_phase == 1)
		{
			max_health = 125;
			actual_health = max_health;
			max_mana = 120;
			actual_mana = max_mana;
			this->speed = 60;
			this->power = 60;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 4);
			skills[1] = SetSkill(entity_type, 5);
			skills[2] = SetSkill(entity_type, 2);
			skills[3] = SetSkill(entity_type, 3);
		}
		else if (app->frontground->adventure_phase == 2)
		{
			max_health = 160;
			actual_health = max_health;
			max_mana = 160;
			actual_mana = max_mana;
			this->speed = 75;
			this->power = 80;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 4);
			skills[1] = SetSkill(entity_type, 5);
			skills[2] = SetSkill(entity_type, 6);
			skills[3] = SetSkill(entity_type, 7);
		}
		else if (app->frontground->adventure_phase == 3)
		{
			max_health = 190;
			actual_health = max_health;
			max_mana = 200;
			actual_mana = max_mana;
			this->speed = 80;
			this->power = 85;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 8);
			skills[1] = SetSkill(entity_type, 9);
			skills[2] = SetSkill(entity_type, 6);
			skills[3] = SetSkill(entity_type, 7);
		}

		break;
	case ENEMIES::GOBLIN:
		weak_to = 2;
		alive = 1;
		entity_type = 6;

		if (app->frontground->adventure_phase == 0)
		{
			max_health = 50;
			actual_health = max_health;
			max_mana = 50;
			actual_mana = max_mana;
			this->speed = 60;
			this->power = 70;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 0);
			skills[1] = SetSkill(entity_type, 1);
			skills[2] = SetSkill(entity_type, 2);
			skills[3] = SetSkill(entity_type, 3);
		}
		else if (app->frontground->adventure_phase == 1)
		{
			max_health = 75;
			actual_health = max_health;
			max_mana = 75;
			actual_mana = max_mana;
			this->speed = 70;
			this->power = 90;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 4);
			skills[1] = SetSkill(entity_type, 5);
			skills[2] = SetSkill(entity_type, 2);
			skills[3] = SetSkill(entity_type, 3);
		}
		else if (app->frontground->adventure_phase == 2)
		{
			max_health = 100;
			actual_health = max_health;
			max_mana = 95;
			actual_mana = max_mana;
			this->speed = 85;
			this->power = 90;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 4);
			skills[1] = SetSkill(entity_type, 5);
			skills[2] = SetSkill(entity_type, 6);
			skills[3] = SetSkill(entity_type, 7);
		}
		else if (app->frontground->adventure_phase == 3)
		{
			max_health = 110;
			actual_health = max_health;
			max_mana = 100;
			actual_mana = max_mana;
			this->speed = 100;
			this->power = 110;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 8);
			skills[1] = SetSkill(entity_type, 9);
			skills[2] = SetSkill(entity_type, 6);
			skills[3] = SetSkill(entity_type, 7);
		}
		
		break;
	case ENEMIES::SKELETON:
		weak_to = -1;
		alive = 1;
		entity_type = 7;

		if (app->frontground->adventure_phase == 0)
		{
			max_health = 120;
			actual_health = max_health;
			max_mana = 30;
			actual_mana = max_mana;
			this->speed = 35;
			this->power = 60;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 0);
			skills[1] = SetSkill(entity_type, 1);
			skills[2] = SetSkill(entity_type, 2);
			skills[3] = SetSkill(entity_type, 3);
		}
		else if (app->frontground->adventure_phase == 1)
		{
			max_health = 160;
			actual_health = max_health;
			max_mana = 45;
			actual_mana = max_mana;
			this->speed = 40;
			this->power = 68;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 4);
			skills[1] = SetSkill(entity_type, 5);
			skills[2] = SetSkill(entity_type, 2);
			skills[3] = SetSkill(entity_type, 3);
		}
		else if (app->frontground->adventure_phase == 2)
		{
			max_health = 200;
			actual_health = max_health;
			max_mana = 55;
			actual_mana = max_mana;
			this->speed = 45;
			this->power = 78;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 4);
			skills[1] = SetSkill(entity_type, 5);
			skills[2] = SetSkill(entity_type, 6);
			skills[3] = SetSkill(entity_type, 7);
		}
		else if (app->frontground->adventure_phase == 3)
		{
			max_health = 250;
			actual_health = max_health;
			max_mana = 60;
			actual_mana = max_mana;
			this->speed = 50;
			this->power = 85;
			shield = 0;
			shield_turns = 0;

			skills[0] = SetSkill(entity_type, 8);
			skills[1] = SetSkill(entity_type, 9);
			skills[2] = SetSkill(entity_type, 6);
			skills[3] = SetSkill(entity_type, 7);
		}

		break;
	case ENEMIES::R_TEMPLAR:
		weak_to = -1;
		alive = 1;
		entity_type = 8;

		max_health = 200;
		actual_health = max_health;
		max_mana = 80;
		actual_mana = max_mana;
		this->speed = 55;
		this->power = 80;
		shield = 0;
		shield_turns = 0;

		skills[0] = SetSkill(entity_type, 0);
		skills[1] = SetSkill(entity_type, 1);
		skills[2] = SetSkill(entity_type, 2);
		skills[3] = SetSkill(entity_type, 3);

		break;
	case ENEMIES::DRAGON:
		weak_to = 3;
		alive = 1;
		entity_type = 9;

		max_health = 800;
		actual_health = max_health;
		max_mana = 600;
		actual_mana = max_mana;
		this->speed = 80;
		this->power = 100;
		shield = 0;
		shield_turns = 0;

		skills[0] = SetSkill(entity_type, 0);
		skills[1] = SetSkill(entity_type, 1);
		skills[2] = SetSkill(entity_type, 2);
		skills[3] = SetSkill(entity_type, 3);

		break;
	case ENEMIES::THESEION:
		weak_to = 0;
		alive = 1;
		entity_type = 10;

		max_health = 700;
		actual_health = max_health;
		max_mana = 150;
		actual_mana = max_mana;
		this->speed = 62;
		this->power = 85;
		shield = 0;
		shield_turns = 0;

		skills[0] = SetSkill(entity_type, 0);
		skills[1] = SetSkill(entity_type, 1);
		skills[2] = SetSkill(entity_type, 2);
		skills[3] = SetSkill(entity_type, 3);

		break;
	case ENEMIES::NECRO_THESEION:
		weak_to = -1;
		alive = 1;
		entity_type = 11;

		max_health = 700;
		actual_health = max_health;
		max_mana = 150;
		actual_mana = max_mana;
		this->speed = 62;
		this->power = 85;
		shield = 0;
		shield_turns = 0;

		skills[0] = SetSkill(entity_type, 0);
		skills[1] = SetSkill(entity_type, 1);
		skills[2] = SetSkill(entity_type, 2);
		skills[3] = SetSkill(entity_type, 3);

		break;
	case ENEMIES::A_TEMPLAR:
		weak_to = -1;
		alive = 1;
		entity_type = 12;

		max_health = 400;
		actual_health = max_health;
		max_mana = 50;
		actual_mana = max_mana;
		this->speed = 10;
		this->power = 90;
		shield = 200;
		shield_turns = 10;

		skills[0] = SetSkill(entity_type, 0);
		skills[1] = SetSkill(entity_type, 1);
		skills[2] = SetSkill(entity_type, 2);
		skills[3] = SetSkill(entity_type, 3);

		break;
	}
}

Combat_Entities::Combat_Entities()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node items_stored = saveGame.child("heroes_stats").child("items_stored").child("equiped");

	skills[0] = SetSkill(-1, items_stored.attribute("item0").as_int()); // read from xml
	skills[1] = SetSkill(-1, items_stored.attribute("item1").as_int()); // read from xml
	skills[2] = SetSkill(-1, items_stored.attribute("item2").as_int()); // read from xml
	skills[3] = SetSkill(-1, items_stored.attribute("item3").as_int()); // read from xml
}

Combat_Entities::Combat_Entities(int owner, int set)
{
	skills[0] = SetSkill(owner, set * 4);
	skills[1] = SetSkill(owner, 1 + set * 4);
	skills[2] = SetSkill(owner, 2 + set * 4);
	skills[3] = SetSkill(owner, 3 + set * 4);
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
		if (bonus == SKILL_BONUS::NOTHING || bonus == SKILL_BONUS::IGNORE_SHIELD || bonus == SKILL_BONUS::DESTROY_SHIELD)
		{
			actual_health -= amount;
		}
		else if (bonus == SKILL_BONUS::CRITICAL)
		{
			if (actual_health <= max_health / 2)
			{
				actual_health -= amount * 2;
			}
			else
			{
				actual_health -= amount * 0.5;
			}
		}
	}

	if (actual_health <= 0)
	{
		actual_health = 0;
		prepared_to_die = true;
		app->particles->AddParticle(app->particles->blood_smoke, position.x - 32, position.y - 35);

		if (entity_type == 10)
		{
			app->menu->theseion2 = true;
		}
	}

	if (shield <= 0)
	{
		shield_turns = 0;
	}

	return true;
}

void Combat_Entities::ReloadMana(int amount)
{
	if (amount == -1)
	{
		actual_mana += max_mana / 2;
	}
	else if (amount == -2)
	{
		actual_mana += max_mana;
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

	int r;

	if (entity_type == 9)
	{
		r = rand() % 10;
		if (type == DEBUFF_TYPE::BURN)
		{
			return;
		}
		else if (type == DEBUFF_TYPE::STUN && r > 4)
		{
			return;
		}
	}
	else if (entity_type == 11)
	{
		if (type == DEBUFF_TYPE::STUN)
		{
			return;
		}
	}

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
		case -1:
			skill.owner = owner;
			skill.skill_name = "NONE";
			skill.mana_cost = 999;
			break;
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
		case 4:
			skill.owner = owner;
			skill.skill_name = "Green Leaves";
			skill.skill_description0 = "All allies obtain relax for 5 turns.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 0;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::RELAX;
			skill.buff_turns = 5;
			break;
		case 5:
			skill.owner = owner;
			skill.skill_name = "Recarm";
			skill.skill_description0 = "Revive an ally.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 0;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.support_type = SUPPORT_TYPE::REVIVE;
			break;
		case 6:
			skill.owner = owner;
			skill.skill_name = "Rainbow Grace";
			skill.skill_description0 = "All allies obtain damage inmunity for 2 turns.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 0;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::DAMAGE_INMUNITY;
			skill.buff_turns = 2;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Anti-Shield";
			skill.skill_description0 = "Destroy the shield form one enemy.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 0;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.skill_bonus = SKILL_BONUS::DESTROY_SHIELD;
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
			skill.skill_name = "Thrust";
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
			skill.skill_description0 = "The user boost his speed for two turn.";
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
			skill.skill_description0 = "Low damage to a single target. The user boost his";
			skill.skill_description1 = "speed for two turn.";
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
			skill.skill_description0 = "Medium damage to all targets.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 30;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Dodge";
			skill.skill_description0 = "The user obtain dodge for one turn.";
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
			skill.skill_description0 = "The user boost his power for two turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 2;
			break;
		case 9: // level 3 up root skills
			skill.owner = owner;
			skill.skill_name = "Piercing Thrust";
			skill.skill_description0 = "Medium damage to a single target, this tactical";
			skill.skill_description1 = "attack ignores the enemy shield.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.skill_bonus = SKILL_BONUS::IGNORE_SHIELD;
			break;
		case 10:
			skill.owner = owner;
			skill.skill_name = "Tactic Thrust";
			skill.skill_description0 = "Medium critical damage to a single target. Critical";
			skill.skill_description1 = "damage hits more when the target is with low";
			skill.skill_description2 = "health or hits less if the target is with high health";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 25;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.skill_bonus = SKILL_BONUS::CRITICAL;
			break;
		case 11:
			skill.owner = owner;
			skill.skill_name = "Great Fire Bomb";
			skill.skill_description0 = "Medium fire damage to all targets and set them on";
			skill.skill_description1 = "fire for 3 turns.";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 1;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 3;
			break;
		case 12:
			skill.owner = owner;
			skill.skill_name = "Spike Trap";
			skill.skill_description0 = "Low damage to all targets and reduce targets speed";
			skill.skill_description1 = "for 2 turns.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_QUICK;
			skill.buff_turns = 2;
			break;
		case 13: // level 3 down root skills
			skill.owner = owner;
			skill.skill_name = "Stealth+";
			skill.skill_description0 = "The user obtain stealth for two turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STEALTH;
			skill.buff_turns = 2;
			break;
		case 14:
			skill.owner = owner;
			skill.skill_name = "Ghost";
			skill.skill_description0 = "The user become inmune to damage for one turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 30;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::DAMAGE_INMUNITY;
			skill.buff_turns = 1;
			break;
		case 15:
			skill.owner = owner;
			skill.skill_name = "Exausting Bomb";
			skill.skill_description0 = "Low damage to all targets and reduce targets";
			skill.skill_description1 = "power for 2 turns.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_STRONG;
			skill.buff_turns = 2;
			break;
		case 16:
			skill.owner = owner;
			skill.skill_name = "Thunder Thrust";
			skill.skill_description0 = "Medium lightning damage to a single target.";
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
			skill.skill_name = "Encourage";
			skill.skill_description0 = "Boosts the target power for two turns.";
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
			skill.skill_description0 = "Give an ally a good shield during one turn.";
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
			skill.skill_description0 = "Heal a small amount of health to all allies.";
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
			skill.skill_description0 = "Remove all buffs of the target.";
			skill.att_effect = ATT_EFFECT::ANTI_HEAL;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.support_type = SUPPORT_TYPE::CLEAN_BUFFS;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Speed Boost";
			skill.skill_description0 = "Boosts the target speed for two turns.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::QUICK;
			skill.buff_turns = 2;
			break;
		case 9: // level 3 up root skills
			skill.owner = owner;
			skill.skill_name = "Inmortal Peach";
			skill.skill_description0 = "Offer to the target the inmortal peach of";
			skill.skill_description1 = "Wukong. Give damage inmunity to an ally for";
			skill.skill_description1 = "two turns.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 120;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::DAMAGE_INMUNITY;
			skill.buff_turns = 2;
			break;
		case 10:
			skill.owner = owner;
			skill.skill_name = "Field Shield";
			skill.skill_description0 = "Give to all allies a small shield during one turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 40;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 11:
			skill.owner = owner;
			skill.skill_name = "Great Heal";
			skill.skill_description0 = "Heal a good amount of health to an ally.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 34;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 12:
			skill.owner = owner;
			skill.skill_name = "Relax";
			skill.skill_description0 = "All allies obtain relax for 3 turns.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 100;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::RELAX;
			skill.buff_turns = 3;
			break;
		case 13: // level 3 down root skills
			skill.owner = owner;
			skill.skill_name = "Field Clean";
			skill.skill_description0 = "Clean all the debuffs from all allies.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 40;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.support_type = SUPPORT_TYPE::CLEAN_DEBUFFS;
			break;
		case 14:
			skill.owner = owner;
			skill.skill_name = "Field Cancel";
			skill.skill_description0 = "Remove all buffs of all targets.";
			skill.att_effect = ATT_EFFECT::ANTI_HEAL;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.support_type = SUPPORT_TYPE::CLEAN_BUFFS;
			break;
		case 15:
			skill.owner = owner;
			skill.skill_name = "Field Encourage";
			skill.skill_description0 = "Boosts all targets power for two turns.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 60;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 2;
			break;
		case 16:
			skill.owner = owner;
			skill.skill_name = "Mana Source";
			skill.skill_description0 = "Use a huge amount of mana to invoke the mana";
			skill.skill_description1 = "spirit. All allies recover a good amount of mana.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 200;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
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
			skill.skill_name = "Strike";
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
			skill.skill_name = "Piercing Slash";
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
			skill.skill_name = "Shell";
			skill.skill_description0 = "The user obtain a small shield during one turn.";
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
			skill.skill_description0 = "Low damage to a single target. The user obtain a";
			skill.skill_description1 = "small shield during one turn.";
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
			skill.skill_name = "Shielding Taunt";
			skill.skill_description0 = "Provoke all enemies, obtain taunt for one turn. The";
			skill.skill_description1 = "user obtain a small shield during one turn.";
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
			skill.skill_name = "Piercing Strike";
			skill.skill_description0 = "Medium damage to a single target, this tactical";
			skill.skill_description1 = "attack ignores the enemy shield.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 25;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.skill_bonus = SKILL_BONUS::IGNORE_SHIELD;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Great Shell";
			skill.skill_description0 = "The user obtain a good shield during one turn.";
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
			skill.skill_name = "Defense Strike";
			skill.skill_description0 = "Medium damage to a single target. The user obtain a";
			skill.skill_description1 = "small shield during one turn.";
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
			skill.skill_name = "Spinning";
			skill.skill_description0 = "Low damage to all targets.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 30;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 11:
			skill.owner = owner;
			skill.skill_name = "Taunt+";
			skill.skill_description0 = "Provoke all enemies, obtain taunt for two turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 2;
			break;
		case 12:
			skill.owner = owner;
			skill.skill_name = "Statue";
			skill.skill_description0 = "The user obtain the resistance of a mountain";
			skill.skill_description1 = "Provoke all enemies, obtain taunt for two turn.";
			skill.skill_description2 = "The user obtain a good shield during two turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 50;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 2;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 2;
			break;
		case 13: // level 3 down root skills
			skill.owner = owner;
			skill.skill_name = "Atlas Slash";
			skill.skill_description0 = "Uses the strenght of Atlas, the titan attack";
			skill.skill_description1 = "destroy the enemy shield.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.skill_bonus = SKILL_BONUS::DESTROY_SHIELD;
			break;
		case 14:
			skill.owner = owner;
			skill.skill_name = "Pierce Spinning";
			skill.skill_description0 = "Low damage to all targets, this tactical attack";
			skill.skill_description1 = "ignores the enemy shield.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.skill_bonus = SKILL_BONUS::IGNORE_SHIELD;
			break;
		case 15:
			skill.owner = owner;
			skill.skill_name = "Great Shell+";
			skill.skill_description0 = "The user obtain a good shield during two turn.";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 25;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 2;
			break;
		case 16:
			skill.owner = owner;
			skill.skill_name = "Revive";
			skill.skill_description0 = "Revive an ally.";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 80;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
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
			skill.skill_description0 = "Low lightning damage to a single target.";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 2;
			skill.att_strenght = 0;
			break;
		case 5: // level 2 skills
			skill.owner = owner;
			skill.skill_name = "Armor Break";
			skill.skill_description0 = "Low damage to a single target. Break the armor of";
			skill.skill_description1 = "an enemy for 2 turns.";
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
			skill.skill_name = "Fire Orb";
			skill.skill_description0 = "Low fire damage to a single target and set him on";
			skill.skill_description1 = "fire for 2 turns.";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 2;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Water Canon";
			skill.skill_description0 = "Low water damage to a single target and reduce his";
			skill.skill_description1 = "speed for 2 turns.";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 3;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_QUICK;
			skill.buff_turns = 1;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Great Lightning";
			skill.skill_description0 = "Medium lightning damage to a single target.";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 2;
			skill.att_strenght = 1;
			break;
		case 9: // level 3 up root skills
			skill.owner = owner;
			skill.skill_name = "Compact Rock";
			skill.skill_description0 = "Lauch a small rock at high speed. Colosal damage to";
			skill.skill_description1 = "a single target.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 60;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 2;
			break;
		case 10:
			skill.owner = owner;
			skill.skill_name = "Giant Rock";
			skill.skill_description0 = "Medium damage to all targets.";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 11:
			skill.owner = owner;
			skill.skill_name = "Fire Circle";
			skill.skill_description0 = "Low fire damage to all targets and set them on fire";
			skill.skill_description1 = "for 2 turns.";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 30;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 2;
			break;
		case 12:
			skill.owner = owner;
			skill.skill_name = "Magma Orb";
			skill.skill_description0 = "Medium fire damage to a single target and set him";
			skill.skill_description1 = "on fire for 3 turns.";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 3;
			break;
		case 13: // level 3 down root skills
			skill.owner = owner;
			skill.skill_name = "Water Splash";
			skill.skill_description0 = "Low water damage to all targets.";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 10;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 3;
			skill.att_strenght = 0;
			break;
		case 14:
			skill.owner = owner;
			skill.skill_name = "Aquarius";
			skill.skill_description0 = "Invoke Aquarius, whose attack causes low water";
			skill.skill_description1 = "damage to all targets and reduce targets speed";
			skill.skill_description2 = "for two turns.";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 3;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_QUICK;
			skill.buff_turns = 2;
			break;
		case 15:
			skill.owner = owner;
			skill.skill_name = "Paralyzing Bolt";
			skill.skill_description0 = "Stun the target for one turn.";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 60;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 2;
			skill.debuff_type = DEBUFF_TYPE::STUN;
			skill.buff_turns = 1;
			break;
		case 16:
			skill.owner = owner;
			skill.skill_name = "Thunder Rain";
			skill.skill_description0 = "Medium lightning damage to all targets.";
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
			skill.skill_name = "Block"; // Bloqueo de escudo (puede bloquear y evitar un ataque a sus compañeros)
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 1;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Templar Scream"; // +5 de daño en todos SUS ataques
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 1;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Fire Edge"; // Daño medio con fuego
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			break;
		case 4:
			skill.owner = owner;
			skill.skill_name = "Double Lunge";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 5:
			skill.owner = owner;
			skill.skill_name = "Defensive Block";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 1;
			break;
		case 6:
			skill.owner = owner;
			skill.skill_name = "Templar Praise";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 30;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 2;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Break";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 30;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			skill.buff_turns = 2;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Tecnical Lunge";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.skill_bonus = SKILL_BONUS::CRITICAL;
			break;
		case 9:
			skill.owner = owner;
			skill.skill_name = "Save Zone";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 70;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::DODGE;
			skill.buff_turns = 2;
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
			skill.skill_name = "Heart Thief"; // Roba +5 de vida a los PROTAGONISTAS y se los pone a los ENEMIGOS
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 25;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
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
		case 4:
			skill.owner = owner;
			skill.skill_name = "Charge";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 5:
			skill.owner = owner;
			skill.skill_name = "Great Heal";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 30;
			skill.ally_objective = ALLY_OBJECTIVE::ONE_ALLY;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 6:
			skill.owner = owner;
			skill.skill_name = "Heart Breaker"; // Roba +5 de vida a los PROTAGONISTAS y se los pone a los ENEMIGOS
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Splash Bubble";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 25;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 3;
			skill.att_strenght = 1;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Dehydrate";
			skill.att_effect = ATT_EFFECT::WATER;
			skill.mana_cost = 60;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::ANTI_QUICK;
			skill.buff_turns = 2;
			break;
		case 9:
			skill.owner = owner;
			skill.skill_name = "Power of Nature";
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 100;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::RELAX;
			skill.buff_turns = 2;
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
			skill.skill_name = "Circle";
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
		case 4:
			skill.owner = owner;
			skill.skill_name = "Money Spoted";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 2;
			break;
		case 5:
			skill.owner = owner;
			skill.skill_name = "Fast Circle";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.buff_type = BUFF_TYPE::QUICK;
			skill.buff_turns = 1;
			break;
		case 6:
			skill.owner = owner;
			skill.skill_name = "Savage Reap";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 50;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 2;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Break Scratch";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 35;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			skill.buff_turns = 2;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Great Circle";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 40;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 9:
			skill.owner = owner;
			skill.skill_name = "Trick";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 35;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_STRONG;
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
			skill.supp_effect = SUPP_EFFECT::BUFF;
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
			skill.mana_cost = 12;
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
		case 4:
			skill.owner = owner;
			skill.skill_name = "Silence+";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 15;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::STEALTH;
			skill.buff_turns = 3;
			break;
		case 5:
			skill.owner = owner;
			skill.skill_name = "Barrier";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 30;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.supp_strenght = 0;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 1;
			break;
		case 6:
			skill.owner = owner;
			skill.skill_name = "Blood Drain";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 18;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::HEAL;
			break;
		case 7:
			skill.owner = owner;
			skill.skill_name = "Strike";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 12;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 8:
			skill.owner = owner;
			skill.skill_name = "Oppression of the undead";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 60;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 2;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 3;
			skill.buff_type = BUFF_TYPE::TAUNT;
			skill.buff_turns = 3;
			break;
		case 9:
			skill.owner = owner;
			skill.skill_name = "Collision";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 22;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
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
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "Recovery";	
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 2;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 2;
			skill.debuff_type = DEBUFF_TYPE::STUN;
			skill.buff_turns = 1;
			skill.zero_mana = true;
			break;
		}
	}
	else if (owner == 9) // DRAGON
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Bite";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.mana_cost = 150;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.supp_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::ANTI_STRONG;
			skill.buff_turns = 2;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Hell flame";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 150;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 1;
			skill.att_strenght = 0;
			skill.debuff_type = DEBUFF_TYPE::BURN;
			skill.buff_turns = 10;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Earthquake";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 150;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::ANTI_QUICK;
			skill.buff_turns = 2;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "FLAME OF CALAMITY";
			skill.att_effect = ATT_EFFECT::FIRE;
			skill.mana_cost = 2;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 1;
			skill.att_strenght = 3;
			skill.zero_mana = true;
			break;
		}
	}
	else if (owner == 10) // THESEION
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "For the law weight";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.mana_cost = 30;
			skill.element = 0;
			skill.att_strenght = 0;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Praise me";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 60;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::RELAX;
			skill.buff_turns = 3;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "You fools";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 35;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.debuff_type = DEBUFF_TYPE::ANTI_STRONG;
			skill.buff_turns = 2;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "I am the ruler";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 40;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::QUICK;
			skill.buff_turns = 3;
			break;
		}
	}
	else if (owner == 11) // THESEION, THE NECROMANCER
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Law of the death";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.mana_cost = 30;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			skill.buff_turns = 2;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Praise the undeads";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 60;
			skill.ally_objective = ALLY_OBJECTIVE::ALL_ALLY;
			skill.element = 0;
			skill.buff_type = BUFF_TYPE::DODGE;
			skill.buff_turns = 3;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Fool ambitions to rest";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 35;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::STUN;
			skill.buff_turns = 1;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "I will rule for ever";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::HEAL;
			skill.mana_cost = 2;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.att_strenght = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::HEAL;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 3;
			skill.zero_mana = true;
			break;
		}
	}
	else if (owner == 12) // Armored Templar (ENEMY)
	{
		switch (skill_number)
		{
		case 0:
			skill.owner = owner;
			skill.skill_name = "Axe Blow";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 20;
			skill.enemy_objective = ENEMY_OBJECTIVE::ONE_ENEMY;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.att_strenght = 2;
			skill.buff_type = BUFF_TYPE::STRONG;
			skill.buff_turns = 2;
			break;
		case 1:
			skill.owner = owner;
			skill.skill_name = "Heavy shield";
			skill.supp_effect = SUPP_EFFECT::BUFF;
			skill.mana_cost = 25;
			skill.ally_objective = ALLY_OBJECTIVE::SELF;
			skill.element = 0;
			skill.supp_strenght = 1;
			skill.support_type = SUPPORT_TYPE::SHIELD;
			skill.shield_turns = 5;
			skill.buff_type = BUFF_TYPE::DEBUFF_INMUNITY;
			skill.buff_turns = 5;
			break;
		case 2:
			skill.owner = owner;
			skill.skill_name = "Spin to win";
			skill.att_effect = ATT_EFFECT::PHYSIC;
			skill.mana_cost = 15;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 0;
			skill.att_strenght = 1;
			break;
		case 3:
			skill.owner = owner;
			skill.skill_name = "For Theseion!!!";
			skill.att_effect = ATT_EFFECT::LIGHTNING;
			skill.mana_cost = 2;
			skill.enemy_objective = ENEMY_OBJECTIVE::ALL_ENEMY;
			skill.element = 2;
			skill.att_strenght = 1;
			skill.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			skill.buff_turns = 2;
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

			if (item->data.buff_type == BUFF_TYPE::QUICK || item->data.buff_type == BUFF_TYPE::STRONG)
			{
				if (item->data.turns > 1)
				{
					app->render->DrawRectangle({ cx + (32 * i) + 1, cy + 1, 30, 30 }, 104, 193, 4, 200);
					app->render->DrawTexture(app->combat_manager->status_effects, cx + (32 * i), cy, &rect);
					i++;
				}
			}
			else
			{
				app->render->DrawRectangle({ cx + (32 * i) + 1, cy + 1, 30, 30 }, 104, 193, 4, 200);
				app->render->DrawTexture(app->combat_manager->status_effects, cx + (32 * i), cy, &rect);
				i++;
			}
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

			if (item->data.debuff_type == DEBUFF_TYPE::STUN || item->data.debuff_type == DEBUFF_TYPE::ANTI_QUICK || item->data.debuff_type == DEBUFF_TYPE::ANTI_STRONG)
			{
				if (item->data.turns > 1)
				{
					app->render->DrawRectangle({ cx + (32 * i) + 1, cy + 1, 30, 30 }, 193, 56, 4, 200);
					app->render->DrawTexture(app->combat_manager->status_effects, cx + (32 * i), cy, &rect);
					i++;
				}
			}
			else
			{
				app->render->DrawRectangle({ cx + (32 * i) + 1, cy + 1, 30, 30 }, 193, 56, 4, 200);
				app->render->DrawTexture(app->combat_manager->status_effects, cx + (32 * i), cy, &rect);
				i++;
			}
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
				description0 = "Stealth, makes the enemy unable to target the";
				description1 = "user with single target skills.";
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
				description0 = "Taunt, the user provoke enemies. Enemies single";
				description1 = "target attacks will hit the user.";
				break;
			case BUFF_TYPE::QUICK:
				rect = { 96, 64, 32, 32 };
				description0 = "Quick, increases by 100% the user speed.";
				description1 = "";
				break;
			case BUFF_TYPE::STRONG:
				rect = { 32, 96, 32, 32 };
				description0 = "Strong, increases by 50% times the user power.";
				description1 = "";
				break;
			case BUFF_TYPE::RELAX:
				rect = { 32, 32, 32, 32 };
				description0 = "Relax, each turn the user will be healed by a";
				description1 = "25% of this max health.";
				break;
			case BUFF_TYPE::GODMODE_STRONG:
				rect = { 64, 96, 32, 32 };
				description0 = "Grace of the Gods, increases by 500% times the user";
				description1 = "power. Only the real gods can use it.";
				break;
			default:
				break;
			}

			if (item->data.buff_type == BUFF_TYPE::QUICK || item->data.buff_type == BUFF_TYPE::STRONG)
			{
				if (item->data.turns > 1)
				{
					app->fonts->BlitCombatText(cx - 32, cy + ((64 + 25) * i), app->fonts->textFont2, std::to_string(item->data.turns - 1).c_str());
					app->render->DrawRectangle({ cx + 1, cy + ((64 + 25) * i) + 1, 30, 30 }, 104, 193, 4, 200);
					app->render->DrawTexture(app->combat_manager->status_effects, cx, cy + ((64 + 25) * i), &rect);
					res = description0.c_str();
					app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i), app->fonts->textFont2, res);
					res = description1.c_str();
					app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i) + 34, app->fonts->textFont2, res);
					i++;
				}
			}
			else
			{
				app->fonts->BlitCombatText(cx - 32, cy + ((64 + 25) * i), app->fonts->textFont2, std::to_string(item->data.turns).c_str());
				app->render->DrawRectangle({ cx + 1, cy + ((64 + 25) * i) + 1, 30, 30 }, 104, 193, 4, 200);
				app->render->DrawTexture(app->combat_manager->status_effects, cx, cy + ((64 + 25) * i), &rect);
				res = description0.c_str();
				app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i), app->fonts->textFont2, res);
				res = description1.c_str();
				app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i) + 34, app->fonts->textFont2, res);
				i++;
			}
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

			if (item->data.debuff_type == DEBUFF_TYPE::STUN || item->data.debuff_type == DEBUFF_TYPE::ANTI_QUICK || item->data.debuff_type == DEBUFF_TYPE::ANTI_STRONG)
			{
				if (item->data.turns > 1)
				{
					app->fonts->BlitCombatText(cx - 32, cy + ((64 + 25) * i), app->fonts->textFont2, std::to_string(item->data.turns - 1).c_str());
					app->render->DrawRectangle({ cx + 1, cy + ((64 + 25) * i) + 1, 30, 30 }, 193, 56, 4, 200);
					app->render->DrawTexture(app->combat_manager->status_effects, cx, cy + ((64 + 25) * i), &rect);
					res = description0.c_str();
					app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i), app->fonts->textFont2, res);
					res = description1.c_str();
					app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i) + 34, app->fonts->textFont2, res);
					i++;
				}
			}
			else
			{
				app->fonts->BlitCombatText(cx - 32, cy + ((64 + 25) * i), app->fonts->textFont2, std::to_string(item->data.turns).c_str());
				app->render->DrawRectangle({ cx + 1, cy + ((64 + 25) * i) + 1, 30, 30 }, 193, 56, 4, 200);
				app->render->DrawTexture(app->combat_manager->status_effects, cx, cy + ((64 + 25) * i), &rect);
				res = description0.c_str();
				app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i), app->fonts->textFont2, res);
				res = description1.c_str();
				app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i) + 34, app->fonts->textFont2, res);
				i++;
			}
		}
	}
}