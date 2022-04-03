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

	if (in_combat && !app->menu->GetGameState())
	{
		if (!combat_init)
		{
			//init allies
			allies[0] = new Combat_Entities(100, 50, 20, 14, 0); // assassin
			allies[1] = new Combat_Entities(100, 50, 7, 14, 1); // tank
			allies[2] = new Combat_Entities(100, 50, 9, 14, 2); // healer
			allies[3] = new Combat_Entities(100, 50, 12, 14, 3); // wizard

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
			if (pass_turn)
			{
				turn++;
				if (turn >= sizeof(turn_order) / sizeof(turn_order[0]))
				{
					turn = 0;
				}
				pass_turn = false;
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
}

void Combat_Manager::UseSkill(Combat_Entities* user, Skill skill, Combat_Entities* objective)
{
	user->ReloadMana(-skill.mana_cost);
	objective->DamageEntity(user->GetPower());

	in_animation = 1;
	//pass_turn = true;
	//app->combat_menu->SetAlliesTurn(false);
}

void Combat_Manager::EnemyTurn(Combat_Entities* user)
{
	app->combat_menu->SetSkillPrepared(user->GetSkill(0));
	UseSkill(user, user->GetSkill(0), allies[0]);
}