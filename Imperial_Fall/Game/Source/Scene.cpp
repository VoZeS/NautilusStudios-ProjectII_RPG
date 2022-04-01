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
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");


	char lookupTableChars[] = { " !'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxyz{|}~ çüéâäàaçêëèïîìäaéÆæôöòûù" };
	textFont = app->fonts->Load("Assets/textures/pixel_letters.png", lookupTableChars, 8);

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{

	if (start_screen != NULL && app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)  
	{
		app->entities->GetPlayer()->SetPlayerLookDir(0);
		PassLevel(1);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(800), PIXELS_TO_METERS(950));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
		app->entities->GetPlayer()->SetCompanion0LookDir(0);
		app->entities->GetPlayer()->SetCompanion1LookDir(0);
		app->entities->GetPlayer()->SetCompanion2LookDir(0);
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
	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		app->entities->GetPlayer()->SetPlayerLookDir(0);
		PassLevel(1);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(800), PIXELS_TO_METERS(1000));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1000));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1000));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1000));
		app->entities->GetPlayer()->SetCompanion0LookDir(0);
		app->entities->GetPlayer()->SetCompanion1LookDir(0);
		app->entities->GetPlayer()->SetCompanion2LookDir(0);
	}
	else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(2);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1600));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(200), PIXELS_TO_METERS(1600));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(100), PIXELS_TO_METERS(1600));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(0), PIXELS_TO_METERS(1600));
	}
	else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(3);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(450), PIXELS_TO_METERS(500));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(300));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(200));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(100));
	}
	else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(4);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(600), PIXELS_TO_METERS(2800));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3000));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3100));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3200));
	}
	else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(5);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(1100), PIXELS_TO_METERS(200));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(200));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(950), PIXELS_TO_METERS(200));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(900), PIXELS_TO_METERS(200));
	}
	else if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(6);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1300));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1500));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1600));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1700));
	}
	else if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(7);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(500), PIXELS_TO_METERS(800));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(600));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(500));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(400));
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

	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		if (!app->frontground->GetCombatState())
		{
			app->frontground->FadeInCombat();
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
