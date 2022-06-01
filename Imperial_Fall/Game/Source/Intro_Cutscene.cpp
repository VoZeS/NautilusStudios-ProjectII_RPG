#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Intro_Cutscene.h"
#include "Menu.h"
#include "Map.h"
#include "Dialog.h"
#include "Fonts.h"
#include "Frontground.h"

#include "Defs.h"
#include "Log.h"

Intro_Cutscene::Intro_Cutscene(bool enabled) : Module(enabled)
{
	name.Create("intro_cutscene");

	// WIZARD idle animation
	W_idleAnimD.PushBack({ 5, 0, 50, 74 });
	W_idleAnimD.PushBack({ 65, 0, 50, 74 });
	W_idleAnimD.speed = 0.03f;

	W_idleAnimU.PushBack({ 5, 240, 50, 74 });
	W_idleAnimU.PushBack({ 65, 240, 50, 74 });
	W_idleAnimU.speed = 0.03f;

	W_idleAnimL.PushBack({ 5, 80, 50, 74 });
	W_idleAnimL.PushBack({ 65, 80, 50, 74 });
	W_idleAnimL.speed = 0.03f;

	W_idleAnimR.PushBack({ 5, 159, 50, 74 });
	W_idleAnimR.PushBack({ 65, 159, 50, 74 });
	W_idleAnimR.speed = 0.03f;

	// main walk animation
	W_walkAnimD.PushBack({ 5, 0, 50, 74 });
	W_walkAnimD.PushBack({ 65, 0, 50, 74 });
	W_walkAnimD.PushBack({ 125, 0, 50, 74 });
	W_walkAnimD.speed = 0.1f;

	W_walkAnimU.PushBack({ 5, 240, 50, 74 });
	W_walkAnimU.PushBack({ 65, 240, 50, 74 });
	W_walkAnimU.PushBack({ 125, 240, 50, 74 });
	W_walkAnimU.speed = 0.1f;

	W_walkAnimL.PushBack({ 5, 80, 50, 74 });
	W_walkAnimL.PushBack({ 65, 80, 50, 74 });
	W_walkAnimL.PushBack({ 125, 80, 50, 74 });
	W_walkAnimL.speed = 0.1f;

	W_walkAnimR.PushBack({ 5, 159, 50, 74 });
	W_walkAnimR.PushBack({ 65, 159, 50, 74 });
	W_walkAnimR.PushBack({ 125, 159, 50, 74 });
	W_walkAnimR.speed = 0.1f;

	// TANK idle animation
	T_idleAnimD.PushBack({ 5, 2, 50, 72 });
	T_idleAnimD.PushBack({ 65, 2, 50, 72 });
	T_idleAnimD.speed = 0.03f;

	T_idleAnimU.PushBack({ 5, 242, 50, 72 });
	T_idleAnimU.PushBack({ 65, 242, 50, 72 });
	T_idleAnimU.speed = 0.03f;

	T_idleAnimL.PushBack({ 5, 82, 50, 72 });
	T_idleAnimL.PushBack({ 65, 82, 50, 72 });
	T_idleAnimL.speed = 0.03f;

	T_idleAnimR.PushBack({ 5, 161, 50, 72 });
	T_idleAnimR.PushBack({ 65, 161, 50, 72 });
	T_idleAnimR.speed = 0.03f;

	// T walk animation
	T_walkAnimD.PushBack({ 5, 2, 50, 72 });
	T_walkAnimD.PushBack({ 65, 2, 50, 72 });
	T_walkAnimD.PushBack({ 125, 2, 50, 72 });
	T_walkAnimD.speed = 0.1f;

	T_walkAnimU.PushBack({ 5, 242, 50, 72 });
	T_walkAnimU.PushBack({ 65, 242, 50, 72 });
	T_walkAnimU.PushBack({ 125, 242, 50, 72 });
	T_walkAnimU.speed = 0.1f;

	T_walkAnimL.PushBack({ 5, 82, 50, 72 });
	T_walkAnimL.PushBack({ 65, 82, 50, 72 });
	T_walkAnimL.PushBack({ 125, 82, 50, 72 });
	T_walkAnimL.speed = 0.1f;

	T_walkAnimR.PushBack({ 5, 161, 50, 72 });
	T_walkAnimR.PushBack({ 65, 161, 50, 72 });
	T_walkAnimR.PushBack({ 125, 161, 50, 72 });
	T_walkAnimR.speed = 0.1f;

	// HEALER idle animation
	H_idleAnimD.PushBack({ 5, 2, 50, 72 });
	H_idleAnimD.PushBack({ 65, 2, 50, 72 });
	H_idleAnimD.speed = 0.03f;

	H_idleAnimU.PushBack({ 5, 242, 50, 72 });
	H_idleAnimU.PushBack({ 65, 242, 50, 72 });
	H_idleAnimU.speed = 0.03f;

	H_idleAnimL.PushBack({ 5, 82, 50, 72 });
	H_idleAnimL.PushBack({ 65, 82, 50, 72 });
	H_idleAnimL.speed = 0.03f;

	H_idleAnimR.PushBack({ 5, 161, 50, 72 });
	H_idleAnimR.PushBack({ 65, 161, 50, 72 });
	H_idleAnimR.speed = 0.03f;

	// H walk animation
	H_walkAnimD.PushBack({ 5, 2, 50, 72 });
	H_walkAnimD.PushBack({ 65, 2, 50, 72 });
	H_walkAnimD.PushBack({ 125, 2, 50, 72 });
	H_walkAnimD.speed = 0.1f;

	H_walkAnimU.PushBack({ 5, 242, 50, 72 });
	H_walkAnimU.PushBack({ 65, 242, 50, 72 });
	H_walkAnimU.PushBack({ 125, 242, 50, 72 });
	H_walkAnimU.speed = 0.1f;

	H_walkAnimL.PushBack({ 5, 82, 50, 72 });
	H_walkAnimL.PushBack({ 65, 82, 50, 72 });
	H_walkAnimL.PushBack({ 125, 82, 50, 72 });
	H_walkAnimL.speed = 0.1f;

	H_walkAnimR.PushBack({ 5, 161, 50, 72 });
	H_walkAnimR.PushBack({ 65, 161, 50, 72 });
	H_walkAnimR.PushBack({ 125, 161, 50, 72 });
	H_walkAnimR.speed = 0.1f;

	// ASSASSIN idle animation
	A_idleAnimD.PushBack({ 5, 2, 50, 72 });
	A_idleAnimD.PushBack({ 65, 2, 50, 72 });
	A_idleAnimD.speed = 0.03f;

	A_idleAnimU.PushBack({ 5, 242, 50, 72 });
	A_idleAnimU.PushBack({ 65, 242, 50, 72 });
	A_idleAnimU.speed = 0.03f;

	A_idleAnimL.PushBack({ 5, 82, 50, 72 });
	A_idleAnimL.PushBack({ 65, 82, 50, 72 });
	A_idleAnimL.speed = 0.03f;

	A_idleAnimR.PushBack({ 5, 161, 50, 72 });
	A_idleAnimR.PushBack({ 65, 161, 50, 72 });
	A_idleAnimR.speed = 0.03f;

	// A walk animation
	A_walkAnimD.PushBack({ 5, 2, 50, 72 });
	A_walkAnimD.PushBack({ 65, 2, 50, 72 });
	A_walkAnimD.PushBack({ 125, 2, 50, 72 });
	A_walkAnimD.speed = 0.1f;

	A_walkAnimU.PushBack({ 5, 242, 50, 72 });
	A_walkAnimU.PushBack({ 65, 242, 50, 72 });
	A_walkAnimU.PushBack({ 125, 242, 50, 72 });
	A_walkAnimU.speed = 0.1f;

	A_walkAnimL.PushBack({ 5, 82, 50, 72 });
	A_walkAnimL.PushBack({ 65, 82, 50, 72 });
	A_walkAnimL.PushBack({ 125, 82, 50, 72 });
	A_walkAnimL.speed = 0.1f;

	A_walkAnimR.PushBack({ 5, 161, 50, 72 });
	A_walkAnimR.PushBack({ 65, 161, 50, 72 });
	A_walkAnimR.PushBack({ 125, 161, 50, 72 });
	A_walkAnimR.speed = 0.1f;
}

