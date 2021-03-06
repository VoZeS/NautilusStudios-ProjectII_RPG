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
#include "Inventory.h"
#include "End_Combat_Scene.h"
#include "LogoScreen.h"
#include "Dialog.h"
#include "Intro_Cutscene.h"
#include "Final_Cutscene.h"
#include "Credits.h"

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

	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(STARTED_FILENAME);

	first_time = saveGame.child("started").child("first_time").attribute("value").as_bool();
	current_level = saveGame.child("started").child("current_level").attribute("value").as_int();;
	adventure_phase = saveGame.child("started").child("adventure_phase").attribute("value").as_int();

	c_mouse_pos = { 640, 360 };

	return true;
}

// Called each loop iteration
bool Frontground::PreUpdate()
{
	// toggle controller
	if (app->input->GetKey(SDL_SCANCODE_C) == KEY_DOWN)
	{
		controller = !controller;
	}

	if (check_phase_change)
	{
		adventure_phase = CheckAdventureState();
		check_phase_change = false;
	}

	if (app->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN)
	{
		adventure_phase++;
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

 		if (!app->end_combat_scene->in_cutscene && fix)
		{
			FadeFromBlack();
		}
		else if (app->end_combat_scene->cutcene_cd > BLACK_TIME)
		{
			fix = false;
			letter_cd ++;

			if (letter_cd >= 60 * 0.05f && letlengh <= app->dialog->limitLenght)
			{
				letlengh++;
				app->dialog->PlayLetterSound();
				letter_cd = 0;
			}

			if (app->end_combat_scene->cutcene_cd == 199 + BLACK_TIME || app->end_combat_scene->cutcene_cd == 399 + BLACK_TIME
				|| app->end_combat_scene->cutcene_cd == 599 + BLACK_TIME || app->end_combat_scene->cutcene_cd == 799 + BLACK_TIME)
			{
				letlengh = 0;
			}
		}
	}
	else if (a <= 0)
	{
		return_black = false;
	}

	if (app->menu->dragonDefeated)// || app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		//Fade Out
		app->frontground->move_to = MOVE_TO::FINALCOMBAT_CUTSCENE_2;
		app->frontground->FadeToBlack();
		app->menu->dragonDefeated = false;
	}

	/*if (app->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		app->frontground->move_to = MOVE_TO::CREDITS;
		app->frontground->FadeToBlack();
	}*/

	return true;
}

