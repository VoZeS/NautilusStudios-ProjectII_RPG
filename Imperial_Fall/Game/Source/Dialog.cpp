#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Menu.h"
#include "Fonts.h"
#include "Physics.h"
#include "Frontground.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

Dialog::Dialog(bool enabled) : Module(enabled)
{
	name.Create("dialog");

	idle_e.PushBack({ 0, 0, 128, 136 });
	idle_e.PushBack({ 128, 0, 128, 136 });
	idle_e.speed = 0.05f;
}

// Destructor
Dialog::~Dialog()
{}

// Called before render is available
bool Dialog::Awake()
{

	return true;
}

// Called before the first frame
bool Dialog::Start()
{
	whitemark_1200x140 = app->tex->Load("Assets/textures/1200x140_whitemark.png");
	whitemark_300x80 = app->tex->Load("Assets/textures/300x80_whitemark.png");

	press_e = app->tex->Load("Assets/textures/Boton_E.png");
	anim = &idle_e;

	LoadDialog();

	//Text 1
	linea1String_Renato[0] = dialog.child("renato").child("text1").attribute("linea1").as_string();
	linea2String_Renato[0] = dialog.child("renato").child("text1").attribute("linea2").as_string();

	linea1String_Renato[1] = dialog.child("renato").child("text2").attribute("linea1").as_string();
	linea2String_Renato[1] = dialog.child("renato").child("text2").attribute("linea2").as_string();

	linea1String_Renato[2] = dialog.child("renato").child("text3").attribute("linea1").as_string();
	linea2String_Renato[2] = dialog.child("renato").child("text3").attribute("linea2").as_string();

	linea1String_Renato[3] = dialog.child("renato").child("text4").attribute("linea1").as_string();
	linea2String_Renato[3] = dialog.child("renato").child("text4").attribute("linea2").as_string();

	linea1String_Renato[4] = dialog.child("renato").child("text5").attribute("linea1").as_string();
	linea2String_Renato[4] = dialog.child("renato").child("text5").attribute("linea2").as_string();

	for (int i = 0; i < 5; i++)
	{
		linea1Char_Renato[i] = linea1String_Renato[i].c_str();
		linea2Char_Renato[i] = linea2String_Renato[i].c_str();
	}

	linea1String_Herrero = dialog.child("herrero").child("text1").attribute("linea1").as_string();
	linea2String_Herrero = dialog.child("herrero").child("text1").attribute("linea2").as_string();

	linea1Char_Herrero = linea1String_Herrero.c_str();
	linea2Char_Herrero = linea2String_Herrero.c_str();



	linea1String_Granjero = dialog.child("granjero").child("text1").attribute("linea1").as_string();
	linea2String_Granjero = dialog.child("granjero").child("text1").attribute("linea2").as_string();

	linea1Char_Granjero = linea1String_Granjero.c_str();
	linea2Char_Granjero = linea2String_Granjero.c_str();



	linea1String_Medico = dialog.child("granjero").child("text1").attribute("linea1").as_string();
	linea2String_Medico = dialog.child("granjero").child("text1").attribute("linea2").as_string();

	linea1Char_Medico = linea1String_Medico.c_str();
	linea2Char_Medico = linea2String_Medico.c_str();

	linea1String_Aldeano = dialog.child("aldeano").child("text1").attribute("linea1").as_string();

	linea1Char_Aldeano = linea1String_Aldeano.c_str();


	/*
	linea1String_Templario = dialog.child("templario").child("text1").attribute("linea1").as_string();
	linea2String_Templario = dialog.child("templario").child("text1").attribute("linea2").as_string();
	
	linea1Char_Templario = linea1String_Templario.c_str();
	linea2Char_Templario = linea2String_Templario.c_str();


	
	linea1String_Seta = dialog.child("seta").child("text1").attribute("linea1").as_string();
	linea2String_Seta = dialog.child("seta").child("text1").attribute("linea2").as_string();

	linea1Char_Seta = linea1String_Seta.c_str();
	linea2Char_Seta = linea2String_Seta.c_str();
	*/
	return true;
}

// Called each loop iteration
bool Dialog::PreUpdate()
{

	return true;
}

