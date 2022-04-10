#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Menu.h"
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
		app->map->Load("combat.tmx");

		// Load music
		//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

		//Enable combat
		app->combat_manager->Enable();
		app->combat_menu->Enable();
		app->particles->Enable();
	}


	return true;
}

// Called each loop iteration
bool Combat_Scene::PreUpdate()
{

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

	app->combat_manager->Disable();
	app->combat_menu->Disable();
	app->particles->Disable();

	// clean textures

	return true;
}