#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Fonts.h"
#include "Map.h"
#include "Pathfinding.h"
#include "Player.h"
#include "Menu.h"
#include "Frontground.h"
#include "Town1.h"
#include "Town2.h"
#include "Forest.h"
#include "Battlefield.h"
#include "Dungeon.h"
#include "Outside_Castle.h"
#include "Inside_Castle.h"

#include "Defs.h"
#include "Log.h"

Frontground::Frontground(bool enabled) : Module(enabled)
{
	name.Create("frontground");
	a = 0;
}

// Destructor
Frontground::~Frontground()
{}

// Called before render is available
bool Frontground::Awake()
{

	return true;
}

// Called before the first frame
bool Frontground::Start()
{
	r = { 0, 0, 1280, 720 };

	press_e = app->tex->Load("Assets/textures/PressE.png");

	return true;
}

// Called each loop iteration
bool Frontground::PreUpdate()
{
	if (go_black)
	{
		if (a < 256 - fade_speed)
		{
			a += fade_speed;
		}
		else if (a < 255)
		{
			a++;
		}
	}
	else if (return_black)
	{
		if (a > fade_speed)
		{
			a -= fade_speed;
		}
		else if (a > 0)
		{
			a--;
		}
	}

	return true;
}

// Called each loop iteration
bool Frontground::Update(float dt)
{

	if (a >= 255)
	{
		go_black = false;

		if (in_combat == 0 && restart == 2)
		{
			restart = 0;
			return_black = true;
			in_combat = 2;
		}
		else if (in_combat == 1 || in_combat == 2)
		{
			FadeOutCombat();
		}
		else if (in_combat == 3)
		{
			if (restart == 0)
			{
				// return field
				in_combat = 0;
				app->menu->SetWinLose(-1); // both false
				FadeFromBlack();
			}
			else if (restart == 1)
			{
				// restart
				in_combat = 0;
				app->menu->SetWinLose(-1); // both false
				restart = 2;
			}
		}
		else
		{
			FadeFromBlack();
		}
	}
	else if (a <= 0)
	{
		return_black = false;
	}

	return true;
}

// Called each loop iteration
bool Frontground::PostUpdate()
{
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;

	if (!press_e_hide)
	{
		app->render->DrawRectangle({ c_x + 540 , c_y + 650, 200, 50 }, 255, 255, 255, 150);
		app->render->DrawTexture(press_e, c_x + 540, c_y + 650);
	}
	
	r.x = c_x;
	r.y = c_y;

	app->render->DrawRectangle(r, 0, 0, 0, a);

	return true;
}

// Called before quitting
bool Frontground::CleanUp()
{

	return true;
}

bool Frontground::FadeToBlack()
{
	go_black = true;

	return true;
}

bool Frontground::FadeFromBlack()
{
	return_black = true;

	app->menu->DisableAll();

	app->physics->CleanMapBoxes();

	if (app->frontground->town1_to_town2)
	{
		app->town2->Enable();
	}

	return true;
}

bool Frontground::FadeInCombat(ENEMIES enemies[])
{
	go_black = true;
	in_combat = 1;

	for (size_t i = 0; i < 4; i++)
	{
		enemies_to_fight[i] = enemies[i];
	}

	return true;
}

bool Frontground::FadeOutCombat()
{
	return_black = true;

	app->map->CleanMaps();
	app->physics->CleanMapBoxes();
	app->map->collision_loaded = false;
	app->entities->CleanUp();

	app->map->Load("combat.tmx");

	app->entities->GetPlayer()->DeleteEntity();
	in_combat = 2;

	return true;
}

bool Frontground::ReturnToField()
{
	in_combat = 3;
	switch (app->frontground->current_level)
	{
	case 1:
		app->town1->Enable();
		break;
	case 2:
		app->town2->Enable();
		break;
	case 3:
		app->forest->Enable();
		break;
	case 4:
		app->battlefield->Enable();
		break;
	case 5:
		app->dungeon->Enable();
		break;
	case 6:
		app->outside->Enable();
		break;
	case 7:
		app->inside->Enable();
		break;
	}
	app->entities->GetPlayer()->SetPlayerPosition(app->entities->GetPlayer()->GetPlayerPosition().x - 7, app->entities->GetPlayer()->GetPlayerPosition().y);
	app->SaveGameRequest();

	return true;
}

bool Frontground::ResetCombat()
{
	go_black = true;
	in_combat = 3;
	restart = 1;

	return true;
}

void Frontground::ReturnStartScreen()
{
	SetA_Black();

	app->map->CleanMaps();
	app->physics->CleanMapBoxes();
	app->map->collision_loaded = false;
	app->entities->CleanUp();

	in_combat = 0;
}