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
#include "Dungeon.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

Dungeon::Dungeon(bool enabled) : Module(enabled)
{
	name.Create("dungeon");
}

// Destructor
Dungeon::~Dungeon()
{}

// Called before render is available
bool Dungeon::Awake()
{
	LOG("Loading Dungeon");

	return true;
}

// Called before the first frame
bool Dungeon::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("dungeon.tmx");

		// Load music
		//app->audio->PlayMusic("Assets/audio/music/dungeon.ogg");
		app->audio->StopMusic(1.0f);

		//Enable Player & map
		app->menu->Enable();
		app->inventory->Enable();
		app->entities->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->dialog->Enable();

		app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(1100), PIXELS_TO_METERS(200), PIXELS_TO_METERS(1000), PIXELS_TO_METERS(200),
			PIXELS_TO_METERS(950), PIXELS_TO_METERS(200), PIXELS_TO_METERS(900), PIXELS_TO_METERS(200));


		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 5;
		
		if (app->frontground->move_to != MOVE_TO::FROM_COMBAT)
		{
			app->LoadGameRequest(false);
		}
	}


	return true;
}

// Called each loop iteration
bool Dungeon::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/dungeon.ogg");
	}

	return true;
}

// Called each loop iteration
bool Dungeon::Update(float dt)
{
	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Dungeon::PostUpdate()
{

	return true;
}

// Called before quitting
bool Dungeon::CleanUp()
{
	LOG("Freeing dungeon");
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