// Called each loop iteration
bool Frontground::PostUpdate()
{
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;

	// draw cursor
	if (!controller)
	{
		app->input->GetMousePosition(c_mouse_pos.x, c_mouse_pos.y);
		app->render->DrawTexture(app->menu->cursor_tex, c_mouse_pos.x + c_x, c_mouse_pos.y + c_y);
	}
	else
	{
		app->render->DrawTexture(app->menu->cursor_tex, c_mouse_pos.x + c_x, c_mouse_pos.y + c_y);
	}
	
	r.x = c_x;
	r.y = c_y;
	if (a > 250)
	{
		app->render->DrawRectangle(r, 0, 0, 0, 255);
	}
	else
	{
		app->render->DrawRectangle(r, 0, 0, 0, a);
	}

	if (app->end_combat_scene->in_cutscene && app->end_combat_scene->Enabled() && app->end_combat_scene->cutcene_cd > BLACK_TIME)
	{
		if (app->end_combat_scene->cutcene_cd < 199 + BLACK_TIME )
		{
			app->render->DrawTexture(app->end_combat_scene->whitemark_1200x140, 40 + c_x, 290 + c_y);
			app->fonts->BlitTextLetter(300 + c_x, 320 + c_y, app->fonts->textFont1, "Pensabais que esto habia acabado????", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		}
		else if(app->end_combat_scene->cutcene_cd < 399 + BLACK_TIME)
		{
			app->render->DrawTexture(app->end_combat_scene->whitemark_1200x140, 40 + c_x, 290 + c_y);
			app->fonts->BlitTextLetter(300 + c_x, 320 + c_y, app->fonts->textFont1, "Nunca podreis acabar conmigo!!!!", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		}
		else if (app->end_combat_scene->cutcene_cd < 599 + BLACK_TIME)
		{
			app->render->DrawTexture(app->end_combat_scene->whitemark_1200x140, 40 + c_x, 290 + c_y);
			app->fonts->BlitTextLetter(300 + c_x, 320 + c_y, app->fonts->textFont1, "Oh, gran Lloyd resurge de nuevo...", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		}
		else if (app->end_combat_scene->cutcene_cd < 799 + BLACK_TIME)
		{
			app->render->DrawTexture(app->end_combat_scene->whitemark_1200x140, 40 + c_x, 290 + c_y);
			app->fonts->BlitTextLetter(300 + c_x, 320 + c_y, app->fonts->textFont1, "Y REDUCE A CENIZAS A ESTOS SERES!!!!", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		}
		else
		{
			return_black = true;
			fix = true;
		}
	}
	else if (!fix)
	{
		return_black = true;
		fix = true;
	}

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
	case MOVE_TO::SCENE_CUTSCENE_1: app->intro->Enable(); 
		break;
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
	case MOVE_TO::SCENE_INSIDE: app->inside->Enable(); app->menu->InitPlayer();
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
	case MOVE_TO::COMBAT_FINALCOMBAT: app->end_combat_scene->Enable(); app->menu->SetWinLoseScape(-1);
		return_black = false; break;
	case MOVE_TO::FINALCOMBAT_CUTSCENE_2: app->final_cut->Enable();
		break;
	case MOVE_TO::CREDITS: app->credits->Enable();
		break;
	default:
		break;
	}

	return true;
}

bool Frontground::FadeInCombat(ENEMIES enemies[], std::string rew)
{
	go_black = true;

	for (size_t i = 0; i < 4; i++)
	{
		enemies_to_fight[i] = enemies[i];
	}

	reward = rew;

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
	if (move_to != MOVE_TO::COMBAT_FINALCOMBAT)
	{
		move_to = MOVE_TO::RESET_COMBAT;
	}

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
	case 0: app->entities->GetPlayer()->SetPlayerPosition(app->entities->GetPlayer()->GetPlayerPosition().x, app->entities->GetPlayer()->GetPlayerPosition().y + 2 + 0.1f);
		break;
	case 1: app->entities->GetPlayer()->SetPlayerPosition(app->entities->GetPlayer()->GetPlayerPosition().x, app->entities->GetPlayer()->GetPlayerPosition().y - 2 + 0.1f);
		break;
	case 2: app->entities->GetPlayer()->SetPlayerPosition(app->entities->GetPlayer()->GetPlayerPosition().x - 2, app->entities->GetPlayer()->GetPlayerPosition().y + 0.1f);
		break;
	case 3: app->entities->GetPlayer()->SetPlayerPosition(app->entities->GetPlayer()->GetPlayerPosition().x + 2, app->entities->GetPlayer()->GetPlayerPosition().y + 0.1f);
		break;
	}

	direction = -1;
}

int Frontground::CheckAdventureState()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(SAVE_STATE_FILENAME);
	pugi::xml_node atr;

	int res = -1;

	atr = saveGame.child("game_state").child("entities").child("enemies");
	if (!atr.child("enemy0").attribute("state").as_bool() && !atr.child("enemy1").attribute("state").as_bool() && !atr.child("enemy2").attribute("state").as_bool()) // mison 1
	{
		res++;
	}
	if (app->dialog->GetRenatoText() >= 6)
	{
		res++;
	}
	if (!atr.child("enemy3").attribute("state").as_bool()) // mision 2
	{
		res++;
	}
	if (app->dialog->GetRenatoText() >= 10)
	{
		res++;
	}
	if (!atr.child("enemy4").attribute("state").as_bool()) // mision 3
	{
		res++;
	}
	if (app->dialog->GetRenatoText() >= 14)
	{
		res++;
	}
	if (!atr.child("enemy5").attribute("state").as_bool()) // castillo
	{
		res++;
	}

	switch (res)
	{
	case -1: app->dialog->SaveRenatoDialog(-1); app->dialog->SaveFarmerDialog(); break;
	case 0: app->dialog->SaveRenatoDialog(2); app->dialog->SaveFarmerDialog(); break;
	case 1: app->dialog->SaveRenatoDialog(6); app->dialog->SaveFarmerDialog(-1); break;
	case 2: app->dialog->SaveRenatoDialog(7); app->dialog->SaveFarmerDialog(-1); break;
	case 3: app->dialog->SaveRenatoDialog(10); app->dialog->SaveFarmerDialog(2); break;
	case 4: app->dialog->SaveRenatoDialog(11); app->dialog->SaveFarmerDialog(2); break;
	case 5: app->dialog->SaveRenatoDialog(14); app->dialog->SaveFarmerDialog(5); break;
	case 6: app->dialog->SaveRenatoDialog(15); app->dialog->SaveFarmerDialog(5); break;
	}

	if (res > adventure_phase)
	{
		if (res == 1 || res == 3 || res == 5)
		{
			app->dialog->UpdateShop();
		}
		
		move_to = MOVE_TO::FROM_COMBAT;
		FadeToBlack();
	}

	return res;
}

void Frontground::SaveStartUp()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(STARTED_FILENAME);

	saveGame.child("started").child("current_level").attribute("value").set_value(current_level);
	saveGame.child("started").child("adventure_phase").attribute("value").set_value(adventure_phase);

	saveGame.save_file(STARTED_FILENAME);

	app->dialog->SaveShop();
}