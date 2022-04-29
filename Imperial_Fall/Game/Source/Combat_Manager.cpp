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
#include "Inventory.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"
#include "Fonts.h"
#include "Particles.h"

#include <stdlib.h>
#include <time.h>

Combat_Manager::Combat_Manager(bool enabled) : Module(enabled)
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
	if (this->Enabled() && !this->Disabled())
	{
		LoadHeroesStats();

		heroes_icons = app->tex->Load("Assets/textures/heroes_icons.png");
		enemies_icons = app->tex->Load("Assets/textures/enemies_icons.png");
		turn_icon = app->tex->Load("Assets/textures/turn_icon.png");
		dead_icon = app->tex->Load("Assets/textures/dead_icon.png");
		turns_icons = app->tex->Load("Assets/textures/turns_icons.png");
		whitemark_64x64 = app->tex->Load("Assets/textures/64x64_whitemark.png");
		whitemark_32x32 = app->tex->Load("Assets/textures/32x32_whitemark.png"); 
		status_effects = app->tex->Load("Assets/textures/status_effects.png");

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

		app->frontground->combat_xp = 0;

		//init enemies
		for (size_t i = 0; i < 4; i++)
		{
			enemies[i] = new Combat_Entities(app->frontground->GetEnemiesToFight(i));
			app->frontground->combat_xp += enemies[i]->xp;
		}
		for (size_t i = 0; i < 4; i++)
		{
			if (enemies[i]->GetSkill(0).owner == 9)
			{
				dragon_breath = app->audio->LoadFx("Assets/audio/fx/dragon_breath.wav");
				break;
			}
		}

		items = new Combat_Entities(); // items
		LoadItemUses();
		items_saved = false;

		//set turn order
		SetOrder();
		turn = -1;
		pass_turn = true;

		casting = false;
		casting_time = 0;
		casting_rect = { -64, 0, 64, 64 };

		winning = false;
		losing = false;
		exit_cd = 0;

		preupdatedone = false;
	}

	return true;
}

// Called each loop iteration
bool Combat_Manager::PreUpdate()
{
	if (!app->menu->GetGameState())
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
					if (turn > 7)
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
			exit_cd++;
			if (exit_cd > EXIT_DELAY)
			{
				app->menu->SetWinLoseScape(0); // win
				if (!items_saved)
				{
					SaveItemUses();
					items_saved = true;
				}
			}
		}
		else if (CheckCombatState() == 2)
		{
			exit_cd++;
			if (exit_cd > EXIT_DELAY)
			{
				app->menu->SetWinLoseScape(1); // lose
			}
		}
	}


	BUFF b;
	b.buff_type = BUFF_TYPE::GODMODE_STRONG;
	if (app->frontground->godmode)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (allies[i]->FindBuff(b) == -1)
			{
				allies[i]->AddBuff(BUFF_TYPE::GODMODE_STRONG, 99);
			}
		}
	}
	else
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (allies[i]->FindBuff(b) != -1)
			{
				allies[i]->RemoveGodModeBuffs();
			}
		}
	}

	preupdatedone = true;

	return true;
}

