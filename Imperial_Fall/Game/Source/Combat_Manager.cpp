#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "Frontground.h"
#include "Combat_Manager.h"
#include "Combat_Menu.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"
#include "Fonts.h"

#include <stdlib.h>
#include <time.h>

Combat_Manager::Combat_Manager() : Module()
{
	name.Create("combat_manager");
}

// Destructor
Combat_Manager::~Combat_Manager()
{}

// Called before render is available
bool Combat_Manager::Awake()
{


	return true;
}

// Called before the first frame
bool Combat_Manager::Start()
{

	return true;
}

// Called each loop iteration
bool Combat_Manager::PreUpdate()
{
	if (app->frontground->GetCombatState() == 2)
	{
		in_combat = true;
	}
	else if (app->frontground->GetCombatState() == 0)
	{
		in_combat = false;
		combat_init = false;
	}

	if (in_combat && !app->menu->GetGameState())
	{
		if (!combat_init)
		{
			//init allies
			allies[0] = new Combat_Entities(70, 50, 50, 65, 0); // assassin
			allies[1] = new Combat_Entities(100, 60, 30, 50, 1); // healer
			allies[2] = new Combat_Entities(140, 50, 10, 50, 2); // tank
			allies[3] = new Combat_Entities(85, 70, 35, 60, 3); // wizard

			//init enemies
			for (size_t i = 0; i < 4; i++)
			{
				enemies[i] = new Combat_Entities(app->frontground->GetEnemiesToFight(i));
			}

			//set turn order
			SetOrder();
			turn = -1;
			pass_turn = true;
		}
		else
		{
			if (CheckCombatState() == 0)
			{
				if (pass_turn)
				{
					srand(time(NULL));
					do
					{
						turn++;
						if (turn >= sizeof(turn_order) / sizeof(turn_order[0]))
						{
							turn = 0;
						}
					} while (!turn_order[turn]->GetEntityState());
					UpdateBuffs();
					pass_turn = false;
				}
			}
			else if (CheckCombatState() == 1)
			{
				if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && app->frontground->GetCombatState())
				{
					app->frontground->ReturnToField();
				}
			}
			else if (CheckCombatState() == 2)
			{
				if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && app->frontground->GetCombatState()) // EXIT BATTLE
				{
					app->frontground->ReturnToField();
				}
				else if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN && app->frontground->GetCombatState()) // RESTART BATTLE
				{
					// RESTART BATTLE
				}
			}
			
		}
	}

	return true;
}

// Called each loop iteration
bool Combat_Manager::Update(float dt)
{
	if (in_combat && !pass_turn && !in_animation)
	{
		if (turn_order[turn]->GetType() == 0 || turn_order[turn]->GetType() == 1 || turn_order[turn]->GetType() == 2 || turn_order[turn]->GetType() == 3) // allies
		{
			app->combat_menu->SetAlliesTurn(true);
		}
		else // enemies
		{
			// AI
			EnemyTurn(turn_order[turn]);
		}
	}

	if (in_animation == 2)
	{
		animation_cd += dt;
		if (animation_cd >= 60 * dt)
		{
			pass_turn = true;
			app->combat_menu->SetAlliesTurn(false);

			in_animation = 0;
			animation_cd = 0;
		}
	}
	

	return true;
}

// Called each loop iteration
bool Combat_Manager::PostUpdate()
{
	if (in_combat)
	{
		if (!combat_init)
		{
			combat_init = true;
		}
		else
		{
			if (app->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN)
			{
				LOG("ally1 h:%d and m:%d, ally2 h:%d and m:%d, ally3 h:%d and m:%d, ally4 h:%d and m:%d, enemy1 h:%d and m:%d, enemy2 h:%d and m:%d, enemy3 h:%d and m:%d, enemy4 h:%d and m:%d",
					allies[0]->GetActualHealth(), allies[0]->GetActualMana(), allies[1]->GetActualHealth(), allies[1]->GetActualMana(),
					allies[2]->GetActualHealth(), allies[2]->GetActualMana(), allies[3]->GetActualHealth(), allies[3]->GetActualMana(),
					enemies[0]->GetActualHealth(), enemies[0]->GetActualMana(), enemies[1]->GetActualHealth(), enemies[1]->GetActualMana(),
					enemies[2]->GetActualHealth(), enemies[2]->GetActualMana(), enemies[3]->GetActualHealth(), enemies[3]->GetActualMana());
			}
			UpdateHUD();
		}
	}

	return true;
}

// Called before quitting
bool Combat_Manager::CleanUp()
{

	return true;
}

