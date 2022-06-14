#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Final_Cutscene.h"
#include "Menu.h"
#include "Map.h"
#include "Dialog.h"
#include "Fonts.h"
#include "Frontground.h"

#include "Defs.h"
#include "Log.h"

Final_Cutscene::Final_Cutscene(bool enabled) : Module(enabled)
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
Final_Cutscene::~Final_Cutscene()
{}

// Called before render is available
bool Final_Cutscene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Final_Cutscene::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		//Load Map
		app->map->Load("inside_castle.tmx");

		app->fonts->Enable();
		app->dialog->Enable();
		app->map->Enable();

		app->render->camera.x = -850;
		app->render->camera.y = 0;

		app->audio->StopMusic(1.0f);

		cutscene_finished = false;

		assassin_texture = app->tex->Load("Assets/textures/Asesino.png");
		tank_texture = app->tex->Load("Assets/textures/Tanque.png");
		healer_texture = app->tex->Load("Assets/textures/Healer.png");
		wizard_texture = app->tex->Load("Assets/textures/Mago.png");
		theseion_texture = app->tex->Load("Assets/textures/Theseion.png");
		renato_texture = app->tex->Load("Assets/textures/Renato_malo.png");
		dead_dragon_texture = app->tex->Load("Assets/maps/dragon1__r1732475211.png");

		whitemark_300x80 = app->tex->Load("Assets/textures/300x80_whitemark.png");
		whitemark_500x70 = app->tex->Load("Assets/textures/500x70_whitemark.png");
		whitemark_1200x140 = app->tex->Load("Assets/textures/1200x140_whitemark.png");
		whitemark_1240x680 = app->tex->Load("Assets/textures/1240x680_whitemark.png");

		door_fx = app->audio->LoadFx("Assets/audio/fx/azote_puerta.wav");

		W_currentAnimation = &W_idleAnimU;
		T_currentAnimation = &T_idleAnimU;
		H_currentAnimation = &H_idleAnimU;
		A_currentAnimation = &A_idleAnimU;
		TH_currentAnimation = &TH_idleAnimD;
		R_currentAnimation = &R_idleAnimR;

		Assassin.x = 1350;
		Assassin.y = 250;

		Tank.x = 1400;
		Tank.y = 250;

		Wizard.x = 1450;
		Wizard.y = 250;

		Healer.x = 1500;
		Healer.y = 250;

		Theseion.x = 1430;
		Theseion.y = 40;

		Renato.x = 700;
		Renato.y = 500;

		Dragon.x = 1600;
		Dragon.y = 100;

		counter = 0;

		inDialog = false;

		whiteMark_Name.x = 0;
		whiteMark_Name.y = 70;
		whiteMark_Name.w = 500;
		whiteMark_Name.h = 70;

		fx_played = false;
	}

	return true;
}

// Called each loop iteration
bool Final_Cutscene::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/inside_castle.ogg");
	}

	return true;
}

// Called each loop iteration
bool Final_Cutscene::Update(float dt)
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

		if (counter == 0 || counter == 100 || counter == 500 || counter == 900 || counter == 1300 || counter == 1700 || counter == 2300 || counter == 2700
			|| counter == 3200 || counter == 3600 || counter == 4000 || counter == 4400 || counter == 4800 || counter == 5200 || counter == 5750)
		{
			letlengh = 0;
			letlengh2 = 0;
		}
	}

	if (counter >= 1750 && counter <= 2300)
	{
		if (Renato.x < 1430)
		{
			R_currentAnimation = &R_walkAnimR;
			R_walkAnimR.Update();

			Renato.x += 2;
		}
		else if (Renato.y > 400)
		{
			R_currentAnimation = &R_walkAnimU;
			R_walkAnimU.Update();

			Renato.y -= 2;
		}
	}
	else if (counter >= 2300 && counter < 5250)
	{
		W_currentAnimation = &W_idleAnimD;
		W_idleAnimD.Update();
		T_currentAnimation = &T_idleAnimD;
		T_idleAnimD.Update();
		H_currentAnimation = &H_idleAnimD;
		H_idleAnimD.Update();
		A_currentAnimation = &A_idleAnimD;
		A_idleAnimD.Update();
	}
	else if (counter > 5750)
	{
		cutscene_finished = true;
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		cutscene_finished = true;
	}

	if (cutscene_finished)
	{
		cutscene_finished = false;

		//Fade Out
		app->frontground->move_to = MOVE_TO::CREDITS;
		app->frontground->FadeToBlack();
	}


	return true;
}

