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
#include "Combat_Scene.h"

#include "Defs.h"
#include "Log.h"

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

	return true;
}

// Called before the first frame
bool Frontground::Start()
{
	r = { 0, 0, 1280, 720 };
	a = 0;

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

		/*if (in_combat == 0 && restart == 2)
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
		{*/
			FadeFromBlack();
		//}
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
		break;
	default:
		break;
	}

	return true;
}

bool Frontground::FadeInCombat(ENEMIES enemies[])
{
	go_black = true;
	//in_combat = 1;

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