#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Menu.h"
#include "Map.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Player.h"
#include "Coins.h"
#include "Hearts.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
	godmode = false;
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
	app->SaveGameRequest();

	start_screen = app->tex->Load("Assets/textures/Start_screen.png");
	
	// Load music
	app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");


	char lookupTableChars[] = { " !'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxyz{|}~ ������a��������a��������" };
	textFont = app->fonts->Load("Assets/textures/pixel_letters.png", lookupTableChars, 8);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{

	if (start_screen != NULL && app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)  
	{
		PassLevel(1);
	}
	else
	{
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);
		iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
		p = app->map->WorldToMap(p.x, p.y);

		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			if (originSelected == true)
			{
				app->pathfinding->CreatePath(origin, p);
				originSelected = false;
			}
			else
			{
				origin = p;
				originSelected = true;
			}
		}
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		PassLevel(1);
	}
	else if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		PassLevel(2);
	}
	else if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		PassLevel(current_level);
	}
	else if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		app->SaveGameRequest();
	}
	else if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		app->LoadGameRequest();
	}
	else if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		godmode = !godmode;
	}
	else if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		app->ToggleFPS();
	}

	// Draw map
	if (start_screen != NULL)
	{
		app->map->Draw();
		
	}

	if (godmode)
	{
		if (app->input->GetKey(SDL_SCANCODE_LEFT))
		{
			app->render->MoveCamera(-5);
		}
		if (app->input->GetKey(SDL_SCANCODE_RIGHT))
		{
			app->render->MoveCamera(5);
		}
	}

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	bool ret = true;

	int c_x = -app->render->camera.x;

	if (start_screen != NULL) 
	{
		app->render->DrawTexture(start_screen, 0, 0);
	}
	else
	{
		app->map->Draw();

		app->fonts->BlitText(c_x + 30, 5, textFont, "MONEDAS: ");
		app->fonts->BlitText(c_x + 330, 5, textFont, app->entities->numCoins);
		app->fonts->BlitText(c_x + 30, 45, textFont, "VIDAS: ");
		app->fonts->BlitText(c_x + 250, 45, textFont, app->entities->numLifes);
	}
	
	if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool Scene::GetStartScreenState()
{
	if (start_screen != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Scene::PassLevel(int dest_level)
{
	if (start_screen != NULL)
	{
		app->frontground->SetA_Black();
		app->frontground->FadeFromBlack(dest_level);
	}
	else
	{
		app->frontground->FadeToBlack(dest_level);
	}

	start_screen = NULL;

	return true;
}

bool Scene::QuitStartScreen()
{
	start_screen = NULL;

	return true;
}

bool Scene::ReturnStartScreen()
{
	start_screen = app->tex->Load("Assets/textures/Start_screen.png");

	return true;
}
