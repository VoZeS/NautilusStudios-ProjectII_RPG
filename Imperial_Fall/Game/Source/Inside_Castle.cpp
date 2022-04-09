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
#include "Inside_Castle.h"
#include "Pathfinding.h"

#include "Defs.h"
#include "Log.h"

Inside_Castle::Inside_Castle(bool enabled) : Module(enabled)
{
	name.Create("inside_castle");
}

// Destructor
Inside_Castle::~Inside_Castle()
{}

// Called before render is available
bool Inside_Castle::Awake()
{
	LOG("Loading Inside Castle");

	return true;
}

// Called before the first frame
bool Inside_Castle::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("inside_castle.tmx");

		// Load music
		//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable Player & map
		app->entities->Enable();
		app->map->Enable();

		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(550), PIXELS_TO_METERS(1000));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(550), PIXELS_TO_METERS(1200));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(550), PIXELS_TO_METERS(1300));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(550), PIXELS_TO_METERS(1400));

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 7;
	}


	return true;
}

// Called each loop iteration
bool Inside_Castle::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Inside_Castle::Update(float dt)
{
	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Inside_Castle::PostUpdate()
{

	return true;
}

// Called before quitting
bool Inside_Castle::CleanUp()
{
	LOG("Freeing inside_castle");

	app->tex->CleanUp();
	app->map->Disable();
	app->entities->Disable();

	return true;
}