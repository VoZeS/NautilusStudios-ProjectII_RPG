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
	LoadHeroesStats();

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
			int health, mana, speed, power;
			HeroesStats(health, mana, speed, power, 0); // assassin
			allies[0] = new Combat_Entities(health, mana, speed, power, 0);
			HeroesStats(health, mana, speed, power, 1); // healer
			allies[1] = new Combat_Entities(health, mana, speed, power, 1);
			HeroesStats(health, mana, speed, power, 2); // tank
			allies[2] = new Combat_Entities(health, mana, speed, power, 2);
			HeroesStats(health, mana, speed, power, 3); // wizard
			allies[3] = new Combat_Entities(health, mana, speed, power, 3);

			//init enemies
			for (size_t i = 0; i < 4; i++)
			{
				enemies[i] = new Combat_Entities(app->frontground->GetEnemiesToFight(i));
			}

			items = new Combat_Entities(); // items

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
					SetEntitiesPositions();
					do
					{
						turn++;
						if (turn >= sizeof(turn_order) / sizeof(turn_order[0]))
						{
							turn = 0;
						}
					} while (turn_order[turn]->GetEntityState() != 1);
					UpdateBuffs();
					pass_turn = false;
				}
			}
			else if (CheckCombatState() == 1)
			{
				app->menu->SetWinLose(0); // win
			}
			else if (CheckCombatState() == 2)
			{
				app->menu->SetWinLose(1); // lose
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
			//UpdateHUD();
			//It is updated in "Combat_Menu" to set the drawing order right (HUD in front, characters in back)
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
	SDL_Rect rect;

	// assassin
	app->render->DrawTexture(app->tex->whitemark_64x64, 8 + cx, 8 + cy);
	rect = { 0, 0, 64, 64 };
	app->render->DrawTexture(app->tex->heroes_icons, 8 + cx, 8 + cy, &rect);
	app->render->DrawRectangle({ 75 + cx, 8 + cy, allies[0]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 76 + cx, 9 + cy, allies[0]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 76 + cx + allies[0]->GetActualHealth(), 9 + cy, allies[0]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 75 + cx, 8 + cy + 34, allies[0]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 76 + cx, 9 + cy + 34, allies[0]->GetActualMana(), 28 }, 0, 0, 255);
	if (!allies[0]->GetEntityState())
	{
		app->render->DrawTexture(app->tex->dead_icon, 8 + cx, 8 + cy);
	}
	else if (turn_order[turn] == allies[0])
	{
		app->render->DrawTexture(app->tex->turn_icon, 8 + cx, 8 + cy);
	}

	// healer
	app->render->DrawTexture(app->tex->whitemark_64x64, 8 + cx, 8 + cy + 67);
	rect = { 64, 0, 64, 64 };
	app->render->DrawTexture(app->tex->heroes_icons, 8 + cx, 8 + cy + 67, &rect);
	app->render->DrawRectangle({ 75 + cx, 8 + cy + 67, allies[1]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 76 + cx, 9 + cy + 67, allies[1]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 76 + cx + allies[1]->GetActualHealth(), 9 + cy + 67, allies[1]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 75 + cx, 8 + cy + 34 + 67, allies[1]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 76 + cx, 9 + cy + 34 + 67, allies[1]->GetActualMana(), 28 }, 0, 0, 255);
	if (!allies[1]->GetEntityState())
	{
		app->render->DrawTexture(app->tex->dead_icon, 8 + cx, 8 + cy + 67);
	}
	else if (turn_order[turn] == allies[1])
	{
		app->render->DrawTexture(app->tex->turn_icon, 8 + cx, 8 + cy + 67);
	}
	

	// tank
	app->render->DrawTexture(app->tex->whitemark_64x64, 8 + cx + 250, 8 + cy);
	rect = { 128, 0, 64, 64 };
	app->render->DrawTexture(app->tex->heroes_icons, 8 + cx + 250, 8 + cy, &rect);
	app->render->DrawRectangle({ 75 + cx + 250, 8 + cy, allies[2]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 76 + cx + 250, 9 + cy, allies[2]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 76 + cx + allies[2]->GetActualHealth() + 250, 9 + cy, allies[2]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 75 + cx + 250, 8 + cy + 34, allies[2]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 76 + cx + 250, 9 + cy + 34, allies[2]->GetActualMana(), 28 }, 0, 0, 255);
	if (!allies[2]->GetEntityState())
	{
		app->render->DrawTexture(app->tex->dead_icon, 8 + cx + 250, 8 + cy);
	}
	else if (turn_order[turn] == allies[2])
	{
		app->render->DrawTexture(app->tex->turn_icon, 8 + cx + 250, 8 + cy);
	}

	// wizard
	app->render->DrawTexture(app->tex->whitemark_64x64, 8 + cx + 250, 8 + cy + 67);
	rect = { 192, 0, 64, 64 };
	app->render->DrawTexture(app->tex->heroes_icons, 8 + cx + 250, 8 + cy + 67, &rect);
	app->render->DrawRectangle({ 75 + cx + 250, 8 + cy + 67, allies[3]->GetMaxHealth(), 30 }, 70, 0, 0);
	app->render->DrawRectangle({ 76 + cx + 250, 9 + cy + 67, allies[3]->GetActualHealth(), 28 }, 255, 0, 0);
	app->render->DrawRectangle({ 76 + cx + allies[3]->GetActualHealth() + 250, 9 + cy + 67, allies[3]->GetShield(), 28 }, 120, 120, 120);
	app->render->DrawRectangle({ 75 + cx + 250, 8 + cy + 34 + 67, allies[3]->GetMaxMana(), 30 }, 0, 0, 70);
	app->render->DrawRectangle({ 76 + cx + 250, 9 + cy + 34 + 67, allies[3]->GetActualMana(), 28 }, 0, 0, 255);
	if (!allies[3]->GetEntityState())
	{
		app->render->DrawTexture(app->tex->dead_icon, 8 + cx + 250, 8 + cy + 67);
	}
	else if (turn_order[turn] == allies[3])
	{
		app->render->DrawTexture(app->tex->turn_icon, 8 + cx + 250, 8 + cy + 67);
	}

	// enemy 1
	if (enemies[0]->GetEntityState() != 2)
	{
		app->render->DrawTexture(app->tex->whitemark_64x64, 8 + cx + 800, 8 + cy);
		switch (enemies[0]->GetType())
		{
		case 4: rect = { 0, 0, 64, 64 };
			  break;
		case 5: rect = { 192, 0, 64, 64 };
			  break;
		case 6: rect = { 64, 0, 64, 64 };
			  break;
		case 7: rect = { 128, 0, 64, 64 };
			  break;
		default: rect = { 0, 0, 64, 64 };
			   break;
		}
		app->render->DrawTexture(app->tex->enemies_icons, 8 + cx + 800, 8 + cy, &rect);
		app->render->DrawRectangle({ 75 + cx + 800, 8 + cy, enemies[0]->GetMaxHealth(), 30 }, 70, 0, 0);
		app->render->DrawRectangle({ 76 + cx + 800, 9 + cy, enemies[0]->GetActualHealth(), 28 }, 255, 0, 0);
		app->render->DrawRectangle({ 76 + cx + enemies[0]->GetActualHealth() + 800, 9 + cy, enemies[0]->GetShield(), 28 }, 120, 120, 120);
		app->render->DrawRectangle({ 75 + cx + 800, 8 + cy + 34, enemies[0]->GetMaxMana(), 30 }, 0, 0, 70);
		app->render->DrawRectangle({ 76 + cx + 800, 9 + cy + 34, enemies[0]->GetActualMana(), 28 }, 0, 0, 255);
		if (enemies[0]->GetEntityState() == 0)
		{
			app->render->DrawTexture(app->tex->dead_icon, 8 + cx + 800, 8 + cy);
		}
		else if (turn_order[turn] == enemies[0])
		{
			app->render->DrawTexture(app->tex->turn_icon, 8 + cx + 800, 8 + cy);
		}
	}

	// enemy 2
	if (enemies[1]->GetEntityState() != 2)
	{
		app->render->DrawTexture(app->tex->whitemark_64x64, 8 + cx + 800, 8 + cy + 67);
		switch (enemies[1]->GetType())
		{
		case 4: rect = { 0, 0, 64, 64 };
			  break;
		case 5: rect = { 192, 0, 64, 64 };
			  break;
		case 6: rect = { 64, 0, 64, 64 };
			  break;
		case 7: rect = { 128, 0, 64, 64 };
			  break;
		default: rect = { 0, 0, 64, 64 };
			   break;
		}
		app->render->DrawTexture(app->tex->enemies_icons, 8 + cx + 800, 8 + cy + 67, &rect);
		app->render->DrawRectangle({ 75 + cx + 800, 8 + cy + 67, enemies[1]->GetMaxHealth(), 30 }, 70, 0, 0);
		app->render->DrawRectangle({ 76 + cx + 800, 9 + cy + 67, enemies[1]->GetActualHealth(), 28 }, 255, 0, 0);
		app->render->DrawRectangle({ 76 + cx + enemies[1]->GetActualHealth() + 800, 9 + cy + 67, enemies[1]->GetShield(), 28 }, 120, 120, 120);
		app->render->DrawRectangle({ 75 + cx + 800, 8 + cy + 34 + 67, enemies[1]->GetMaxMana(), 30 }, 0, 0, 70);
		app->render->DrawRectangle({ 76 + cx + 800, 9 + cy + 34 + 67, enemies[1]->GetActualMana(), 28 }, 0, 0, 255);
		if (enemies[1]->GetEntityState() == 0)
		{
			app->render->DrawTexture(app->tex->dead_icon, 8 + cx + 800, 8 + cy + 67);
		}
		else if (turn_order[turn] == enemies[1])
		{
			app->render->DrawTexture(app->tex->turn_icon, 8 + cx + 800, 8 + cy + 67);
		}
	}

	// enemy 3
	if (enemies[2]->GetEntityState() != 2)
	{
		app->render->DrawTexture(app->tex->whitemark_64x64, 8 + cx + 250 + 800, 8 + cy);
		switch (enemies[2]->GetType())
		{
		case 4: rect = { 0, 0, 64, 64 };
			  break;
		case 5: rect = { 192, 0, 64, 64 };
			  break;
		case 6: rect = { 64, 0, 64, 64 };
			  break;
		case 7: rect = { 128, 0, 64, 64 };
			  break;
		default: rect = { 0, 0, 64, 64 };
			   break;
		}
		app->render->DrawTexture(app->tex->enemies_icons, 8 + cx + 250 + 800, 8 + cy, &rect);
		app->render->DrawRectangle({ 75 + cx + 250 + 800, 8 + cy, enemies[2]->GetMaxHealth(), 30 }, 70, 0, 0);
		app->render->DrawRectangle({ 76 + cx + 250 + 800, 9 + cy, enemies[2]->GetActualHealth(), 28 }, 255, 0, 0);
		app->render->DrawRectangle({ 76 + cx + enemies[2]->GetActualHealth() + 250 + 800, 9 + cy, enemies[2]->GetShield(), 28 }, 120, 120, 120);
		app->render->DrawRectangle({ 75 + cx + 250 + 800, 8 + cy + 34, enemies[2]->GetMaxMana(), 30 }, 0, 0, 70);
		app->render->DrawRectangle({ 76 + cx + 250 + 800, 9 + cy + 34, enemies[2]->GetActualMana(), 28 }, 0, 0, 255);
		if (enemies[2]->GetEntityState() == 0)
		{
			app->render->DrawTexture(app->tex->dead_icon, 8 + cx + 250 + 800, 8 + cy);
		}
		else if (turn_order[turn] == enemies[2])
		{
			app->render->DrawTexture(app->tex->turn_icon, 8 + cx + 250 + 800, 8 + cy);
		}
	}

	// enemy 4
	if (enemies[3]->GetEntityState() != 2)
	{
		app->render->DrawTexture(app->tex->whitemark_64x64, 8 + cx + 250 + 800, 8 + cy + 67);
		switch (enemies[3]->GetType())
		{
		case 4: rect = { 0, 0, 64, 64 };
			  break;
		case 5: rect = { 192, 0, 64, 64 };
			  break;
		case 6: rect = { 64, 0, 64, 64 };
			  break;
		case 7: rect = { 128, 0, 64, 64 };
			  break;
		default: rect = { 0, 0, 64, 64 };
			   break;
		}
		app->render->DrawTexture(app->tex->enemies_icons, 8 + cx + 250 + 800, 8 + cy + 67, &rect);
		app->render->DrawRectangle({ 75 + cx + 250 + 800, 8 + cy + 67, enemies[3]->GetMaxHealth(), 30 }, 70, 0, 0);
		app->render->DrawRectangle({ 76 + cx + 250 + 800, 9 + cy + 67, enemies[3]->GetActualHealth(), 28 }, 255, 0, 0);
		app->render->DrawRectangle({ 76 + cx + enemies[3]->GetActualHealth() + 250 + 800, 9 + cy + 67, enemies[3]->GetShield(), 28 }, 120, 120, 120);
		app->render->DrawRectangle({ 75 + cx + 250 + 800, 8 + cy + 34 + 67, enemies[3]->GetMaxMana(), 30 }, 0, 0, 70);
		app->render->DrawRectangle({ 76 + cx + 250 + 800, 9 + cy + 34 + 67, enemies[3]->GetActualMana(), 28 }, 0, 0, 255);
		if (enemies[3]->GetEntityState() == 0)
		{
			app->render->DrawTexture(app->tex->dead_icon, 8 + cx + 250 + 800, 8 + cy + 67);
		}
		else if (turn_order[turn] == enemies[3])
		{
			app->render->DrawTexture(app->tex->turn_icon, 8 + cx + 250 + 800, 8 + cy + 67);
		}
	}
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
			objective->DamageEntity(damage, skill.skill_bonus);
			if (skill.debuff_type != DEBUFF_TYPE::NOTHING)
			{
				objective->AddDebuff(skill.debuff_type, skill.buff_turns);
			}
		}
		else if (skill.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
		{
			for (size_t i = 0; i < 4; i++)
			{
				if (user->GetType() < 4) // allies
				{
					enemies[i]->DamageEntity(damage, skill.skill_bonus);
					if (skill.debuff_type != DEBUFF_TYPE::NOTHING)
					{
						enemies[i]->AddDebuff(skill.debuff_type, skill.buff_turns);
					}
				}
				else // enemies
				{
					allies[i]->DamageEntity(damage, skill.skill_bonus);
					if (skill.debuff_type != DEBUFF_TYPE::NOTHING)
					{
						allies[i]->AddDebuff(skill.debuff_type, skill.buff_turns);
					}
				}
				
			}
		}

		// lauch support skill
		if (skill.ally_objective == ALLY_OBJECTIVE::ONE_ALLY)
		{
			if (skill.support_type == SUPPORT_TYPE::SHIELD)
			{
				objective->ShieldEntity(support * 5, skill.buff_turns);
			}
			else if (skill.support_type == SUPPORT_TYPE::HEAL)
			{
				objective->HealEntity(support * 2);
			}
			else if (skill.support_type == SUPPORT_TYPE::CLEAN)
			{
				objective->CleanEntity();
			}
			else if (skill.support_type == SUPPORT_TYPE::RELOAD)
			{
				objective->ReloadMana(support * 5);
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
				if (user->GetType() < 4) // allies
				{
					for (size_t i = 0; i < 4; i++)
					{
						allies[i]->ShieldEntity(support * 5, skill.buff_turns);
					}
				}
				else // enemies
				{
					for (size_t i = 0; i < 4; i++)
					{
						enemies[i]->ShieldEntity(support * 5, skill.buff_turns);
					}
				}
				
			}
			else if (skill.support_type == SUPPORT_TYPE::HEAL)
			{
				if (user->GetType() < 4) // allies
				{
					for (size_t i = 0; i < 4; i++)
					{
						allies[i]->HealEntity(support * 2);
					}
				}
				else // enemies
				{
					for (size_t i = 0; i < 4; i++)
					{
						enemies[i]->HealEntity(support * 2);
					}
				}
			}
			else if (skill.support_type == SUPPORT_TYPE::CLEAN)
			{
				if (user->GetType() < 4) // allies
				{
					for (size_t i = 0; i < 4; i++)
					{
						allies[i]->CleanEntity();
					}
				}
				else // enemies
				{
					for (size_t i = 0; i < 4; i++)
					{
						enemies[i]->CleanEntity();
					}
				}
			}
			else if (skill.support_type == SUPPORT_TYPE::RELOAD)
			{
				if (user->GetType() < 4) // allies
				{
					for (size_t i = 0; i < 4; i++)
					{
						allies[i]->ReloadMana(support * 5);
					}
				}
				else // enemies
				{
					for (size_t i = 0; i < 4; i++)
					{
						enemies[i]->ReloadMana(support * 5);
					}
				}
			}
		}
		else if (skill.ally_objective == ALLY_OBJECTIVE::SELF)
		{
			if (skill.support_type == SUPPORT_TYPE::SHIELD)
			{
				user->ShieldEntity(support * 5, skill.buff_turns);
			}
			else if (skill.support_type == SUPPORT_TYPE::HEAL)
			{
				user->HealEntity(support * 2);
			}
			else if (skill.support_type == SUPPORT_TYPE::CLEAN)
			{
				user->CleanEntity();
			}
			else if (skill.support_type == SUPPORT_TYPE::RELOAD)
			{
				user->ReloadMana(support * 5);
			}

			if (skill.buff_type != BUFF_TYPE::NOTHING)
			{
				user->AddBuff(skill.buff_type, skill.buff_turns);
			}
		}

		in_animation = 1;

		if (skill.anim_effect != ANIM_EFFECT::EMPTY)
		{
			app->combat_menu->SetSkillAnimation(skill.anim_effect, objective->position.x, objective->position.y);
		}
	}
}

