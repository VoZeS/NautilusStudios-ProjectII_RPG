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
#include "Particles.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

Combat_Menu::Combat_Menu() : Module()
{
	name.Create("combat_menu");

	idleAnim.PushBack({ 5, 164, 50, 72 });
	idleAnim.PushBack({ 65, 164, 50, 72 });
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

	goblinAnim.PushBack({ 0, 0, 64, 70 });
	goblinAnim.PushBack({ 64, 0, 64, 70 });
	goblinAnim.PushBack({ 128, 0, 64, 70 });
	goblinAnim.PushBack({ 192, 0, 64, 70 });
	goblinAnim.speed = 0.03f;

	skeletonAnim.PushBack({ 0, 0, 192, 210 });
	skeletonAnim.PushBack({ 192, 0, 192, 210 });
	skeletonAnim.PushBack({ 384, 0, 192, 210 });
	skeletonAnim.speed = 0.03f;
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
	char lookupTableChars[] = { " !'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxyz{|}~ çüéâäàaçêëèïîìäaéÆæôöòûù" };
	textFont = app->fonts->Load("Assets/textures/Tipografia_Titulos.png", lookupTableChars, 8);

	r = { 0, 0, 1280, 720 };
	currentAnimation = &idleAnim;

	chosed = 0;
	app->win->GetWindowSize(win_w, win_h);

	click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
	hover_sound = app->audio->LoadFx("Assets/audio/fx/water.wav");

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

	return true;
}