// Called each loop iteration
bool Final_Cutscene::PostUpdate()
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
	app->render->AddrenderObject(dead_dragon_texture, iPoint(Dragon.x, Dragon.y), Dragon, 1);

	if (counter >= 5200)
	{
	app->render->DrawRectangle({ 0,0,2200,1080 }, 0, 0, 0, 255);
	if (!fx_played)
	{
		app->audio->PlayFx(door_fx);
		fx_played = true;
	}
	app->audio->StopMusic(0.0f);
	}

	if (counter >= 100 && counter < 500)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Fernan, el Brujo:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Por fin... Todo lo luchado... Mi venganza se ha cumplido...", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "Pero... Me siento raro... Ahora siento un gran vacio en mi.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 500 && counter < 900)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Gera, la Sanadora:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Es normal Fernan. Ha sido un largo viaje, amigo.", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "Ahora toca ser feliz. Vivir. Simplemente. Vivir. Nada mas.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 900 && counter < 1300)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Igol, el Astuto:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Jajajajaja. Mira a Theseion. Se ha quedado sentado en su", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "silla. Parece como si estuviera vivo, eh? Aunque mas palido.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 1300 && counter < 1700)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Asteriol, el Gigante:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Si. Pero ya te digo yo que de ahi no se levanta.", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "Igual que su dragon. Pobre bestia... Obligada a luchar asi...", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 2300 && counter < 2700)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Fernan, el Mago:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Renato? Que haces aqui? Pensabamos que estarias en", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "tu casa. Ahora ibamos a informarte: Theseion esta muerto.", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 2800 && counter < 3200)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Igol, el Astuto:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Chicos... Soy yo el unico que ve raro a Renato?", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "Sera el cambio en su vestimenta? Me gustaba mas antes...", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 3200 && counter < 3600)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Renato, el Sabio:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "HAHAHAHAHAH! Tan gracioso como siempre, Igol...", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "Gracias por acabar con Theseion. Quien lo diria...", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 3600 && counter < 4000)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Renato, el Sabio:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Quien diria que unos simples crios conseguirian lo que", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "tanto ansiaba... Pero ahora ya esta hecho! Ya tengo el poder!", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 4000 && counter < 4400)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Gera, la Sanadora:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Crios?? A quien llama crios?? De que esta hablando??", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "Me esta empezando a dar miedo... Chicos?", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 4400 && counter < 4800)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Renato, el Sabio:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Mi hermano! Por fin muerto! HAHAHAHAHAHAH!", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "Ahora tengo yo el poder! Ahora estoy yo al mando!", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 4800 && counter < 5200)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Renato, el Sabio:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Pero vosotros... Sois demasiado poderosos...", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "No podeis salir libres de aqui. Guardias! Encerradlos!", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (counter >= 5350 && counter < 5750)
	{
		inDialog = true;
		app->render->DrawTexture(whitemark_500x70, 30 + c_x, 480 + c_y, &whiteMark_Name);
		app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
		app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "Renato, el Sabio:");
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, "Es vuestro fin muchachos. Ya no valeis nada para mi.", 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, "Pero tranquilos... No os va a doler mucho...", 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else
	{
		inDialog = false;
	}

	return ret;
}

// Called before quitting
bool Final_Cutscene::CleanUp()
{
	LOG("Freeing scene");

	app->fonts->Disable();

	app->dialog->Disable();
	app->map->Disable();

	// clean textures

	return true;
}