// Called each loop iteration
bool Dialog::Update(float dt)
{
	if (app->frontground->controller)
	{
		GamePad& pad = app->input->pads[0];

		if (pad.b == true)
		{
			app->input->SetKey(SDL_SCANCODE_E, KEY_REPEAT);
		}
	}

	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_UP)
	{
		if (app->physics->GetInNPC(1))
		{
			if (!app->menu->redtemplar_killed)
			{
				if (ContinueDialog(renato_text, renato_maxtext - 1))
				{
					letlengh = 0;
					letlengh2 = 0;

					inDialog = true;
					actual_dialog = DIALOGS::RENATO;
					SetPressE_Hide(true);
				}
				else
				{
					inDialog = false;
					actual_dialog = DIALOGS::NO_ONE;
				}
			}
			else
			{
				if (!dialog_finish)
				{
					renato_text = 4;
					letlengh = 0;
					letlengh2 = 0;

					inDialog = true;
					actual_dialog = DIALOGS::RENATO;
					SetPressE_Hide(true);
					dialog_finish = true;
				}
				else
				{
					inDialog = false;
					actual_dialog = DIALOGS::NO_ONE;
					dialog_finish = false;
				}
			}
		}
		else if (app->physics->GetInNPC(2))
		{
			if (ContinueDialog(medico_text, medico_maxtext))
			{
				letlengh = 0;
				letlengh2 = 0;

				inDialog = true;
				actual_dialog = DIALOGS::MEDICO;
				SetPressE_Hide(true);
			}
			else
			{
				inDialog = false;
				actual_dialog = DIALOGS::NO_ONE;
			}
		}
		else if (app->physics->GetInNPC(3))
		{
			if (ContinueDialog(herrero_text, herrero_maxtext))
			{
				letlengh = 0;
				letlengh2 = 0;

				inDialog = true;
				actual_dialog = DIALOGS::HERRERO;
				SetPressE_Hide(true);
			}
			else
			{
				inDialog = false;
				actual_dialog = DIALOGS::NO_ONE;
			}
		}
		else if (app->physics->GetInNPC(4))
		{
			if (ContinueDialog(granjero_text, granjero_maxtext))
			{
				letlengh = 0;
				letlengh2 = 0;

				inDialog = true;
				actual_dialog = DIALOGS::GRANJERO;
				SetPressE_Hide(true);
			}
			else
			{
				inDialog = false;
				actual_dialog = DIALOGS::NO_ONE;
			}
		}
		else if (app->physics->GetInNPC(5))
		{
			if (ContinueDialog(aldeano_text, aldeano_maxtext))
			{
				letlengh = 0;
				letlengh2 = 0;

				inDialog = true;
				actual_dialog = DIALOGS::ALDEANO;
				SetPressE_Hide(true);
			}
			else
			{
				inDialog = false;
				actual_dialog = DIALOGS::NO_ONE;
			}
		}
		else
		{
			inDialog = false;
			actual_dialog = DIALOGS::NO_ONE;
		}
	}

	letter_cd += dt;

	float speedlet = 0.05f;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		speedlet = 0.01f;
	}

	if (app->GetFPS() == 16) // 60 fps
	{
		if (letter_cd >= 60 * dt * speedlet && inDialog == true && letlengh <= limitLenght)
		{
			letlengh++;

			letter_cd = 0;
		}
	}
	else // 30 fps
	{
		if (letter_cd >= 120 * dt * speedlet && inDialog == true && letlengh <= limitLenght)
		{
			letlengh++;
			
			letter_cd = 0;
		}
	}
	
	if (app->GetFPS() == 16) // 60 fps
	{
		if (letter_cd >= 60 * dt * speedlet && inDialog == true && letlengh2 <= limitLenght2)
		{
			letlengh2++;

			letter_cd = 0;
		}
	}
	else // 30 fps
	{
		if (letter_cd >= 120 * dt * speedlet && inDialog == true && letlengh2 <= limitLenght2)
		{
			letlengh2++;

			letter_cd = 0;
		}
	}

	if (!press_e_hide)
	{
		anim->Update();
	}

	return true;
}

// Called each loop iteration
bool Dialog::PostUpdate()
{
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;

	if (inDialog)
	{
		if (actual_dialog == DIALOGS::RENATO) // RENATO TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "RENATO:");
			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Renato[renato_text], 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Renato[renato_text], 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		else if (actual_dialog == DIALOGS::HERRERO) // ALLY TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "HERRERO:");

			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Herrero, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Herrero, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		else if (actual_dialog == DIALOGS::MEDICO) // ALLY TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "MEDICO:");

			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Medico, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Medico, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		else if (actual_dialog == DIALOGS::GRANJERO) // ALLY TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "GRANJERO:");

			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Granjero, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Granjero, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		/*else if (actual_dialog == DIALOGS::ENEMIGO) // ENEMIES TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "ENEMY:");
			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Templario, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Templario, 1, 255, 255, 255, 1920, 1, letlengh2, 1);

		}*/
		else if (actual_dialog == DIALOGS::ALDEANO) // ALDEANO TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "ALDEANO:");

			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Aldeano, 1, 255, 255, 255, 1920, 1, letlengh, 1);
		}
	}
	else
	{
		letlengh = 0;
	}

	SDL_Rect rect = anim->GetCurrentFrame();

	if (!press_e_hide)
	{
		app->render->DrawTexture(press_e, c_x + 1110, c_y + 550, &rect);
	}

	return true;
}

// Called before quitting
bool Dialog::CleanUp()
{
	// clean textures
	app->tex->UnLoad(whitemark_1200x140);
	whitemark_1200x140 = NULL;
	app->tex->UnLoad(whitemark_300x80);
	whitemark_300x80 = NULL;
	app->tex->UnLoad(press_e);
	press_e = NULL;
	anim = NULL;
	return true;
}

bool Dialog::LoadDialog()
{
	bool ret = true;

	pugi::xml_parse_result result = dialogFile.load_file(DIALOG_FILENAME);

	if (result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		dialog = dialogFile.child("dialog");
	}

	return ret;
}

bool Dialog::ContinueDialog(int& actual_text, int max_text)
{
	actual_text++;
	if (actual_text < max_text)
	{
		return true;
	}
	else 
	{
		actual_text = -1;
		return false;
	}
}