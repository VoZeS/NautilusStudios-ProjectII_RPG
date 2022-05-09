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
#include "Outside_Castle.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

Outside_Castle::Outside_Castle(bool enabled) : Module(enabled)
{
	name.Create("ouside_castle");

	lever1Anim.PushBack({ 0, 0, 32,  32});
	lever1Anim.PushBack({ 0, 32, 32,  32});
	lever1Anim.PushBack({ 0, 64, 32,  32});
	lever1Anim.speed = 1.0f;
	lever1Anim.loop = false;

	lever2Anim.PushBack({ 0, 0, 32,  32 });
	lever2Anim.PushBack({ 0, 32, 32,  32 });
	lever2Anim.PushBack({ 0, 64, 32,  32 });
	lever2Anim.speed = 1.0f;
	lever2Anim.loop = false;
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
		//app->audio->PlayMusic("Assets/audio/music/outside_castle.ogg");
		app->audio->StopMusic(1.0f);

		//Enable Player & map
		app->menu->Enable();
		app->inventory->Enable();
		app->entities->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->dialog->Enable();

		if (app->frontground->move_to == MOVE_TO::TOWN1_OUTSIDE)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1300), PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1500),
				PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1600), PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1700));
		}
		else if (app->frontground->move_to == MOVE_TO::INSIDE_OUTSIDE == true)
		{
			app->entities->SetPlayerSavedPos(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(300), PIXELS_TO_METERS(1000), PIXELS_TO_METERS(200),
				PIXELS_TO_METERS(1000), PIXELS_TO_METERS(100), PIXELS_TO_METERS(1000), PIXELS_TO_METERS(0));
		}

		int w, h;
		uchar* data = NULL;

		if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

		app->frontground->current_level = 6;
		
		if (app->frontground->move_to != MOVE_TO::FROM_COMBAT)
		{
			app->LoadGameRequest(false);
		}

		leverText = app->tex->Load("Assets/textures/lever.png");

		currentAnimL1 = &lever1Anim;
		currentAnimL2 = &lever2Anim;

	}


	return true;
}

// Called each loop iteration
bool Outside_Castle::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/outside_castle.ogg");
	}

	return true;
}

// Called each loop iteration
bool Outside_Castle::Update(float dt)
{
	if (app->physics->inLever1 && app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		currentAnimL1->Update();
		lever1Active = true;
	}
	if (app->physics->inLever2 && app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		currentAnimL2->Update();
		lever2Active = true;

	}

	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Outside_Castle::PostUpdate()
{
	if (app->physics->lever[0].body != nullptr && app->physics->lever[1].body != nullptr)
	{
		app->render->AddrenderObject(leverText, { METERS_TO_PIXELS(app->physics->lever[0].body->GetPosition().x - 32.0f), METERS_TO_PIXELS(app->physics->lever[0].body->GetPosition().y - 32.0f) }, currentAnimL1->GetCurrentFrame(), 1, 1.0f, 0.0f);
		app->render->AddrenderObject(leverText, { METERS_TO_PIXELS(app->physics->lever[1].body->GetPosition().x - 32.0f), METERS_TO_PIXELS(app->physics->lever[1].body->GetPosition().y - 32.0f) }, currentAnimL2->GetCurrentFrame(), 1, 1.0f, 0.0f);

	}
	
	return true;
}

// Called before quitting
bool Outside_Castle::CleanUp()
{
	LOG("Freeing outside_castle");
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