// Called each loop iteration
bool Combat_Menu::PreUpdate()
{
	if (app->frontground->GetCombatState() == 2)
	{
		in_combat = true;

		if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
		{
			controller = !controller;
			app->combat_menu->SetButtonsController(controller);
		}

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
	}
	else if (app->frontground->GetCombatState() == 0)
	{
		in_combat = false;
		allies_turn = false;
	}

	if (!controller) // keyboard
	{
		if (in_combat && !app->menu->GetGameState() && allies_turn)
		{
			int x, y;
			app->input->GetMousePosition(x, y);
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
							general_buttons[i].state = 3;
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
						chosed = i;
						items_buttons[i].state = 1;
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
					if (app->combat_manager->GetEnemyByNumber(i)->FindBuff(b) != -1)
					{
						for (size_t j = 0; j < 4; j++)
						{
							if (j != i)
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
				}
			}
		}
		else if (in_combat && app->menu->GetGameState())
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
	}
	else // controller
	{
		GamePad& pad = app->input->pads[0];

		if (pad.up == true)
		{
			app->input->SetKey(SDL_SCANCODE_UP, KEY_REPEAT);
		}
		if (pad.down == true)
		{
			app->input->SetKey(SDL_SCANCODE_DOWN, KEY_REPEAT);
		}
		if (pad.left == true)
		{
			app->input->SetKey(SDL_SCANCODE_LEFT, KEY_REPEAT);
		}
		if (pad.right == true)
		{
			app->input->SetKey(SDL_SCANCODE_RIGHT, KEY_REPEAT);
		}


		if (in_combat && !app->menu->GetGameState() && allies_turn)
		{
			if (!in_items && !in_enemies && !in_allies)
			{
				if (general_buttons[0].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						general_buttons[0].state = 0;
						general_buttons[1].state = 1;
						chosed = 1;
					}
					else if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						general_buttons[0].state = 0;
						general_buttons[2].state = 1;
						chosed = 2;
					}
				}
				else if (general_buttons[1].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						general_buttons[1].state = 0;
						general_buttons[4].state = 1;
						chosed = 4;
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						general_buttons[1].state = 0;
						general_buttons[0].state = 1;
						chosed = 0;
					}
					else if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						general_buttons[1].state = 0;
						general_buttons[3].state = 1;
						chosed = 3;
					}
				}
				else if (general_buttons[2].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						general_buttons[2].state = 0;
						general_buttons[0].state = 1;
						chosed = 0;
					}
					else if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						general_buttons[2].state = 0;
						general_buttons[3].state = 1;
						chosed = 3;
					}
				}
				else if (general_buttons[3].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						general_buttons[3].state = 0;
						general_buttons[1].state = 1;
						chosed = 1;
					}
					else if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						general_buttons[3].state = 0;
						general_buttons[4].state = 1;
						chosed = 4;
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						general_buttons[3].state = 0;
						general_buttons[2].state = 1;
						chosed = 2;
					}
				}
				else if (general_buttons[4].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						general_buttons[4].state = 0;
						general_buttons[5].state = 1;
						chosed = 5;
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						general_buttons[4].state = 0;
						general_buttons[1].state = 1;
						chosed = 1;
					}
				}
				else if (general_buttons[5].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						general_buttons[5].state = 0;
						general_buttons[6].state = 1;
						chosed = 6;
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						general_buttons[5].state = 0;
						general_buttons[4].state = 1;
						chosed = 4;
					}
				}
				else if (general_buttons[6].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						general_buttons[6].state = 0;
						general_buttons[5].state = 1;
						chosed = 5;
					}
				}
			}

			if (in_items && !in_enemies && !in_allies)
			{
				if (items_buttons[0].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						items_buttons[0].state = 0;
						items_buttons[1].state = 1;
						chosed = 1;
					}
				}
				else if (items_buttons[1].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						items_buttons[1].state = 0;
						items_buttons[2].state = 1;
						chosed = 2;
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						items_buttons[1].state = 0;
						items_buttons[0].state = 1;
						chosed = 0;
					}
				}
				else if (items_buttons[2].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						items_buttons[2].state = 0;
						items_buttons[3].state = 1;
						chosed = 3;
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						items_buttons[2].state = 0;
						items_buttons[1].state = 1;
						chosed = 1;
					}
				}
				else if (items_buttons[3].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						items_buttons[3].state = 0;
						items_buttons[4].state = 1;
						chosed = 4;
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						items_buttons[3].state = 0;
						items_buttons[2].state = 1;
						chosed = 2;
					}
				}
				else if (items_buttons[4].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						items_buttons[4].state = 0;
						items_buttons[3].state = 1;
						chosed = 3;
					}
				}
			}

			if (!in_items && in_enemies && !in_allies)
			{
				if (enemies_buttons[0].state == 1 || enemies_buttons[0].state == 3)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						if (app->combat_manager->GetEnemyByNumber(1)->GetEntityState() == 1)
						{
							enemies_buttons[0].state = 0;
							enemies_buttons[1].state = 1;
							chosed = 1;
						}
						else
						{
							if (app->combat_manager->GetEnemyByNumber(2)->GetEntityState() == 1)
							{
								enemies_buttons[0].state = 0;
								enemies_buttons[2].state = 1;
								chosed = 2;
							}
							else
							{
								if (app->combat_manager->GetEnemyByNumber(3)->GetEntityState() == 1)
								{
									enemies_buttons[0].state = 0;
									enemies_buttons[3].state = 1;
									chosed = 3;
								}
							}
						}
						
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						enemies_buttons[0].state = 0;
						enemies_buttons[4].state = 1;
						chosed = 4;
					}
				}
				else if (enemies_buttons[1].state == 1 || enemies_buttons[1].state == 3)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						if (app->combat_manager->GetEnemyByNumber(2)->GetEntityState() == 1)
						{
							enemies_buttons[1].state = 0;
							enemies_buttons[2].state = 1;
							chosed = 2;
						}
						else
						{
							if (app->combat_manager->GetEnemyByNumber(3)->GetEntityState() == 1)
							{
								enemies_buttons[1].state = 0;
								enemies_buttons[3].state = 1;
								chosed = 3;
							}
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						if (app->combat_manager->GetEnemyByNumber(0)->GetEntityState() == 1)
						{
							enemies_buttons[1].state = 0;
							enemies_buttons[0].state = 1;
							chosed = 0;
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						enemies_buttons[1].state = 0;
						enemies_buttons[4].state = 1;
						chosed = 4;
					}
				}
				else if (enemies_buttons[2].state == 1 || enemies_buttons[2].state == 3)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						if (app->combat_manager->GetEnemyByNumber(3)->GetEntityState() == 1)
						{
							enemies_buttons[2].state = 0;
							enemies_buttons[3].state = 1;
							chosed = 3;
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						if (app->combat_manager->GetEnemyByNumber(1)->GetEntityState() == 1)
						{
							enemies_buttons[2].state = 0;
							enemies_buttons[1].state = 1;
							chosed = 1;
						}
						else
						{
							if (app->combat_manager->GetEnemyByNumber(0)->GetEntityState() == 1)
							{
								enemies_buttons[2].state = 0;
								enemies_buttons[0].state = 1;
								chosed = 0;
							}
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						enemies_buttons[2].state = 0;
						enemies_buttons[4].state = 1;
						chosed = 4;
					}
				}
				else if (enemies_buttons[3].state == 1 || enemies_buttons[3].state == 3)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						enemies_buttons[3].state = 0;
						enemies_buttons[4].state = 1;
						chosed = 4;
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						if (app->combat_manager->GetEnemyByNumber(2)->GetEntityState() == 1)
						{
							enemies_buttons[3].state = 0;
							enemies_buttons[2].state = 1;
							chosed = 2;
						}
						else
						{
							if (app->combat_manager->GetEnemyByNumber(1)->GetEntityState() == 1)
							{
								enemies_buttons[3].state = 0;
								enemies_buttons[1].state = 1;
								chosed = 1;
							}
							else
							{
								if (app->combat_manager->GetEnemyByNumber(0)->GetEntityState() == 1)
								{
									enemies_buttons[3].state = 0;
									enemies_buttons[0].state = 1;
									chosed = 0;
								}
							}
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						enemies_buttons[3].state = 0;
						enemies_buttons[4].state = 1;
						chosed = 4;
					}
				}
				else if (enemies_buttons[4].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						if (app->combat_manager->GetEnemyByNumber(0)->GetEntityState() == 1)
						{
							enemies_buttons[4].state = 0;
							enemies_buttons[0].state = 1;
							chosed = 0;
						}
						else
						{
							if (app->combat_manager->GetEnemyByNumber(1)->GetEntityState() == 1)
							{
								enemies_buttons[4].state = 0;
								enemies_buttons[1].state = 1;
								chosed = 1;
							}
							else
							{
								if (app->combat_manager->GetEnemyByNumber(2)->GetEntityState() == 1)
								{
									enemies_buttons[4].state = 0;
									enemies_buttons[2].state = 1;
									chosed = 2;
								}
								else
								{
									if (app->combat_manager->GetEnemyByNumber(3)->GetEntityState() == 1)
									{
										enemies_buttons[4].state = 0;
										enemies_buttons[3].state = 1;
										chosed = 3;
									}
								}
							}
						}
					}
				}
				if (skill_prepared.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
				{
					if ((enemies_buttons[0].state == 1 || enemies_buttons[1].state == 1 || enemies_buttons[2].state == 1 || enemies_buttons[3].state == 1) && enemies_buttons[4].state == 0)
					{
						for (size_t i = 0; i < 4; i++)
						{
							if (app->combat_manager->GetEnemyByNumber(i)->GetEntityState() == 1)
							{
								enemies_buttons[i].state = 1;
								chosed = i;
							}
						}
					}
					else
					{
						for (size_t i = 0; i < 4; i++)
						{
							enemies_buttons[i].state = 0;
						}
					}
				}
				for (size_t i = 0; i < 4; i++)
				{
					BUFF b;
					// if one enemy taunt
					b.buff_type = BUFF_TYPE::TAUNT;
					if (app->combat_manager->GetEnemyByNumber(i)->FindBuff(b) != -1)
					{
						for (size_t j = 0; j < 4; j++)
						{
							enemies_buttons[j].state = 0;
						}
						enemies_buttons[i].state = 1;
						chosed = i;
					}
					// if one enemy stealth
					b.buff_type = BUFF_TYPE::STEALTH;
					if (app->combat_manager->GetEnemyByNumber(i)->FindBuff(b) != -1 && enemies_buttons[i].state == 1
						&& skill_prepared.enemy_objective != ENEMY_OBJECTIVE::ALL_ENEMY)
					{
						enemies_buttons[i].state = 3;
					}
				}
			}

			if (!in_items && !in_enemies && in_allies)
			{
				if (allies_buttons[0].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						if (app->combat_manager->GetAllyByNumber(1)->GetEntityState() == 1)
						{
							allies_buttons[0].state = 0;
							allies_buttons[1].state = 1;
							chosed = 1;
						}
						else
						{
							if (app->combat_manager->GetAllyByNumber(2)->GetEntityState() == 1)
							{
								allies_buttons[0].state = 0;
								allies_buttons[2].state = 1;
								chosed = 2;
							}
							else
							{
								if (app->combat_manager->GetAllyByNumber(3)->GetEntityState() == 1)
								{
									allies_buttons[0].state = 0;
									allies_buttons[3].state = 1;
									chosed = 3;
								}
							}
						}

					}
					else if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						allies_buttons[0].state = 0;
						allies_buttons[4].state = 1;
						chosed = 4;
					}
				}
				else if (allies_buttons[1].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						if (app->combat_manager->GetAllyByNumber(2)->GetEntityState() == 1)
						{
							allies_buttons[1].state = 0;
							allies_buttons[2].state = 1;
							chosed = 2;
						}
						else
						{
							if (app->combat_manager->GetAllyByNumber(3)->GetEntityState() == 1)
							{
								allies_buttons[1].state = 0;
								allies_buttons[3].state = 1;
								chosed = 3;
							}
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						if (app->combat_manager->GetAllyByNumber(0)->GetEntityState() == 1)
						{
							allies_buttons[1].state = 0;
							allies_buttons[0].state = 1;
							chosed = 0;
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						allies_buttons[1].state = 0;
						allies_buttons[4].state = 1;
						chosed = 4;
					}
				}
				else if (allies_buttons[2].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						if (app->combat_manager->GetAllyByNumber(3)->GetEntityState() == 1)
						{
							allies_buttons[2].state = 0;
							allies_buttons[3].state = 1;
							chosed = 3;
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						if (app->combat_manager->GetAllyByNumber(1)->GetEntityState() == 1)
						{
							allies_buttons[2].state = 0;
							allies_buttons[1].state = 1;
							chosed = 1;
						}
						else
						{
							if (app->combat_manager->GetAllyByNumber(0)->GetEntityState() == 1)
							{
								allies_buttons[2].state = 0;
								allies_buttons[0].state = 1;
								chosed = 0;
							}
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						allies_buttons[2].state = 0;
						allies_buttons[4].state = 1;
						chosed = 4;
					}
				}
				else if (allies_buttons[3].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						allies_buttons[3].state = 0;
						allies_buttons[4].state = 1;
						chosed = 3;
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						if (app->combat_manager->GetAllyByNumber(2)->GetEntityState() == 1)
						{
							allies_buttons[3].state = 0;
							allies_buttons[2].state = 1;
							chosed = 2;
						}
						else
						{
							if (app->combat_manager->GetAllyByNumber(1)->GetEntityState() == 1)
							{
								allies_buttons[3].state = 0;
								allies_buttons[1].state = 1;
								chosed = 1;
							}
							else
							{
								if (app->combat_manager->GetAllyByNumber(0)->GetEntityState() == 1)
								{
									allies_buttons[3].state = 0;
									allies_buttons[0].state = 1;
									chosed = 0;
								}
							}
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						allies_buttons[3].state = 0;
						allies_buttons[4].state = 1;
						chosed = 4;
					}
				}
				else if (allies_buttons[4].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						if (app->combat_manager->GetAllyByNumber(0)->GetEntityState() == 1)
						{
							allies_buttons[4].state = 0;
							allies_buttons[0].state = 1;
							chosed = 0;
						}
						else
						{
							if (app->combat_manager->GetAllyByNumber(1)->GetEntityState() == 1)
							{
								allies_buttons[4].state = 0;
								allies_buttons[1].state = 1;
								chosed = 1;
							}
							else
							{
								if (app->combat_manager->GetAllyByNumber(2)->GetEntityState() == 1)
								{
									allies_buttons[4].state = 0;
									allies_buttons[2].state = 1;
									chosed = 2;
								}
								else
								{
									if (app->combat_manager->GetAllyByNumber(3)->GetEntityState() == 1)
									{
										allies_buttons[4].state = 0;
										allies_buttons[3].state = 1;
										chosed = 3;
									}
								}
							}
						}
					}
				}
				if (skill_prepared.ally_objective == ALLY_OBJECTIVE::ALL_ALLY && skill_prepared.enemy_objective == ENEMY_OBJECTIVE::NOTHING)
				{
					if ((allies_buttons[0].state == 1 || allies_buttons[1].state == 1 || allies_buttons[2].state == 1 || allies_buttons[3].state == 1) && allies_buttons[4].state == 0)
					{
						for (size_t i = 0; i < 4; i++)
						{
							allies_buttons[i].state = 1;
						}
					}
				}
				else if (skill_prepared.ally_objective == ALLY_OBJECTIVE::SELF && skill_prepared.enemy_objective == ENEMY_OBJECTIVE::NOTHING)
				{
					if (allies_buttons[skill_prepared.owner].state != 1 && allies_buttons[4].state != 1)
					{
						for (size_t i = 0; i < 4; i++)
						{
							allies_buttons[i].state = 0;
						}
						allies_buttons[skill_prepared.owner].state = 1;
						chosed = skill_prepared.owner;
					}
				}
				for (size_t i = 0; i < 4; i++)
				{
					if (app->combat_manager->GetAllyByNumber(i)->GetEntityState() != 1 && skill_prepared.support_type != SUPPORT_TYPE::REVIVE)
					{
						allies_buttons[i].state = 0;
					}
				}
			}
		}
		else if (in_combat && app->menu->GetGameState())
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
	}
	

	if (prep_in_items == 1)
	{
		in_items = false;
		prep_in_items = 0;
		for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
		{
			items_buttons[i].state = 0;
		}
		if (controller)
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
		if (controller)
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
		if (controller)
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
		if (controller)
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
		if (controller)
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

		if (controller)
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

	return true;
}