void Combat_Manager::SetOrder()
{
	Combat_Entities* aux[8];
	aux[0] = allies[0];
	aux[1] = allies[1];
	aux[2] = allies[2];
	aux[3] = allies[3];
	aux[4] = enemies[0];
	aux[5] = enemies[1];
	aux[6] = enemies[2];
	aux[7] = enemies[3];

	int max = 0;
	int id;

	// order
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (aux[j]->GetSpeed() > max && !InArray(turn_order, i, aux[j]))
			{
				id = j;
				max = allies[j]->GetSpeed();
			}
		}
		turn_order[i] = aux[id];
		max = 0;
	}
}

bool Combat_Manager::InArray(Combat_Entities* array[], int length, Combat_Entities* check)
{
	for (size_t i = 0; i < length; i++)
	{
		if (array[i] == check)
		{
			return true;
		}
	}
	return false;
}

void Combat_Manager::UpdateHUD()
{
	int cx = -app->render->camera.x;
	int cy = -app->render->camera.y;

	// max health allies
	app->render->DrawRectangle({ 350 + cx - 200, 150 + cy, allies[0]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 250 + cx - 200, 250 + cy, allies[1]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 350 + cx - 200, 350 + cy, allies[2]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 250 + cx - 200, 450 + cy, allies[3]->GetMaxHealth(), 30 }, 70, 0, 0);
	// actual health allies
	app->render->DrawRectangle({ 351 + cx - 200, 151 + cy, allies[0]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 251 + cx - 200, 251 + cy, allies[1]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 351 + cx - 200, 351 + cy, allies[2]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 251 + cx - 200, 451 + cy, allies[3]->GetActualHealth(), 28 }, 255, 0, 0);

	// max mana allies
	app->render->DrawRectangle({ 350 + cx - 200, 150 + cy + 35, allies[0]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 250 + cx - 200, 250 + cy + 35, allies[1]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 350 + cx - 200, 350 + cy + 35, allies[2]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 250 + cx - 200, 450 + cy + 35, allies[3]->GetMaxMana(), 30 }, 0, 0, 70);

	// actual mana allies
	app->render->DrawRectangle({ 351 + cx - 200, 151 + cy + 35, allies[0]->GetActualMana(), 28}, 0, 0, 255);
	app->render->DrawRectangle({ 251 + cx - 200, 251 + cy + 35, allies[1]->GetActualMana(), 28 }, 0, 0, 255);
	app->render->DrawRectangle({ 351 + cx - 200, 351 + cy + 35, allies[2]->GetActualMana(), 28 }, 0, 0, 255);
	app->render->DrawRectangle({ 251 + cx - 200, 451 + cy + 35, allies[3]->GetActualMana(), 28 }, 0, 0, 255);

	// shield allies
	app->render->DrawRectangle({ 351 + cx - 200 + allies[0]->GetActualHealth(), 151 + cy, allies[0]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 251 + cx - 200 + allies[0]->GetActualHealth(), 251 + cy, allies[1]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 351 + cx - 200 + allies[0]->GetActualHealth(), 351 + cy, allies[2]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 251 + cx - 200 + allies[0]->GetActualHealth(), 451 + cy, allies[3]->GetShield(), 28 }, 120, 120, 120);

	// max health enemies
	app->render->DrawRectangle({ 866 + cx + 60, 150 + cy, enemies[0]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 966 + cx + 60, 250 + cy, enemies[1]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 866 + cx + 60, 350 + cy, enemies[2]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 966 + cx + 60, 450 + cy, enemies[3]->GetMaxHealth(), 30 }, 70, 0, 0);
	// actual health enemies
	app->render->DrawRectangle({ 867 + cx + 60, 151 + cy, enemies[0]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 967 + cx + 60, 251 + cy, enemies[1]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 867 + cx + 60, 351 + cy, enemies[2]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 967 + cx + 60, 451 + cy, enemies[3]->GetActualHealth(), 28 }, 255, 0, 0);

	// max mana enemies
	app->render->DrawRectangle({ 866 + cx + 60, 150 + cy + 35, enemies[0]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 966 + cx + 60, 250 + cy + 35, enemies[1]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 866 + cx + 60, 350 + cy + 35, enemies[2]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 966 + cx + 60, 450 + cy + 35, enemies[3]->GetMaxMana(), 30 }, 0, 0, 70);

	// actual mana enemies
	app->render->DrawRectangle({ 867 + cx + 60, 151 + cy + 35, enemies[0]->GetActualMana(), 28 }, 0, 0, 255);
	app->render->DrawRectangle({ 967 + cx + 60, 251 + cy + 35, enemies[1]->GetActualMana(), 28 }, 0, 0, 255);
	app->render->DrawRectangle({ 867 + cx + 60, 351 + cy + 35, enemies[2]->GetActualMana(), 28 }, 0, 0, 255);
	app->render->DrawRectangle({ 967 + cx + 60, 451 + cy + 35, enemies[3]->GetActualMana(), 28 }, 0, 0, 255);

	// shield enemies
	app->render->DrawRectangle({ 866 + cx + 60 + enemies[0]->GetActualHealth(), 151 + cy, enemies[0]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 966 + cx + 60 + enemies[0]->GetActualHealth(), 251 + cy, enemies[1]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 866 + cx + 60 + enemies[0]->GetActualHealth(), 351 + cy, enemies[2]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 966 + cx + 60 + enemies[0]->GetActualHealth(), 451 + cy, enemies[3]->GetShield(), 28 }, 120, 120, 120);
}

