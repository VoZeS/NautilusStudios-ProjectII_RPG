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
#include "Town2.h"
#include "Pathfinding.h"

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
		app->map->Load("town_2.tmx");

		// Load music
		//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable Player &
		app->entities->Enable();
		app->map->Enable();
		

		if (app->frontground->town1_to_town2 == true)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1600));
			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1600));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(200), PIXELS_TO_METERS(1600));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(100), PIXELS_TO_METERS(1600));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(0), PIXELS_TO_METERS(1600));
		}
		else if (app->frontground->forest_to_town2 == true)
		{
			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(2350), PIXELS_TO_METERS(2600));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(2350), PIXELS_TO_METERS(2800));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(2350), PIXELS_TO_METERS(2900));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(2350), PIXELS_TO_METERS(3000));
		}
		else if (app->frontground->battlefield_to_town2 == true)
		{
			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(2350), PIXELS_TO_METERS(400));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(2350), PIXELS_TO_METERS(200));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(2350), PIXELS_TO_METERS(100));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(2350), PIXELS_TO_METERS(0));
		}
		else if (app->frontground->dungeon_to_town2 == true)
		{
			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(850), PIXELS_TO_METERS(1850));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(850), PIXELS_TO_METERS(1850));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(850), PIXELS_TO_METERS(1850));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(850), PIXELS_TO_METERS(1850));
		}

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 2;
	}

	return true;
}

// Called each loop iteration
bool Town2::PreUpdate()
{

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

	app->tex->CleanUp();
	app->map->Disable();
	app->entities->Disable();

	return true;
}