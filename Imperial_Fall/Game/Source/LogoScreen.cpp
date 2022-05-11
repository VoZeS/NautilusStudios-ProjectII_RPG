#include "LogoScreen.h"

#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Audio.h"
#include "Input.h"
#include "Map.h"
#include "Player.h"
#include "Frontground.h"
#include "Window.h"


LogoScreen::LogoScreen(bool enabled) : Module(enabled)
{

}

LogoScreen::~LogoScreen()
{

}

// Load assets
bool LogoScreen::Start()
{

	app->render->camera.x = 0;
	app->render->camera.y = 0;

	backgroundLogo.x = 0;
	backgroundLogo.y = 0;
	backgroundLogo.w = 1280;
	backgroundLogo.h = 720;
	
	logoRect.w = 283;
	logoRect.h = 260;
	logoRect.x = (app->win->screenSurface->w / 3) - (logoRect.w / 2);
	logoRect.y = (app->win->screenSurface->h / 4) - (logoRect.h / 2);
	

	// Members Texture

	//Aqui podem posar algun so a veure amb la pantalla d'inici
	//app->audio->PlayMusic("Assets/Audio/02_character_selection.ogg", 1.0f);

	logoTimer.Start();

	//Fade In

	return true;

}

bool LogoScreen::Update(float dt)
{

	// ScanCodes
	if (logoTimer.ReadSec() >= 3.0f || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		//Fade Out
		app->frontground->move_to = MOVE_TO::LOGO_SCENE;
		app->frontground->FadeToBlack();

	}

	else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		return false;
	}

	return true;
}

// Update: draw background
bool LogoScreen::PostUpdate()
{
	/*
	app->render->DrawRectangle(backgroundLogo, 84, 133, 255, 255);
	app->render->DrawTexture(logo, logoRect.x, logoRect.y, false, NULL);*/
	return true;
}
