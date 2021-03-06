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
#include "Town2.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

Town2::Town2(bool enabled) : Module(enabled)
{
	name.Create("town2");
}

// Destructor
Town2::~Town2()
{}

// Called before render is available
bool Town2::Awake()
{
	LOG("Loading Town2");

	return true;
}

// Called before the first frame
bool Town2::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("town_2_64.tmx");

		// Load music
		//app->audio->PlayMusic("Assets/audio/music/zone2.ogg");
		app->audio->StopMusic(1.0f);

		//Enable Player &
		app->menu->Enable();
		app->inventory->Enable();
		app->entities->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->dialog->Enable();
		

		if (app->frontground->move_to == MOVE_TO::TOWN1_TOWN2)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(256), PIXELS_TO_METERS(3328));
		}
		else if (app->frontground->move_to == MOVE_TO::FOREST_TOWN2)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(4736), PIXELS_TO_METERS(5429));
		}
		else if (app->frontground->move_to == MOVE_TO::BATTLEFIELD_TOWN2)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(4672), PIXELS_TO_METERS(640));
		}
		else if (app->frontground->move_to == MOVE_TO::DUNGEON_TOWN2)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(1728), PIXELS_TO_METERS(4288));
		}
		else if (app->frontground->move_to == MOVE_TO::SCENE_TOWN2)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(1472), PIXELS_TO_METERS(3328));
		}

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 2;
		
		if (app->frontground->move_to != MOVE_TO::FROM_COMBAT)
		{
			app->LoadGameRequest(false);
		}
	}

	return true;
}

// Called each loop iteration
bool Town2::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/zone2.ogg");
	}

	return true;
}

// Called each loop iteration
bool Town2::Update(float dt)
{

	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Town2::PostUpdate()
{

	return true;
}

// Called before quitting
bool Town2::CleanUp()
{
	LOG("Freeing town2");
	app->menu->Disable();
	app->tex->CleanUp();
	app->fonts->Disable();
	app->dialog->Disable();
	app->map->Disable();
	app->inventory->Disable();
	app->entities->Disable();

	// clean textures

	return true;
}