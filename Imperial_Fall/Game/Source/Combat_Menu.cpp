#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "Frontground.h"
#include "Combat_Menu.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

Combat_Menu::Combat_Menu() : Module()
{
	name.Create("combat_menu");
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
	r = { 0, 0, 1280, 720 };

	general_buttons[0].state = 1;
	items_buttons[0].state = 1;
	enemies_buttons[0].state = 1;
	chosed = 0;
	app->win->GetWindowSize(win_w, win_h);

	click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
	hover_sound = app->audio->LoadFx("Assets/audio/fx/water.wav");

	for (size_t i = 0; i < NUM_BUTTONS; i++)
	{
		general_buttons[i].rect.x = ((int)win_w / 2) - (general_buttons[i].rect.w / 2);
		general_buttons[i].rect.y = ((int)win_h / (NUM_BUTTONS + 1)) * (i + 1);
	}

	for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
	{
		items_buttons[i].rect.x = ((int)win_w / 2) - (items_buttons[i].rect.w / 2);
		items_buttons[i].rect.y = ((int)win_h / (NUM_ITEMS_BUTTONS + 1)) * (i + 1);
	}

	for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
	{
		enemies_buttons[i].rect.x = ((int)win_w / 2) - (enemies_buttons[i].rect.w / 2);
		enemies_buttons[i].rect.y = ((int)win_h / (NUM_ENEMIES_BUTTONS + 3)) * (i + 2.5f);
	}

	for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
	{
		allies_buttons[i].rect.x = ((int)win_w / 2) - (allies_buttons[i].rect.w / 2);
		allies_buttons[i].rect.y = ((int)win_h / (NUM_ALLIES_BUTTONS + 3)) * (i + 2.5f);
	}

	general_buttons[0].tex = app->tex->Load("Assets/textures/Exit.png"); // Attack 1
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
	allies_buttons[3].tex = app->tex->Load("Assets/textures/Exit.png"); // Ally 4

	return true;
}

// Called each loop iteration
bool Combat_Menu::PreUpdate()
{
	in_combat = app->frontground->GetCombatState();

	if (in_combat)
	{
		int x, y;
		app->input->GetMousePosition(x, y);
		float cx = -app->render->camera.x;
		float cy = -app->render->camera.y;
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

	return true;
}

// Called each loop iteration
bool Combat_Menu::Update(float dt)
{
	if (in_combat)
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
					//attack 1
					break;
				case 1:
					//attack 2
					break;
				case 2:
					//attack 3
					break;
				case 3:
					//attack 4
					break;
				case 4:
					//reload mana
					break;
				case 5:
					//open item menu
					break;
				case 6:
					//scape
					break;
				}

				general_buttons[chosed].state = 2;
			}
		}

		//items buttons
		if (in_items && !in_enemies && in_allies)
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && items_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					//item 1
					break;
				case 1:
					//item 2
					break;
				case 2:
					//item 3
					break;
				case 3:
					//item 4
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
					break;
				case 1:
					//choose enemy 2
					break;
				case 2:
					//choose enemy 3
					break;
				case 3:
					//choose enemy 4
					break;
				}

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
					break;
				case 1:
					//choose ally 2
					break;
				case 2:
					//choose ally 3
					break;
				case 3:
					//choose ally 4
					break;
				}

				allies_buttons[chosed].state = 2;
			}
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
		r.x = c_x;
		r.y = c_y;

		if (app->scene->GetStartScreenState() != NULL)
		{
			app->render->DrawTexture(app->tex->start_menu, 0 + c_x, 0 + c_y);
		}

		if (!in_items && !in_enemies && !in_allies)
		{
			//app->render->DrawRectangle(r, 0, 0, 0, 200);

			for (size_t i = 0; i < NUM_BUTTONS; i++)
			{
				general_buttons[i].rect.x = ((int)win_w / 2) - (general_buttons[i].rect.w / 2) + c_x - 300;
				general_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 1)) * (i + 1) + c_y;

				if (general_buttons[i].state == 0)
				{
					app->render->DrawRectangle(general_buttons[i].rect, idleColorR, idleColorG, idleColorB);
				}
				else if (general_buttons[i].state == 1)
				{
					app->render->DrawRectangle(general_buttons[i].rect, inColorR, inColorG, inColorB);
				}
				else if (general_buttons[i].state == 2)
				{
					app->render->DrawRectangle(general_buttons[i].rect, pColorR, pColorG, pColorB);
				}

				app->render->DrawTexture(general_buttons[i].tex, general_buttons[i].rect.x + 10, general_buttons[i].rect.y + 10);
			}
		}

		if (in_items && !in_enemies && !in_allies)
		{
			for (size_t i = 0; i < NUM_MENU_BUTTONS; i++)
			{
				items_buttons[i].rect.x = ((int)win_w / 2) - (items_buttons[i].rect.w / 2) + c_x - 300;
				items_buttons[i].rect.y = ((int)win_h / (NUM_MENU_BUTTONS + 1)) * (i + 1) + c_y;

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
			//app->render->DrawRectangle(r, 0, 0, 0, 200);

			for (size_t i = 0; i < NUM_ENEMIES_BUTTONS; i++)
			{
				enemies_buttons[i].rect.x = ((int)win_w / 2) - (enemies_buttons[i].rect.w / 2) + c_x - 300;
				enemies_buttons[i].rect.y = ((int)win_h / (NUM_ENEMIES_BUTTONS + 1)) * (i + 1) + c_y;

				if (enemies_buttons[i].state == 0)
				{
					app->render->DrawRectangle(enemies_buttons[i].rect, idleColorR, idleColorG, idleColorB);
				}
				else if (enemies_buttons[i].state == 1)
				{
					app->render->DrawRectangle(enemies_buttons[i].rect, inColorR, inColorG, inColorB);
				}
				else if (enemies_buttons[i].state == 2)
				{
					app->render->DrawRectangle(enemies_buttons[i].rect, pColorR, pColorG, pColorB);
				}

				app->render->DrawTexture(enemies_buttons[i].tex, enemies_buttons[i].rect.x + 10, enemies_buttons[i].rect.y + 10);
			}
		}

		if (!in_items && !in_enemies && in_allies)
		{
			//app->render->DrawRectangle(r, 0, 0, 0, 200);

			for (size_t i = 0; i < NUM_ALLIES_BUTTONS; i++)
			{
				allies_buttons[i].rect.x = ((int)win_w / 2) - (allies_buttons[i].rect.w / 2) + c_x - 300;
				allies_buttons[i].rect.y = ((int)win_h / (NUM_ALLIES_BUTTONS + 1)) * (i + 1) + c_y;

				if (allies_buttons[i].state == 0)
				{
					app->render->DrawRectangle(allies_buttons[i].rect, idleColorR, idleColorG, idleColorB);
				}
				else if (allies_buttons[i].state == 1)
				{
					app->render->DrawRectangle(allies_buttons[i].rect, inColorR, inColorG, inColorB);
				}
				else if (allies_buttons[i].state == 2)
				{
					app->render->DrawRectangle(allies_buttons[i].rect, pColorR, pColorG, pColorB);
				}

				app->render->DrawTexture(allies_buttons[i].tex, allies_buttons[i].rect.x + 10, allies_buttons[i].rect.y + 10);
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
