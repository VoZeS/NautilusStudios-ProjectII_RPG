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

	// THESEION anim
	//TH_idleAnimD.PushBack({ 13, 0, 48, 76 });
	TH_idleAnimD.PushBack({ 67, 0, 48, 76 });
	TH_idleAnimD.speed = 0.03f;

	//TH_idleAnimL.PushBack({ 13, 76, 48, 76 });
	TH_idleAnimL.PushBack({ 67, 76, 48, 76 });
	TH_idleAnimL.speed = 0.03f;

	//TH_idleAnimR.PushBack({ 13, 157, 48, 76 });
	TH_idleAnimR.PushBack({ 67, 157, 48, 76 });
	TH_idleAnimR.speed = 0.03f;

	//TH_idleAnimU.PushBack({ 13, 238, 48, 76 });
	TH_idleAnimU.PushBack({ 67, 238, 48, 76 });
	TH_idleAnimU.speed = 0.03f;

	// TH walk animation
	TH_walkAnimD.PushBack({ 13, 0, 48, 76 });
	TH_walkAnimD.PushBack({ 67, 0, 48, 76 });
	TH_walkAnimD.PushBack({ 121, 0, 48, 76 });
	TH_walkAnimD.speed = 0.1f;

	TH_walkAnimL.PushBack({ 13, 76, 48, 76 });
	TH_walkAnimL.PushBack({ 67, 76, 48, 76 });
	TH_walkAnimL.PushBack({ 121, 76, 48, 76 });
	TH_walkAnimL.speed = 0.1f;

	TH_walkAnimR.PushBack({ 13, 157, 48, 76 });
	TH_walkAnimR.PushBack({ 67, 157, 48, 76 });
	TH_walkAnimR.PushBack({ 121, 157, 48, 76 });
	TH_walkAnimR.speed = 0.1f;

	TH_walkAnimU.PushBack({ 13, 238, 48, 76 });
	TH_walkAnimU.PushBack({ 67, 238, 48, 76 });
	TH_walkAnimU.PushBack({ 121, 238, 48, 76 });
	TH_walkAnimU.speed = 0.1f;

	// RENATO anim
	//R_idleAnimD.PushBack({ 16, 0, 50, 78 });
	R_idleAnimD.PushBack({ 66, 0, 50, 78 });
	R_idleAnimD.speed = 0.03f;

	//R_idleAnimL.PushBack({ 16, 78, 50, 78 });
	R_idleAnimL.PushBack({ 66, 78, 50, 78 });
	R_idleAnimL.speed = 0.03f;

	//R_idleAnimR.PushBack({ 16, 157, 50, 78 });
	R_idleAnimR.PushBack({ 66, 157, 50, 78 });
	R_idleAnimR.speed = 0.03f;

	//R_idleAnimU.PushBack({ 16, 236, 50, 78 });
	R_idleAnimU.PushBack({ 66, 236, 50, 78 });
	R_idleAnimU.speed = 0.03f;

	// R walk animation
	R_walkAnimD.PushBack({ 16, 0, 50, 78 });
	R_walkAnimD.PushBack({ 66, 0, 50, 78 });
	R_walkAnimD.PushBack({ 116, 0, 50, 78 });
	R_walkAnimD.speed = 0.1f;

	R_walkAnimL.PushBack({ 16, 78, 50, 78 });
	R_walkAnimL.PushBack({ 66, 78, 50, 78 });
	R_walkAnimL.PushBack({ 116, 78, 50, 78 });
	R_walkAnimL.speed = 0.1f;

	R_walkAnimR.PushBack({ 16, 157, 50, 78 });
	R_walkAnimR.PushBack({ 66, 157, 50, 78 });
	R_walkAnimR.PushBack({ 116, 157, 50, 78 });
	R_walkAnimR.speed = 0.1f;

	R_walkAnimU.PushBack({ 16, 236, 50, 78 });
	R_walkAnimU.PushBack({ 66, 236, 50, 78 });
	R_walkAnimU.PushBack({ 116, 236, 50, 78 });
	R_walkAnimU.speed = 0.1f;
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
		theseion_texture = app->tex->Load("Assets/textures/Theseion.png");
		renato_texture = app->tex->Load("Assets/textures/renato_bueno.png");

		whitemark_300x80 = app->tex->Load("Assets/textures/300x80_whitemark.png");
		whitemark_500x70 = app->tex->Load("Assets/textures/500x70_whitemark.png");
		whitemark_1200x140 = app->tex->Load("Assets/textures/1200x140_whitemark.png");

		W_currentAnimation = &W_idleAnimU;
		T_currentAnimation = &T_idleAnimU;
		H_currentAnimation = &H_idleAnimU;
		A_currentAnimation = &A_idleAnimU;
		TH_currentAnimation = &TH_idleAnimD;
		R_currentAnimation = &R_idleAnimL;

		Wizard.x = 1575;
		Wizard.y = 1800;

		Tank.x = 1575;
		Tank.y = 1850;

		Healer.x = 1625;
		Healer.y = 1800;

		Assassin.x = 1525;
		Assassin.y = 1800;

		Theseion.x = 1575;
		Theseion.y = 1250;

		Renato.x = 2300;
		Renato.y = 1800;
		
		counter = 0;

		inDialog = false;

		whiteMark_Name.x = 0;
		whiteMark_Name.y = 70;
		whiteMark_Name.w = 500;
		whiteMark_Name.h = 70;

	}

	return true;
}

