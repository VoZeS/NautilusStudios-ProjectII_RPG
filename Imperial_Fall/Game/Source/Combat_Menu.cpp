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
#include "Player.h"
#include "Defs.h"
#include "Log.h"

Combat_Menu::Combat_Menu() : Module()
{
	name.Create("combat_menu");

	idleAnim.PushBack({ 5, 164, 50, 72 });
	idleAnim.PushBack({ 65, 164, 50, 72 });
	idleAnim.speed = 0.03f;
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
	textFont = app->fonts->Load("Assets/textures/pixel_letters.png", lookupTableChars, 8);

	r = { 0, 0, 1280, 720 };
	currentAnimation = &idleAnim;

	/*general_buttons[0].state = 1; only with controller
	items_buttons[0].state = 1;
	enemies_buttons[0].state = 1;*/
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

	enemy_pos[0] = { 866.0f, 150.0f };
	enemy_pos[1] = { 966.0f, 250.0f };
	enemy_pos[2] = { 866.0f, 350.0f };
	enemy_pos[3] = { 966.0f, 450.0f };
	enemy_pos[4] = { 415.0f, 660.0f };

	ally_pos[0] = { 350.0f, 150.0f };
	ally_pos[1] = { 250.0f, 250.0f };
	ally_pos[2] = { 350.0f, 350.0f };
	ally_pos[3] = { 250.0f, 450.0f };
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

	/*general_buttons[0].tex = app->tex->Load("Assets/textures/Exit.png"); // Attack 1
	general_buttons[1].tex = app->tex->Load("Assets/textures/Exit.png"); // Attack 2
	general_buttons[2].tex = app->tex->Load("Assets/textures/Exit.png"); // Attack 3
	general_buttons[3].tex = app->tex->Load("Assets/textures/Exit.png"); // Attack 4
	general_buttons[4].tex = app->tex->Load("Assets/textures/Exit.png"); //Reload Mana
	general_buttons[5].tex = app->tex->Load("Assets/textures/Exit.png"); // Use Item
	general_buttons[6].tex = app->tex->Load("Assets/textures/Exit.png"); // Scape

	items_buttons[0].tex = app->tex->Load("Assets/textures/Exit.png"); // Item 1
	items_buttons[1].tex = app->tex->Load("Assets/textures/Exit.png"); // Item 2
	items_buttons[2].tex = app->tex->Load("Assets/textures/Exit.png"); // Item 3
	items_buttons[3].tex = app->tex->Load("Assets/textures/Exit.png"); // Item 4
	
	enemies_buttons[0].tex = app->tex->Load("Assets/textures/Exit.png"); // Enemy 1
	enemies_buttons[1].tex = app->tex->Load("Assets/textures/Exit.png"); // Enemy 2
	enemies_buttons[2].tex = app->tex->Load("Assets/textures/Exit.png"); // Enemy 3
	enemies_buttons[3].tex = app->tex->Load("Assets/textures/Exit.png"); // Enemy 4

	allies_buttons[0].tex = app->tex->Load("Assets/textures/Exit.png"); // Ally 1
	allies_buttons[1].tex = app->tex->Load("Assets/textures/Exit.png"); // Ally 2
	allies_buttons[2].tex = app->tex->Load("Assets/textures/Exit.png"); // Ally 3
	allies_buttons[3].tex = app->tex->Load("Assets/textures/Exit.png"); // Ally 4*/

	return true;
}

// Called each loop iteration
bool Combat_Menu::PreUpdate()
{
	if (app->frontground->GetCombatState() == 2)
	{
		in_combat = true;
	}

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
					chosed = i;
					general_buttons[i].state = 1;
				}
				else
				{
					general_buttons[i].state = 0;
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

	return true;
}