void Combat_Manager::UpdateBuffs()
{
	GetActualEntity()->UpdateBuffs();
	GetActualEntity()->UpdateDamageDebuffs();
	GetActualEntity()->UpdateDebuffs();
	GetActualEntity()->UpdateShield();
}

void Combat_Manager::EnemyTurn(Combat_Entities* user)
{
	int r;

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
		do
		{
			r = rand() % 4;
		} while (!allies[r]->GetEntityState());
		app->combat_menu->SetSkillPrepared(user->GetSkill(0));
		UseSkill(user, user->GetSkill(0), allies[r]);
	}
}

void Combat_Manager::SetEntitiesPositions()
{
	for (size_t i = 0; i < 4; i++)
	{
		allies[i]->position = app->combat_menu->GetEntityPosition(true, i);
		enemies[i]->position = app->combat_menu->GetEntityPosition(false, i);
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

void Combat_Manager::HeroesStats(int& health, int& mana, int& speed, int& power, int owner)
{
	pugi::xml_node hero;
	switch (owner)
	{
	case 0: hero = heroes_stats.child("assassin");
		break;
	case 1:  hero = heroes_stats.child("healer");
		break;
	case 2: hero = heroes_stats.child("tank");
		break;
	case 3: hero = heroes_stats.child("wizard");
		break;
	}

	health = hero.child("basic_stats").attribute("health").as_int();
	mana = hero.child("basic_stats").attribute("mana").as_int();
	speed = hero.child("basic_stats").attribute("speed").as_int();
	power = hero.child("basic_stats").attribute("power").as_int();
}

bool Combat_Manager::LoadHeroesStats()
{
	bool ret = true;

	pugi::xml_parse_result result = heroes_statsFile.load_file(HEROES_STATS_FILENAME);

	if (result == NULL)
	{
		LOG("Could not load xml file heroes_stats.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		heroes_stats = heroes_statsFile.child("heroes_stats");
	}

	return ret;
}