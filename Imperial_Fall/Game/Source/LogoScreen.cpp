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
	logo_anim.PushBack({ 0, 0, 1280, 720 });
	logo_anim.PushBack({ 1280, 0, 1280, 720 });
	logo_anim.PushBack({ 2560, 0, 1280, 720 });
	logo_anim.PushBack({ 3840, 0, 1280, 720 });
	logo_anim.PushBack({ 5120, 0, 1280, 720 });
	logo_anim.PushBack({ 0, 720, 1280, 720 });
	logo_anim.PushBack({ 1280, 720, 1280, 720 });
	logo_anim.PushBack({ 2560, 720, 1280, 720 });
	logo_anim.PushBack({ 3840, 720, 1280, 720 });
	logo_anim.PushBack({ 5120, 720, 1280, 720 });
	logo_anim.PushBack({ 0, 0, 1280, 720 });
	logo_anim.PushBack({ 1280, 1440, 1280, 720 });
	logo_anim.PushBack({ 2560, 1440, 1280, 720 });
	logo_anim.PushBack({ 3840, 1440, 1280, 720 });
	logo_anim.PushBack({ 5120, 1440, 1280, 720 });
	logo_anim.PushBack({ 0, 2160, 1280, 720 });
	logo_anim.PushBack({ 1280, 2160, 1280, 720 });
	logo_anim.PushBack({ 2560, 2160, 1280, 720 });
	logo_anim.PushBack({ 3840, 2160, 1280, 720 });
	logo_anim.PushBack({ 3840, 2160, 1280, 720 });
	logo_anim.PushBack({ 3840, 2160, 1280, 720 });
	logo_anim.PushBack({ 3840, 2160, 1280, 720 });
	logo_anim.speed = 0.2f;
	logo_anim.loop = false;
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

	logo = app->tex->Load("Assets/textures/logo.png");
	currentAnim = &logo_anim;

	//logoTimer.Start();

	//Fade In

	return true;

}

bool LogoScreen::Update(float dt)
{

	// ScanCodes
	/*if (logoTimer.ReadSec() >= 3.0f || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		//Fade Out
		app->frontground->move_to = MOVE_TO::LOGO_SCENE;
		app->frontground->FadeToBlack();

	}
	else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		return false;
	}*/

	if (logo_anim.HasFinished() || app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP)
	{
		//Fade Out
		app->frontground->move_to = MOVE_TO::LOGO_SCENE;
		app->frontground->FadeToBlack();
	}

	currentAnim->Update();

	return true;
}

// Update: draw background
bool LogoScreen::PostUpdate()
{
	SDL_Rect r = currentAnim->GetCurrentFrame();
	//app->render->DrawRectangle(backgroundLogo, 84, 133, 255, 255);
	//app->render->DrawTexture(logo, logoRect.x, logoRect.y, false, NULL);
	app->render->DrawTexture(logo, 0, 0, &r);

	return true;
}

bool LogoScreen::CleanUp()
{
	// clean textures
	app->tex->UnLoad(logo);
	logo = NULL;

	return true;
}