void Combat_Manager::UseSkill(Combat_Entities* user, Skill skill, Combat_Entities* objective)
{
	if (user->GetActualMana() < skill.mana_cost)
	{
		app->combat_menu->CancelAction();
	}
	else
	{
		user->ReloadMana(-skill.mana_cost);

		// power calculation
		int damage;
		int support;

		switch (skill.att_strenght)
		{
		case 0: damage = 0.2f * user->GetPower();
			break;
		case 1: damage = 0.4f * user->GetPower();
			break;
		case 2: damage = 0.6f * user->GetPower();
			break;
		}

		switch (skill.supp_strenght)
		{
		case 0: support = 0.2f * user->GetPower();
			break;
		case 1: support = 0.4f * user->GetPower();
			break;
		case 2: support = 0.6f * user->GetPower();
			break;
		}

		// lauch attack skill
		if (skill.enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
		{
			objective->DamageEntity(damage);
		}
		else if (skill.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
		{
			for (size_t i = 0; i < 4; i++)
			{
				enemies[i]->DamageEntity(damage);
			}
		}

		// lauch support skill
		if (skill.ally_objective == ALLY_OBJECTIVE::ONE_ALLY)
		{
			if (skill.support_type == SUPPORT_TYPE::SHIELD)
			{
				objective->ShieldEntity(support);
			}
			else if (skill.support_type == SUPPORT_TYPE::HEAL)
			{
				objective->HealEntity(support);
			}
			else if (skill.support_type == SUPPORT_TYPE::CLEAN)
			{
				objective->CleanEntity();
			}
			else if (skill.support_type == SUPPORT_TYPE::REVIVE)
			{
				// revive
			}
		}
		else if (skill.ally_objective == ALLY_OBJECTIVE::ALL_ALLY)
		{
			if (skill.support_type == SUPPORT_TYPE::SHIELD)
			{
				for (size_t i = 0; i < 4; i++)
				{
					allies[i]->ShieldEntity(support);
				}
			}
			else if (skill.support_type == SUPPORT_TYPE::HEAL)
			{
				for (size_t i = 0; i < 4; i++)
				{
					allies[i]->HealEntity(support);
				}
			}
			else if (skill.support_type == SUPPORT_TYPE::CLEAN)
			{
				for (size_t i = 0; i < 4; i++)
				{
					allies[i]->CleanEntity();
				}
			}
		}
		else if (skill.ally_objective == ALLY_OBJECTIVE::SELF)
		{
			if (skill.support_type == SUPPORT_TYPE::SHIELD)
			{
				user->ShieldEntity(support);
			}
			else if (skill.support_type == SUPPORT_TYPE::HEAL)
			{
				user->HealEntity(support);
			}
			else if (skill.support_type == SUPPORT_TYPE::CLEAN)
			{
				user->CleanEntity();
			}

			if (skill.buff_type == BUFF_TYPE::STEALTH)
			{
				user->AddBuff(skill.buff_type, skill.buff_turns);
			}
			else if (skill.buff_type == BUFF_TYPE::TAUNT)
			{
				user->AddBuff(skill.buff_type, skill.buff_turns);
			}
		}

		in_animation = 1;
	}
}

void Combat_Manager::UpdateBuffs()
{
	GetActualEntity()->UpdateBuffs();
}

void Combat_Manager::EnemyTurn(Combat_Entities* user)
{
	int r = rand() % 4;

	if (user->GetActualMana() < user->GetSkill(0).mana_cost)
	{
		user->ReloadMana();
		Skill reload;
		reload.skill_name = "reload";
		app->combat_menu->SetSkillPrepared(reload);
		SetInAnimation(1);
	}
	else
	{
		app->combat_menu->SetSkillPrepared(user->GetSkill(0));
		UseSkill(user, user->GetSkill(0), allies[r]);
	}
}

int Combat_Manager::CheckCombatState()
{
	int ret = 0;
	int allies_alive = 0;
	int enemies_alive = 0;

	for (size_t i = 0; i < 4; i++)
	{
		if (allies[i]->GetEntityState())
		{
			allies_alive++;
		}

		if (enemies[i]->GetEntityState())
		{
			enemies_alive++;
		}
	}

	if (allies_alive == 0)
	{
		ret = 2;
	}
	else if (enemies_alive == 0)
	{
		ret = 1;
	}

	return ret;
}