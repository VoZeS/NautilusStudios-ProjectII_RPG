#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "Frontground.h"
#include "Combat_Manager.h"
#include "Combat_Menu.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

Combat_Manager::Combat_Manager() : Module()
{
	name.Create("combat_manager");
}

// Destructor
Combat_Manager::~Combat_Manager()
{}

// Called before render is available
bool Combat_Manager::Awake()
{


	return true;
}

// Called before the first frame
bool Combat_Manager::Start()
{
	
	return true;
}

// Called each loop iteration
bool Combat_Manager::PreUpdate()
{
	if (app->frontground->GetCombatState() == 2)
	{
		in_combat = true;
	}

	if (in_combat && !app->menu->GetGameState())
	{
		if (!combat_init)
		{
			//init allies
			allies[0] = new Combat_Entities(100, 50, 12, 14, 0); // assassin
			allies[1] = new Combat_Entities(100, 50, 12, 14, 1); // tank
			allies[2] = new Combat_Entities(100, 50, 12, 14, 2); // healer
			allies[3] = new Combat_Entities(100, 50, 12, 14, 3); // wizard

			//init enemies


			//set turn order
		}
	}

	return true;
}

// Called each loop iteration
bool Combat_Menu::Update(float dt)
{
	if (in_combat)
	{
		
	}

	return true;
}

// Called each loop iteration
bool Combat_Menu::PostUpdate()
{
	if (in_combat)
	{
		
	}

	return true;
}

// Called before quitting
bool Combat_Menu::CleanUp()
{

	return true;
}
