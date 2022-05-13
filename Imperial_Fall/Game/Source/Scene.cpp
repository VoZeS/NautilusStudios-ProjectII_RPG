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
#include "AssetsManager.h"

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
	// TODO 5: Uncomment all of this, resolve how to load the document from the memory with the link

	char* buffer = NULL;
	pugi::xml_document dataFile;

	int bytesFile = app->assetsmanager->LoadData("data.xml", &buffer);

	// Loading from memory with PUGI: https://pugixml.org/docs/manual.html#loading.memory
	pugi::xml_parse_result result = dataFile.load_buffer(buffer, bytesFile);

	RELEASE_ARRAY(buffer);

	LoadTexFile(dataFile);
	LoadFxFile(dataFile);
	LoadMusFile(dataFile);


	/*if (this->Enabled() && !this->Disabled())
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
	*/
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


		app->render->DrawTexture(texture1, app->render->camera.x, app->render->camera.y);
		

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
	
	app->fonts->Disable();
	app->menu->Disable();

	// clean textures
	app->tex->UnLoad(start_screen);
	start_screen = NULL;
	app->tex->UnLoad(settings_screen);
	settings_screen = NULL;

	return true;
}

void Scene::LoadTexFile(const pugi::xml_document& dataFile)
{
	pugi::xml_node tex_node = dataFile.child("data").child("texture");
	texture1 = app->tex->Load(tex_node.attribute("file").as_string());
	texture2 = app->tex->Load(tex_node.attribute("file2").as_string());
}

void Scene::LoadFxFile(const pugi::xml_document& dataFile)
{
	pugi::xml_node fx_node = dataFile.child("data").child("fx");
	app->audio->LoadFx(fx_node.attribute("file").as_string());
}

void Scene::LoadMusFile(const pugi::xml_document& dataFile)
{
	pugi::xml_node mus_node = dataFile.child("data").child("mus");
	app->audio->PlayMusic(mus_node.attribute("file").as_string());
}