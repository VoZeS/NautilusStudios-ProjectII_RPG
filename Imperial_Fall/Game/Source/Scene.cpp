#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Menu.h"
#include "Map.h"
#include "Pathfinding.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Combat_Entities.h"
#include "Player.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene() : Module()
{
	name.Create("scene");
	godmode = false;
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = LoadDialog();

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	c_y_menu = -app->render->camera.y + 140; // Posicion de la camara en el inicio del juego

	app->SaveGameRequest();
	
	start_screen = app->tex->Load("Assets/textures/Menu_BackGround.png");
	settings_screen = app->tex->Load("Assets/textures/Settings_BackGround.png");

	// Load music
	//app->audio->PlayMusic("Assets/audio/music/music_spy.ogg");

	LoadDialog();

	char lookupTableChars[] = { " !'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxyz{|}~ çüéâäàaçêëèïîìäaéÆæôöòûù" };
	textFont = app->fonts->Load("Assets/textures/Tipografia_Dialogos.png", lookupTableChars, 8);

	char lookupTableCharsDialogs[] = { " !'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxyz{|}~ çüéâäàaçêëèïîìäaéÆæôöòûù" };
	textFontDialog = app->fonts->Load("Assets/textures/Tipografia_Titulos.png", lookupTableCharsDialogs, 8);

	//DIALOGO RENATO VERTICAL SLICE

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
bool Scene::PreUpdate()
{
	if (start_screen != NULL && app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)  
	{
		PassLevel(1);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(800), PIXELS_TO_METERS(950));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
		app->entities->GetPlayer()->SetPlayerLookDir(0);
	}
	else
	{
		int mouseX, mouseY;
		app->input->GetMousePosition(mouseX, mouseY);
		iPoint p = app->render->ScreenToWorld(mouseX, mouseY);
		p = app->map->WorldToMap(p.x, p.y);

		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
		{
			if (originSelected == true)
			{
				app->pathfinding->CreatePath(origin, p);
				originSelected = false;
			}
			else
			{
				origin = p;
				originSelected = true;
			}
		}
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(1);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(800), PIXELS_TO_METERS(1000));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1000));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1000));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1000));
		app->entities->GetPlayer()->SetPlayerLookDir(1);
	}
	else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(2);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1600));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(200), PIXELS_TO_METERS(1600));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(100), PIXELS_TO_METERS(1600));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(0), PIXELS_TO_METERS(1600));
	}
	else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(3);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(450), PIXELS_TO_METERS(500));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(300));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(200));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(100));
	}
	else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(4);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(600), PIXELS_TO_METERS(2800));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3000));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3100));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3200));
	}
	else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(5);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(1100), PIXELS_TO_METERS(200));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(200));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(950), PIXELS_TO_METERS(200));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(900), PIXELS_TO_METERS(200));
	}
	else if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(6);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1300));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1500));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1600));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1700));
	}
	else if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
	{
		PassLevel(7);
		app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(500), PIXELS_TO_METERS(800));
		app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(600));
		app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(500));
		app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(400));
	}
	else if (app->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
	{
		PassLevel(current_level);
	}
	else if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
	{
		app->SaveGameRequest();
	}
	else if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		app->LoadGameRequest(false);
	}
	else if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		godmode = !godmode;
	}
	else if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		app->ToggleFPS();
	}
	
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

	// Draw map
	if (start_screen != NULL)
	{
		app->map->Draw();
	}

	if (app->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN)
	{
		if (!app->frontground->GetCombatState())
		{
			ENEMIES enemies[4];
			enemies[0] = ENEMIES::MUSHROOM;
			enemies[1] = ENEMIES::W_TEMPLAR;
			enemies[2] = ENEMIES::SKELETON;
			enemies[3] = ENEMIES::GOBLIN;
			app->frontground->FadeInCombat(enemies);
		}
	}
	else if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
	{
		if (app->frontground->GetCombatState())
		{
			app->frontground->ReturnToField();
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
bool Scene::PostUpdate()
{
	
	bool ret = true;
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;

	SDL_Rect prueba;
	SDL_Rect fondoNegro;
	zom_w;
	zom_h;
	zom_x;
	zom_y;
	prueba = { zom_x,zom_y,zom_w,zom_h };
	fondoNegro = { c_x,c_y,1280,720 };
	
	
	//--------------------------------------MENU----------------------------


	//Desplazamiento del fondo al inicio del juego
	//Una vez pulses el Espacio entrara el menu de opciones
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || desMenu==true)
	{
		space_boton = false;
		desMenu = true;
		c_y_menu -= 10.0f;
		fuegoSeguir = true;

	}

	//Limite de donde la camara llegara al principio del juego
	if (c_y_menu <= -555)
	{
		esc = true;
		desMenu = false;
		fuegoSeguir = false;
    }

	 //Primera pantalla menu
	if (esc == false && app->menu->settings == false)
	{

		app->render->DrawTexture(start_screen, c_x, c_y_menu);
		
	}



	//zoom prueba------------------------------------
	/*
	* 	if (daleZom1 == true ) {

	
		app->render->DrawRectangle(fondoNegro , 0, 0, 0);
		zom_x += 25;
		zom_y += 15;

		zom_w -= 25*2;
		zom_h -= 15*2;
		app->render->DrawTexture(start_screen, c_x+zom_x, c_y+zom_y, &prueba);

		if (zom_w <= 0 || zom_h <= 0)
		{
			daleZom1 = false;
			daleZom2 = true;

		}
	
	}

	if ( daleZom2 == true) {
	
		app->render->DrawRectangle(fondoNegro, 0, 0, 0);

		zom_x -= 25;
		zom_y -= 15;

	
		zom_w += 25*2;
		zom_h += 15*2;
		app->render->DrawTexture(settings_screen, c_x + zom_x , c_y + zom_y, &prueba);
		
		if (zom_w >= 1280 || zom_h >= 720) {
			daleZom2 = false;
			opciones = true;
		}
	}

	if ( opciones == true)
	{
	
		app->render->DrawTexture(settings_screen, c_x, c_y);		
	}
	*/


	

	//----------------------------------------------------
	
	 //-------------------Settings
	if (app->menu->settings == true)
	{
		
		app->render->DrawTexture(settings_screen, c_x, c_y);
	}
	


	

	
	//Segunda Pantalla Menu
	if (start_screen != NULL && esc == true && app->menu->settings == false)
	{
		

		app->render->DrawTexture(start_screen, c_x, c_y-700);
		

	}

	//----------------------------------------------------------------------

	 if(app->menu->started)
	 {
		app->map->Draw();

		if (inDialog)
		{
			if (inDialogRenato) // RENATO TALKING
			{
				app->render->DrawTexture(app->tex->whitemark_300x80, 30 + c_x, 480 + c_y);
				app->render->DrawTexture(app->tex->whitemark_1200x140, 30 + c_x, 560 + c_y);
				app->fonts->BlitText(c_x + 50, c_y + 500, textFontDialog, "RENATO:");
				app->fonts->BlitTextLetter(c_x + 50, c_y + 600, textFontDialog, linea1Char_Renato, 1, 255, 255, 255, 1920, 1, letlengh, 1);
				app->fonts->BlitTextLetter(c_x + 50, c_y + 640, textFontDialog, linea2Char_Renato, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
			}
			else if (inDialogAlly) // ALLY TALKING
			{
				app->render->DrawTexture(app->tex->whitemark_300x80, 30 + c_x, 480 + c_y);
				app->render->DrawTexture(app->tex->whitemark_1200x140, 30 + c_x, 560 + c_y);
				app->fonts->BlitText(c_x + 50, c_y + 500, textFontDialog, "ALLY:");
				
				app->fonts->BlitTextLetter(c_x + 50, c_y + 600, textFontDialog, linea1Char_Ally, 1, 255, 255, 255, 1920, 1, letlengh, 1);
				app->fonts->BlitTextLetter(c_x + 50, c_y + 640, textFontDialog, linea2Char_Ally, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
			}
			else if (inDialogEnemy) // ENEMIES TALKING
			{
				app->render->DrawTexture(app->tex->whitemark_300x80, 30 + c_x, 480 + c_y);
				app->render->DrawTexture(app->tex->whitemark_1200x140, 30 + c_x, 560 + c_y);
				app->fonts->BlitText(c_x + 50, c_y + 500, textFontDialog, "ENEMY:");
				app->fonts->BlitTextLetter(c_x + 50, c_y + 600, textFontDialog, linea1Char_Enemy, 1, 255, 255, 255, 1920, 1, letlengh, 1);
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

	 }
	
	if (app->input->GetKey(SDL_SCANCODE_X) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool Scene::GetStartScreenState()
{
	if (start_screen != NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Scene::PassLevel(int dest_level)
{
	if (start_screen != NULL)
	{
		app->frontground->SetA_Black();
		app->frontground->FadeFromBlack(dest_level);
		start_screen = NULL;
	}
	else
	{
		app->frontground->FadeToBlack(dest_level);
	}

	return true;
}

bool Scene::QuitStartScreen()
{
	start_screen = NULL;

	return true;
}

bool Scene::ReturnStartScreen()
{
	start_screen = app->tex->Load("Assets/textures/Menu_BackGround.png");
	app->menu->started = false;
	app->frontground->SetA_Black();

	return true;
}

bool Scene::LoadDialog()
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