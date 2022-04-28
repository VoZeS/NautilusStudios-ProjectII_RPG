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
#include "Forest.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Dialog.h"
#include "Physics.h"

#include "Defs.h"
#include "Log.h"

Forest::Forest(bool enabled) : Module(enabled)
{
	name.Create("forest");
}

// Destructor
Forest::~Forest()
{}

// Called before render is available
bool Forest::Awake()
{
	LOG("Loading Forest");

	return true;
}

// Called before the first frame
bool Forest::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("forest.tmx");

		// Load music
		app->audio->PlayMusic("Assets/audio/music/forest.ogg");

		//Enable Player & map
		app->menu->Enable();
		app->entities->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->dialog->Enable();

		app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(450), PIXELS_TO_METERS(500), PIXELS_TO_METERS(450), PIXELS_TO_METERS(300),
			PIXELS_TO_METERS(450), PIXELS_TO_METERS(200), PIXELS_TO_METERS(450), PIXELS_TO_METERS(100));

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 3;
		
		if (app->frontground->move_to != MOVE_TO::FROM_COMBAT)
		{
			app->LoadGameRequest(false);
		}
	}


	return true;
}

// Called each loop iteration
bool Forest::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Forest::Update(float dt)
{
	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Forest::PostUpdate()
{

	return true;
}

// Called before quitting
bool Forest::CleanUp()
{
	LOG("Freeing forest");
	app->menu->Disable();
	app->tex->CleanUp();
	app->fonts->Disable();
	app->dialog->Disable();
	app->map->Disable();
	app->entities->Disable();

	// clean textures

	return true;
}