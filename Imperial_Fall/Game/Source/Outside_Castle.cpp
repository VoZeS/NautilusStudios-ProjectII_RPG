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
#include "Outside_Castle.h"
#include "Pathfinding.h"

#include "Defs.h"
#include "Log.h"

Outside_Castle::Outside_Castle(bool enabled) : Module(enabled)
{
	name.Create("ouside_castle");
}

// Destructor
Outside_Castle::~Outside_Castle()
{}

// Called before render is available
bool Outside_Castle::Awake()
{
	LOG("Loading Outside Castle");

	return true;
}

// Called before the first frame
bool Outside_Castle::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("outside_castle.tmx");

		// Load music
		//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable Player & map
		app->entities->Enable();
		app->map->Enable();

		if (app->frontground->town1_to_outside == true)
		{
			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1300));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1500));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1600));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1700));
		}
		else if (app->frontground->inside_to_outside == true)
		{
			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(300));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(200));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(100));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(0));
		}

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 6;
	}


	return true;
}

// Called each loop iteration
bool Outside_Castle::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Outside_Castle::Update(float dt)
{
	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Outside_Castle::PostUpdate()
{

	return true;
}

// Called before quitting
bool Outside_Castle::CleanUp()
{
	LOG("Freeing outside_castle");

	app->tex->CleanUp();
	app->map->Disable();
	app->entities->Disable();

	return true;
}