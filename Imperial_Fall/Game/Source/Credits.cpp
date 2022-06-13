#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Credits.h"
#include "Menu.h"
#include "Map.h"
#include "Dialog.h"
#include "Fonts.h"
#include "Frontground.h"

#include "Defs.h"
#include "Log.h"

Credits::Credits(bool enabled) : Module(enabled)
{
	name.Create("credits");

}

// Destructor
Credits::~Credits()
{}

// Called before render is available
bool Credits::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Credits::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		app->audio->StopMusic(1.0f);

		credits = app->tex->Load("Assets/textures/Creditos2.png");

		creditsRect.x = 0;
		creditsRect.y = 0;
		creditsRect.w = 1280;
		creditsRect.h = 3804;

		app->render->camera.x = 0;
		app->render->camera.y = 0;
	}

	return true;
}

// Called each loop iteration
bool Credits::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/Medieval_Music_-_Festival_Town.mp3");
	}

	return true;
}

// Called each loop iteration
bool Credits::Update(float dt)
{
	creditsCounter++;

	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;

	if (c_y < creditsRect.h + 600)
	{

		if (app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->render->camera.y -= 4;
		}
		else
		{
			app->render->camera.y -= 1;

		}
	}

	return true;
}

// Called each loop iteration
bool Credits::PostUpdate()
{
	bool ret = true;

	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;

	app->render->DrawTexture(credits, 0, 600, &creditsRect);

	if (c_y >= creditsRect.h + 600)
	{
		app->frontground->move_to = MOVE_TO::INSIDE_SCENE;
		app->frontground->FadeToBlack();
	}

	return ret;
}

// Called before quitting
bool Credits::CleanUp()
{
	LOG("Freeing scene");

	// clean textures

	return true;
}