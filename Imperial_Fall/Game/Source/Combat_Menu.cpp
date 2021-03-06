#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Combat_Manager.h"
#include "Combat_Menu.h"
#include "Inventory.h"
#include "Particles.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

#include <string.h>

Combat_Menu::Combat_Menu(bool enabled) : Module(enabled)
{
	name.Create("combat_menu");

	idleAnim.PushBack({ 7, 161, 46, 71 });
	idleAnim.PushBack({ 67, 161, 46, 71 });
	idleAnim.speed = 0.03f;

	templarAnim.PushBack({ 0, 0, 100, 102 });
	templarAnim.PushBack({ 100, 0, 100, 102 });
	templarAnim.PushBack({ 200, 0, 100, 102 });
	templarAnim.PushBack({ 300, 0, 100, 102 });
	templarAnim.PushBack({ 400, 0, 100, 102 });
	templarAnim.PushBack({ 500, 0, 100, 102 });
	templarAnim.speed = 0.06f;

	mushroomAnim.PushBack({ 0, 0, 100, 125 });
	mushroomAnim.PushBack({ 100, 0, 100, 125 });
	mushroomAnim.PushBack({ 200, 0, 100, 125 });
	mushroomAnim.PushBack({ 300, 0, 100, 125 });
	mushroomAnim.speed = 0.03f;

	goblinAnim.PushBack({ 0, 0, 66, 72 });
	goblinAnim.PushBack({ 66, 0, 66, 72 });
	goblinAnim.PushBack({ 132, 0, 66, 72 });
	goblinAnim.PushBack({ 198, 0, 66, 72 });
	goblinAnim.speed = 0.03f;

	skeletonAnim.PushBack({ 0, 0, 192, 210 });
	skeletonAnim.PushBack({ 192, 0, 192, 210 });
	skeletonAnim.PushBack({ 384, 0, 192, 210 });
	skeletonAnim.speed = 0.03f;

	dragon_idleAnim.PushBack({ 0, 0, 240, 240 });
	dragon_idleAnim.PushBack({ 240, 0, 240, 240 });
	dragon_idleAnim.speed = 0.02f;

	dragon_ultAnim.PushBack({ 0, 0, 500, 500 });
	dragon_ultAnim.PushBack({ 500, 0, 500, 500 });
	dragon_ultAnim.PushBack({ 1000, 0, 500, 500 });
	dragon_ultAnim.PushBack({ 1500, 0, 500, 500 });
	dragon_ultAnim.PushBack({ 2000, 0, 500, 500 });
	dragon_ultAnim.speed = 0.05f;
	dragon_ultAnim.loop = false;

	theseionAnim.PushBack({ 68, 78, 46, 74 });
	theseionAnim.PushBack({ 124, 78, 46, 74 });
	theseionAnim.speed = 0.03f;

	armoredAnim.PushBack({ 0, 0, 220, 140 });
	armoredAnim.PushBack({ 220, 0, 220, 140 });
	armoredAnim.PushBack({ 440, 0, 220, 140 });
	armoredAnim.PushBack({ 660, 0, 220, 140 });
	armoredAnim.PushBack({ 880, 0, 220, 140 });
	armoredAnim.PushBack({ 0, 140, 220, 140 });
	armoredAnim.PushBack({ 220, 140, 220, 140 });
	armoredAnim.PushBack({ 440, 140, 220, 140 });
	armoredAnim.PushBack({ 660, 140, 220, 140 });
	armoredAnim.PushBack({ 880, 140, 220, 140 });
	armoredAnim.speed = 0.08f;
}

// Destructor
Combat_Menu::~Combat_Menu()
{}

// Called before render is available
bool Combat_Menu::Awake()
{

	return true;
}

// Called before the first frame
bool Combat_Menu::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		r = { 0, 0, 1280, 720 };
		currentAnimation = &idleAnim;

		preupdatedone = false;
		updatedone = false;

		in_description = false;
		skill_prepared_is_item = -1;

		chosed = 0;
		enemy_chosed = -1;
		ally_chosed = -1;
		app->win->GetWindowSize(win_w, win_h);

		// textures
		assassin_texture = app->tex->Load("Assets/textures/Asesino.png");
		tank_texture = app->tex->Load("Assets/textures/Tanque.png");
		healer_texture = app->tex->Load("Assets/textures/Healer.png");
		wizard_texture = app->tex->Load("Assets/textures/Mago.png");
		target = app->tex->Load("Assets/textures/target.png");
		tombstone = app->tex->Load("Assets/textures/tombstone.png");
		goblin = app->tex->Load("Assets/textures/goblin_b.png");
		skeleton = app->tex->Load("Assets/textures/skeleton_b.png");
		mushroom = app->tex->Load("Assets/textures/mushroom_b.png");
		white_templar = app->tex->Load("Assets/textures/white_templar_b.png");
		red_templar = app->tex->Load("Assets/textures/red_templar_b.png");
		dragon_idle = app->tex->Load("Assets/textures/dragon_idle.png");
		dragon_ult = app->tex->Load("Assets/textures/dragon_ult.png");
		theseion = app->tex->Load("Assets/textures/Theseion.png");
		armored_templar = app->tex->Load("Assets/textures/armored_templar.png");
		whitemark_400x50 = app->tex->Load("Assets/textures/400x50_whitemark.png");
		whitemark_110x110 = app->tex->Load("Assets/textures/110x110_whitemark.png");
		whitemark_128x128 = app->tex->Load("Assets/textures/128x128_whitemark.png");
		whitemark_800x50 = app->tex->Load("Assets/textures/800x50_whitemark.png");
		special_buttons = app->tex->Load("Assets/textures/special_buttons.png");
		items = app->tex->Load("Assets/textures/Objects/items.png");
		casting = app->tex->Load("Assets/textures/casting.png");
		skills_icons = app->tex->Load("Assets/textures/skill_icons.png");

		// sounds
		click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");

		physic_fx = app->audio->LoadFx("Assets/audio/fx/physic_attack.wav");
		fire_fx = app->audio->LoadFx("Assets/audio/fx/fire_attack.wav");
		lightning_fx = app->audio->LoadFx("Assets/audio/fx/lightning_attack.wav");
		water_fx = app->audio->LoadFx("Assets/audio/fx/water_attack.wav");
		heal_fx = app->audio->LoadFx("Assets/audio/fx/heal.wav");
		buff_fx = app->audio->LoadFx("Assets/audio/fx/buff.wav");


		action_pos[0] = { 50.0f, 600.0f };
		action_pos[1] = { 460.0f, 600.0f };
		action_pos[2] = { 50.0f, 660.0f };
		action_pos[3] = { 460.0f, 660.0f };
		action_pos[4] = { 870.0f, 600.0f };
		action_pos[5] = { 990.0f, 600.0f };
		action_pos[6] = { 1110.0f, 600.0f };

		item_pos[0] = { 300.0f, 550.0f };
		item_pos[1] = { 438.0f, 550.0f };
		item_pos[2] = { 576.0f, 550.0f };
		item_pos[3] = { 714.0f, 550.0f };
		item_pos[4] = { 852.0f, 550.0f };

		enemy_pos[0] = { 866.0f, 180.0f };
		enemy_pos[1] = { 966.0f, 280.0f };
		enemy_pos[2] = { 866.0f, 380.0f };
		enemy_pos[3] = { 966.0f, 480.0f };
		enemy_pos[4] = { 415.0f, 660.0f };

		ally_pos[0] = { 350.0f, 180.0f };
		ally_pos[1] = { 250.0f, 280.0f };
		ally_pos[2] = { 350.0f, 380.0f };
		ally_pos[3] = { 250.0f, 480.0f };
		ally_pos[4] = { 415.0f, 660.0f };

		// attack buttons dimensions
		for (size_t i = 0; i < 4; i++)
		{
			general_buttons[i].rect.x = action_pos[i].x;
			general_buttons[i].rect.y = action_pos[i].y;
			general_buttons[i].rect.w = 400;
			general_buttons[i].rect.h = 50;
		}
		// reload
		general_buttons[4].rect.x = action_pos[4].x;
		general_buttons[4].rect.y = action_pos[4].y;
		general_buttons[4].rect.w = 110;
		general_buttons[4].rect.h = 110;
		// item and scape
		for (size_t i = 5; i < 7; i++)
		{
			general_buttons[i].rect.x = action_pos[i].x;
			general_buttons[i].rect.y = action_pos[i].y;
			general_buttons[i].rect.w = 110;
			general_buttons[i].rect.h = 110;
		}

		for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
		{
			items_buttons[i].rect.x = item_pos[i].x;
			items_buttons[i].rect.y = item_pos[i].y;
			items_buttons[i].rect.w = 128;
			items_buttons[i].rect.h = 128;
		}

		for (size_t i = 0; i < NUM_ENEMIES_BUTTONS - 1; i++)
		{
			enemies_buttons[i].rect.x = enemy_pos[i].x;
			enemies_buttons[i].rect.y = enemy_pos[i].y;
			enemies_buttons[i].rect.w = 64;
			enemies_buttons[i].rect.h = 70;
		}
		enemies_buttons[4].rect.x = enemy_pos[4].x;
		enemies_buttons[4].rect.y = enemy_pos[4].y;
		enemies_buttons[4].rect.w = 400;
		enemies_buttons[4].rect.h = 50;

		for (size_t i = 0; i < NUM_ALLIES_BUTTONS - 1; i++)
		{
			allies_buttons[i].rect.x = ally_pos[i].x;
			allies_buttons[i].rect.y = ally_pos[i].y;
			allies_buttons[i].rect.w = 64;
			allies_buttons[i].rect.h = 70;
		}
		allies_buttons[4].rect.x = ally_pos[4].x;
		allies_buttons[4].rect.y = ally_pos[4].y;
		allies_buttons[4].rect.w = 400;
		allies_buttons[4].rect.h = 50;
	}

	return true;
}

