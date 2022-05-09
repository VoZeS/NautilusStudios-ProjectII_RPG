#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Menu.h"
#include "Inventory.h"
#include "Map.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Combat_Entities.h"
#include "Player.h"
#include "Town1.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

Town1::Town1(bool enabled) : Module(enabled)
{
	name.Create("town1");
}

// Destructor
Town1::~Town1()
{}

// Called before render is available
bool Town1::Awake()
{
	LOG("Loading Town1");

	return true;
}

// Called before the first frame
bool Town1::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("town.tmx");


		// Load music
		//app->audio->PlayMusic("Assets/audio/music/zone1.ogg");
		app->audio->StopMusic(1.0f);

		//Enable Player & map
		app->menu->Enable();
		app->inventory->Enable();
		app->entities->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->dialog->Enable();
	
		if (app->frontground->move_to == MOVE_TO::TOWN2_TOWN1)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(2700), PIXELS_TO_METERS(1000), PIXELS_TO_METERS(2900), PIXELS_TO_METERS(1000),
				PIXELS_TO_METERS(3000), PIXELS_TO_METERS(1000), PIXELS_TO_METERS(3100), PIXELS_TO_METERS(1000));
		}
		else if (app->frontground->move_to == MOVE_TO::OUTSIDE_TOWN1 == true)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(800), PIXELS_TO_METERS(300), PIXELS_TO_METERS(800), PIXELS_TO_METERS(100),
				PIXELS_TO_METERS(800), PIXELS_TO_METERS(0), PIXELS_TO_METERS(800), PIXELS_TO_METERS(0));
		}
		else if (app->frontground->move_to == MOVE_TO::SCENE_TOWN1)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(1600), PIXELS_TO_METERS(1800), PIXELS_TO_METERS(1550), PIXELS_TO_METERS(1800),
				PIXELS_TO_METERS(1500), PIXELS_TO_METERS(1800), PIXELS_TO_METERS(1450), PIXELS_TO_METERS(1800));
		}

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 1;

		if (app->frontground->move_to != MOVE_TO::FROM_COMBAT)
		{
			app->LoadGameRequest(false);
		}
	}

	return true;
}

// Called each loop iteration
bool Town1::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/zone1.ogg");
	}

	return true;
}

// Called each loop iteration
bool Town1::Update(float dt)
{
	// Draw map
	app->map->Draw();

	//testing
	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		ENEMIES enemies[4];
		enemies[0] = ENEMIES::SKELETON;
		enemies[1] = ENEMIES::NOTHING;
		enemies[2] = ENEMIES::NOTHING;
		enemies[3] = ENEMIES::NOTHING;
		app->frontground->move_to = MOVE_TO::TOWN1_COMBAT;
		app->frontground->FadeInCombat(enemies, "999");
	}
	else if(app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		app->inventory->AddCoins(30);
	}
	else if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
	{
		app->inventory->AddCoins(-30);
	}

	return true;
}

// Called each loop iteration
bool Town1::PostUpdate()
{

	return true;
}

// Called before quitting
bool Town1::CleanUp()
{
	LOG("Freeing town1");
	app->tex->CleanUp();
	app->fonts->Disable();
	app->dialog->Disable();
	app->map->Disable();
	app->entities->Disable();
	app->inventory->Disable();
	app->menu->Disable();

	// clean textures

	return true;
}