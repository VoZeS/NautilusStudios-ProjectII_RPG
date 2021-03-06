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
#include "Inside_Castle.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Dialog.h"

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
		//app->audio->PlayMusic("Assets/audio/music/inside_castle.ogg");
		app->audio->StopMusic(1.0f);

		//Enable Player & map
		app->menu->Enable();
		app->inventory->Enable();
		app->entities->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->dialog->Enable();

		app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(550), PIXELS_TO_METERS(1000));

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 7;
		
		if (app->frontground->move_to != MOVE_TO::FROM_COMBAT)
		{
			app->LoadGameRequest(false);
		}
	}


	return true;
}

// Called each loop iteration
bool Inside_Castle::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/inside_castle.ogg");
	}

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