// Destructor
Intro_Cutscene::~Intro_Cutscene()
{}

// Called before render is available
bool Intro_Cutscene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Intro_Cutscene::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("town_1_64.tmx");

		app->fonts->Enable();
		app->dialog->Enable();
		app->map->Enable();

		app->frontground->current_level = -1;

		app->render->camera.x = -950;
		app->render->camera.y = -250;

		app->audio->StopMusic(1.0f);

		cutscene_finished = false;

		assassin_texture = app->tex->Load("Assets/textures/Asesino.png");
		tank_texture = app->tex->Load("Assets/textures/Tanque.png");
		healer_texture = app->tex->Load("Assets/textures/Healer.png");
		wizard_texture = app->tex->Load("Assets/textures/Mago.png");

		W_currentAnimation = &W_idleAnimU;
		T_currentAnimation = &T_idleAnimU;
		H_currentAnimation = &H_idleAnimU;
		A_currentAnimation = &A_idleAnimU;

		Wizard.x = 1575;
		Wizard.y = 1800;

		Tank.x = 1575;
		Tank.y = 1850;

		Healer.x = 1625;
		Healer.y = 1800;

		Assassin.x = 1525;
		Assassin.y = 1800;
		
	}

	return true;
}

// Called each loop iteration
bool Intro_Cutscene::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/menu.ogg");
	}

	return true;
}

// Called each loop iteration
bool Intro_Cutscene::Update(float dt)
{
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;
	
	W_idleAnimU.Update();
	T_idleAnimU.Update();
	H_idleAnimU.Update();
	A_idleAnimU.Update();

	// Draw map
	app->map->Draw();

	if (c_y < 1250)
	{
		app->render->camera.y -= 4;
	}

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
	{
		cutscene_finished = true;
	}

	if (cutscene_finished)
	{
		cutscene_finished = false;

		//Fade Out
		app->frontground->move_to = MOVE_TO::SCENE_TOWN1;
		app->frontground->FadeToBlack();
	}


	return true;
}

// Called each loop iteration
bool Intro_Cutscene::PostUpdate()
{

	bool ret = true;
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;

	app->render->AddrenderObject(wizard_texture, iPoint(Wizard.x, Wizard.y), W_currentAnimation->GetCurrentFrame(), 1);
	app->render->AddrenderObject(healer_texture, iPoint(Healer.x, Healer.y), H_currentAnimation->GetCurrentFrame(), 1);
	app->render->AddrenderObject(assassin_texture, iPoint(Assassin.x, Assassin.y), A_currentAnimation->GetCurrentFrame(), 1);
	app->render->AddrenderObject(tank_texture, iPoint(Tank.x, Tank.y), T_currentAnimation->GetCurrentFrame(), 1);

	return ret;
}

// Called before quitting
bool Intro_Cutscene::CleanUp()
{
	LOG("Freeing scene");

	app->fonts->Disable();

	app->dialog->Disable();
	app->map->Disable();

	// clean textures

	return true;
}