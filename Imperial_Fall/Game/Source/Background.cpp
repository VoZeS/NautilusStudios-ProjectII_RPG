#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Input.h"
#include "Scene.h"
#include "Background.h"
#include "Menu.h"

#include "Defs.h"
#include "Log.h"

Background::Background() : Module()
{
	name.Create("background");
}

// Destructor
Background::~Background()
{}

// Called before render is available
bool Background::Awake()
{

	return true;
}

// Called before the first frame
bool Background::Start()
{
	sky_r = { 0, 0, 2560 * 2, 1440 };
	sky_texture = app->tex->Load("Assets/textures/sky_solid_color.png");
	n_mountain_r = { 0, 0, 2560, 720 };
	n_mountain_texture = app->tex->Load("Assets/textures/n_mountain.png");
	f_mountain_r = { 0, 0, 2560, 800 };
	f_mountain_texture = app->tex->Load("Assets/textures/f_mountain.png");
	clouds_r = { 0, 0, 2400, 480 };
	clouds_texture = app->tex->Load("Assets/textures/clouds.png");

	return true;
}

// Called each loop iteration
bool Background::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Background::Update(float dt)
{
	if (!app->menu->GetGameState())
	{
		if (app->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			//n_mountain_parallaxX += 0;
			f_mountain_parallaxX += 1;
			clouds_parallaxX += 2;
			
		}
		if (app->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			//n_mountain_parallaxX -= 0;
			f_mountain_parallaxX -= 1;
			clouds_parallaxX -= 2;
		}
	}

	return true;
}

// Called each loop iteration
bool Background::PostUpdate()
{
	int c_x = -app->render->camera.x;
	app->render->DrawTexture(sky_texture, c_x, 0, &sky_r);
	app->render->DrawTexture(clouds_texture, c_x + clouds_parallaxX, 50, &clouds_r);
	app->render->DrawTexture(clouds_texture, c_x + 2560 + clouds_parallaxX, 50, &clouds_r); // parallax
	app->render->DrawTexture(clouds_texture, c_x + 5120 + clouds_parallaxX, 50, &clouds_r); // parallax
	app->render->DrawTexture(f_mountain_texture, c_x + f_mountain_parallaxX, 640, &f_mountain_r);
	app->render->DrawTexture(f_mountain_texture, c_x + 2560 + f_mountain_parallaxX, 640, &f_mountain_r); // parallax
	app->render->DrawTexture(f_mountain_texture, c_x + 5120 + f_mountain_parallaxX, 640, &f_mountain_r); // parallax
	app->render->DrawTexture(n_mountain_texture, n_mountain_parallaxX, 720, &n_mountain_r);
	app->render->DrawTexture(n_mountain_texture, 2560 + n_mountain_parallaxX, 720, &n_mountain_r);
	
	return true;
}

// Called before quitting
bool Background::CleanUp()
{

	return true;
}