// Called each loop iteration
bool Combat_Manager::Update(float dt)
{
	if (!preupdatedone)
	{
		return true;
	}

	if (!pass_turn && in_animation == 0 && !casting)
	{
		if (turn_order[turn]->GetType() == 0 || turn_order[turn]->GetType() == 1 || turn_order[turn]->GetType() == 2 || turn_order[turn]->GetType() == 3) // allies
		{
			app->combat_menu->SetAlliesTurn(true);

			if (turn_order[turn]->prepared_to_die)
			{
				in_animation = 1;
			}

			// control debuffs
			DEBUFF b;
			b.debuff_type = DEBUFF_TYPE::STUN;
			if (turn_order[turn]->FindDebuff(b) != -1)
			{
				in_animation = 1;
				app->particles->AddParticle(app->particles->stun, turn_order[turn]->position.x - 32, turn_order[turn]->position.y - 100);
			}
		}
		else // enemies
		{
			if (turn_order[turn]->prepared_to_die)
			{
				in_animation = 1;
			}

			// AI
			enemies_loops = 0;
			if (app->frontground->fast_combat)
			{
				EnemyTurn(turn_order[turn]);
			}
			else
			{
				casting = true;
			}
		}
	}

	if (casting)
	{
		casting_time += dt;

		if (app->GetFPS() == 16) // 60 fps
		{
			if (casting_time >= CASTING_TIME * dt * 60)
			{
				EnemyTurn(turn_order[turn]);
				casting = false;
				casting_time = 0;
				casting_rect = { -64, 0, 64, 64 };
			}
			else if (casting_time >= 0.75 * CASTING_TIME * dt * 60)
			{
				casting_rect = { 192, 0, 64, 64 };
			}
			else if (casting_time >= 0.50 * CASTING_TIME * dt * 60)
			{
				casting_rect = { 128, 0, 64, 64 };
			}
			else if (casting_time >= 0.25 * CASTING_TIME * dt * 60)
			{
				casting_rect = { 64, 0, 64, 64 };
			}
			else
			{
				casting_rect = { 0, 0, 64, 64 };
			}
		}
		else // 30 fps
		{
			if (casting_time >= CASTING_TIME * dt * 120)
			{
				EnemyTurn(turn_order[turn]);
				casting = false;
				casting_time = 0;
				casting_rect = { -64, 0, 64, 64 };
			}
			else if (casting_time >= 0.75 * CASTING_TIME * dt * 120)
			{
				casting_rect = { 192, 0, 64, 64 };
			}
			else if (casting_time >= 0.50 * CASTING_TIME * dt * 120)
			{
				casting_rect = { 128, 0, 64, 64 };
			}
			else if (casting_time >= 0.25 * CASTING_TIME * dt * 120)
			{
				casting_rect = { 64, 0, 64, 64 };
			}
			else
			{
				casting_rect = { 0, 0, 64, 64 };
			}
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

	return true;
}

// Called before quitting
bool Combat_Manager::CleanUp()
{
	// clean textures
	app->tex->UnLoad(heroes_icons);
	heroes_icons = NULL;
	app->tex->UnLoad(enemies_icons);
	enemies_icons = NULL;
	app->tex->UnLoad(turn_icon);
	heroes_icons = NULL;
	app->tex->UnLoad(dead_icon);
	dead_icon = NULL;
	app->tex->UnLoad(turns_icons);
	turns_icons = NULL;
	app->tex->UnLoad(whitemark_64x64);
	whitemark_64x64 = NULL;
	app->tex->UnLoad(whitemark_32x32);
	whitemark_32x32 = NULL;

	// clean pointers
	for (uint i = 0; i < 8; ++i)
	{
		if (turn_order[i] != nullptr)
		{
			delete turn_order[i];
			turn_order[i] = nullptr;
		}
	}
	/*for (uint i = 0; i < 4; ++i)
	{
		if (allies[i] != nullptr)
		{
			delete allies[i];
			allies[i] = nullptr;
		}
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}*/
	if (items != nullptr)
	{
		delete items;
		items = nullptr;
	}

	for (size_t i = 0; i < 4; i++)
	{
		s_item_uses[i] = 0;
		f_item_uses[i] = 0;
	}

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

	int max = -1;
	int id;

	// order
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			if (aux[j]->GetSpeed() > max && !InArray(i, aux[j]))
			{
				id = j;
				max = aux[j]->GetSpeed();
			}
		}
		turn_order[i] = aux[id];
		max = -1;
	}
}

