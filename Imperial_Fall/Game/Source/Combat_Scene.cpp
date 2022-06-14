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
#include "Combat_Scene.h"
#include "Pathfinding.h"

#include "Defs.h"
#include "Log.h"

Combat_Scene::Combat_Scene(bool enabled) : Module(enabled)
{
	name.Create("combat_scene");
}

// Destructor
Combat_Scene::~Combat_Scene()
{}

// Called before render is available
bool Combat_Scene::Awake()
{
	LOG("Loading Combat_Scene");

	return true;
}

// Called before the first frame
bool Combat_Scene::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		switch (app->frontground->current_level)
		{
		case 1: app->map->Load("combat.tmx"); break;
		case 2: app->map->Load("combat.tmx"); break;
		case 3: app->map->Load("combat_dark.tmx"); break;
		case 4: app->map->Load("combat_light.tmx"); break;
		case 5: app->map->Load("combat.tmx"); break;
		case 6: app->map->Load("combat_outcastle.tmx"); break;
		case 7: app->map->Load("combat_castle.tmx"); break;
		}

		// Load music
		/*if (!app->entities->in_boss)
		{
			app->audio->PlayMusic("Assets/audio/music/combat.ogg");
		}
		else
		{
			app->audio->PlayMusic("Assets/audio/music/boss.ogg");
		}*/
		app->audio->StopMusic(1.0f);

		//Enable combat
		app->menu->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->combat_manager->Enable();
		app->combat_menu->Enable();
		app->particles->Enable();
	}


	return true;
}

// Called each loop iteration
bool Combat_Scene::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		if (!app->entities->in_boss)
		{
			app->audio->PlayMusic("Assets/audio/music/combat.ogg");
		}
		else
		{
			app->audio->PlayMusic("Assets/audio/music/boss.ogg");
		}
	}

	return true;
}

// Called each loop iteration
bool Combat_Scene::Update(float dt)
{
	// Draw map
	app->map->Draw();

	return true;
}

// Called each loop iteration
bool Combat_Scene::PostUpdate()
{

	return true;
}

// Called before quitting
bool Combat_Scene::CleanUp()
{
	LOG("Freeing combat_scene");
	app->tex->CleanUp();
	app->map->Disable();
	app->fonts->Disable();
	app->combat_manager->Disable();
	app->combat_menu->Disable();
	app->particles->Disable();
	app->menu->Disable();

	// clean textures

	return true;
}