// Called each loop iteration
bool Combat_Menu::PreUpdate()
{
	// animations
	for (size_t i = 0; i < 4; i++)
	{
		if (app->combat_manager->GetEnemyByNumber(i)->GetEntityState() == 1) // alive
		{
			switch (app->combat_manager->GetEnemyByNumber(i)->GetType())
			{
			case 4:
				if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &templarAnim)
				{
					app->combat_manager->GetEnemyByNumber(i)->current_anim = &templarAnim;
				}
				break;
			case 5:
				if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &mushroomAnim)
				{
					app->combat_manager->GetEnemyByNumber(i)->current_anim = &mushroomAnim;
				}
				break;
			case 6:
				if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &goblinAnim)
				{
					app->combat_manager->GetEnemyByNumber(i)->current_anim = &goblinAnim;
				}
				break;
			case 7:
				if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &skeletonAnim)
				{
					app->combat_manager->GetEnemyByNumber(i)->current_anim = &skeletonAnim;
				}
				break;
			case 8:
				if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &templarAnim)
				{
					app->combat_manager->GetEnemyByNumber(i)->current_anim = &templarAnim;
				}
				break;
			case 9:
				if (skill_prepared.zero_mana && skill_prepared.owner == 9)
				{
					if (dragon_ultAnim.HasFinished())
					{
						dragon_ultAnim.Reset();
						CleanSkillPrepared();
						if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &dragon_idleAnim)
						{
							dragon_idleAnim.Reset();
							app->combat_manager->GetEnemyByNumber(i)->current_anim = &dragon_idleAnim;
						}
					}
					else
					{
						if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &dragon_ultAnim)
						{
							app->combat_manager->GetEnemyByNumber(i)->current_anim = &dragon_ultAnim;
						}
					}
				}
				else
				{
					if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &dragon_idleAnim)
					{
						dragon_idleAnim.Reset();
						app->combat_manager->GetEnemyByNumber(i)->current_anim = &dragon_idleAnim;
					}
				}
				break;
			case 10:
				if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &theseionAnim)
				{
					app->combat_manager->GetEnemyByNumber(i)->current_anim = &theseionAnim;
				}
				break;
			case 11:
				if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &theseionAnim)
				{
					app->combat_manager->GetEnemyByNumber(i)->current_anim = &theseionAnim;
				}
				break;
			case 12:
				if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &armoredAnim)
				{
					app->combat_manager->GetEnemyByNumber(i)->current_anim = &armoredAnim;
				}
				break;
			default:
				if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &idleAnim)
				{
					app->combat_manager->GetEnemyByNumber(i)->current_anim = &idleAnim;
				}
				break;
			}
		}
		else
		{
			if (app->combat_manager->GetEnemyByNumber(i)->current_anim != &idleAnim)
			{
				app->combat_manager->GetEnemyByNumber(i)->current_anim = &idleAnim;
			}
		}
	}

	if (in_description && (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP))
	{
		in_description = false;
	}

	if (!app->menu->GetGameState() && allies_turn && !app->menu->scape && !in_description)
	{
		int x, y;
		x = app->frontground->c_mouse_pos.x;
		y = app->frontground->c_mouse_pos.y;
		//app->input->GetMousePosition(x, y);
		float cx = -app->render->camera.x;
		float cy = -app->render->camera.y;

		if (!in_items && !in_enemies && !in_allies)
		{
			for (size_t i = 0; i < NUM_BUTTONS; i++)
			{
				SDL_Rect rect = general_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					if (i < 4 && app->combat_manager->GetActualEntity()->GetActualMana() < app->combat_manager->GetActualEntity()->GetSkill(i).mana_cost)
					{
						chosed = i;
						general_buttons[i].state = 3;
					}
					else if (i < 4 && std::string(app->combat_manager->GetActualEntity()->GetSkill(i).skill_name) == "no skill")
					{
						general_buttons[i].state = 0;
					}
					else
					{
						chosed = i;
						general_buttons[i].state = 1;
					}
				}
				else
				{
					if (i < 4 && app->combat_manager->GetActualEntity()->GetActualMana() < app->combat_manager->GetActualEntity()->GetSkill(i).mana_cost)
					{
						general_buttons[i].state = 3;
					}
					else if (i < 4 && std::string(app->combat_manager->GetActualEntity()->GetSkill(i).skill_name) == "no skill")
					{
						general_buttons[i].state = 0;
					}
					else
					{
						general_buttons[i].state = 0;
					}
				}
			}
		}

		if (in_items && !in_enemies && !in_allies)
		{
			for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
			{
				SDL_Rect rect = items_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					if (i == 4 || app->combat_manager->GetItemUses(i) > 0)
					{
						chosed = i;
						items_buttons[i].state = 1;
					}
					else
					{
						items_buttons[i].state = 0;
					}
				}
				else
				{
					items_buttons[i].state = 0;
				}
			}
		}

		if (!in_items && in_enemies && !in_allies)
		{
			for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
			{
				SDL_Rect rect = enemies_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					chosed = i;
					enemies_buttons[i].state = 1;
				}
				else
				{
					enemies_buttons[i].state = 0;
				}
			}
			if (skill_prepared.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
			{
				if ((enemies_buttons[0].state == 1 && app->combat_manager->GetEnemyByNumber(0)->GetEntityState() == 1) ||
					(enemies_buttons[1].state == 1 && app->combat_manager->GetEnemyByNumber(1)->GetEntityState() == 1) ||
					(enemies_buttons[2].state == 1 && app->combat_manager->GetEnemyByNumber(2)->GetEntityState() == 1) ||
					(enemies_buttons[3].state == 1 && app->combat_manager->GetEnemyByNumber(3)->GetEntityState() == 1))
				{
					for (size_t i = 0; i < 4; i++)
					{
						enemies_buttons[i].state = 1;
					}
				}
			}
			for (size_t i = 0; i < 4; i++)
			{
				// if enemy dead
				if (app->combat_manager->GetEnemyByNumber(i)->GetEntityState() != 1)
				{
					enemies_buttons[i].state = 0;
				}

				BUFF b;
				// if one enemy taunt
				b.buff_type = BUFF_TYPE::TAUNT;
				if (app->combat_manager->GetEnemyByNumber(i)->FindBuff(b) != -1 && skill_prepared.enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
				{
					for (size_t j = 0; j < 4; j++)
					{
						if (j != i && app->combat_manager->GetEnemyByNumber(j)->FindBuff(b) == -1)
						{
							enemies_buttons[j].state = 0;
						}
					}
				}
				// if one enemy stealth
				b.buff_type = BUFF_TYPE::STEALTH;
				if (app->combat_manager->GetEnemyByNumber(i)->FindBuff(b) != -1 && enemies_buttons[i].state == 1
					&& skill_prepared.enemy_objective != ENEMY_OBJECTIVE::ALL_ENEMY)
				{
					enemies_buttons[i].state = 3;

					if ((app->combat_manager->GetEnemyByNumber(0)->FindBuff(b) != -1 || app->combat_manager->GetEnemyByNumber(0)->GetEntityState() != 1)
						&& (app->combat_manager->GetEnemyByNumber(1)->FindBuff(b) != -1 || app->combat_manager->GetEnemyByNumber(1)->GetEntityState() != 1)
						&& (app->combat_manager->GetEnemyByNumber(2)->FindBuff(b) != -1 || app->combat_manager->GetEnemyByNumber(2)->GetEntityState() != 1)
						&& (app->combat_manager->GetEnemyByNumber(3)->FindBuff(b) != -1 || app->combat_manager->GetEnemyByNumber(3)->GetEntityState() != 1))
					{
						enemies_buttons[i].state = 1;
					}
				}
			}
		}

		if (!in_items && !in_enemies && in_allies)
		{
			for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
			{
				SDL_Rect rect = allies_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					chosed = i;
					allies_buttons[i].state = 1;
				}
				else
				{
					allies_buttons[i].state = 0;
				}
			}
			if (skill_prepared.ally_objective == ALLY_OBJECTIVE::ALL_ALLY && skill_prepared.enemy_objective == ENEMY_OBJECTIVE::NOTHING)
			{
				if (allies_buttons[0].state == 1 || allies_buttons[1].state == 1 || allies_buttons[2].state == 1 || allies_buttons[3].state == 1)
				{
					for (size_t i = 0; i < 4; i++)
					{
						allies_buttons[i].state = 1;
					}
				}
			}
			else if (skill_prepared.ally_objective == ALLY_OBJECTIVE::SELF && skill_prepared.enemy_objective == ENEMY_OBJECTIVE::NOTHING)
			{
				if (allies_buttons[skill_prepared.owner].state != 1)
				{
					for (size_t i = 0; i < 4; i++)
					{
						allies_buttons[i].state = 0;
					}
				}
			}
			for (size_t i = 0; i < 4; i++)
			{
				if (app->combat_manager->GetAllyByNumber(i)->GetEntityState() != 1 && skill_prepared.support_type != SUPPORT_TYPE::REVIVE)
				{
					allies_buttons[i].state = 0;
				}
				else if (app->combat_manager->GetAllyByNumber(i)->GetEntityState() == 1 && skill_prepared.support_type == SUPPORT_TYPE::REVIVE)
				{
					allies_buttons[i].state = 0;
				}
			}
		}

		// enemy description
		int e = 0;
		for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
		{
			SDL_Rect rect = enemies_buttons[i].rect;
			if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
			{
				enemy_chosed = i;
				e++;
			}
			else if (e == 0)
			{
				enemy_chosed = -1;
			}
		}

		// ally description
		int a = 0;
		for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
		{
			SDL_Rect rect = allies_buttons[i].rect;
			if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
			{
				ally_chosed = i;
				a++;
			}
			else if (a == 0)
			{
				ally_chosed = -1;
			}
		}
	}
	else if (app->menu->GetGameState() || app->menu->scape || in_description)
	{
		for (size_t i = 0; i < NUM_BUTTONS; i++)
		{
			general_buttons[i].state = 0;
		}

		for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
		{
			items_buttons[i].state = 0;
		}

		for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
		{
			enemies_buttons[i].state = 0;
		}

		for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
		{
			allies_buttons[i].state = 0;
		}
	}
	

	if (prep_in_items == 1)
	{
		in_items = false;
		prep_in_items = 0;
		for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
		{
			items_buttons[i].state = 0;
		}
		if (app->frontground->controller)
		{
			general_buttons[0].state = 1;
			chosed = 0;
		}
	}
	else if (prep_in_items == 2)
	{
		in_items = true;
		prep_in_items = 0;
		in_action = true;
		for (size_t i = 0; i < NUM_BUTTONS; i++)
		{
			general_buttons[i].state = 0;
		}
		if (app->frontground->controller)
		{
			items_buttons[0].state = 1;
			chosed = 0;
		}
	}
	if (prep_in_enemies == 1)
	{
		in_enemies = false;
		prep_in_enemies = false;
		in_action = false;
		for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
		{
			enemies_buttons[i].state = 0;
		}
		if (app->frontground->controller)
		{
			general_buttons[0].state = 1;
			chosed = 0;
		}
	}
	else if (prep_in_enemies == 2)
	{
		in_enemies = true;
		prep_in_enemies = 0;
		in_action = true;
		for (size_t i = 0; i < NUM_BUTTONS; i++)
		{
			general_buttons[i].state = 0;
		}
		if (app->frontground->controller)
		{
			if (app->combat_manager->GetEnemyByNumber(0)->GetEntityState() == 1)
			{
				enemies_buttons[0].state = 1;
				chosed = 0;
			}
			else
			{
				if (app->combat_manager->GetEnemyByNumber(1)->GetEntityState() == 1)
				{
					enemies_buttons[1].state = 1;
					chosed = 1;
				}
				else
				{
					if (app->combat_manager->GetEnemyByNumber(2)->GetEntityState() == 1)
					{
						enemies_buttons[2].state = 1;
						chosed = 2;
					}
				}
			}
		}
	}
	if (prep_in_allies == 1)
	{
		in_allies = false;
		prep_in_allies = false;
		in_action = false;
		for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
		{
			allies_buttons[i].state = 0;
		}
		if (app->frontground->controller)
		{
			general_buttons[0].state = 1;
			chosed = 0;
		}
	}
	else if (prep_in_allies == 2)
	{
		in_allies = true;
		prep_in_allies = 0;
		in_action = true;
		for (size_t i = 0; i < NUM_BUTTONS; i++)
		{
			general_buttons[i].state = 0;
		}

		if (app->frontground->controller)
		{
			if (app->combat_manager->GetAllyByNumber(0)->GetEntityState() == 1)
			{
				allies_buttons[0].state = 1;
				chosed = 0;
			}
			else
			{
				if (app->combat_manager->GetAllyByNumber(1)->GetEntityState() == 1)
				{
					allies_buttons[1].state = 1;
					chosed = 1;
				}
				else
				{
					if (app->combat_manager->GetAllyByNumber(2)->GetEntityState() == 1)
					{
						allies_buttons[2].state = 1;
						chosed = 2;
					}
				}
			}
		}
	}

	if (app->combat_manager->GetInAnimation() == 1)
	{
		app->combat_manager->SetInAnimation(2);
	}

	preupdatedone = true;

	return true;
}