bool Combat_Manager::InArray(int length, Combat_Entities* check)
{
	for (size_t i = 0; i < length; i++)
	{
		if (turn_order[i] == check)
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

	for (size_t i = 0; i < 4; i++)
	{
		if (allies[i]->damage_recived > 0)
		{
			allies[i]->damage_recived--;
		}
		if (enemies[i]->damage_recived > 0)
		{
			enemies[i]->damage_recived--;
		}
	}

	float divider = ((float)app->frontground->adventure_phase / 3) + 1;

	// assassin
	app->render->DrawTexture(whitemark_64x64, 8 + cx + 250, 8 + cy);
	rect = { 0, 0, 64, 64 };
	app->render->DrawTexture(heroes_icons, 8 + cx + 250, 8 + cy, &rect);
	app->render->DrawRectangle({ 75 + cx + 250, 8 + cy, (int)(allies[0]->GetMaxHealth() / divider), 15 }, 70, 0, 0);
	app->render->DrawRectangle({ 76 + cx + 250, 9 + cy, (int)(allies[0]->GetActualHealth() / divider), 13 }, 255, 0, 0);
	app->render->DrawRectangle({ 76 + cx + (int)(allies[0]->GetActualHealth() / divider) + 250, 9 + cy, (int)(allies[0]->GetShield() / divider), 13 }, 120, 120, 120, 200);
	app->render->DrawRectangle({ 75 + cx + 250, 8 + cy + 16, (int)(allies[0]->GetMaxMana() / divider), 15 }, 0, 0, 70);
	app->render->DrawRectangle({ 76 + cx + 250, 9 + cy + 16, (int)(allies[0]->GetActualMana() / divider), 13 }, 0, 0, 255);
	app->render->DrawRectangle({ 76 + cx + (int)(allies[0]->GetActualHealth() / divider) + 250, 9 + cy, (int)(allies[0]->damage_recived / divider), 13 }, 218, 155, 0);
	allies[0]->DisplayStatus(75 + cx + 250, 8 + cy + 32);
	if (!allies[0]->GetEntityState())
	{
		app->render->DrawTexture(dead_icon, 8 + cx + 250, 8 + cy);
	}
	else if (turn_order[turn] == allies[0])
	{
		app->render->DrawTexture(turn_icon, 8 + cx + 250, 8 + cy);
	}

	// healer
	app->render->DrawTexture(whitemark_64x64, 8 + cx, 8 + cy);
	rect = { 64, 0, 64, 64 };
	app->render->DrawTexture(heroes_icons, 8 + cx, 8 + cy, &rect);
	app->render->DrawRectangle({ 75 + cx, 8 + cy, (int)(allies[1]->GetMaxHealth() / divider), 15 }, 70, 0, 0);
	app->render->DrawRectangle({ 76 + cx, 9 + cy, (int)(allies[1]->GetActualHealth() / divider), 13 }, 255, 0, 0);
	app->render->DrawRectangle({ 76 + cx + (int)(allies[1]->GetActualHealth() / divider), 9 + cy, (int)(allies[1]->GetShield() / divider), 13 }, 120, 120, 120, 200);
	app->render->DrawRectangle({ 75 + cx, 8 + cy + 16, (int)(allies[1]->GetMaxMana() / divider), 15 }, 0, 0, 70);
	app->render->DrawRectangle({ 76 + cx, 9 + cy + 16, (int)(allies[1]->GetActualMana() / divider), 13 }, 0, 0, 255);
	app->render->DrawRectangle({ 76 + cx + (int)(allies[1]->GetActualHealth() / divider), 9 + cy, (int)(allies[1]->damage_recived / divider), 13 }, 218, 155, 0);
	allies[1]->DisplayStatus(75 + cx, 8 + cy + 32);
	if (!allies[1]->GetEntityState())
	{
		app->render->DrawTexture(dead_icon, 8 + cx, 8 + cy);
	}
	else if (turn_order[turn] == allies[1])
	{
		app->render->DrawTexture(turn_icon, 8 + cx, 8 + cy);
	}

	// tank
	app->render->DrawTexture(whitemark_64x64, 8 + cx + 250, 8 + cy + 67);
	rect = { 128, 0, 64, 64 };
	app->render->DrawTexture(heroes_icons, 8 + cx + 250, 8 + cy + 67, &rect);
	app->render->DrawRectangle({ 75 + cx + 250, 8 + cy + 67, (int)(allies[2]->GetMaxHealth() / divider), 15 }, 70, 0, 0);
	app->render->DrawRectangle({ 76 + cx + 250, 9 + cy + 67, (int)(allies[2]->GetActualHealth() / divider), 13 }, 255, 0, 0);
	app->render->DrawRectangle({ 76 + cx + (int)(allies[2]->GetActualHealth() / divider) + 250, 9 + cy + 67, (int)(allies[2]->GetShield() / divider), 13 }, 120, 120, 120, 200);
	app->render->DrawRectangle({ 75 + cx + 250, 8 + cy + 16 + 67, (int)(allies[2]->GetMaxMana() / divider), 15 }, 0, 0, 70);
	app->render->DrawRectangle({ 76 + cx + 250, 9 + cy + 16 + 67, (int)(allies[2]->GetActualMana() / divider), 13 }, 0, 0, 255);
	app->render->DrawRectangle({ 76 + cx + (int)(allies[2]->GetActualHealth() / divider) + 250, 9 + cy + 67, (int)(allies[2]->damage_recived / divider), 13 }, 218, 155, 0);
	allies[2]->DisplayStatus(75 + cx + 250, 8 + cy + 32 + 67);
	if (!allies[2]->GetEntityState())
	{
		app->render->DrawTexture(dead_icon, 8 + cx + 250, 8 + cy + 67);
	}
	else if (turn_order[turn] == allies[2])
	{
		app->render->DrawTexture(turn_icon, 8 + cx + 250, 8 + cy + 67);
	}

	// wizard
	app->render->DrawTexture(whitemark_64x64, 8 + cx, 8 + cy + 67);
	rect = { 192, 0, 64, 64 };
	app->render->DrawTexture(heroes_icons, 8 + cx, 8 + cy + 67, &rect);
	app->render->DrawRectangle({ 75 + cx, 8 + cy + 67, (int)(allies[3]->GetMaxHealth() / divider), 15 }, 70, 0, 0);
	app->render->DrawRectangle({ 76 + cx, 9 + cy + 67, (int)(allies[3]->GetActualHealth() / divider), 13 }, 255, 0, 0);
	app->render->DrawRectangle({ 76 + cx + (int)(allies[3]->GetActualHealth() / divider), 9 + cy + 67, (int)(allies[3]->GetShield() / divider), 13 }, 120, 120, 120, 200);
	app->render->DrawRectangle({ 75 + cx, 8 + cy + 16 + 67, (int)(allies[3]->GetMaxMana() / divider), 15 }, 0, 0, 70);
	app->render->DrawRectangle({ 76 + cx, 9 + cy + 16 + 67, (int)(allies[3]->GetActualMana() / divider), 13 }, 0, 0, 255);
	app->render->DrawRectangle({ 76 + cx + (int)(allies[3]->GetActualHealth() / divider), 9 + cy + 67, (int)(allies[3]->damage_recived / divider), 13 }, 218, 155, 0);
	allies[3]->DisplayStatus(75 + cx, 8 + cy + 32 + 67);
	if (!allies[3]->GetEntityState())
	{
		app->render->DrawTexture(dead_icon, 8 + cx, 8 + cy + 67);
	}
	else if (turn_order[turn] == allies[3])
	{
		app->render->DrawTexture(turn_icon, 8 + cx, 8 + cy + 67);
	}

	// enemy 1
	if (enemies[0]->GetEntityState() != 2)
	{
		app->render->DrawTexture(whitemark_64x64, 8 + cx + 800, 8 + cy);
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
		case 8: rect = { 256, 0, 64, 64 };
			  break;
		case 9: rect = { 320, 0, 64, 64 };
			  break;
		case 10: rect = { 384, 0, 64, 64 };
			   break;
		case 11: rect = { 448, 0, 64, 64 };
			   break;
		case 12: rect = { 512, 0, 64, 64 };
			   break;
		default: rect = { 0, 0, 64, 64 };
			   break;
		}
		app->render->DrawTexture(enemies_icons, 8 + cx + 800, 8 + cy, &rect);
		app->render->DrawRectangle({ 75 + cx + 800, 8 + cy, (int)(enemies[0]->GetMaxHealth() / divider), 15 }, 70, 0, 0);
		app->render->DrawRectangle({ 76 + cx + 800, 9 + cy, (int)(enemies[0]->GetActualHealth() / divider), 13 }, 255, 0, 0);
		app->render->DrawRectangle({ 76 + cx + (int)(enemies[0]->GetActualHealth() / divider) + 800, 9 + cy, (int)(enemies[0]->GetShield() / divider), 13 }, 120, 120, 120, 200);
		app->render->DrawRectangle({ 75 + cx + 800, 8 + cy + 16, (int)(enemies[0]->GetMaxMana() / divider), 15 }, 0, 0, 70);
		app->render->DrawRectangle({ 76 + cx + 800, 9 + cy + 16, (int)(enemies[0]->GetActualMana() / divider), 13 }, 0, 0, 255);
		app->render->DrawRectangle({ 76 + cx + (int)(enemies[0]->GetActualHealth() / divider) + 800, 9 + cy, (int)(enemies[0]->damage_recived / divider), 13 }, 218, 155, 0);
		enemies[0]->DisplayStatus(75 + cx + 800, 8 + cy + 32);
		if (enemies[0]->GetEntityState() == 0)
		{
			app->render->DrawTexture(dead_icon, 8 + cx + 800, 8 + cy);
		}
		else if (turn_order[turn] == enemies[0])
		{
			app->render->DrawTexture(turn_icon, 8 + cx + 800, 8 + cy);
		}
	}

	// enemy 2
	if (enemies[1]->GetEntityState() != 2)
	{
		app->render->DrawTexture(whitemark_64x64, 8 + cx + 250 + 800, 8 + cy);
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
		case 8: rect = { 256, 0, 64, 64 };
			  break;
		case 9: rect = { 320, 0, 64, 64 };
			  break;
		case 10: rect = { 384, 0, 64, 64 };
			   break;
		case 11: rect = { 448, 0, 64, 64 };
			   break;
		case 12: rect = { 512, 0, 64, 64 };
			   break;
		default: rect = { 0, 0, 64, 64 };
			   break;
		}
		app->render->DrawTexture(enemies_icons, 8 + cx + 250 + 800, 8 + cy, &rect);
		app->render->DrawRectangle({ 75 + cx + 250 + 800, 8 + cy, (int)(enemies[1]->GetMaxHealth() / divider), 15 }, 70, 0, 0);
		app->render->DrawRectangle({ 76 + cx + 250 + 800, 9 + cy, (int)(enemies[1]->GetActualHealth() / divider), 13 }, 255, 0, 0);
		app->render->DrawRectangle({ 76 + cx + (int)(enemies[2]->GetActualHealth() / divider) + 250 + 800, 9 + cy, (int)(enemies[1]->GetShield() / divider), 13 }, 120, 120, 120, 200);
		app->render->DrawRectangle({ 75 + cx + 250 + 800, 8 + cy + 16, (int)(enemies[1]->GetMaxMana() / divider), 15 }, 0, 0, 70);
		app->render->DrawRectangle({ 76 + cx + 250 + 800, 9 + cy + 16, (int)(enemies[1]->GetActualMana() / divider), 13 }, 0, 0, 255);
		app->render->DrawRectangle({ 76 + cx + (int)(enemies[1]->GetActualHealth() / divider) + 250 + 800, 9 + cy, (int)(enemies[1]->damage_recived / divider), 13 }, 218, 155, 0);
		enemies[1]->DisplayStatus(75 + cx + 250 + 800, 8 + cy + 32);
		if (enemies[1]->GetEntityState() == 0)
		{
			app->render->DrawTexture(dead_icon, 8 + cx + 250 + 800, 8 + cy);
		}
		else if (turn_order[turn] == enemies[1])
		{
			app->render->DrawTexture(turn_icon, 8 + cx + 250 + 800, 8 + cy);
		}
	}

	// enemy 3
	if (enemies[2]->GetEntityState() != 2)
	{
		app->render->DrawTexture(whitemark_64x64, 8 + cx + 800, 8 + cy + 67);
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
		case 8: rect = { 256, 0, 64, 64 };
			  break;
		case 9: rect = { 320, 0, 64, 64 };
			  break;
		case 10: rect = { 384, 0, 64, 64 };
			   break;
		case 11: rect = { 448, 0, 64, 64 };
			   break;
		case 12: rect = { 512, 0, 64, 64 };
			   break;
		default: rect = { 0, 0, 64, 64 };
			   break;
		}
		app->render->DrawTexture(enemies_icons, 8 + cx + 800, 8 + cy + 67, &rect);
		app->render->DrawRectangle({ 75 + cx + 800, 8 + cy + 67, (int)(enemies[2]->GetMaxHealth() / divider), 15 }, 70, 0, 0);
		app->render->DrawRectangle({ 76 + cx + 800, 9 + cy + 67, (int)(enemies[2]->GetActualHealth() / divider), 13 }, 255, 0, 0);
		app->render->DrawRectangle({ 76 + cx + (int)(enemies[2]->GetActualHealth() / divider) + 800, 9 + cy + 67, (int)(enemies[2]->GetShield() / divider), 13 }, 120, 120, 120, 200);
		app->render->DrawRectangle({ 75 + cx + 800, 8 + cy + 16 + 67, (int)(enemies[2]->GetMaxMana() / divider), 15 }, 0, 0, 70);
		app->render->DrawRectangle({ 76 + cx + 800, 9 + cy + 16 + 67, (int)(enemies[2]->GetActualMana() / divider), 13 }, 0, 0, 255);
		app->render->DrawRectangle({ 76 + cx + (int)(enemies[2]->GetActualHealth() / divider) + 800, 9 + cy + 67, (int)(enemies[2]->damage_recived / divider), 13 }, 218, 155, 0);
		enemies[2]->DisplayStatus(75 + cx + 800, 8 + cy + 32 + 67);
		if (enemies[2]->GetEntityState() == 0)
		{
			app->render->DrawTexture(dead_icon, 8 + cx + 800, 8 + cy + 67);
		}
		else if (turn_order[turn] == enemies[2])
		{
			app->render->DrawTexture(turn_icon, 8 + cx + 800, 8 + cy + 67);
		}
	}

	// enemy 4
	if (enemies[3]->GetEntityState() != 2)
	{
		app->render->DrawTexture(whitemark_64x64, 8 + cx + 250 + 800, 8 + cy + 67);
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
		case 8: rect = { 256, 0, 64, 64 };
			  break;
		case 9: rect = { 320, 0, 64, 64 };
			  break;
		case 10: rect = { 384, 0, 64, 64 };
			   break;
		case 11: rect = { 448, 0, 64, 64 };
			   break;
		case 12: rect = { 512, 0, 64, 64 };
			   break;
		default: rect = { 0, 0, 64, 64 };
			   break;
		}
		app->render->DrawTexture(enemies_icons, 8 + cx + 250 + 800, 8 + cy + 67, &rect);
		app->render->DrawRectangle({ 75 + cx + 250 + 800, 8 + cy + 67, (int)(enemies[3]->GetMaxHealth() / divider), 15 }, 70, 0, 0);
		app->render->DrawRectangle({ 76 + cx + 250 + 800, 9 + cy + 67, (int)(enemies[3]->GetActualHealth() / divider), 13 }, 255, 0, 0);
		app->render->DrawRectangle({ 76 + cx + (int)(enemies[3]->GetActualHealth() / divider) + 250 + 800, 9 + cy + 67, (int)(enemies[3]->GetShield() / divider), 13 }, 120, 120, 120, 200);
		app->render->DrawRectangle({ 75 + cx + 250 + 800, 8 + cy + 16 + 67, (int)(enemies[3]->GetMaxMana() / divider), 15 }, 0, 0, 70);
		app->render->DrawRectangle({ 76 + cx + 250 + 800, 9 + cy + 16 + 67, (int)(enemies[3]->GetActualMana() / divider), 13 }, 0, 0, 255);
		app->render->DrawRectangle({ 76 + cx + (int)(enemies[3]->GetActualHealth() / divider) + 250 + 800, 9 + cy + 67, (int)(enemies[3]->damage_recived / divider), 13 }, 218, 155, 0);
		enemies[3]->DisplayStatus(75 + cx + 250 + 800, 8 + cy + 32 + 67);
		if (enemies[3]->GetEntityState() == 0)
		{
			app->render->DrawTexture(dead_icon, 8 + cx + 250 + 800, 8 + cy + 67);
		}
		else if (turn_order[turn] == enemies[3])
		{
			app->render->DrawTexture(turn_icon, 8 + cx + 250 + 800, 8 + cy + 67);
		}
	}

	DisplayOrder(cx, cy);
}

