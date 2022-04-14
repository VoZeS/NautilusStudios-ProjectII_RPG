#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Input.h"
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
#include "Combat_Scene.h"
#include "Combat_Menu.h"
#include "LogoScreen.h"

#include "Defs.h"
#include "Log.h"

#include <math.h>

Frontground::Frontground(bool enabled) : Module(enabled)
{
	name.Create("frontground");
}

// Destructor
Frontground::~Frontground()
{}

// Called before render is available
bool Frontground::Awake()
{
	godmode = false;

	fast_combat = false;

	return true;
}

// Called before the first frame
bool Frontground::Start()
{
	r = { 0, 0, 1280, 720 };
	a = 0;

	SDL_ShowCursor(false);

	return true;
}

// Called each loop iteration
bool Frontground::PreUpdate()
{
	// toggle controller
	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		controller = !controller;
		if (controller)
		{
			app->menu->SetController();
			app->combat_menu->SetController();
		}
	}
	
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

		FadeFromBlack();
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
	
	r.x = c_x;
	r.y = c_y;
	
	if (a == 254)
	{
		a++;
	}

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

	if (move_to != MOVE_TO::NOTHING)
	{
		app->menu->DisableAll();
		app->physics->CleanMapBoxes();
	}

	switch (move_to)
	{
	case MOVE_TO::LOGO_SCENE: app->scene->Enable();  app->menu->started = false;
		break;
	case MOVE_TO::SCENE_TOWN1: app->town1->Enable(); app->menu->InitPlayer();
		break;
	case MOVE_TO::SCENE_TOWN2: app->town2->Enable(); app->menu->InitPlayer();
		break;
	case MOVE_TO::SCENE_FOREST: app->forest->Enable(); app->menu->InitPlayer();
		break;
	case MOVE_TO::SCENE_BATTLEFIELD: app->battlefield->Enable(); app->menu->InitPlayer();
		break;
	case MOVE_TO::SCENE_DUNGEON: app->dungeon->Enable(); app->menu->InitPlayer();
		break;
	case MOVE_TO::SCENE_OUTSIDE: app->outside->Enable(); app->menu->InitPlayer();
		break;
	case MOVE_TO::SCENE_INSIDE: app->town1->Enable(); app->menu->InitPlayer();
		break;
	case MOVE_TO::TOWN1_SCENE: app->scene->Enable(); app->menu->started = false;
		break;
	case MOVE_TO::TOWN1_TOWN2: app->town2->Enable();
		break;
	case MOVE_TO::TOWN1_OUTSIDE: app->outside->Enable();
		break;
	case MOVE_TO::TOWN1_COMBAT: app->combat_scene->Enable();
		break;
	case MOVE_TO::TOWN2_SCENE: app->scene->Enable(); app->menu->started = false;
		break;
	case MOVE_TO::TOWN2_TOWN1: app->town1->Enable();
		break;
	case MOVE_TO::TOWN2_FOREST: app->forest->Enable();
		break;
	case MOVE_TO::TOWN2_BATTLEFIELD: app->battlefield->Enable();
		break;
	case MOVE_TO::TOWN2_DUNGEON: app->dungeon->Enable();
		break;
	case MOVE_TO::TOWN2_COMBAT: app->combat_scene->Enable();
		break;
	case MOVE_TO::FOREST_SCENE: app->scene->Enable(); app->menu->started = false;
		break;
	case MOVE_TO::FOREST_TOWN2: app->town2->Enable();
		break;
	case MOVE_TO::FOREST_COMBAT: app->combat_scene->Enable();
		break;
	case MOVE_TO::BATTLEFIELD_SCENE: app->scene->Enable(); app->menu->started = false;
		break;
	case MOVE_TO::BATTLEFIELD_TOWN2: app->town2->Enable();
		break;
	case MOVE_TO::BATTLEFIELD_COMBAT: app->combat_scene->Enable();
		break;
	case MOVE_TO::DUNGEON_SCENE: app->scene->Enable(); app->menu->started = false;
		break;
	case MOVE_TO::DUNGEON_TOWN2: app->town2->Enable();
		break;
	case MOVE_TO::DUNGEON_COMBAT: app->combat_scene->Enable();
		break;
	case MOVE_TO::OUTSIDE_SCENE: app->scene->Enable(); app->menu->started = false;
		break;
	case MOVE_TO::OUTSIDE_TOWN1: app->town1->Enable();
		break;
	case MOVE_TO::OUTSIDE_INSIDE: app->inside->Enable();
		break;
	case MOVE_TO::OUTSIDE_COMBAT: app->combat_scene->Enable();
		break;
	case MOVE_TO::INSIDE_SCENE: app->scene->Enable(); app->menu->started = false;
		break;
	case MOVE_TO::INSIDE_OUTSIDE: app->outside->Enable();
		break;
	case MOVE_TO::INSIDE_COMBAT: app->combat_scene->Enable();
		break;
	case MOVE_TO::FROM_COMBAT:
		switch (current_level)
		{
		case 1: app->town1->Enable();
			break;
		case 2: app->town2->Enable();
			break;
		case 3: app->forest->Enable();
			break;
		case 4: app->battlefield->Enable();
			break;
		case 5: app->dungeon->Enable();
			break;
		case 6: app->outside->Enable();
			break;
		case 7: app->inside->Enable();
			break;
		default:
			break;
		}

		app->menu->SetWinLoseScape(-1);
		break;
	case MOVE_TO::RESET_COMBAT: app->combat_scene->Enable(); app->menu->SetWinLoseScape(-1);
		break;
	default:
		break;
	}

	return true;
}