// Called each loop iteration
bool Intro_Cutscene::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/zone1.ogg");
	}

	return true;
}

// Called each loop iteration
bool Intro_Cutscene::Update(float dt)
{
	counter++;

	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;
	
	W_idleAnimU.Update();
	T_idleAnimU.Update();
	H_idleAnimU.Update();
	A_idleAnimU.Update();
	TH_idleAnimD.Update();
	R_idleAnimL.Update();

	// Draw map
	app->map->Draw();

	if (c_y < 1250)
	{
		app->render->camera.y -= 4;
	}

	if (inDialog)
	{
		letter_cd++;

		if (letter_cd >= 60 * 0.05f && letlengh <= app->dialog->limitLenght)
		{
			letlengh++;
			app->dialog->PlayLetterSound();
			letter_cd = 0;
		}

		if (letter_cd >= 60 * 0.05f && letlengh2 <= app->dialog->limitLenght2)
		{
			letlengh2++;
			app->dialog->PlayLetterSound();
			letter_cd = 0;
		}

		if (counter == 800 || counter == 1200 || counter == 1500 || counter == 1600 || counter == 2000 || counter == 2400 || counter == 3200
			|| counter == 4000 || counter == 4400 || counter == 4800 || counter == 5200 || counter == 5600 || counter == 6000 
			|| counter == 6400 || counter == 6600 || counter == 7000 || counter == 7400)
		{
			letlengh = 0;
			letlengh2 = 0;
		}
	}

	if (counter >= 2400 && counter < 3250)
	{
		if (Theseion.x < 2000)
		{
			TH_currentAnimation = &TH_walkAnimR;
			TH_walkAnimR.Update();

			Theseion.x += 2;
		}
		else if (Theseion.y < 1590)
		{
			TH_currentAnimation = &TH_walkAnimD;
			TH_walkAnimD.Update();

			Theseion.y += 2;
		}

	}
	else if (counter >= 3250 && counter < 3700)
	{
		if (Theseion.y > 1250)
		{
			TH_currentAnimation = &TH_walkAnimU;
			TH_walkAnimU.Update();

			Theseion.y -= 2;
		}
		else if (Theseion.x > 1575)
		{
			TH_currentAnimation = &TH_walkAnimL;
			TH_walkAnimL.Update();

			Theseion.x -= 2;
		}
	}
	else if (counter >= 3700 && counter <= 7000)
	{
		if (Renato.x > 1780)
		{
			R_currentAnimation = &R_walkAnimL;
			R_walkAnimL.Update();

			Renato.x -= 2;
		}
		else
		{
			W_currentAnimation = &W_idleAnimR;
			H_currentAnimation = &H_idleAnimR;
			A_currentAnimation = &A_idleAnimR;
			T_currentAnimation = &T_idleAnimR;

			W_idleAnimR.Update();
			H_idleAnimR.Update();
			A_idleAnimR.Update();
			T_idleAnimR.Update();

		}
	}
	else if (counter >= 7450 && counter <= 7800)
	{
		if (Renato.x < 2300)
		{
			R_currentAnimation = &R_walkAnimR;
			R_walkAnimR.Update();

			Renato.x += 2;
		}
	}
	else if (counter > 7850)
	{
		cutscene_finished = true;
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
	app->render->AddrenderObject(theseion_texture, iPoint(Theseion.x, Theseion.y), TH_currentAnimation->GetCurrentFrame(), 1);
	app->render->AddrenderObject(renato_texture, iPoint(Renato.x, Renato.y), R_currentAnimation->GetCurrentFrame(), 1);

	if (counter >= 400 && counter < 800)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Fernan, el Brujo:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Mi familia... Mi vida... Todo quemado... AAAGHH!!", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Estoy cansado de esconderme. Lo pagaran. No los perdonare.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 800 && counter < 1200)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Gera, la Sanadora:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Se que es duro amigo. Pero no viviran para contarlo.", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Nosotros te ayudaremos. Verdad chicos?", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 1200 && counter < 1500)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Igol, el Astuto:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Claro que si!!", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Se arrepentiran de sus acciones.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 1500 && counter < 1600)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Igol, el Astuto:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, ".     .     .", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Aunque...", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 1600 && counter < 2000)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Igol, el Astuto:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Esto es obra de los templarios, verdad?", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Su lider da un poco de miedo...    No?", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 2000 && counter < 2400)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Asteriol, el Gigante:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Igol! No digas tonterias! Theseion es humano, cierto?", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Pues va a ver que toda accion tiene sus consecuencias.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 2800 && counter < 3200)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Theseion, el Cazador:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "HAHAHAHAH! Quemadlas a todas! TODAS LAS BRUJAS DEBEN MORIR!", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "ESTE PUEBLO DEBE TEMER A LOS ENVIADOS POR SATANAS!", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 4000 && counter < 4400)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "          ???");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Veo la furia en vuestras caras, jovenes.", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Y creo saber que es eso que os atormenta. Theseion, verdad?", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 4400 && counter < 4800)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Fernan, el Mago:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Puede ser. Que te importa? Dejanos.", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "De hecho, quien eres?", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 4800 && counter < 5200)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Igol, el Astuto:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Un viejo iniciando conversacion con 4 jovenes?", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Llamaria a los guardias, pero estos son templarios.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 5200 && counter < 5600)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Igol, el Astuto:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "No es que nos llevemos muy bien... asi que si la situacion", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "se pone tensa voy a sacar el cuchillo, te lo advierto.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 5600 && counter < 6000)
	{
	inDialog = true;
	app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
	app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
	app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Renato, el Sabio");
	app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Ja, ja.        Tranquilos. Me llamo Renato. Y yo tampoco", 1, 255, 255, 255, 1920, 1, letlengh, 1);
	app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "me llevo demasiado bien con los templarios.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 6000 && counter < 6400)
	{
	inDialog = true;
	app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
	app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
	app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Renato, el Sabio");
	app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Yo tambien ando persiguiendo mi venganza contra Theseion...", 1, 255, 255, 255, 1920, 1, letlengh, 1);
	app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Si os interesa, podemos hablar y juntos derrotarlo.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 6400 && counter < 6600)
	{
	inDialog = true;
	app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
	app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
	app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Gera, la Curandera");
	app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Habla. Pero cuida bien tus palabras, viejo.", 1, 255, 255, 255, 1920, 1, letlengh, 1);
	}
	else if (counter >= 6600 && counter < 7000)
	{
	inDialog = true;
	app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
	app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
	app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Renato, el Sabio");
	app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Theseion se ha ido de expedicion. Ahora que no esta", 1, 255, 255, 255, 1920, 1, letlengh, 1);
	app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "podemos debilitarlo atacando a sus 2 secuaces mas valiosos.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (counter >= 7000 && counter < 7400)
	{
	inDialog = true;
	app->render->DrawTexture(whitemark_500x70, 30 + c_x, 160 + c_y, &whiteMark_Name);
	app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 20 + c_y);
	app->fonts->BlitText(c_x + 50, c_y + 180, app->fonts->textFont1, "Renato, el Sabio");
	app->fonts->BlitTextLetter(c_x + 50, c_y + 60, app->fonts->textFont1, "Con ello sabremos cuando va a volver y acabar con el.", 1, 255, 255, 255, 1920, 1, letlengh, 1);
	app->fonts->BlitTextLetter(c_x + 50, c_y + 100, app->fonts->textFont1, "Pero aun no estais preparados. Venid a verme a mi casa.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else
	{
		inDialog = false;
	}

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