// Called each loop iteration
bool Combat_Menu::Update(float dt)
{
	if (in_combat && allies_turn)
	{
		if (controller)
		{
			GamePad& pad = app->input->pads[0];

			if (pad.a == true)
			{
				app->input->SetKey(SDL_SCANCODE_Y, KEY_REPEAT);
			}
		}

		// general buttons
		if (!in_items && !in_enemies && !in_allies)
		{
			LOG("%d", chosed);
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && general_buttons[chosed].state == 1)
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
					break;
				case 5:
					//open item menu
					prep_in_items = 2;
					break;
				case 6:
					//scape
					break;
				}

				if ((chosed == 4 || chosed == 6) && controller)
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
		}

		//items buttons
		if (in_items && !in_enemies && !in_allies)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && items_buttons[chosed].state == 1)
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
					break;
				case 4:
					in_action = false;
				break;
				}

				prep_in_items = 1;
				items_buttons[chosed].state = 2;
			}
		}

		//enemies buttons
		if (!in_items && in_enemies && !in_allies)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && enemies_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//choose enemy 1
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(0));
					break;
				case 1:
					//choose enemy 2
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(1));
					break;
				case 2:
					//choose enemy 3
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(2));
					break;
				case 3:
					//choose enemy 4
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(3));
					break;
				case 4:
					//cancel action
					break;
				}

				prep_in_enemies = 1;
				enemies_buttons[chosed].state = 2;
			}
		}

		//allies buttons
		if (!in_items && !in_enemies && in_allies)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && allies_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//choose ally 1
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetAllyByNumber(0));
					break;
				case 1:
					//choose ally 2
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetAllyByNumber(1));
					break;
				case 2:
					//choose ally 3
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetAllyByNumber(2));
					break;
				case 3:
					//choose ally 4
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetAllyByNumber(3));
					break;
				case 4:
					//cancel action
					break;
				}

				prep_in_allies = 1;
				allies_buttons[chosed].state = 2;
			}
		}
	}

	currentAnimation->Update();
	if (in_combat)
	{
		for (size_t i = 0; i < 4; i++)
		{
			app->combat_manager->GetEnemyByNumber(i)->current_anim->Update();
		}
	}

	return true;
}

