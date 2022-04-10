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
		//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable Player & map
		app->entities->Enable();
		app->map->Enable();

		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(600), PIXELS_TO_METERS(2800));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3000));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3100));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3200));

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 4;
		app->LoadGameRequest(false);
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

	app->tex->CleanUp();
	app->map->Disable();
	app->entities->Disable();

	return true;
}