// Called each loop iteration
bool Combat_Menu::Update(float dt)
{
	if (!preupdatedone)
	{
		return true;
	}

	if (allies_turn)
	{
		// general buttons
		if (!in_items && !in_enemies && !in_allies)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && general_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//prepare attack 1
					if (app->combat_manager->GetActualEntity()->GetSkill(0).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY || 
						app->combat_manager->GetActualEntity()->GetSkill(0).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						prep_in_enemies = 2;
					}
					else
					{
						prep_in_allies = 2;
					}
					skill_prepared = app->combat_manager->GetActualEntity()->GetSkill(0);
					break;
				case 1:
					//prepare attack 2
					if (app->combat_manager->GetActualEntity()->GetSkill(1).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY ||
						app->combat_manager->GetActualEntity()->GetSkill(1).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						prep_in_enemies = 2;
					}
					else
					{
						prep_in_allies = 2;
					}
					skill_prepared = app->combat_manager->GetActualEntity()->GetSkill(1);
					break;
				case 2:
					//prepare attack 3
					if (app->combat_manager->GetActualEntity()->GetSkill(2).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY ||
						app->combat_manager->GetActualEntity()->GetSkill(2).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						prep_in_enemies = 2;
					}
					else
					{
						prep_in_allies = 2;
					}
					skill_prepared = app->combat_manager->GetActualEntity()->GetSkill(2);
					break;
				case 3:
					//prepare attack 4
					if (app->combat_manager->GetActualEntity()->GetSkill(3).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY ||
						app->combat_manager->GetActualEntity()->GetSkill(3).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						prep_in_enemies = 2;
					}
					else
					{
						prep_in_allies = 2;
					}
					skill_prepared = app->combat_manager->GetActualEntity()->GetSkill(3);
					break;
				case 4:
					//reload mana
					app->combat_manager->GetActualEntity()->ReloadMana();
					skill_prepared.skill_name = "reload";
					app->combat_manager->SetInAnimation(1);
					SetSkillAnimation(ATT_EFFECT::EMPTY, SUPP_EFFECT::EMPTY, 0, 0);
					break;
				case 5:
					//open item menu
					prep_in_items = 2;
					break;
				case 6:
					//scape
					app->menu->SetWinLoseScape(2);
					break;
				}

				if ((chosed == 4 || chosed == 6) && app->frontground->controller)
				{
					general_buttons[chosed].state = 0;
					general_buttons[0].state = 1;
					chosed = 0;
				}
				else
				{
					general_buttons[chosed].state = 2;
				}
			}
			else if ((app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && (general_buttons[chosed].state == 1 || general_buttons[chosed].state == 3))
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//attack 1 description
					in_description = true;
					description_type = 1;
					desc_skill = app->combat_manager->GetActualEntity()->GetSkill(0);
					break;
				case 1:
					//attack 2 description
					in_description = true;
					description_type = 1;
					desc_skill = app->combat_manager->GetActualEntity()->GetSkill(1);
					break;
				case 2:
					//attack 3 description
					in_description = true;
					description_type = 1;
					desc_skill = app->combat_manager->GetActualEntity()->GetSkill(2);
					break;
				case 3:
					//attack 4 description
					in_description = true;
					description_type = 1;
					desc_skill = app->combat_manager->GetActualEntity()->GetSkill(3);
					break;
				}
			}
		}

		//items buttons
		if (in_items && !in_enemies && !in_allies)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && items_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//prepare item 1
					if (app->combat_manager->GetItemList()->GetSkill(0).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY ||
						app->combat_manager->GetItemList()->GetSkill(0).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						prep_in_enemies = 2;
					}
					else
					{
						prep_in_allies = 2;
					}
					skill_prepared = app->combat_manager->GetItemList()->GetSkill(0);
					skill_prepared_is_item = 0;
					break;
				case 1:
					//prepare item 2
					if (app->combat_manager->GetItemList()->GetSkill(1).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY ||
						app->combat_manager->GetItemList()->GetSkill(1).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						prep_in_enemies = 2;
					}
					else
					{
						prep_in_allies = 2;
					}
					skill_prepared = app->combat_manager->GetItemList()->GetSkill(1);
					skill_prepared_is_item = 1;
					break;
				case 2:
					//prepare item 3
					if (app->combat_manager->GetItemList()->GetSkill(2).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY ||
						app->combat_manager->GetItemList()->GetSkill(2).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						prep_in_enemies = 2;
					}
					else
					{
						prep_in_allies = 2;
					}
					skill_prepared = app->combat_manager->GetItemList()->GetSkill(2);
					skill_prepared_is_item = 2;
					break;
				case 3:
					//prepare item 4
					if (app->combat_manager->GetItemList()->GetSkill(3).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY ||
						app->combat_manager->GetItemList()->GetSkill(3).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						prep_in_enemies = 2;
					}
					else
					{
						prep_in_allies = 2;
					}
					skill_prepared = app->combat_manager->GetItemList()->GetSkill(3);
					skill_prepared_is_item = 3;
					break;
				case 4:
					in_action = false;
				break;
				}

				prep_in_items = 1;
				items_buttons[chosed].state = 2;
			}
			else if ((app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && items_buttons[chosed].state == 1 && chosed != 4)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//attack 1 description
					in_description = true;
					description_type = 1;
					desc_skill = app->combat_manager->GetItemList()->GetSkill(0);
					break;
				case 1:
					//attack 2 description
					in_description = true;
					description_type = 1;
					desc_skill = app->combat_manager->GetItemList()->GetSkill(1);
					break;
				case 2:
					//attack 3 description
					in_description = true;
					description_type = 1;
					desc_skill = app->combat_manager->GetItemList()->GetSkill(2);
					break;
				case 3:
					//attack 4 description
					in_description = true;
					description_type = 1;
					desc_skill = app->combat_manager->GetItemList()->GetSkill(3);
					break;
				}
			}
		}

		//enemies buttons
		if (!in_items && in_enemies && !in_allies)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && enemies_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//choose enemy 1
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(0));
					if (skill_prepared_is_item != -1)
					{
						UseItem(skill_prepared_is_item);
						skill_prepared_is_item = -1;
					}
					break;
				case 1:
					//choose enemy 2
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(1));
					if (skill_prepared_is_item != -1)
					{
						UseItem(skill_prepared_is_item);
						skill_prepared_is_item = -1;
					}
					break;
				case 2:
					//choose enemy 3
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(2));
					if (skill_prepared_is_item != -1)
					{
						UseItem(skill_prepared_is_item);
						skill_prepared_is_item = -1;
					}
					break;
				case 3:
					//choose enemy 4
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(3));
					if (skill_prepared_is_item != -1)
					{
						UseItem(skill_prepared_is_item);
						skill_prepared_is_item = -1;
					}
					break;
				case 4:
					//cancel action
					if (skill_prepared_is_item != -1)
					{
						skill_prepared_is_item = -1;
					}
					break;
				}

				prep_in_enemies = 1;
				enemies_buttons[chosed].state = 2;
			}
		}

		//allies buttons
		if (!in_items && !in_enemies && in_allies)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && allies_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//choose ally 1
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetAllyByNumber(0));
					if (skill_prepared_is_item != -1)
					{
						UseItem(skill_prepared_is_item);
						skill_prepared_is_item = -1;
					}
					break;
				case 1:
					//choose ally 2
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetAllyByNumber(1));
					if (skill_prepared_is_item != -1)
					{
						UseItem(skill_prepared_is_item);
						skill_prepared_is_item = -1;
					}
					break;
				case 2:
					//choose ally 3
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetAllyByNumber(2));
					if (skill_prepared_is_item != -1)
					{
						UseItem(skill_prepared_is_item);
						skill_prepared_is_item = -1;
					}
					break;
				case 3:
					//choose ally 4
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetAllyByNumber(3));
					if (skill_prepared_is_item != -1)
					{
						UseItem(skill_prepared_is_item);
						skill_prepared_is_item = -1;
					}
					break;
				case 4:
					//cancel action
					if (skill_prepared_is_item != -1)
					{
						skill_prepared_is_item = -1;
					}
					break;
				}

				prep_in_allies = 1;
				allies_buttons[chosed].state = 2;
			}
		}

		if ((app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && enemy_chosed != -1)
		{
			app->audio->PlayFx(click_sound);
			switch (enemy_chosed)
			{
			case 0:
				//enemy 1 description
				in_description = true;
				description_type = 0;
				desc_entity = app->combat_manager->GetEnemyByNumber(0);
				break;
			case 1:
				//enemy 2 description
				in_description = true;
				description_type = 0;
				desc_entity = app->combat_manager->GetEnemyByNumber(1);
				break;
			case 2:
				//enemy 3 description
				in_description = true;
				description_type = 0;
				desc_entity = app->combat_manager->GetEnemyByNumber(2);
				break;
			case 3:
				//enemy 4 description
				in_description = true;
				description_type = 0;
				desc_entity = app->combat_manager->GetEnemyByNumber(3);
				break;
			}
		}
		else if ((app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && ally_chosed != -1)
		{
			app->audio->PlayFx(click_sound);
			switch (ally_chosed)
			{
			case 0:
				//ally 1 description
				in_description = true;
				description_type = 0;
				desc_entity = app->combat_manager->GetAllyByNumber(0);
				break;
			case 1:
				//ally 2 description
				in_description = true;
				description_type = 0;
				desc_entity = app->combat_manager->GetAllyByNumber(1);
				break;
			case 2:
				//ally 3 description
				in_description = true;
				description_type = 0;
				desc_entity = app->combat_manager->GetAllyByNumber(2);
				break;
			case 3:
				//ally 4 description
				in_description = true;
				description_type = 0;
				desc_entity = app->combat_manager->GetAllyByNumber(3);
				break;
			}
		}
	}

	// animations
	currentAnimation->Update();
	for (size_t i = 0; i < 4; i++)
	{
		app->combat_manager->GetEnemyByNumber(i)->current_anim->Update();
	}

	updatedone = true;

	return true;
}

