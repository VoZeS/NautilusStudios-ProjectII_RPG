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
			int health, mana, speed, power, skill1, skill2, skill3, skill4;
			HeroesStats(health, mana, speed, power, 0, skill1, skill2, skill3, skill4); // assassin
			allies[0] = new Combat_Entities(health, mana, speed, power, 0, skill1, skill2, skill3, skill4);
			HeroesStats(health, mana, speed, power, 1, skill1, skill2, skill3, skill4); // healer
			allies[1] = new Combat_Entities(health, mana, speed, power, 1, skill1, skill2, skill3, skill4);
			HeroesStats(health, mana, speed, power, 2, skill1, skill2, skill3, skill4); // tank
			allies[2] = new Combat_Entities(health, mana, speed, power, 2, skill1, skill2, skill3, skill4);
			HeroesStats(health, mana, speed, power, 3, skill1, skill2, skill3, skill4); // wizard
			allies[3] = new Combat_Entities(health, mana, speed, power, 3, skill1, skill2, skill3, skill4);
			
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
							SetOrder();
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

			// control debuffs
			DEBUFF b;
			b.debuff_type = DEBUFF_TYPE::STUN;
			if (turn_order[turn]->FindDebuff(b) != -1)
			{
				in_animation = 1;
			}
		}
		else // enemies
		{
			// AI
			enemies_loops = 0;
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
			KillPreparedEntities();
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
	app->render->DrawRectangle({ 76 + cx + allies[0]->GetActualHealth(), 9 + cy, allies[0]->GetShield(), 28 }, 120, 120, 120, 200);
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
	app->render->DrawRectangle({ 76 + cx + allies[1]->GetActualHealth(), 9 + cy + 67, allies[1]->GetShield(), 28 }, 120, 120, 120, 200);
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
	app->render->DrawRectangle({ 76 + cx + allies[2]->GetActualHealth() + 250, 9 + cy, allies[2]->GetShield(), 28 }, 120, 120, 120, 200);
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
	app->render->DrawRectangle({ 76 + cx + allies[3]->GetActualHealth() + 250, 9 + cy + 67, allies[3]->GetShield(), 28 }, 120, 120, 120, 200);
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
		app->render->DrawRectangle({ 76 + cx + enemies[0]->GetActualHealth() + 800, 9 + cy, enemies[0]->GetShield(), 28 }, 120, 120, 120, 200);
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
		app->render->DrawRectangle({ 76 + cx + enemies[1]->GetActualHealth() + 800, 9 + cy + 67, enemies[1]->GetShield(), 28 }, 120, 120, 120, 200);
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
		app->render->DrawRectangle({ 76 + cx + enemies[2]->GetActualHealth() + 250 + 800, 9 + cy, enemies[2]->GetShield(), 28 }, 120, 120, 120, 200);
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
		app->render->DrawRectangle({ 76 + cx + enemies[3]->GetActualHealth() + 250 + 800, 9 + cy + 67, enemies[3]->GetShield(), 28 }, 120, 120, 120, 200);
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
		case -1: damage = 0.0f * user->GetPower();
			break;
		case 0: damage = 0.3f * user->GetPower();
			break;
		case 1: damage = 0.4f * user->GetPower();
			break;
		case 2: damage = 0.5f * user->GetPower();
			break;
		}

		switch (skill.supp_strenght)
		{
		case -1: support = 0.0f * user->GetPower();
			break;
		case 0: support = 0.6f * user->GetPower();
			break;
		case 1: support = 0.8f * user->GetPower();
			break;
		case 2: support = 1.0f * user->GetPower();
			break;
		}

		// damage inmunity
		BUFF b;
		b.buff_type = BUFF_TYPE::DAMAGE_INMUNITY;
		if (objective->FindBuff(b) != -1)
		{
			damage = 0;
		}
		
		b.buff_type = BUFF_TYPE::DEBUFF_INMUNITY;
		if (objective->FindBuff(b) != -1)
		{
			skill.debuff_type = DEBUFF_TYPE::NOTHING;
		}
		

		// lauch attack skill
		if (skill.enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
		{
			DEBUFF b;
			b.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			if (objective->GetWeakness() == skill.element)
			{
				damage *= 1.5f;
			}
			else if (objective->FindDebuff(b) != -1 && skill.element == 0)
			{
				damage *= 1.5f;
			}

			objective->DamageEntity(damage, skill.skill_bonus);

			if (skill.debuff_type != DEBUFF_TYPE::NOTHING)
			{
				objective->AddDebuff(skill.debuff_type, skill.buff_turns);
			}

			if (skill.ally_objective == ALLY_OBJECTIVE::ALL_ALLY)
			{
				if (skill.support_type == SUPPORT_TYPE::SHIELD)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->ShieldEntity(support * 2, skill.buff_turns);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->ShieldEntity(support * 2, skill.buff_turns);
							}
						}
					}
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->HealEntity(support);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->HealEntity(support);
							}
						}
					}
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->CleanEntity();
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->CleanEntity();
							}
						}
					}
				}
				else if (skill.support_type == SUPPORT_TYPE::RELOAD)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->ReloadMana(support * 2);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->ReloadMana(support * 2);
							}
						}
					}
				}
			}
			if (skill.ally_objective == ALLY_OBJECTIVE::SELF)
			{
				if (skill.support_type == SUPPORT_TYPE::SHIELD)
				{
					user->ShieldEntity(support * 2, skill.buff_turns);
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					user->HealEntity(support);
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN)
				{
					user->CleanEntity();
				}
				else if (skill.support_type == SUPPORT_TYPE::RELOAD)
				{
					user->ReloadMana(support * 2);
				}

				if (skill.buff_type != BUFF_TYPE::NOTHING)
				{
					user->AddBuff(skill.buff_type, skill.buff_turns);
				}
			}
		}
		else if (skill.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
		{
			DEBUFF b;
			b.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			for (size_t i = 0; i < 4; i++)
			{
				if (user->GetType() < 4) // allies
				{
					if (enemies[i]->GetWeakness() == skill.element)
					{
						damage *= 1.5f;
					}
					else if (enemies[i]->FindDebuff(b) != -1 && skill.element == 0)
					{
						damage *= 1.5f;
					}


					BUFF b;
					b.buff_type = BUFF_TYPE::DODGE;
					if (enemies[i]->GetEntityState() && enemies[i]->FindBuff(b) == -1)
					{
						enemies[i]->DamageEntity(damage, skill.skill_bonus);

						if (skill.debuff_type != DEBUFF_TYPE::NOTHING)
						{
							enemies[i]->AddDebuff(skill.debuff_type, skill.buff_turns);
						}
					}
				}
				else // enemies
				{
					if (allies[i]->GetWeakness() == skill.element)
					{
						damage *= 1.5f;
					}
					else if (allies[i]->FindDebuff(b) != -1 && skill.element == 0)
					{
						damage *= 1.5f;
					}

					BUFF b;
					b.buff_type = BUFF_TYPE::DODGE;
					if (allies[i]->GetEntityState() && allies[i]->FindBuff(b) == -1)
					{
						allies[i]->DamageEntity(damage, skill.skill_bonus);

						if (skill.debuff_type != DEBUFF_TYPE::NOTHING)
						{
							allies[i]->AddDebuff(skill.debuff_type, skill.buff_turns);
						}
					}
				}
			}

			if (skill.ally_objective == ALLY_OBJECTIVE::ALL_ALLY)
			{
				if (skill.support_type == SUPPORT_TYPE::SHIELD)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->ShieldEntity(support * 2, skill.buff_turns);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->ShieldEntity(support * 2, skill.buff_turns);
							}
						}
					}
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->HealEntity(support);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->HealEntity(support);
							}
						}
					}
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->CleanEntity();
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->CleanEntity();
							}
						}
					}
				}
				else if (skill.support_type == SUPPORT_TYPE::RELOAD)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->ReloadMana(support * 2);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->ReloadMana(support * 2);
							}
						}
					}
				}
			}
			if (skill.ally_objective == ALLY_OBJECTIVE::SELF)
			{
				if (skill.support_type == SUPPORT_TYPE::SHIELD)
				{
					user->ShieldEntity(support * 2, skill.buff_turns);
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					user->HealEntity(support);
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN)
				{
					user->CleanEntity();
				}
				else if (skill.support_type == SUPPORT_TYPE::RELOAD)
				{
					user->ReloadMana(support * 2);
				}

				if (skill.buff_type != BUFF_TYPE::NOTHING)
				{
					user->AddBuff(skill.buff_type, skill.buff_turns);
				}
			}
		}

		// lauch support skill
		if (skill.enemy_objective == ENEMY_OBJECTIVE::NOTHING)
		{
			if (skill.ally_objective == ALLY_OBJECTIVE::ONE_ALLY)
			{
				if (skill.support_type == SUPPORT_TYPE::SHIELD)
				{
					objective->ShieldEntity(support * 2, skill.buff_turns);
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					objective->HealEntity(support);
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN)
				{
					objective->CleanEntity();
				}
				else if (skill.support_type == SUPPORT_TYPE::RELOAD)
				{
					objective->ReloadMana(support * 2);
				}
				else if (skill.support_type == SUPPORT_TYPE::REVIVE)
				{
					objective->HealEntity(support);
					objective->Revive();
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
							if (allies[i]->GetEntityState())
							{
								allies[i]->ShieldEntity(support * 2, skill.buff_turns);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->ShieldEntity(support * 2, skill.buff_turns);
							}
						}
					}

				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->HealEntity(support);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->HealEntity(support);
							}
						}
					}
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->CleanEntity();
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->CleanEntity();
							}
						}
					}
				}
				else if (skill.support_type == SUPPORT_TYPE::RELOAD)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->ReloadMana(support * 2);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->ReloadMana(support * 2);
							}
						}
					}
				}
			}
			else if (skill.ally_objective == ALLY_OBJECTIVE::SELF)
			{
				if (skill.support_type == SUPPORT_TYPE::SHIELD)
				{
					user->ShieldEntity(support * 2, skill.buff_turns);
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					user->HealEntity(support);
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN)
				{
					user->CleanEntity();
				}
				else if (skill.support_type == SUPPORT_TYPE::RELOAD)
				{
					user->ReloadMana(support * 2);
				}

				if (skill.buff_type != BUFF_TYPE::NOTHING)
				{
					user->AddBuff(skill.buff_type, skill.buff_turns);
				}
			}
		}

		in_animation = 1;

		if (skill.att_effect != ATT_EFFECT::EMPTY || skill.supp_effect != SUPP_EFFECT::EMPTY)
		{
			app->combat_menu->SetSkillAnimation(skill.att_effect, skill.supp_effect, objective->position.x, objective->position.y);
		}
	}
}