// Called each loop iteration
bool Combat_Menu::PostUpdate()
{
	if (in_combat)
	{
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
						texture = app->tex->white_templar;
						r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
						app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 20, enemies_buttons[i].rect.y - 40, &r);
						break;
					case 5:
						texture = app->tex->mushroom;
						r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
						app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 20, enemies_buttons[i].rect.y - 50, &r);
						break;
					case 6: 
						texture = app->tex->goblin;
						r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
						app->render->DrawTexture(texture, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y - 10, &r);
						break;
					case 7:
						texture = app->tex->skeleton;
						r = app->combat_manager->GetEnemyByNumber(i)->current_anim->GetCurrentFrame();
						app->render->DrawTexture(texture, enemies_buttons[i].rect.x - 75, enemies_buttons[i].rect.y - 110, &r);
						break;
					default: 
						texture = app->tex->assassin_texture;
						r = currentAnimation->GetCurrentFrame();
						app->render->DrawTexture(texture, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &r);
						break;
					}
				}
				else if (app->combat_manager->GetEnemyByNumber(i)->GetEntityState() == 0)
				{
					texture = app->tex->tombstone;
					r = { 64, 0, 64, 64 };
					app->render->DrawTexture(texture, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &r);
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
					case 0: texture = app->tex->assassin_texture;
						break;
					case 1: texture = app->tex->healer_texture;
						break;
					case 2: texture = app->tex->tank_texture;
						break;
					case 3: texture = app->tex->wizard_texture;
						break;
					}

					app->render->DrawTexture(texture, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &r);
				}
				else if (app->combat_manager->GetAllyByNumber(i)->GetEntityState() == 0)
				{
					texture = app->tex->tombstone;
					r = { 0, 0, 64, 64 };
					app->render->DrawTexture(texture, allies_buttons[i].rect.x, allies_buttons[i].rect.y + 5, &r);
				}
			}
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
							//app->render->DrawRectangle(general_buttons[i].rect, inColorR, inColorG, inColorB);
							g_rect = { 0, 50, 400, 50 };
						}
						else if (general_buttons[i].state == 2 && !in_action)
						{
							//app->render->DrawRectangle(general_buttons[i].rect, pColorR, pColorG, pColorB);
							g_rect = { 0, 100, 400, 50 };
						}
						else if (general_buttons[i].state == 3)
						{
							//app->render->DrawRectangle(general_buttons[i].rect, pColorR, pColorG, pColorB);
							g_rect = { 0, 100, 400, 50 };
						}
						else if (general_buttons[i].state == 0)
						{
							//app->render->DrawRectangle(general_buttons[i].rect, idleColorR, idleColorG, idleColorB);
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
							}
						}
						texture = app->tex->whitemark_400x50;
					}
					else
					{
						if (general_buttons[i].state == 1 && !in_action)
						{
							//app->render->DrawRectangle(general_buttons[i].rect, inColorR, inColorG, inColorB);
							g_rect = { 0, 110, 110, 110 };
						}
						else if (general_buttons[i].state == 2 && !in_action)
						{
							//app->render->DrawRectangle(general_buttons[i].rect, pColorR, pColorG, pColorB);
							g_rect = { 0, 220, 110, 110 };
						}
						else if (general_buttons[i].state == 0)
						{
							g_rect = { 0, 0, 110, 110 };
						}
						texture = app->tex->whitemark_110x110;
					}
					app->render->DrawTexture(texture, general_buttons[i].rect.x, general_buttons[i].rect.y, &g_rect);
				}

				for (size_t i = 0; i < 4; i++)
				{
					general_buttons[i].rect.x = action_pos[i].x + c_x;
					general_buttons[i].rect.y = action_pos[i].y + c_y;

					app->fonts->BlitText(general_buttons[i].rect.x, general_buttons[i].rect.y + 10, textFont, app->combat_manager->GetActualEntity()->GetSkill(i).skill_name);
				}
			}

			if (in_items && !in_enemies && !in_allies)
			{
				SDL_Rect i_rect;
				for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
				{
					items_buttons[i].rect.x = item_pos[i].x + c_x;
					items_buttons[i].rect.y = item_pos[i].y + c_y;

					if (items_buttons[i].state == 0)
					{
						//app->render->DrawRectangle(items_buttons[i].rect, idleColorR, idleColorG, idleColorB);
						i_rect = { 0, 0, 128, 128 };
					}
					else if (items_buttons[i].state == 1)
					{
						//app->render->DrawRectangle(items_buttons[i].rect, inColorR, inColorG, inColorB);
						i_rect = { 0, 128, 128, 128 };
					}
					else if (items_buttons[i].state == 2)
					{
						//app->render->DrawRectangle(items_buttons[i].rect, pColorR, pColorG, pColorB);
						i_rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(app->tex->whitemark_128x128, items_buttons[i].rect.x, items_buttons[i].rect.y, &i_rect);
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
							app->render->DrawTexture(app->tex->whitemark_400x50, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &e_rect);
						}
						else
						{
							SDL_Rect rect = { 0, 0, 64, 64 };
							app->render->DrawTexture(app->tex->target, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &rect);
						}
					}
					else if (enemies_buttons[i].state == 2)
					{
						// fire sprites
						if (i == 4)
						{
							//app->render->DrawRectangle(enemies_buttons[i].rect, pColorR, pColorG, pColorB);
							e_rect = { 0, 100, 400, 50 };
							app->render->DrawTexture(app->tex->whitemark_400x50, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &e_rect);
						}
						else
						{
							SDL_Rect rect = { 64, 0, 64, 64 };
							app->render->DrawTexture(app->tex->target, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &rect);
						}
					}
					else if (enemies_buttons[i].state == 3)
					{
						// no selectable sprites
						SDL_Rect rect = { 256, 0, 64, 64 };
						app->render->DrawTexture(app->tex->target, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &rect);
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
						}
						app->render->DrawTexture(app->tex->whitemark_400x50, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &e_rect);
					}

					if (i == 4)
					{
						app->fonts->BlitText(enemies_buttons[i].rect.x, enemies_buttons[i].rect.y + 10, textFont, skill_prepared.skill_name);
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
							app->render->DrawTexture(app->tex->whitemark_400x50, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &a_rect);
						}
						else
						{
							SDL_Rect rect = { 128, 0, 64, 64 };
							app->render->DrawTexture(app->tex->target, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &rect);
						}
					}
					else if (allies_buttons[i].state == 2)
					{
						// fire sprites
						if (i == 4)
						{
							//app->render->DrawRectangle(allies_buttons[i].rect, pColorR, pColorG, pColorB);
							a_rect = { 0, 100, 400, 50 };
							app->render->DrawTexture(app->tex->whitemark_400x50, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &a_rect);
						}
						else
						{
							SDL_Rect rect = { 192, 0, 64, 64 };
							app->render->DrawTexture(app->tex->target, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &rect);
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
						}
						app->render->DrawTexture(app->tex->whitemark_400x50, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &a_rect);
					}

					if (i == 4)
					{
						app->fonts->BlitText(allies_buttons[i].rect.x, allies_buttons[i].rect.y + 15, textFont, skill_prepared.skill_name);
					}
				}
			}
		}
		else if (app->combat_manager->GetInAnimation() == 2)
		{
			app->fonts->BlitText(500 + c_x, 100 + c_y, textFont, skill_prepared.skill_name);
			if (skill_effect != ANIM_EFFECT::EMPTY)
			{
				if (skill_prepared.ally_objective == ALLY_OBJECTIVE::ALL_ALLY)
				{
					for (size_t i = 0; i < 4; i++)
					{
						if (app->combat_manager->GetAllyByNumber(i)->GetEntityState() == 1)
						{
							app->particles->PlayParticle(skill_effect, allies_buttons[i].rect.x - 32, allies_buttons[i].rect.y - 32);
						}
					}
				}
				else if (skill_prepared.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
				{
					for (size_t i = 0; i < 4; i++)
					{
						if (app->combat_manager->GetEnemyByNumber(i)->GetEntityState() == 1)
						{
							app->particles->PlayParticle(skill_effect, enemies_buttons[i].rect.x - 32, enemies_buttons[i].rect.y - 32);
						}
					}
				}
				else
				{
					app->particles->PlayParticle(skill_effect, objective_pos.x - 32, objective_pos.y - 32);
				}

				SetSkillAnimation(ANIM_EFFECT::EMPTY, 0, 0);
			}
		}
		app->combat_manager->UpdateHUD();
	}

	return true;
}

// Called before quitting
bool Combat_Menu::CleanUp()
{

	return true;
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