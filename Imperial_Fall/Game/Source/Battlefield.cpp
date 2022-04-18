#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Menu.h"
#include "Map.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Combat_Entities.h"
#include "Player.h"
#include "Battlefield.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

Battlefield::Battlefield(bool enabled) : Module(enabled)
{
	name.Create("battlefield");
}

// Destructor
Battlefield::~Battlefield()
{}

// Called before render is available
bool Battlefield::Awake()
{
	LOG("Loading Battlefield");

	return true;
}

// Called before the first frame
bool Battlefield::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("battlefield.tmx");

		// Load music
		app->audio->PlayMusic("Assets/audio/music/battlefield.ogg");

		//Enable Player & map
		app->menu->Enable();
		app->entities->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->dialog->Enable();

	if (app->frontground->move_to == MOVE_TO::TOWN2_BATTLEFIELD)
	{
		app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(600), PIXELS_TO_METERS(2800), PIXELS_TO_METERS(600), PIXELS_TO_METERS(3000),
			PIXELS_TO_METERS(600), PIXELS_TO_METERS(3100), PIXELS_TO_METERS(600), PIXELS_TO_METERS(3200));
	}
	else if (app->frontground->move_to == MOVE_TO::SCENE_BATTLEFIELD)
	{
		app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(600), PIXELS_TO_METERS(2800), PIXELS_TO_METERS(600), PIXELS_TO_METERS(3000),
			PIXELS_TO_METERS(600), PIXELS_TO_METERS(3100), PIXELS_TO_METERS(600), PIXELS_TO_METERS(3200));
	}
		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 4;

		if (app->frontground->move_to != MOVE_TO::FROM_COMBAT)
		{
			app->LoadGameRequest(false);
		}
	}


	return true;
}

// Called each loop iteration
bool Battlefield::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Battlefield::Update(float dt)
{
	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Battlefield::PostUpdate()
{

	return true;
}

// Called before quitting
bool Battlefield::CleanUp()
{
	LOG("Freeing battlefield");
	app->menu->Disable();
	app->tex->CleanUp();
	app->fonts->Disable();
	app->dialog->Disable();
	app->map->Disable();
	app->entities->Disable();

	// clean textures

	return true;
}