bool Frontground::FadeInCombat(ENEMIES enemies[])
{
	go_black = true;

	for (size_t i = 0; i < 4; i++)
	{
		enemies_to_fight[i] = enemies[i];
	}

	return true;
}

bool Frontground::ReturnToField()
{
	app->SaveGameRequest();
	move_to = MOVE_TO::FROM_COMBAT;

	FadeToBlack();
	MovePlayer();
	app->entities->freeze = false;

	return true;
}

bool Frontground::ResetCombat()
{
	move_to = MOVE_TO::RESET_COMBAT;

	FadeToBlack();

	return true;
}

void Frontground::ReturnStartScreen()
{
	switch (current_level)
	{
	case 1:
		move_to = MOVE_TO::TOWN1_SCENE;
		break;
	case 2:
		move_to = MOVE_TO::TOWN2_SCENE;
		break;
	case 3:
		move_to = MOVE_TO::FOREST_SCENE;
		break;
	case 4:
		move_to = MOVE_TO::BATTLEFIELD_SCENE;
		break;
	case 5:
		move_to = MOVE_TO::DUNGEON_SCENE;
		break;
	case 6:
		move_to = MOVE_TO::OUTSIDE_SCENE;
		break;
	case 7:
		move_to = MOVE_TO::INSIDE_SCENE;
		break;
	}

	FadeToBlack();
}

void Frontground::SaveDirection()
{
	fPoint enemy_position = app->entities->GetEnemyPos();
	float x = 0, y = 0, modulo = 0;

	if (enemy_position.x != 0 || enemy_position.y != 0)
	{
		x = app->entities->GetPlayer()->GetPlayerPosition().x - enemy_position.x;
		y = app->entities->GetPlayer()->GetPlayerPosition().y - enemy_position.y;

		if (abs(x) >= abs(y))
		{
			// desplazamiento horizontal
			if (x > 0)
			{
				direction = 3;
			}
			else
			{
				direction = 2;
			}
		}
		else
		{
			// desplazamiento vertical
			if (y > 0)
			{
				direction = 0;
			}
			else
			{
				direction = 1;
			}
		}
	}
}

void Frontground::MovePlayer()
{
	switch (direction)
	{
	case 0: app->entities->GetPlayer()->SetPlayerPosition(app->entities->GetPlayer()->GetPlayerPosition().x, app->entities->GetPlayer()->GetPlayerPosition().y + 1);
		break;
	case 1: app->entities->GetPlayer()->SetPlayerPosition(app->entities->GetPlayer()->GetPlayerPosition().x, app->entities->GetPlayer()->GetPlayerPosition().y - 1);
		break;
	case 2: app->entities->GetPlayer()->SetPlayerPosition(app->entities->GetPlayer()->GetPlayerPosition().x - 1, app->entities->GetPlayer()->GetPlayerPosition().y);
		break;
	case 3: app->entities->GetPlayer()->SetPlayerPosition(app->entities->GetPlayer()->GetPlayerPosition().x + 1, app->entities->GetPlayer()->GetPlayerPosition().y);
		break;
	}

	direction = -1;
}