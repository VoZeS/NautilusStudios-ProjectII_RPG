#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Map.h"
#include "Pathfinding.h"
#include "Player.h"
#include "Frontground.h"

#include "Defs.h"
#include "Log.h"

Frontground::Frontground() : Module()
{
	name.Create("frontground");
	a = 0;
}

// Destructor
Frontground::~Frontground()
{}

// Called before render is available
bool Frontground::Awake()
{

	return true;
}

// Called before the first frame
bool Frontground::Start()
{
	r = { 0, 0, 1280, 720 };

	press_e = app->tex->Load("Assets/textures/PressE.png");

	return true;
}

// Called each loop iteration
bool Frontground::PreUpdate()
{
	if (go_black)
	{
		if (a < 256 - fade_speed)
		{
			a += fade_speed;
		}
		else if (a < 255)
		{
			a++;
		}
	}
	else if (return_black)
	{
		if (a > fade_speed)
		{
			a -= fade_speed;
		}
		else if (a > 0)
		{
			a--;
		}
	}

	return true;
}

// Called each loop iteration
bool Frontground::Update(float dt)
{
	if (a >= 255)
	{
		go_black = false;
		FadeFromBlack(destination_level);
		
	}
	else if (a <= 0)
	{
		return_black = false;
	}

	return true;
}

// Called each loop iteration
bool Frontground::PostUpdate()
{
	int c_x = -app->render->camera.x;

	if (!press_e_hide)
	{
		app->render->DrawRectangle({ c_x + 640 , 650, 100, 25 }, 255, 255, 255, 150);
		app->render->DrawTexture(press_e, c_x + 640, 650);
	}

	r.x = c_x;

	app->render->DrawRectangle(r, 0, 0, 0, a);

	return true;
}

// Called before quitting
bool Frontground::CleanUp()
{

	return true;
}

bool Frontground::FadeToBlack(int dest_level)
{
	go_black = true;
	if (dest_level != -1) destination_level = dest_level;

	return true;
}

bool Frontground::FadeFromBlack(int dest_level)
{
	return_black = true;

	if (dest_level != -1)
	{
		app->map->CleanMaps();
		app->physics->CleanMapBoxes();
		app->map->collision_loaded = false;

		switch (dest_level)
		{
		case 0:
			app->scene->ReturnStartScreen();
			break;
		case 1: 
			app->SaveGameRequest();
			if (app->map->Load("battlefield.tmx") == true)
			{
				int w, h;
				uchar* data = NULL;

				if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

				RELEASE_ARRAY(data);
			}
			app->scene->current_level = 1;
			break;
		case 2:
			app->SaveGameRequest();
			if (app->map->Load("town_2.tmx") == true)
			{
				int w, h;
				uchar* data = NULL;

				if (app->map->CreateWalkabilityMap(w, h, &data)) app->pathfinding->SetMap(w, h, data);

				RELEASE_ARRAY(data);
			}
			app->scene->current_level = 2;
			break;
		}
	}


	return true;
}

