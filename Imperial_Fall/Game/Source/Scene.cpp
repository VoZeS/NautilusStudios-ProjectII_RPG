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
#include "Town1.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene(bool enabled) : Module(enabled)
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	c_y_menu = -app->render->camera.y + 0; // Posicion de la camara en el inicio del juego
	
	start_screen = app->tex->Load("Assets/textures/Menu_BackGround.png");
	settings_screen = app->tex->Load("Assets/textures/Settings_BackGround.png");

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		if (!app->frontground->GetCombatState())
		{
			ENEMIES enemies[4];
			enemies[0] = ENEMIES::MUSHROOM;
			enemies[1] = ENEMIES::W_TEMPLAR;
			enemies[2] = ENEMIES::SKELETON;
			enemies[3] = ENEMIES::GOBLIN;
			app->frontground->FadeInCombat(enemies);
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		if (app->frontground->GetCombatState())
		{
			app->frontground->ReturnToField();
		}
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	
	bool ret = true;
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;	
	
	//--------------------------------------MENU----------------------------


	//Desplazamiento del fondo al inicio del juego
	//Una vez pulses el Espacio entrara el menu de opciones
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || desMenu == true)
	{
		space_boton = false;
		desMenu = true;
		c_y_menu -= 10.0f;
		fuegoSeguir = true;

	}

	//Limite de donde la camara llegara al principio del juego
	if (c_y_menu <= -700)
	{
		esc = true;
		desMenu = false;
		fuegoSeguir = false;
    }

	//Primera pantalla menu
	if (esc == false && app->menu->settings == false)
	{
		app->render->DrawTexture(start_screen, c_x, c_y_menu);
	}	

	//----------------------------------------------------
	//-------------------Settings
	if (app->menu->settings == true)
	{
		app->render->DrawTexture(settings_screen, c_x, c_y);
	}
	
	//Segunda Pantalla Menu
	if (start_screen != NULL && esc == true && app->menu->settings == false)
	{
		app->render->DrawTexture(start_screen, c_x, c_y - 700);
	}

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	app->tex->CleanUp();

	return true;
}