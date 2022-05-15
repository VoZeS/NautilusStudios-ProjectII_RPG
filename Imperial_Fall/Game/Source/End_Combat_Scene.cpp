#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Menu.h"
#include "Scene.h"
#include "Map.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Combat_Manager.h"
#include "Combat_Menu.h"
#include "Combat_Entities.h"
#include "Particles.h"
#include "Player.h"
#include "End_Combat_Scene.h"
#include "Pathfinding.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

End_Combat_Scene::End_Combat_Scene(bool enabled) : Module(enabled)
{
	name.Create("end_combat_scene");

	fire_loop.PushBack({ 0, 0, 64, 64 });
	fire_loop.PushBack({ 64, 0, 64, 64 });
	fire_loop.PushBack({ 128, 0, 64, 64 });
	fire_loop.PushBack({ 192, 0, 64, 64 });
	fire_loop.PushBack({ 256, 0, 64, 64 });
	fire_loop.PushBack({ 320, 0, 64, 64 });
	fire_loop.PushBack({ 384, 0, 64, 64 });
	fire_loop.speed = 0.03f;
}

// Destructor
End_Combat_Scene::~End_Combat_Scene()
{}

// Called before render is available
bool End_Combat_Scene::Awake()
{
	LOG("Loading End-Combat_Scene");

	return true;
}

// Called before the first frame
bool End_Combat_Scene::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("end_combat.tmx");

		// Load music
		app->audio->StopMusic(1.0f);
		evil_laugh = app->audio->LoadFx("Assets/audio/fx/evil_laugh.wav");
		dragon_roar = app->audio->LoadFx("Assets/audio/fx/dragon_roar.wav");

		whitemark_1200x140 = app->tex->Load("Assets/textures/1200x140_whitemark.png");
		fire_tex = app->tex->Load("Assets/textures/fire.png");

		//Enable combat
		app->menu->Enable();
		app->map->Enable();
		app->fonts->Enable();
		app->combat_manager->Enable();
		app->combat_menu->Enable();
		app->particles->Enable();
		app->dialog->Enable();

		in_cutscene = true;
		cutcene_cd = 0;

		fire = &fire_loop;
	}


	return true;
}

// Called each loop iteration
bool End_Combat_Scene::PreUpdate()
{
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		cutcene_cd = 9999;
	}

	if (in_cutscene)
	{
		cutcene_cd++;
		if (cutcene_cd == 150 + BLACK_TIME)
		{
			app->audio->PlayFx(evil_laugh);
		}
		else if (cutcene_cd == 400 + BLACK_TIME)
		{
			app->audio->PlayMusic("Assets/audio/music/misterius.ogg", 0.0f);
		}
		else if (cutcene_cd == 700 + BLACK_TIME)
		{
			app->audio->PlayFx(dragon_roar);
		}
		else if (cutcene_cd >= 800 + BLACK_TIME)
		{
			in_cutscene = false;
			cutcene_cd = 0;
			app->audio->PlayMusic("Assets/audio/music/final_boss.ogg");
		}
	}

	return true;
}

// Called each loop iteration
bool End_Combat_Scene::Update(float dt)
{
	// Draw map
	app->map->Draw();

	fire->Update();

	return true;
}

// Called each loop iteration
bool End_Combat_Scene::PostUpdate()
{
	app->render->DrawTexture(fire_tex, 50, 500, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 450, 100, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 863, 600, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 700, 150, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 968, 200, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 230, 387, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 140, 450, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 268, 560, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 1030, 40, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 1140, 135, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 650, 420, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 700, 480, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 530, 563, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 830, 354, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 426, 475, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 678, 387, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 598, 362, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 543, 156, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 1030, 132, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 1140, 478, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 990, 450, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 256, 120, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 154, 162, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 400, 300, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 324, 224, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 1030, 256, &fire->GetCurrentFrame());
	app->render->DrawTexture(fire_tex, 114, 123, &fire->GetCurrentFrame());

	return true;
}

// Called before quitting
bool End_Combat_Scene::CleanUp()
{
	LOG("Freeing combat_scene");
	app->tex->CleanUp();
	app->map->Disable();
	app->fonts->Disable();
	app->combat_manager->Disable();
	app->combat_menu->Disable();
	app->particles->Disable();
	app->dialog->Disable();
	app->menu->Disable();

	// clean textures

	return true;
}