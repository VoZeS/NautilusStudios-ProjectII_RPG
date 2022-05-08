#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Menu.h"
#include "Scene.h"
#include "Map.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Combat_Manager.h"
#include "Combat_Menu.h"
#include "Combat_Entities.h"
#include "Particles.h"
#include "Player.h"
#include "End_Combat_Scene.h"
#include "Pathfinding.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

End_Combat_Scene::End_Combat_Scene(bool enabled) : Module(enabled)
{
	name.Create("end_combat_scene");
}

// Destructor
End_Combat_Scene::~End_Combat_Scene()
{}

// Called before render is available
bool End_Combat_Scene::Awake()
{
	LOG("Loading End-Combat_Scene");

	return true;
}

// Called before the first frame
bool End_Combat_Scene::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("end_combat.tmx", app->tex);

		// Load music
		app->audio->StopMusic(1.0f);
		evil_laugh = app->audio->LoadFx("Assets/audio/fx/evil_laugh.wav");
		dragon_roar = app->audio->LoadFx("Assets/audio/fx/dragon_roar.wav");

		whitemark_1200x140 = app->tex->Load("Assets/textures/1200x140_whitemark.png");

		//Enable combat
		app->menu->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->combat_manager->Enable();
		app->combat_menu->Enable();
		app->particles->Enable();
		app->dialog->Enable();

		in_cutscene = true;
		cutcene_cd = 0;
	}


	return true;
}

// Called each loop iteration
bool End_Combat_Scene::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		cutcene_cd = 9999;
	}

	if (in_cutscene)
	{
		cutcene_cd++;
		if (cutcene_cd == 150 + BLACK_TIME)
		{
			app->audio->PlayFx(evil_laugh);
		}
		else if (cutcene_cd == 400 + BLACK_TIME)
		{
			app->audio->PlayMusic("Assets/audio/music/misterius.ogg", 0.0f);
		}
		else if (cutcene_cd == 700 + BLACK_TIME)
		{
			app->audio->PlayFx(dragon_roar);
		}
		else if (cutcene_cd >= 800 + BLACK_TIME)
		{
			in_cutscene = false;
			cutcene_cd = 0;
			app->audio->PlayMusic("Assets/audio/music/final_boss.ogg");
		}
	}

	return true;
}

// Called each loop iteration
bool End_Combat_Scene::Update(float dt)
{
	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool End_Combat_Scene::PostUpdate()
{

	return true;
}

// Called before quitting
bool End_Combat_Scene::CleanUp()
{
	LOG("Freeing combat_scene");
	app->tex->CleanUp();
	app->map->Disable();
	app->fonts->Disable();
	app->combat_manager->Disable();
	app->combat_menu->Disable();
	app->particles->Disable();
	app->dialog->Disable();
	app->menu->Disable();

	// clean textures

	return true;
}