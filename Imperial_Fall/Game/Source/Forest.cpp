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
		//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable Player & map
		app->entities->Enable();
		app->map->Enable();

		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(450), PIXELS_TO_METERS(500));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(300));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(200));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(100));

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 3;
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

	app->tex->CleanUp();
	app->map->Disable();
	app->entities->Disable();

	return true;
}