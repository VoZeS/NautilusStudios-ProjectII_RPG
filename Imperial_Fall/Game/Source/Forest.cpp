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

	// moving animation
	movingBox_Anim.PushBack({ 0, 0, 64, 65 });
	movingBox_Anim.PushBack({ 64, 0, 64, 65 });
	movingBox_Anim.PushBack({ 128, 0, 64, 65 });
	movingBox_Anim.speed = 0.03f;
	movingBox_Anim.loop = true;
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
		//app->audio->PlayMusic("Assets/audio/music/forest.ogg");
		app->audio->StopMusic(1.0f);

		//Load Box Tex
		box_texture = app->tex->Load("Assets/textures/S_Box.png");

		//Enable Player & map
		app->menu->Enable();
		app->inventory->Enable();
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

		currentAnimation = &movingBox_Anim;
	}

	boxRect = { 0, 0, 64,65 };

	return true;
}

// Called each loop iteration
bool Forest::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/forest.ogg");
	}

	return true;
}

// Called each loop iteration
bool Forest::Update(float dt)
{
	if (app->physics->inSignal && app->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
	{
		// town_2 --> forest
		app->frontground->move_to = MOVE_TO::TOWN2_FOREST;

		app->frontground->FadeToBlack();
	}


	if (app->map->S1_Box != nullptr)
	{
		currentAnimation->Update();
	}

	if (app->physics->box1Done && app->physics->box2Done && app->physics->box3Done && app->physics->box4Done)
	{
		allBoxesDone = true;
	}

	if (app->map->S1_Box != nullptr && box_texture != nullptr && !allBoxesDone)
	{
		app->render->AddrenderObject(box_texture, { METERS_TO_PIXELS(app->map->S1_Box->GetBody()->GetPosition().x - 32), METERS_TO_PIXELS(app->map->S1_Box->GetBody()->GetPosition().y - 32) }, boxRect, 0, 1.0f, 0.0f);

		//app->render->DrawTexture(box_texture, METERS_TO_PIXELS(app->map->S1_Box->GetBody()->GetPosition().x - 32), METERS_TO_PIXELS(app->map->S1_Box->GetBody()->GetPosition().y - 32), &boxRect);
	}
	if (app->map->S2_Box != nullptr && box_texture != nullptr && !allBoxesDone)
	{
		app->render->AddrenderObject(box_texture, { METERS_TO_PIXELS(app->map->S2_Box->GetBody()->GetPosition().x - 32), METERS_TO_PIXELS(app->map->S2_Box->GetBody()->GetPosition().y - 32) }, boxRect, 0, 1.0f, 0.0f);

		//app->render->DrawTexture(box_texture, METERS_TO_PIXELS(app->map->S2_Box->GetBody()->GetPosition().x - 32), METERS_TO_PIXELS(app->map->S2_Box->GetBody()->GetPosition().y - 32), &boxRect);
	}
	if (app->map->S3_Box != nullptr && box_texture != nullptr && !allBoxesDone)
	{
		app->render->AddrenderObject(box_texture, { METERS_TO_PIXELS(app->map->S3_Box->GetBody()->GetPosition().x - 32), METERS_TO_PIXELS(app->map->S3_Box->GetBody()->GetPosition().y - 32) }, boxRect, 0, 1.0f, 0.0f);

		//app->render->DrawTexture(box_texture, METERS_TO_PIXELS(app->map->S3_Box->GetBody()->GetPosition().x - 32), METERS_TO_PIXELS(app->map->S3_Box->GetBody()->GetPosition().y - 32), &boxRect);
	}
	if (app->map->S4_Box != nullptr && box_texture != nullptr && !allBoxesDone)
	{
		app->render->AddrenderObject(box_texture, { METERS_TO_PIXELS(app->map->S4_Box->GetBody()->GetPosition().x - 32), METERS_TO_PIXELS(app->map->S4_Box->GetBody()->GetPosition().y - 32) }, boxRect, 0, 1.0f, 0.0f);

		//app->render->DrawTexture(box_texture, METERS_TO_PIXELS(app->map->S4_Box->GetBody()->GetPosition().x - 32), METERS_TO_PIXELS(app->map->S4_Box->GetBody()->GetPosition().y - 32), &boxRect);
	}


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
	app->inventory->Disable();
	app->entities->Disable();

	// clean textures

	return true;
}