void Combat_Manager::UpdateBuffs()
{
	GetActualEntity()->UpdateBuffs();
	GetActualEntity()->UpdateHealBuffs();
	GetActualEntity()->UpdateDamageDebuffs();
	GetActualEntity()->UpdateDebuffs();
	GetActualEntity()->UpdateShield();
}

void Combat_Manager::EnemyTurn(Combat_Entities* user)
{
	int objective, skill = 1, rounds = 0;

	DEBUFF b;
	b.debuff_type = DEBUFF_TYPE::STUN;
	if (user->FindDebuff(b) != -1)
	{
		Skill null;
		null.skill_name = "null";
		app->combat_menu->SetSkillPrepared(null);
		in_animation = 1;
		return;
	}


	/*do
	{
		skill = rand() % 4;
		rounds++;
	} while (user->GetActualMana() < user->GetSkill(skill).mana_cost && rounds < 10);*/
	
	if (user->GetActualMana() < user->GetSkill(skill).mana_cost || enemies_loops == 10)
	{
		user->ReloadMana();
		Skill reload;
		reload.skill_name = "reload";
		app->combat_menu->SetSkillPrepared(reload);
		SetInAnimation(1);
	}
	else
	{
		if (user->GetSkill(skill).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
		{
			do
			{
				objective = rand() % 4;
			} while (!allies[objective]->GetEntityState());
			app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
			UseSkill(user, user->GetSkill(skill), allies[objective]);
		}
		else if (user->GetSkill(skill).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
		{
			app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
			UseSkill(user, user->GetSkill(skill), allies[0]);
		}
		else if (user->GetSkill(skill).ally_objective == ALLY_OBJECTIVE::ONE_ALLY)
		{
			if (user->GetSkill(skill).support_type == SUPPORT_TYPE::HEAL)
			{
				rounds = 0;
				do
				{
					objective = rand() % 4;
					rounds++;
				} while ((!enemies[objective]->GetEntityState() || (enemies[objective]->GetActualHealth() > enemies[objective]->GetMaxHealth() - 20)) && rounds < 10);

				if (rounds == 10)
				{
					// restart AI
					enemies_loops++;
					EnemyTurn(user);
				}
				else
				{
					app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
					UseSkill(user, user->GetSkill(skill), enemies[objective]);
				}
			}
			else if (user->GetSkill(skill).support_type == SUPPORT_TYPE::SHIELD)
			{
				do
				{
					objective = rand() % 4;
				} while (!enemies[objective]->GetEntityState());

				app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
				UseSkill(user, user->GetSkill(skill), enemies[objective]);
			}
			else if (user->GetSkill(skill).support_type == SUPPORT_TYPE::CLEAN)
			{
				rounds = 0;
				do
				{
					objective = rand() % 4;
					rounds++;
				} while ((!enemies[objective]->GetEntityState() || (enemies[objective]->GetDebuffList().Count() > 0)) && rounds < 10);

				if (rounds == 10)
				{
					// restart AI
					enemies_loops++;
					EnemyTurn(user);
				}
				else
				{
					app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
					UseSkill(user, user->GetSkill(skill), enemies[objective]);
				}
			}
			else if (user->GetSkill(skill).support_type == SUPPORT_TYPE::RELOAD)
			{
				rounds = 0;
				do
				{
					objective = rand() % 4;
					rounds++;
				} while ((!enemies[objective]->GetEntityState() || (enemies[objective]->GetActualMana() < (enemies[objective]->GetMaxMana() / 2))) && rounds < 10);

				if (rounds == 10)
				{
					// restart AI
					enemies_loops++;
					EnemyTurn(user);
				}
				else
				{
					app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
					UseSkill(user, user->GetSkill(skill), enemies[objective]);
				}
			}
			else if (user->GetSkill(skill).support_type == SUPPORT_TYPE::REVIVE)
			{
				rounds = 0;
				do
				{
					objective = rand() % 4;
					rounds++;
				} while (enemies[objective]->GetEntityState() && rounds < 10);

				if (rounds == 10)
				{
					// restart AI
					enemies_loops++;
					EnemyTurn(user);
				}
				else
				{
					app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
					UseSkill(user, user->GetSkill(skill), enemies[objective]);
				}
			}
		}
		else if (user->GetSkill(skill).ally_objective == ALLY_OBJECTIVE::ALL_ALLY || user->GetSkill(skill).ally_objective == ALLY_OBJECTIVE::SELF)
		{
			app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
			UseSkill(user, user->GetSkill(skill), user);
		}
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

void Combat_Manager::KillPreparedEntities()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (allies[i]->prepared_to_die == true)
		{
			allies[i]->KillEntity();
			allies[i]->RemoveAllBuffs();
			allies[i]->RemoveAllDebuffs();
			allies[i]->DestroyShield();
		}
		if (enemies[i]->prepared_to_die == true)
		{
			enemies[i]->KillEntity();
			enemies[i]->RemoveAllBuffs();
			enemies[i]->RemoveAllDebuffs();
			enemies[i]->DestroyShield();
		}
	}
}

void Combat_Manager::HeroesStats(int& health, int& mana, int& speed, int& power, int owner, int &skill1, int &skill2, int &skill3, int &skill4)
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
	skill1 = hero.child("equiped_skills").attribute("skill1").as_int();
	skill2 = hero.child("equiped_skills").attribute("skill2").as_int();
	skill3 = hero.child("equiped_skills").attribute("skill3").as_int();
	skill4 = hero.child("equiped_skills").attribute("skill4").as_int();
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