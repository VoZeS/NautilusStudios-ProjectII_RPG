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

	LoadDialog();

	//Text 1
	linea1String_Renato = dialog.child("renato").child("text1").attribute("linea1").as_string();
	linea2String_Renato = dialog.child("renato").child("text1").attribute("linea2").as_string();

	linea1Char_Renato = linea1String_Renato.c_str();
	linea2Char_Renato = linea2String_Renato.c_str();


	linea1String_Ally = dialog.child("ally").child("text1").attribute("linea1").as_string();
	linea2String_Ally = dialog.child("ally").child("text1").attribute("linea2").as_string();

	linea1Char_Ally = linea1String_Ally.c_str();
	linea2Char_Ally = linea2String_Ally.c_str();


	linea1String_Enemy = dialog.child("enemy").child("text1").attribute("linea1").as_string();
	
	linea1Char_Enemy = linea1String_Enemy.c_str();

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
	if (app->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)
	{
		if (app->physics->GetInNPC(1))
		{
			letlengh = 0;
			letlengh2 = 0;

			inDialog = !inDialog;
			inDialogRenato = !inDialogRenato;
			app->frontground->SetPressE_Hide(true);
		}
		else if (app->physics->GetInNPC(2))
		{
			letlengh = 0;
			letlengh2 = 0;

			inDialog = !inDialog;
			inDialogAlly = !inDialogAlly;
			app->frontground->SetPressE_Hide(true);
		}
		else if (app->physics->GetInNPC(3))
		{
			letlengh = 0;
			letlengh2 = 0;

			inDialog = !inDialog;
			inDialogEnemy = !inDialogEnemy;
			app->frontground->SetPressE_Hide(true);
		}
		else
		{
			inDialog = false;
			inDialogRenato = false;
			inDialogAlly = false;
			inDialogEnemy = false;
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

	return true;
}

// Called each loop iteration
bool Dialog::PostUpdate()
{
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;

	if (inDialog)
	{
		if (inDialogRenato) // RENATO TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "RENATO:");
			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Renato, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Renato, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		else if (inDialogAlly) // ALLY TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "ALLY:");

			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Ally, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Ally, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		else if (inDialogEnemy) // ENEMIES TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "ENEMY:");
			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Enemy, 1, 255, 255, 255, 1920, 1, letlengh, 1);
		}
	}
	else
	{
		letlengh = 0;
	}
	/*
	// RENATO TALKING
	if (inDialog && inDialogRenato && !inDialogAlly && !inDialogEnemy)
	{
		app->render->DrawRectangle({ c_x + 30, c_y + 480, 300, 80 }, 0, 255, 0, 100); // Green
		app->render->DrawRectangle({ c_x + 30, c_y + 560, 1200, 140 }, 255, 255, 255, 100); // White
		app->fonts->BlitText(c_x + 50,c_y + 500, textFontDialog, "RENATO:");
		app->fonts->BlitTextLetter(c_x + 50,c_y + 600, textFontDialog, linea1Char_Renato, 1,255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, textFontDialog, linea2Char_Renato, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
	}
	else if (!inDialog)
	{
		letlengh = 0;
	}

	// ALLY TALKING
	if (inDialog && inDialogAlly && !inDialogRenato && !inDialogEnemy)
	{
		app->render->DrawRectangle({ c_x + 30, c_y + 480, 300, 80 }, 0, 0, 255, 100); // Blue
		app->render->DrawRectangle({ c_x + 30, c_y + 560, 1200, 140 }, 255, 255, 255, 100); // White
		app->fonts->BlitText(c_x + 50,c_y + 500, textFontDialog, "ALLY:");
		//app->fonts->BlitTextLetter(c_x + 50,c_y + 600, textFontDialog, "Buenos dias, por ahora no", 1,255, 255, 255, 1920, 1, letlengh);
		//app->fonts->BlitTextLetter(c_x + 50,c_y + 640, textFontDialog, "tenemos nada disponible.", 1,255, 255, 255, 1920, 1, letlengh);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, textFontDialog, linea1Char_Ally, 1, 255, 255, 255, 1920, 1, letlengh, 1);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 640, textFontDialog, linea2Char_Ally, 1, 255, 255, 255, 1920, 1, letlengh2, 2);

	}
	else if (!inDialog)
	{
		letlengh = 0;
	}

	// ENEMIES TALKING
	if(inDialog && inDialogEnemy && !inDialogAlly && !inDialogRenato)
	{
		app->render->DrawRectangle({ c_x + 30,c_y + 480, 300, 80 }, 255, 0, 0, 100); //Red
		app->render->DrawRectangle({ c_x + 30,c_y + 560, 1200, 140 }, 255, 255, 255, 100); //White
		app->fonts->BlitText(c_x + 50,c_y + 500, textFontDialog, "ENEMY:");
		//app->fonts->BlitTextLetter(c_x + 50,c_y + 600, textFontDialog, "Buenas, soy un enemigo.", 1,255, 255, 255, 1920, 1, letlengh);
		app->fonts->BlitTextLetter(c_x + 50, c_y + 600, textFontDialog, linea1Char_Enemy, 1, 255, 255, 255, 1920, 1, letlengh, 1);
	}
	else  if (!inDialog)
	{
		letlengh = 0;
	}*/

	return true;
}

// Called before quitting
bool Dialog::CleanUp()
{
	

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