void Combat_Manager::DisplayOrder(int cx, int cy)
{
	// turns order indicators
	app->render->DrawTexture(whitemark_64x64, 608 + cx, 30 + cy);
	app->render->DrawTexture(whitemark_32x32, 624 + cx, 95 + cy);
	app->render->DrawTexture(whitemark_32x32, 624 + cx, 128 + cy);
	app->render->DrawTexture(whitemark_32x32, 624 + cx, 161 + cy);

	int t = turn;
	SDL_Rect rect;

	switch (turn_order[t]->GetType())
	{
	case 0:
		rect = { 0, 0, 64, 64 };
		app->render->DrawTexture(heroes_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 1:
		rect = { 64, 0, 64, 64 };
		app->render->DrawTexture(heroes_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 2:
		rect = { 128, 0, 64, 64 };
		app->render->DrawTexture(heroes_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 3:
		rect = { 192, 0, 64, 64 };
		app->render->DrawTexture(heroes_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 4:
		rect = { 0, 0, 64, 64 };
		app->render->DrawTexture(enemies_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 5:
		rect = { 192, 0, 64, 64 };
		app->render->DrawTexture(enemies_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 6:
		rect = { 64, 0, 64, 64 };
		app->render->DrawTexture(enemies_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 7:
		rect = { 128, 0, 64, 64 };
		app->render->DrawTexture(enemies_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 8:
		rect = { 256, 0, 64, 64 };
		app->render->DrawTexture(enemies_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 9: 
		rect = { 320, 0, 64, 64 };
		app->render->DrawTexture(enemies_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 10:
		rect = { 384, 0, 64, 64 };
		app->render->DrawTexture(enemies_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 11:
		rect = { 448, 0, 64, 64 };
		app->render->DrawTexture(enemies_icons, 608 + cx, 30 + cy, &rect);
		break;
	case 12:
		rect = { 512, 0, 64, 64 };
		app->render->DrawTexture(enemies_icons, 608 + cx, 30 + cy, &rect);
		break;
	}

	for (size_t i = 0; i < 3; i++)
	{
		do
		{
			if (t == 7)
			{
				t = 0;
			}
			else
			{
				t++;
			}
		} while (turn_order[t]->GetEntityState() != 1);

		rect = { 32 * turn_order[t]->GetType(), 0, 32, 32 };
		app->render->DrawTexture(turns_icons, 624 + cx, 95 + cy + (i * 33), &rect);
	}
}

void Combat_Manager::UseSkill(Combat_Entities* user, Skill skill, Combat_Entities* objective)
{
	if (user->GetActualMana() < skill.mana_cost - 2)
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
		case 1: damage = 0.45f * user->GetPower();
			break;
		case 2: damage = 0.8f * user->GetPower();
			break;
		case 3: damage = 5.0f * user->GetPower();
			break;
		}

		switch (skill.supp_strenght)
		{
		case -1: support = 0.0f * user->GetPower();
			break;
		case 0: support = 0.4f * user->GetPower();
			break;
		case 1: support = 0.6f * user->GetPower();
			break;
		case 2: support = 1.1f * user->GetPower();
			break;
		}

		// lauch attack skill
		if (skill.enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
		{
			DEBUFF d;
			d.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			if (objective->GetWeakness() == skill.element)
			{
				damage *= 1.5f;
				app->particles->AddParticle(app->particles->weak, objective->position.x - 32, objective->position.y - 100);
			}
			else if (objective->FindDebuff(d) != -1 && skill.element == 0)
			{
				damage *= 1.5f;
				app->particles->AddParticle(app->particles->weak, objective->position.x - 32, objective->position.y - 100);
			}

			BUFF b;
			b.buff_type = BUFF_TYPE::DAMAGE_INMUNITY;
			if (objective->FindBuff(b) != -1)
			{
				damage = 0;
				app->particles->AddParticle(app->particles->null, objective->position.x - 32, objective->position.y - 100);
			}

			objective->DamageEntity(damage, skill.skill_bonus);

			b.buff_type = BUFF_TYPE::DEBUFF_INMUNITY;
			if (skill.debuff_type != DEBUFF_TYPE::NOTHING && objective->FindBuff(b) == -1)
			{
				objective->AddDebuff(skill.debuff_type, skill.buff_turns);
			}

			if (skill.support_type == SUPPORT_TYPE::CLEAN_BUFFS)
			{
				objective->RemoveAllBuffs();
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
				else if (skill.support_type == SUPPORT_TYPE::CLEAN_DEBUFFS)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->RemoveAllDebuffs();
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->RemoveAllDebuffs();
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

				if (skill.buff_type != BUFF_TYPE::NOTHING)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->AddBuff(skill.buff_type, skill.buff_turns);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->AddBuff(skill.buff_type, skill.buff_turns);
							}
						}
					}
				}
			}
			if (skill.ally_objective == ALLY_OBJECTIVE::SELF)
			{
				if (skill.support_type == SUPPORT_TYPE::SHIELD)
				{
					user->ShieldEntity(support * 2, skill.shield_turns);
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					user->HealEntity(support);
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN_DEBUFFS)
				{
					user->RemoveAllDebuffs();
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
			DEBUFF d;
			d.debuff_type = DEBUFF_TYPE::DEF_REDUCC;
			BUFF b1, b2, b3;
			b1.buff_type = BUFF_TYPE::DODGE;
			b2.buff_type = BUFF_TYPE::DAMAGE_INMUNITY;
			b3.buff_type = BUFF_TYPE::DEBUFF_INMUNITY;
			for (size_t i = 0; i < 4; i++)
			{
				if (user->GetType() < 4) // allies
				{
					if (enemies[i]->GetEntityState() == 1 && enemies[i]->FindBuff(b1) == -1)
					{
						if (enemies[i]->FindBuff(b2) != -1)
						{
							damage = 0;
							app->particles->AddParticle(app->particles->null, enemies[i]->position.x - 32, enemies[i]->position.y - 100);
						}
						else if ((enemies[i]->GetWeakness() == skill.element) || (enemies[i]->FindDebuff(d) != -1 && skill.element == 0))
						{
							enemies[i]->DamageEntity(damage * 1.5f, skill.skill_bonus);
							app->particles->AddParticle(app->particles->weak, enemies[i]->position.x - 32, enemies[i]->position.y - 100);
						}
						else
						{
							enemies[i]->DamageEntity(damage, skill.skill_bonus);
						}

						if (skill.debuff_type != DEBUFF_TYPE::NOTHING && enemies[i]->FindBuff(b3) == -1)
						{
							enemies[i]->AddDebuff(skill.debuff_type, skill.buff_turns);
						}

						if (skill.support_type == SUPPORT_TYPE::CLEAN_BUFFS)
						{
							enemies[i]->RemoveAllBuffs();
						}
					}
				}
				else // enemies
				{
					if (allies[i]->GetEntityState() && allies[i]->FindBuff(b1) == -1)
					{
						if (allies[i]->FindBuff(b2) != -1)
						{
							// dont do damage
						}
						else if ((allies[i]->GetWeakness() == skill.element) || (allies[i]->FindDebuff(d) != -1 && skill.element == 0))
						{
							allies[i]->DamageEntity(damage * 1.5f, skill.skill_bonus);
						}
						else
						{
							allies[i]->DamageEntity(damage, skill.skill_bonus);
						}

						if (skill.debuff_type != DEBUFF_TYPE::NOTHING && allies[i]->FindBuff(b3) == -1)
						{
							allies[i]->AddDebuff(skill.debuff_type, skill.buff_turns);
						}

						if (skill.support_type == SUPPORT_TYPE::CLEAN_BUFFS)
						{
							allies[i]->RemoveAllBuffs();
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
								allies[i]->ShieldEntity(support * 2, skill.shield_turns);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->ShieldEntity(support * 2, skill.shield_turns);
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
				else if (skill.support_type == SUPPORT_TYPE::CLEAN_DEBUFFS)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->RemoveAllDebuffs();
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->RemoveAllDebuffs();
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

				if (skill.buff_type != BUFF_TYPE::NOTHING)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->AddBuff(skill.buff_type, skill.buff_turns);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->AddBuff(skill.buff_type, skill.buff_turns);
							}
						}
					}
				}
			}
			if (skill.ally_objective == ALLY_OBJECTIVE::SELF)
			{
				if (skill.support_type == SUPPORT_TYPE::SHIELD)
				{
					user->ShieldEntity(support * 2, skill.shield_turns);
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					user->HealEntity(support);
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN_DEBUFFS)
				{
					user->RemoveAllDebuffs();
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
					objective->ShieldEntity(support * 2, skill.shield_turns);
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					objective->HealEntity(support);
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN_DEBUFFS)
				{
					objective->RemoveAllDebuffs();
				}
				else if (skill.support_type == SUPPORT_TYPE::RELOAD)
				{
					objective->ReloadMana(support * 2);
				}
				else if (skill.support_type == SUPPORT_TYPE::REVIVE)
				{
					objective->Revive();
				}

				if (skill.buff_type != BUFF_TYPE::NOTHING)
				{
					objective->AddBuff(skill.buff_type, skill.buff_turns);
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
								allies[i]->ShieldEntity(support * 2, skill.shield_turns);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->ShieldEntity(support * 2, skill.shield_turns);
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
				else if (skill.support_type == SUPPORT_TYPE::CLEAN_DEBUFFS)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->RemoveAllDebuffs();
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->RemoveAllDebuffs();
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

				if (skill.buff_type != BUFF_TYPE::NOTHING)
				{
					if (user->GetType() < 4) // allies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (allies[i]->GetEntityState())
							{
								allies[i]->AddBuff(skill.buff_type, skill.buff_turns);
							}
						}
					}
					else // enemies
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (enemies[i]->GetEntityState())
							{
								enemies[i]->AddBuff(skill.buff_type, skill.buff_turns);
							}
						}
					}
				}
			}
			else if (skill.ally_objective == ALLY_OBJECTIVE::SELF)
			{
				if (skill.support_type == SUPPORT_TYPE::SHIELD)
				{
					user->ShieldEntity(support * 2, skill.shield_turns);
				}
				else if (skill.support_type == SUPPORT_TYPE::HEAL)
				{
					user->HealEntity(support);
				}
				else if (skill.support_type == SUPPORT_TYPE::CLEAN_DEBUFFS)
				{
					user->RemoveAllDebuffs();
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

		if (skill.zero_mana)
		{
			if (skill.owner == 9)
			{
				app->audio->PlayFx(dragon_breath);
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
	int objective, skill, rounds = 0;

	DEBUFF b;
	b.debuff_type = DEBUFF_TYPE::STUN;
	if (user->FindDebuff(b) != -1)
	{
		Skill null;
		null.skill_name = "null";
		app->combat_menu->SetSkillPrepared(null);
		in_animation = 1;
		app->particles->AddParticle(app->particles->stun, turn_order[turn]->position.x - 32, turn_order[turn]->position.y - 100);
		return;
	}

	do
	{
		skill = rand() % 4;
		rounds++;
	} while ((user->GetActualMana() < user->GetSkill(skill).mana_cost && rounds < 10) || user->GetSkill(skill).zero_mana);
	
	if (user->GetActualMana() < user->GetSkill(skill).mana_cost || enemies_loops == 10)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (user->GetSkill(i).zero_mana)
			{
				skill = i;
			}
		}
		if (!user->GetSkill(skill).zero_mana)
		{
			user->ReloadMana();
			Skill reload;
			reload.skill_name = "reload";
			app->combat_menu->SetSkillPrepared(reload);
			SetInAnimation(1);
			return;
		}
	}

	BUFF b1;
	b1.buff_type = BUFF_TYPE::STEALTH;
	BUFF b2;
	b2.buff_type = BUFF_TYPE::TAUNT;
	bool has_taunt = false;
	if (user->GetSkill(skill).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
	{
		rounds = 0;
		do
		{
			for (size_t i = 0; i < 4; i++)
			{
				if (allies[i]->FindBuff(b2) != -1)
				{
					objective = i;
					has_taunt = true;
					break;
				}
			}
			if (!has_taunt)
			{
				objective = rand() % 4;
				rounds++;
			}
		} while ((allies[objective]->GetEntityState() == 0 || allies[objective]->FindBuff(b1) != -1) && rounds < 10);

		if (rounds == 10)
		{
			do
			{
				objective = rand() % 4;
			} while ((allies[objective]->GetEntityState() == 0));
			app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
			UseSkill(user, user->GetSkill(skill), allies[objective]);
		}
		else
		{
			app->combat_menu->SetSkillPrepared(user->GetSkill(skill));
			UseSkill(user, user->GetSkill(skill), allies[objective]);
		}
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
			} while ((enemies[objective]->GetEntityState() != 1 || (enemies[objective]->GetActualHealth() > enemies[objective]->GetMaxHealth() * 0.7)) && rounds < 10);

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
		else if (user->GetSkill(skill).support_type == SUPPORT_TYPE::CLEAN_DEBUFFS)
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
		if (allies[i]->GetEntityState() == 1)
		{
			allies_alive++;
		}

		if (enemies[i]->GetEntityState() == 1)
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

void Combat_Manager::LoadItemUses()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node set = saveGame.child("objects").child("items").child("uses");
	
	for (size_t i = 0; i < 4; i++)
	{
		std::string p = "item";
		std::string s = std::to_string(app->combat_menu->GetItemByName(items->GetSkill(i).skill_name));
		std::string t = p + s;
		const char* c = t.c_str();

		if (s != "-1")
		{
			if (set.attribute(c).as_int() > 3)
			{
				s_item_uses[i] = 3;
			}
			else
			{
				s_item_uses[i] = set.attribute(c).as_int();
			}
		}
		else
		{
			s_item_uses[i] = 0;
		}
		
		f_item_uses[i] = s_item_uses[i];
	}
}

void Combat_Manager::SaveItemUses()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node set = saveGame.child("objects").child("items").child("uses");
	int uses, used;

	for (size_t i = 0; i < 4; i++)
	{
		std::string p = "item";
		std::string s = std::to_string(app->combat_menu->GetItemByName(items->GetSkill(i).skill_name));
		std::string t = p + s;
		const char* c = t.c_str();

		if (s != "-1")
		{
			uses = set.attribute(c).as_int();

			used = s_item_uses[i] - f_item_uses[i];
			set.attribute(c).set_value(uses - used);
		}
	}

	saveGame.save_file(UNLOCKABLE_OBJECTS_FILENAME);
}

void Combat_Manager::KillPreparedEntities()
{
	for (size_t i = 0; i < 4; i++)
	{
		if (allies[i]->prepared_to_die)
		{
			allies[i]->KillEntity();
			allies[i]->RemoveAllBuffs();
			allies[i]->RemoveAllDebuffs();
			allies[i]->DestroyShield();
		}
		if (enemies[i]->prepared_to_die)
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

	health = hero.child("basic_stats").attribute("health").as_int() + app->inventory->SumGearStats(owner, 0);
	mana = hero.child("basic_stats").attribute("mana").as_int() + app->inventory->SumGearStats(owner, 1);
	speed = hero.child("basic_stats").attribute("speed").as_int() + app->inventory->SumGearStats(owner, 2);
	power = hero.child("basic_stats").attribute("power").as_int() + app->inventory->SumGearStats(owner, 3);
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