// Called each loop iteration
bool Combat_Menu::Update(float dt)
{
	if (in_combat && allies_turn)
	{
		// general buttons
		if (!in_items && !in_enemies && !in_allies)
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && general_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//prepare attack 1
					if (app->combat_manager->GetActualEntity()->GetSkill(0).objective)
					{
						in_enemies = true;
					}
					else
					{
						in_allies = true;
					}
					skill_prepared = app->combat_manager->GetActualEntity()->GetSkill(0);
					break;
				case 1:
					//prepare attack 2
					if (app->combat_manager->GetActualEntity()->GetSkill(1).objective)
					{
						in_enemies = true;
					}
					else
					{
						in_allies = true;
					}
					skill_prepared = app->combat_manager->GetActualEntity()->GetSkill(1);
					break;
				case 2:
					//prepare attack 3
					if (app->combat_manager->GetActualEntity()->GetSkill(2).objective)
					{
						in_enemies = true;
					}
					else
					{
						in_allies = true;
					}
					skill_prepared = app->combat_manager->GetActualEntity()->GetSkill(2);
					break;
				case 3:
					//prepare attack 4
					if (app->combat_manager->GetActualEntity()->GetSkill(3).objective)
					{
						in_enemies = true;
					}
					else
					{
						in_allies = true;
					}
					skill_prepared = app->combat_manager->GetActualEntity()->GetSkill(3);
					break;
				case 4:
					//reload mana
					break;
				case 5:
					//open item menu
					in_items = true;
					break;
				case 6:
					//scape
					break;
				}

				in_action = true;
				general_buttons[chosed].state = 2;
			}
		}

		//items buttons
		if (in_items && !in_enemies && !in_allies)
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && items_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//prepare item 1
					//if (/*damage skill*/)
					{
						in_items = false;
						in_enemies = true;
					}
					//else if (/*support skill*/)
					{
						//in_allies = true;
					}
					break;
				case 1:
					//prepare item 2
					//if (/*damage skill*/)
					{
						//in_enemies = true;
					}
					//else if (/*support skill*/)
					{
						in_items = false;
						in_allies = true;
					}
					break;
				case 2:
					//prepare item 3
					//if (/*damage skill*/)
					{
						in_items = false;
						in_enemies = true;
					}
					//else if (/*support skill*/)
					{
						//in_allies = true;
					}
					break;
				case 3:
					//prepare item 4
					//if (/*damage skill*/)
					{
						in_items = false;
						in_enemies = true;
					}
					//else if (/*support skill*/)
					{
						//in_allies = true;
					}
					break;
				case 4:
					in_items = false;
				break;
				}

				items_buttons[chosed].state = 2;
			}
		}

		//enemies buttons
		if (!in_items && in_enemies && !in_allies)
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && enemies_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//choose enemy 1
					in_enemies = false;
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(0));
					break;
				case 1:
					//choose enemy 2
					in_enemies = false;
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(1));
					break;
				case 2:
					//choose enemy 3
					in_enemies = false;
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(2));
					break;
				case 3:
					//choose enemy 4
					in_enemies = false;
					app->combat_manager->UseSkill(app->combat_manager->GetActualEntity(), skill_prepared, app->combat_manager->GetEnemyByNumber(3));
					break;
				case 4:
					//cancel action
					in_enemies = false;
					break;
				}

				in_action = false;
				enemies_buttons[chosed].state = 2;
			}
		}

		//allies buttons
		if (!in_items && !in_enemies && in_allies)
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && allies_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//choose ally 1
					in_allies = false;
					break;
				case 1:
					//choose ally 2
					in_allies = false;
					break;
				case 2:
					//choose ally 3
					in_allies = false;
					break;
				case 3:
					//choose ally 4
					in_allies = false;
					break;
				case 4:
					//cancel action
					in_allies = false;
					break;
				}

				in_action = false;
				allies_buttons[chosed].state = 2;
			}
		}
	}

	currentAnimation->Update();

	return true;
}

