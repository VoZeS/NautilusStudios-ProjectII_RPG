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
#include "Dungeon.h"
#include "Pathfinding.h"

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
		//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable Player & map
		app->entities->Enable();
		app->map->Enable();
	
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(1100), PIXELS_TO_METERS(200));
				app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(200));
				app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(950), PIXELS_TO_METERS(200));
				app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(900), PIXELS_TO_METERS(200));

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 5;
	}


	return true;
}

// Called each loop iteration
bool Dungeon::PreUpdate()
{

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

	app->tex->CleanUp();
	app->map->Disable();
	app->entities->Disable();

	return true;
}