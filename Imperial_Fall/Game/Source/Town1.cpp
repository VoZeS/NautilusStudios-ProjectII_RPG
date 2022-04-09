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
#include "Town1.h"
#include "Pathfinding.h"

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
		app->map->Load("town_1.tmx");

		// Load music
		//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable Player & map
		app->entities->Enable();
		app->map->Enable();
	
		if (app->frontground->town2_to_town1 == true)
		{
			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(2700), PIXELS_TO_METERS(1000));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(2900), PIXELS_TO_METERS(1000));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(3000), PIXELS_TO_METERS(1000));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(3100), PIXELS_TO_METERS(1000));
		}
		else if (app->frontground->outside_to_town1 == true)
		{
			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(800), PIXELS_TO_METERS(300));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(800), PIXELS_TO_METERS(100));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(800), PIXELS_TO_METERS(0));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(800), PIXELS_TO_METERS(0));
		}
		else if (app->frontground->scene_to_town1)
		{
			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(800), PIXELS_TO_METERS(950));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
			app->entities->GetPlayer()->SetCompanion0LookDir(0);
			app->entities->GetPlayer()->SetCompanion1LookDir(0);
			app->entities->GetPlayer()->SetCompanion2LookDir(0);
		}

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 1;
	}

	return true;
}

// Called each loop iteration
bool Town1::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Town1::Update(float dt)
{
	// Draw map
	app->map->Draw();

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
	app->map->Disable();
	app->entities->Disable();

	return true;
}