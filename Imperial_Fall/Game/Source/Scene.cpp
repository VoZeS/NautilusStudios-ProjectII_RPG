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
	if (this->Enabled() && !this->Disabled())
	{
		app->fonts->Enable();

		c_y_menu = -app->render->camera.y + 0; // Posicion de la camara en el inicio del juego

		start_screen = app->tex->Load("Assets/textures/Menu_BackGround.png");
		settings_screen = app->tex->Load("Assets/textures/Settings_BackGround.png");
	

		//app->audio->PlayMusic("Assets/audio/music/menu.ogg");
		app->audio->StopMusic(1.0f);

		if (!app->menu->Enabled())
		{
			app->menu->Enable();
		}
	}

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/menu.ogg");
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	
	bool ret = true;
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;	

	if (app->frontground->controller)
	{
		GamePad& pad = app->input->pads[0];

		if (pad.a == true)
		{
			app->input->SetKey(SDL_SCANCODE_Y, KEY_REPEAT);
		}
	}
	
	//--------------------------------------MENU----------------------------


	//Desplazamiento del fondo al inicio del juego
	//Una vez pulses el Espacio entrara el menu de opciones
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP || desMenu == true)
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
		
		app->render->DrawTexture(start_screen, c_x, c_y - 700);
		app->render->DrawRectangle(app->menu->r, 0, 0, 0, 200);
		app->render->DrawTexture(settings_screen, c_x, app->menu->c_y_corre);
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
	
	app->fonts->Disable();
	app->menu->Disable();

	// clean textures
	app->tex->UnLoad(start_screen);
	start_screen = NULL;
	app->tex->UnLoad(settings_screen);
	settings_screen = NULL;

	return true;
}