// Called each loop iteration
bool Combat_Menu::PostUpdate()
{
	if (in_combat)
	{
		int c_x = -app->render->camera.x;
		int c_y = -app->render->camera.y;

		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		SDL_Texture* texture = NULL;

		for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
		{
			enemies_buttons[i].rect.x = enemy_pos[i].x + c_x;
			enemies_buttons[i].rect.y = enemy_pos[i].y + c_y;

			if (i != 4)
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

				// enemies sprites
				app->render->DrawTexture(texture, enemies_buttons[i].rect.x, enemies_buttons[i].rect.y, &rect);
			}
		}

		for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
		{
			allies_buttons[i].rect.x = ally_pos[i].x + c_x;
			allies_buttons[i].rect.y = ally_pos[i].y + c_y;

			if (i != 4)
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

				// heroes sprites
				app->render->DrawTexture(texture, allies_buttons[i].rect.x, allies_buttons[i].rect.y, &rect);
			}
		}

		if (allies_turn)
		{
			if (!in_items && !in_enemies && !in_allies)
			{
				for (size_t i = 0; i < NUM_BUTTONS; i++)
				{
					general_buttons[i].rect.x = action_pos[i].x + c_x;
					general_buttons[i].rect.y = action_pos[i].y + c_y;

					if (general_buttons[i].state == 1 && !in_action)
					{
						app->render->DrawRectangle(general_buttons[i].rect, inColorR, inColorG, inColorB);
					}
					else if (general_buttons[i].state == 2 && !in_action)
					{
						app->render->DrawRectangle(general_buttons[i].rect, pColorR, pColorG, pColorB);
					}
					else if (general_buttons[i].state == 0)
					{
						app->render->DrawRectangle(general_buttons[i].rect, idleColorR, idleColorG, idleColorB);
					}
				}

				for (size_t i = 0; i < 4; i++)
				{
					general_buttons[i].rect.x = action_pos[i].x + c_x;
					general_buttons[i].rect.y = action_pos[i].y + c_y;

					app->fonts->BlitText(general_buttons[i].rect.x, general_buttons[i].rect.y + 15, textFont, app->combat_manager->GetActualEntity()->GetSkill(i).skill_name);
				}
			}

			if (in_items && !in_enemies && !in_allies)
			{
				for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
				{
					items_buttons[i].rect.x = item_pos[i].x + c_x;
					items_buttons[i].rect.y = item_pos[i].y + c_y;

					if (items_buttons[i].state == 0)
					{
						app->render->DrawRectangle(items_buttons[i].rect, idleColorR, idleColorG, idleColorB);
					}
					else if (items_buttons[i].state == 1)
					{
						app->render->DrawRectangle(items_buttons[i].rect, inColorR, inColorG, inColorB);
					}
					else if (items_buttons[i].state == 2)
					{
						app->render->DrawRectangle(items_buttons[i].rect, pColorR, pColorG, pColorB);
					}
				}
			}

			if (!in_items && in_enemies && !in_allies)
			{
				for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
				{
					if (enemies_buttons[i].state == 1)
					{
						// aiming sprites
						app->render->DrawRectangle(enemies_buttons[i].rect, inColorR, inColorG, inColorB);
					}
					else if (enemies_buttons[i].state == 2)
					{
						// fire sprites
						app->render->DrawRectangle(enemies_buttons[i].rect, 0, 255, 0);
					}
					else if (enemies_buttons[i].state == 0 && i == 4)
					{
						app->render->DrawRectangle(enemies_buttons[i].rect, idleColorR, idleColorG, idleColorB);
					}

					if (i == 4)
					{
						app->fonts->BlitText(enemies_buttons[i].rect.x, enemies_buttons[i].rect.y + 15, textFont, skill_prepared.skill_name);
					}
				}
			}

			if (!in_items && !in_enemies && in_allies)
			{
				for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
				{
					if (allies_buttons[i].state == 1)
					{
						// aiming sprites
						app->render->DrawRectangle(allies_buttons[i].rect, inColorR, inColorG, inColorB);
					}
					else if (allies_buttons[i].state == 2)
					{
						// fire sprites
						app->render->DrawRectangle(allies_buttons[i].rect, 0, 255, 0);
					}
					else if (allies_buttons[i].state == 0 && i == 4)
					{
						app->render->DrawRectangle(allies_buttons[i].rect, idleColorR, idleColorG, idleColorB);
					}

					if (i == 4)
					{
						app->fonts->BlitText(allies_buttons[i].rect.x, allies_buttons[i].rect.y + 15, textFont, skill_prepared.skill_name);
					}
				}
			}
		}
	}

	return true;
}

// Called before quitting
bool Combat_Menu::CleanUp()
{

	return true;
}