// Called each loop iteration
bool Combat_Menu::PostUpdate()
{
	if (!updatedone)
	{
		return true;
	}

	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;

	SDL_Rect r = currentAnimation->GetCurrentFrame();
	SDL_Texture* texture = NULL;

	for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
	{
		enemies_buttons[i].rect.x = enemy_pos[i].x + c_x;
		enemies_buttons[i].rect.y = enemy_pos[i].y + c_y;

		if (i != 4)
		{
			if (app->combat_manager->GetEnemyByNumber(i)->GetEntityState() == 1)
			{
				switch (app->combat_manager->GetEnemyByNumber(i)->GetType())
				{
				case 4:
					texture = white_templar;
					r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 20, enemies_buttons[i].rect.y - 40, &r);
					break;
				case 5:
					texture = mushroom;
					r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 20, enemies_buttons[i].rect.y - 50, &r);
					break;
				case 6:
					texture = goblin;
					r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y - 10, &r);
					break;
				case 7:
					texture = skeleton;
					r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 75, enemies_buttons[i].rect.y - 110, &r);
					break;
				case 8:
					texture = red_templar;
					r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 20, enemies_buttons[i].rect.y - 40, &r);
					break;
				case 9:
					if (app->combat_manager->GetEnemyByNumber(i)->current_anim == &dragon_ultAnim)
					{
						texture = dragon_ult;
						r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
						app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 225, enemies_buttons[i].rect.y - 300, &r);
					}
					else
					{
						texture = dragon_idle;
						r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
						app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 80, enemies_buttons[i].rect.y - 150, &r);
					}
					break;
				case 10:
					texture = theseion;
					r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x + 5, enemies_buttons[i].rect.y + 5, &r);
					break;
				case 11:
					texture = theseion;
					r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x + 5, enemies_buttons[i].rect.y + 5, &r);
					break;
				case 12:
					texture = armored_templar;
					r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 80, enemies_buttons[i].rect.y - 50, &r);
					break;
				default:
					texture = assassin_texture;
					r = currentAnimation->GetCurrentFrame();
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &r);
					break;
				}
			}
			else if (app->combat_manager->GetEnemyByNumber(i)->GetEntityState() == 0)
			{
				texture = tombstone;
				SDL_Rect dre = { 64, 0, 64, 64 };
				app->render->DrawTexture(texture, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &dre);
			}
		}
	}

	r = currentAnimation->GetCurrentFrame();
	for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
	{
		allies_buttons[i].rect.x = ally_pos[i].x + c_x;
		allies_buttons[i].rect.y = ally_pos[i].y + c_y;

		if (i != 4)
		{
			if (app->combat_manager->GetAllyByNumber(i)->GetEntityState() == 1)
			{
				switch (i)
				{
				case 0: texture = assassin_texture;
					break;
				case 1: texture = healer_texture;
					break;
				case 2: texture = tank_texture;
					break;
				case 3: texture = wizard_texture;
					break;
				}

				app->render->DrawTexture(texture, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &r);
			}
			else if (app->combat_manager->GetAllyByNumber(i)->GetEntityState() == 0)
			{
				texture = tombstone;
				SDL_Rect dra = { 0, 0, 64, 64 };
				app->render->DrawTexture(texture, allies_buttons[i].rect.x, allies_buttons[i].rect.y + 5, &dra);
			}
		}
	}

	SDL_Rect casting_rect = { 0, 0, 64, 64 };
	if (!allies_turn && !app->frontground->fast_combat)
	{
		app->render->DrawTexture(casting, app->combat_manager->GetActualEntity()->position.x, app->combat_manager->GetActualEntity()->position.y, &app->combat_manager->GetCastingRect());
	}
	else if (!allies_turn && app->frontground->fast_combat)
	{
		casting_rect = { 192, 0, 64, 64 };
		app->render->DrawTexture(casting, app->combat_manager->GetActualEntity()->position.x, app->combat_manager->GetActualEntity()->position.y, &casting_rect);
	}
	else if (allies_turn)
	{
		casting_rect = { 256, 0, 64, 64 };
		app->render->DrawTexture(casting, app->combat_manager->GetActualEntity()->position.x, app->combat_manager->GetActualEntity()->position.y, &casting_rect);
	}

	if (allies_turn && app->combat_manager->GetInAnimation() != 2)
	{
		if (!in_items && !in_enemies && !in_allies)
		{
			SDL_Rect g_rect;
			for (size_t i = 0; i < NUM_BUTTONS; i++)
			{
				general_buttons[i].rect.x = action_pos[i].x + c_x;
				general_buttons[i].rect.y = action_pos[i].y + c_y;

				if (i < 4)
				{
					if (general_buttons[i].state == 1 && !in_action)
					{
						g_rect = { 0, 50, 400, 50 };
					}
					else if (general_buttons[i].state == 2 && !in_action)
					{
						g_rect = { 0, 100, 400, 50 };
					}
					else if (general_buttons[i].state == 3)
					{
						g_rect = { 0, 100, 400, 50 };
					}
					else if (general_buttons[i].state == 0)
					{
						switch (app->combat_manager->GetActualEntity()->GetSkill(i).element)
						{
						case 0: g_rect = { 0, 0, 400, 50 };
							  break;
						case 1: g_rect = { 0, 150, 400, 50 };
							  break;
						case 2: g_rect = { 0, 250, 400, 50 };
							  break;
						case 3: g_rect = { 0, 200, 400, 50 };
							  break;
						case 4: g_rect = { 0, 300, 400, 50 };
							  break;
						}
					}

					texture = whitemark_400x50;
				}
				else
				{
					if (general_buttons[i].state == 1 && !in_action)
					{
						g_rect = { 0, 110, 110, 110 };
					}
					else if (general_buttons[i].state == 2 && !in_action)
					{
						g_rect = { 0, 220, 110, 110 };
					}
					else if (general_buttons[i].state == 0)
					{
						g_rect = { 0, 0, 110, 110 };
					}
					texture = whitemark_110x110;
				}
				app->render->DrawTexture(texture, general_buttons[i].rect.x, general_buttons[i].rect.y, &g_rect);
			}

			SDL_Rect sp_rect;
			for (size_t i = 0; i < 4; i++)
			{
				general_buttons[i].rect.x = action_pos[i].x + c_x;
				general_buttons[i].rect.y = action_pos[i].y + c_y;

				app->fonts->BlitCombatText(general_buttons[i].rect.x, general_buttons[i].rect.y + 10, app->fonts->textFont2, app->combat_manager->GetActualEntity()->GetSkill(i).skill_name);
				
				if (app->combat_manager->GetActualEntity()->GetSkill(i).enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
				{
					sp_rect = { 40, 0, 40, 40 };
				}
				else if (app->combat_manager->GetActualEntity()->GetSkill(i).enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
				{
					sp_rect = { 0, 0, 40, 40 };
				}
				else if (app->combat_manager->GetActualEntity()->GetSkill(i).ally_objective == ALLY_OBJECTIVE::ONE_ALLY)
				{
					sp_rect = { 120, 0, 40, 40 };
				}
				else if (app->combat_manager->GetActualEntity()->GetSkill(i).ally_objective == ALLY_OBJECTIVE::ALL_ALLY)
				{
					sp_rect = { 80, 0, 40, 40 };
				}
				else if (app->combat_manager->GetActualEntity()->GetSkill(i).ally_objective == ALLY_OBJECTIVE::SELF)
				{
					sp_rect = { 160, 0, 40, 40 };
				}
				app->render->DrawTexture(skills_icons, general_buttons[i].rect.x + 350, general_buttons[i].rect.y + 5, &sp_rect);
			}
			for (size_t i = 4; i < 7; i++)
			{
				general_buttons[i].rect.x = action_pos[i].x + c_x;
				general_buttons[i].rect.y = action_pos[i].y + c_y;

				switch (i)
				{
				case 4: sp_rect = { 0, 0, 110, 110 }; break;
				case 5: sp_rect = { 110, 0, 110, 110 }; break;
				case 6: sp_rect = { 220, 0, 110, 110 }; break;
				}

				app->render->DrawTexture(special_buttons, general_buttons[i].rect.x, general_buttons[i].rect.y, &sp_rect);
			}
		}

		if (in_items && !in_enemies && !in_allies)
		{
			SDL_Rect i_rect;
			SDL_Rect e_rect;
			for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
			{
				items_buttons[i].rect.x = item_pos[i].x + c_x;
				items_buttons[i].rect.y = item_pos[i].y + c_y;

				if (items_buttons[i].state == 0)
				{
					i_rect = { 0, 0, 128, 128 };
				}
				else if (items_buttons[i].state == 1)
				{
					i_rect = { 0, 128, 128, 128 };
				}
				else if (items_buttons[i].state == 2)
				{
					i_rect = { 0, 256, 128, 128 };
				}
				app->render->DrawTexture(whitemark_128x128, items_buttons[i].rect.x, items_buttons[i].rect.y, &i_rect);

				int item_num = GetItemByName(app->combat_manager->GetItemList()->GetSkill(i).skill_name);
				if (i == 4)
				{
					e_rect = { 0, 0, 128, 128 };
				}
				else if (item_num == -1)
				{
					e_rect = { 128, 0, 128, 128 };
				}
				else if(item_num == 0)
				{
					e_rect = { 256, 0, 128, 128 };
				}
				else if (item_num == 1)
				{
					e_rect = { 384, 0, 128, 128 };
				}
				else if (item_num == 2)
				{
					e_rect = { 512, 0, 128, 128 };
				}
				else if (item_num == 3)
				{
					e_rect = { 0, 128, 128, 128 };
				}
				else if (item_num == 4)
				{
					e_rect = { 128, 128, 128, 128 };
				}
				else if (item_num == 5)
				{
					e_rect = { 256, 128, 128, 128 };
				}
				else if (item_num == 6)
				{
					e_rect = { 384, 128, 128, 128 };
				}
				else if (item_num == 7)
				{
					e_rect = { 512, 128, 128, 128 };
				}

				app->render->DrawTexture(items, items_buttons[i].rect.x, items_buttons[i].rect.y, &e_rect);

				if (i != 4 && app->combat_manager->GetItemUses(i) == 0)
				{
					e_rect = { 128, 0, 128, 128 };
					app->render->DrawTexture(items, items_buttons[i].rect.x, items_buttons[i].rect.y, &e_rect);
				}

				if (item_num > -1 && app->combat_manager->GetItemUses(i) > 0)
				{
					app->fonts->BlitCombatText(items_buttons[i].rect.x + 100, items_buttons[i].rect.y + 100, app->fonts->textFont2, std::to_string(app->combat_manager->GetItemUses(i)).c_str());
				}
			}
		}

		if (!in_items && in_enemies && !in_allies)
		{
			SDL_Rect e_rect;
			for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
			{
				if (enemies_buttons[i].state == 1)
				{
					// aiming sprites
					if (i == 4)
					{
						//app->render->DrawRectangle(enemies_buttons[i].rect, inColorR, inColorG, inColorB);
						e_rect = { 0, 50, 400, 50 };
						app->render->DrawTexture(whitemark_400x50, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &e_rect);
					}
					else
					{
						SDL_Rect rect = { 0, 0, 64, 64 };
						app->render->DrawTexture(target, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &rect);
					}
				}
				else if (enemies_buttons[i].state == 2)
				{
					// fire sprites
					if (i == 4)
					{
						//app->render->DrawRectangle(enemies_buttons[i].rect, pColorR, pColorG, pColorB);
						e_rect = { 0, 100, 400, 50 };
						app->render->DrawTexture(whitemark_400x50, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &e_rect);
					}
					else
					{
						SDL_Rect rect = { 64, 0, 64, 64 };
						app->render->DrawTexture(target, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &rect);
					}
				}
				else if (enemies_buttons[i].state == 3)
				{
					// no selectable sprites
					SDL_Rect rect = { 256, 0, 64, 64 };
					app->render->DrawTexture(target, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &rect);
				}
				else if (enemies_buttons[i].state == 0 && i == 4)
				{
					//app->render->DrawRectangle(enemies_buttons[i].rect, idleColorR, idleColorG, idleColorB);
					switch (skill_prepared.element)
					{
					case 0: e_rect = { 0, 0, 400, 50 };
						  break;
					case 1: e_rect = { 0, 150, 400, 50 };
						  break;
					case 2: e_rect = { 0, 250, 400, 50 };
						  break;
					case 3: e_rect = { 0, 200, 400, 50 };
						  break;
					case 4: e_rect = { 0, 300, 400, 50 };
						  break;
					}
					app->render->DrawTexture(whitemark_400x50, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &e_rect);
				}

				if (i == 4)
				{
					app->fonts->BlitCombatText(enemies_buttons[i].rect.x, enemies_buttons[i].rect.y + 10, app->fonts->textFont2, skill_prepared.skill_name);
				
					if (skill_prepared.enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
					{
						e_rect = { 40, 0, 40, 40 };
					}
					else if (skill_prepared.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						e_rect = { 0, 0, 40, 40 };
					}
					else if (skill_prepared.ally_objective == ALLY_OBJECTIVE::ONE_ALLY)
					{
						e_rect = { 120, 0, 40, 40 };
					}
					else if (skill_prepared.ally_objective == ALLY_OBJECTIVE::ALL_ALLY)
					{
						e_rect = { 80, 0, 40, 40 };
					}
					else if (skill_prepared.ally_objective == ALLY_OBJECTIVE::SELF)
					{
						e_rect = { 160, 0, 40, 40 };
					}
					app->render->DrawTexture(skills_icons, enemies_buttons[i].rect.x + 350, enemies_buttons[i].rect.y + 5, &e_rect);
				}
			}
		}

		if (!in_items && !in_enemies && in_allies)
		{
			for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
			{
				SDL_Rect a_rect;
				if (allies_buttons[i].state == 1)
				{
					// aiming sprites
					if (i == 4)
					{
						//app->render->DrawRectangle(allies_buttons[i].rect, inColorR, inColorG, inColorB);
						a_rect = { 0, 50, 400, 50 };
						app->render->DrawTexture(whitemark_400x50, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &a_rect);
					}
					else
					{
						SDL_Rect rect = { 128, 0, 64, 64 };
						app->render->DrawTexture(target, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &rect);
					}
				}
				else if (allies_buttons[i].state == 2)
				{
					// fire sprites
					if (i == 4)
					{
						//app->render->DrawRectangle(allies_buttons[i].rect, pColorR, pColorG, pColorB);
						a_rect = { 0, 100, 400, 50 };
						app->render->DrawTexture(whitemark_400x50, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &a_rect);
					}
					else
					{
						SDL_Rect rect = { 192, 0, 64, 64 };
						app->render->DrawTexture(target, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &rect);
					}
				}
				else if (allies_buttons[i].state == 0 && i == 4)
				{
					//app->render->DrawRectangle(allies_buttons[i].rect, idleColorR, idleColorG, idleColorB);
					switch (skill_prepared.element)
					{
					case 0: a_rect = { 0, 0, 400, 50 };
						  break;
					case 1: a_rect = { 0, 150, 400, 50 };
						  break;
					case 2: a_rect = { 0, 250, 400, 50 };
						  break;
					case 3: a_rect = { 0, 200, 400, 50 };
						  break;
					case 4: a_rect = { 0, 300, 400, 50 };
						  break;
					}
					app->render->DrawTexture(whitemark_400x50, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &a_rect);
				}

				if (i == 4)
				{
					app->fonts->BlitCombatText(allies_buttons[i].rect.x, allies_buttons[i].rect.y + 15, app->fonts->textFont2, skill_prepared.skill_name);
				
					if (skill_prepared.enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
					{
						a_rect = { 40, 0, 40, 40 };
					}
					else if (skill_prepared.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						a_rect = { 0, 0, 40, 40 };
					}
					else if (skill_prepared.ally_objective == ALLY_OBJECTIVE::ONE_ALLY)
					{
						a_rect = { 120, 0, 40, 40 };
					}
					else if (skill_prepared.ally_objective == ALLY_OBJECTIVE::ALL_ALLY)
					{
						a_rect = { 80, 0, 40, 40 };
					}
					else if (skill_prepared.ally_objective == ALLY_OBJECTIVE::SELF)
					{
						a_rect = { 160, 0, 40, 40 };
					}
					app->render->DrawTexture(skills_icons, allies_buttons[i].rect.x + 350, allies_buttons[i].rect.y + 5, &a_rect);
				}
			}
		}
	}
	else if (app->combat_manager->GetInAnimation() == 2 && skill_prepared.skill_name != "null")
	{
		if (skill_prepared.owner ==  9 && skill_prepared.zero_mana)
		{

		}

		SDL_Rect r_text = { 0, 0, 400, 50 };
		app->render->DrawTexture(whitemark_400x50, 415 + c_x, 660 + c_y, &r_text);
		app->fonts->BlitCombatText(415 + c_x, 660 + c_y + 10, app->fonts->textFont2, skill_prepared.skill_name);

		if (skill_att_effect != ATT_EFFECT::EMPTY)
		{
			// fx
			switch (skill_att_effect)
			{
			case ATT_EFFECT::PHYSIC: PlaySkillFx(0);
				break;
			case ATT_EFFECT::FIRE: PlaySkillFx(1);
				break;
			case ATT_EFFECT::LIGHTNING: PlaySkillFx(2);
				break;
			case ATT_EFFECT::WATER: PlaySkillFx(3);
				break;
			default:
				break;
			}

			if (skill_prepared.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
			{
				if (skill_prepared.owner < 4)
				{
					for (size_t i = 0; i < 4; i++)
					{
						if (app->combat_manager->GetEnemyByNumber(i)->GetEntityState() == 1)
						{
							app->particles->PlayParticle(skill_att_effect, SUPP_EFFECT::EMPTY, enemies_buttons[i].rect.x - 32, enemies_buttons[i].rect.y - 32);
						}
					}
				}
				else
				{
					for (size_t i = 0; i < 4; i++)
					{
						if (app->combat_manager->GetAllyByNumber(i)->GetEntityState() == 1)
						{
							app->particles->PlayParticle(skill_att_effect, SUPP_EFFECT::EMPTY, allies_buttons[i].rect.x - 32, allies_buttons[i].rect.y - 32);
						}
					}
				}
			}
			else
			{
				app->particles->PlayParticle(skill_att_effect, SUPP_EFFECT::EMPTY, objective_pos.x - 32, objective_pos.y - 32);
			}
		}
		if (skill_supp_effect != SUPP_EFFECT::EMPTY)
		{
			// fx
			switch (skill_supp_effect)
			{
			case SUPP_EFFECT::HEAL: PlaySkillFx(4);
				break;
			case SUPP_EFFECT::BUFF: PlaySkillFx(5);
				break;
			}
			
			if (skill_prepared.ally_objective == ALLY_OBJECTIVE::ALL_ALLY)
			{
				if (skill_prepared.owner < 4)
				{
					for (size_t i = 0; i < 4; i++)
					{
						if (app->combat_manager->GetAllyByNumber(i)->GetEntityState() == 1)
						{
							app->particles->PlayParticle(ATT_EFFECT::EMPTY, skill_supp_effect, allies_buttons[i].rect.x - 32, allies_buttons[i].rect.y - 32);
						}
					}
				}
				else
				{
					for (size_t i = 0; i < 4; i++)
					{
						if (app->combat_manager->GetEnemyByNumber(i)->GetEntityState() == 1)
						{
							app->particles->PlayParticle(ATT_EFFECT::EMPTY, skill_supp_effect, enemies_buttons[i].rect.x - 32, enemies_buttons[i].rect.y - 32);
						}
					}
				}
			}
			else if (skill_prepared.enemy_objective != ENEMY_OBJECTIVE::NOTHING && skill_prepared.ally_objective == ALLY_OBJECTIVE::SELF)
			{
				app->particles->PlayParticle(ATT_EFFECT::EMPTY, skill_supp_effect, app->combat_manager->GetActualEntity()->position.x - 32, app->combat_manager->GetActualEntity()->position.y - 32);
			}
			else
			{
				app->particles->PlayParticle(ATT_EFFECT::EMPTY, skill_supp_effect, objective_pos.x - 32, objective_pos.y - 32);
			}
		}

		SetSkillAnimation(ATT_EFFECT::EMPTY, SUPP_EFFECT::EMPTY, 0, 0);
	}

	app->combat_manager->UpdateHUD();

	return true;
}

// Called before quitting
bool Combat_Menu::CleanUp()
{
	// clean textures
	app->tex->UnLoad(assassin_texture);
	assassin_texture = NULL;
	app->tex->UnLoad(tank_texture);
	tank_texture = NULL;
	app->tex->UnLoad(healer_texture);
	healer_texture = NULL;
	app->tex->UnLoad(wizard_texture);
	wizard_texture = NULL;
	app->tex->UnLoad(target);
	target = NULL;
	app->tex->UnLoad(tombstone);
	tombstone = NULL;
	app->tex->UnLoad(goblin);
	goblin = NULL;
	app->tex->UnLoad(skeleton);
	skeleton = NULL;
	app->tex->UnLoad(mushroom);
	mushroom = NULL;
	app->tex->UnLoad(white_templar);
	white_templar = NULL;
	app->tex->UnLoad(red_templar);
	red_templar = NULL;
	app->tex->UnLoad(whitemark_400x50);
	whitemark_400x50 = NULL;
	app->tex->UnLoad(whitemark_110x110);
	whitemark_110x110 = NULL;
	app->tex->UnLoad(whitemark_128x128);
	whitemark_128x128 = NULL;
	app->tex->UnLoad(whitemark_800x50);
	whitemark_800x50 = NULL;
	app->tex->UnLoad(special_buttons);
	special_buttons = NULL;
	app->tex->UnLoad(items);
	items = NULL;

	return true;
}

void Combat_Menu::CleanSkillPrepared()
{
	Skill clean;
	clean.skill_name = "";
	clean.owner = -1;

	SetSkillPrepared(clean);
}

iPoint Combat_Menu::GetEntityPosition(bool ally, int n)
{
	iPoint pos;

	if (ally)
	{
		pos.x = allies_buttons[n].rect.x;
		pos.y = allies_buttons[n].rect.y;
	}
	else
	{
		pos.x = enemies_buttons[n].rect.x;
		pos.y = enemies_buttons[n].rect.y;
	}

	return pos;
}

void Combat_Menu::PlaySkillFx(int n)
{
	switch (n)
	{
	case 0: app->audio->PlayFx(physic_fx);
		break;
	case 1: app->audio->PlayFx(fire_fx);
		break;
	case 2: app->audio->PlayFx(lightning_fx);
		break;
	case 3: app->audio->PlayFx(water_fx);
		break;
	case 4: app->audio->PlayFx(heal_fx);
		break;
	case 5: app->audio->PlayFx(buff_fx);
		break;
	}
}

void Combat_Menu::DisplaySkillEffects(Skill skill, int cx, int cy)
{
	int i = 0;
	SDL_Rect rect;
	std::string description0;
	std::string description1;
	const char* res;

	if (skill.buff_type != BUFF_TYPE::NOTHING)
	{
		switch (skill.buff_type)
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
			description0 = "Relax, each turn the user will be healed by a";
			description1 = "25% of this max health.";
			break;
		case BUFF_TYPE::GODMODE_STRONG:
			rect = { 64, 96, 32, 32 };
			description0 = "Grace of the Gods, increases 5 times the user";
			description1 = "power. Only the real gods can use it.";
			break;
		default:
			break;
		}

		app->render->DrawRectangle({ cx + 1, cy + 1, 30, 30 }, 104, 193, 4, 200);
		app->render->DrawTexture(app->combat_manager->status_effects, cx, cy, &rect);
		res = description0.c_str();
		app->fonts->BlitCombatText(cx + 33, cy, app->fonts->textFont2, res);
		res = description1.c_str();
		app->fonts->BlitCombatText(cx + 33, cy + 32, app->fonts->textFont2, res);
		i++;
	}

	if (skill.debuff_type != DEBUFF_TYPE::NOTHING)
	{
		switch (skill.debuff_type)
		{
		case DEBUFF_TYPE::BURN:
			rect = { 0, 32, 32, 32 };
			description0 = "Burn, the user takes a 10% of his max health";
			description1 = "as damage each turn.";
			break;
		case DEBUFF_TYPE::DEF_REDUCC:
			rect = { 32, 0, 32, 32 };
			description0 = "Defense Reduction, user will receive extra damage";
			description1 = "from physic damage.";
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
		app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i), app->fonts->textFont2, res);
		res = description1.c_str();
		app->fonts->BlitCombatText(cx + 33, cy + ((64 + 25) * i) + 32, app->fonts->textFont2, res);
	}
}

int Combat_Menu::GetItemByName(const char* skill_name)
{
	if (skill_name == NULL)
	{
		return -1;
	}
	else if (!std::strcmp(skill_name, "HP Potion"))
	{
		return 0;
	}
	else if (!std::strcmp(skill_name, "MP Potion"))
	{
		return 1;
	}
	else if (skill_name == "Fire Jar")
	{
		return 2;
	}
	else if (skill_name == "Lightning Jar")
	{
		return 3;
	}
	else if (skill_name == "Green Leaves")
	{
		return 4;
	}
	else if (skill_name == "Recarm")
	{
		return 5;
	}
	else if (skill_name == "Rainbow Grace")
	{
		return 6;
	}
	else if (skill_name == "Anti-Shield")
	{
		return 7;
	}
	else
	{
		return -1;
	}
}

void Combat_Menu::UseItem(int n)
{
	app->combat_manager->f_item_uses[n]--;
}