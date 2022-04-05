#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "Frontground.h"
#include "Menu.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

Menu::Menu() : Module()
{
	name.Create("menu");

	torch_selection_anim.PushBack({ 0,0,33,49 });
	torch_selection_anim.PushBack({ 35,0,33,49 });
	torch_selection_anim.PushBack({ 70,0,33,49 });
	torch_selection_anim.speed = 0.1f;
	torch_selection_anim.loop = true;

    torch_light_1_anim.PushBack({ 0,0,460,240 });
	torch_light_1_anim.PushBack({ 490,0,460,240 });
	torch_light_1_anim.PushBack({ 1000,0,460,240 });
	torch_light_1_anim.speed = 0.165f;
	torch_light_1_anim.loop = true;

	torch_light_2_anim.PushBack({ 0,0,570,182 });
	torch_light_2_anim.PushBack({ 566,0,570,182 });
	torch_light_2_anim.PushBack({ 1140,0,570,182 });
	torch_light_2_anim.speed = 0.165f;
	torch_light_2_anim.loop = true;

	torch_light_3_anim.PushBack({ 0,0,520,182 });
	torch_light_3_anim.PushBack({ 522,0,520,182 });
	torch_light_3_anim.PushBack({ 1023,0,520,182 });
	torch_light_3_anim.speed = 0.165f;
	torch_light_3_anim.loop = true;

	torch_light_4_anim.PushBack({ 0,0,318,167 });
	torch_light_4_anim.PushBack({ 318,0,318,167 });
	torch_light_4_anim.PushBack({ 660,0,318,167 });
	torch_light_4_anim.speed = 0.165f;
	torch_light_4_anim.loop = true;


	big_fire_anim.PushBack({ 244,0,231,720 });
	big_fire_anim.PushBack({ 475,0,400,720 });
	big_fire_anim.PushBack({ 0,0,244,720 });
	
	big_fire_anim.speed = 0.1f;
	big_fire_anim.loop = true;

	light_big_fire_anim.PushBack({ 4,0,518,378 });
	light_big_fire_anim.PushBack({ 533,0,563,405 });
	light_big_fire_anim.PushBack({ 1106,0,494,355 });
	light_big_fire_anim.speed = 0.165f;
	light_big_fire_anim.loop = true;


	smook_big_fire_anim.PushBack({ 0,0,226,490 });
	smook_big_fire_anim.PushBack({ 460,0,225,490 });
	smook_big_fire_anim.PushBack({ 238,0,217,490 });
	smook_big_fire_anim.speed = 0.06f;
	smook_big_fire_anim.loop = true;
}

// Destructor
Menu::~Menu()
{}

// Called before render is available
bool Menu::Awake()
{

	return true;
}

// Called before the first frame
bool Menu::Start()
{
	r = { 0, 0, 1280, 720 };
	PauseMenuHUD = { 100,500,400,720 }; //Cuadro Menu Pause

	

	paused = false;
	settings = false;
	dead = false;
	lose = false;
	slider = false;
	slider2 = false;
	fullscreen = false;
	vsync = false;
	credits = false;
	intro = false;

	pause_buttons[0].state = 1;
	menu_buttons[0].state = 1;
	dead_buttons[0].state = 1;
	settings_buttons[0].state = 1;
	chosed = 0;
	app->win->GetWindowSize(win_w, win_h);

	click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
	hover_sound = app->audio->LoadFx("Assets/audio/fx/water.wav");

	for (size_t i = 0; i < NUM_PAUSE_BUTTONS; i++)
	{
		pause_buttons[i].rect.x = ((int)win_w / 2) - (pause_buttons[i].rect.w / 2);
		pause_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 1)) * (i + 1);
	}

	for (size_t i = 0; i < NUM_MENU_BUTTONS; i++)
	{
		menu_buttons[i].rect.x = ((int)win_w / 2) - (menu_buttons[i].rect.w / 2);
		menu_buttons[i].rect.y = ((int)win_h / (NUM_MENU_BUTTONS + 1)) * (i + 1);
	}

	for (size_t i = 0; i < NUM_DEAD_BUTTONS; i++)
	{
		dead_buttons[i].rect.x = ((int)win_w / 2) - (dead_buttons[i].rect.w / 2);
		dead_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 3)) * (i + 2.5f);
	}

	for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
	{
		settings_buttons[i].rect.x = ((int)win_w / 2) - (settings_buttons[i].rect.w / 2);
		settings_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 1)) * (i + 1);
	}

	lose_button.rect.x = (int)win_w / 2;
	lose_button.rect.y = (int)win_h / 2;

	pause_buttons[0].tex = app->tex->Load("Assets/textures/Continue.png"); // Continue
	pause_buttons[1].tex = app->tex->Load("Assets/textures/Settings.png"); // Settings
	pause_buttons[2].tex = app->tex->Load("Assets/textures/Back.png"); // Back to Menu
	pause_buttons[3].tex = app->tex->Load("Assets/textures/Exit.png"); // Exit
	

	dead_buttons[0].tex = app->tex->Load("Assets/textures/Load.png"); // Load
	dead_buttons[1].tex = app->tex->Load("Assets/textures/Exit.png"); //Exit

	menu_buttons[0].tex = app->tex->Load("Assets/textures/Play.png"); // Play
	menu_buttons[0].alt_tex = app->tex->Load("Assets/textures/Continue.png"); // Continue
	menu_buttons[1].tex = app->tex->Load("Assets/textures/Settings.png"); // Settings
	menu_buttons[2].tex = app->tex->Load("Assets/textures/Credits.png"); // Credits
	menu_buttons[2].alt_tex = app->tex->Load("Assets/textures/CreditsImage.png"); // Credits
	menu_buttons[3].tex = app->tex->Load("Assets/textures/Exit.png"); // Exit

	settings_buttons[0].alt_tex = settings_buttons[1].alt_tex = app->tex->Load("Assets/textures/Slider.png"); // Slider
	settings_buttons[0].tex = app->tex->Load("Assets/textures/Sound.png"); // Audio
	settings_buttons[1].tex = app->tex->Load("Assets/textures/Fx.png"); // Fx slider
	settings_buttons[2].tex = app->tex->Load("Assets/textures/Fullscreen_no.png"); // Fullscreen
	settings_buttons[2].alt_tex = app->tex->Load("Assets/textures/Fullscreen_si.png"); // Fullscreen
	settings_buttons[3].tex = app->tex->Load("Assets/textures/Vsync_no.png"); // Vsync
	settings_buttons[3].alt_tex = app->tex->Load("Assets/textures/Vsync_si.png"); // Vsync

	lose_button.tex = app->tex->Load("Assets/textures/Exit.png"); // Exit

	gameOver = app->tex->Load("Assets/textures/Game_Over.png"); 
	cat = app->tex->Load("Assets/textures/Dead_Image.png"); 


	torch_fire = app->tex->Load("Assets/textures/Torch_Fire.png");
	light_fire1 = app->tex->Load("Assets/textures/Torch1_light.png");
	light_fire2 = app->tex->Load("Assets/textures/Torch2_light.png");
	light_fire3 = app->tex->Load("Assets/textures/Torch3_light.png");
	light_fire4 = app->tex->Load("Assets/textures/Torch4_light.png");

	big_fire = app->tex->Load("Assets/textures/Big_Fire.png");
	big_fire_light = app->tex->Load("Assets/textures/Big_Fire_Light.png");

	smook_big_fire = app->tex->Load("Assets/textures/Smoke.png");

	

	return true;
}

// Called each loop iteration
bool Menu::PreUpdate()
{

	LOG("%d", chosed);

	intro = app->scene->GetStartScreenState();

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !dead && intro == false )
	{
		paused = !paused;
		
	}

	if (settings && app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		settings = false;
		app->scene->opciones = false;
	}

	if (app->scene->esc == true) {

	int x, y;
	app->input->GetMousePosition(x, y);

	float cx = -app->render->camera.x;
	float cy = -app->render->camera.y;

	if (paused)
	{
		for (size_t i = 0; i < NUM_PAUSE_BUTTONS; i++)
		{
			SDL_Rect rect = pause_buttons[i].rect;
			if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
			{
				if (paused)
				{
					app->audio->PlayFx(hover_sound);
				}
				chosed = i;
				pause_buttons[i].state = 1;
			}
			else
			{
				pause_buttons[i].state = 0;
			}
		}
	}
	else if (intro && !settings)
	{
		for (size_t i = 0; i < NUM_MENU_BUTTONS; i++)
		{
			SDL_Rect rect = menu_buttons[i].rect;
			if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
			{
				if (intro && !settings)
				{
					app->audio->PlayFx(hover_sound);
				}
				chosed = i;
				menu_buttons[i].state = 1;
			}
			else
			{
				menu_buttons[i].state = 0;
			}
		}
	}
	
	if (settings) 
	{
		for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
		{
			SDL_Rect rect = settings_buttons[i].rect;
			if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
			{
				if (settings)
				{
					app->audio->PlayFx(hover_sound);
				}
				chosed = i;
				settings_buttons[i].state = 1;
			}
			else
			{
				settings_buttons[i].state = 0;
			}
		}
	}
	

	for (size_t i = 0; i < NUM_DEAD_BUTTONS; i++)
	{
		SDL_Rect rect = dead_buttons[i].rect;
		if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
		{
			if (dead)
			{
				app->audio->PlayFx(hover_sound);
			}
			chosed = i;
			dead_buttons[i].state = 1;
		}
		else
		{
			dead_buttons[i].state = 0;
		}
	}

	SDL_Rect rect = lose_button.rect;
	if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
	{
		if (lose)
		{
			app->audio->PlayFx(hover_sound);
		}
		lose_button.state = 1;
	}
	else
	{
		lose_button.state = 0;
	}
}
	return true;
}

// Called each loop iteration
bool Menu::Update(float dt)
{
	// ------------------------------------- Anims Update
	torch_selection_anim.Update();
	torch_light_1_anim.Update();
	torch_light_2_anim.Update();
	torch_light_3_anim.Update();
	torch_light_4_anim.Update();


	big_fire_anim.Update();
	light_big_fire_anim.Update();
	smook_big_fire_anim.Update();


	if (app->scene->esc == true) {
	// pause buttons
	if (paused && !intro && !settings)
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && pause_buttons[chosed].state == 1)
		{
			app->audio->PlayFx(click_sound);
			switch (chosed)
			{
			case 0:
				paused = false;
				started = true;
				break;
			case 1:
				settings = true;
				paused = false;
				started = true;
			
				//app->scene->opciones = true;
				break;
			case 2:
				app->scene->ReturnStartScreen();
				
				paused = false;
				break;
			case 3:
				return false;
				break;
			}

			pause_buttons[chosed].state = 2;
		}
	}

	//menu buttons
	if (intro && !settings)
	{
		
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && menu_buttons[chosed].state == 1)
		{
			app->audio->PlayFx(click_sound);
			switch (chosed)
			{
			case 0:
				if (!started)
				{
					app->scene->PassLevel(1);
					app->entities->GetPlayer()->SetPlayerLookDir(0);
					app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(800), PIXELS_TO_METERS(950));
					app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
					app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
					app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
					app->entities->GetPlayer()->SetCompanion0LookDir(0);
					app->entities->GetPlayer()->SetCompanion1LookDir(0);
					app->entities->GetPlayer()->SetCompanion2LookDir(0);
					saving = true;
					intro = false;
					paused = false;
					started = true;
			

				}
				else
				{
					app->scene->QuitStartScreen();
					app->LoadGameRequest();
				}
				break;
			case 1:
				settings = true;
				//app->scene->daleZom1 = true;
					break;
			case 2:
				credits = !credits;
				break;
			case 3:
				return false;
				break;
			}

			menu_buttons[chosed].state = 2;
		}
	}

	//settings buttons
	if (settings)
	{
		
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && settings_buttons[chosed].state == 1)
		{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					slider = !slider;
					break;
				case 1:
					slider2 = !slider2;
					break;
				case 2:
					fullscreen = !fullscreen;
					if (fullscreen)
					{
						SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
					}
					else
					{
						SDL_SetWindowFullscreen(app->win->window, 0);
					}
					break;
				case 3:
					vsync = !vsync;
					if (vsync)
					{
						// 1 to activate, 0 to deactivate
						SDL_GL_SetSwapInterval(1);
					}
					else
					{
						SDL_GL_SetSwapInterval(0);
					}
					break;
				}
				settings_buttons[chosed].state = 2;
		}
	
	}

	// fade at load
	if (loading)
	{
		load_cd--;
		if (load_cd <= 0)
		{
			app->LoadGameRequest();
			load_cd = 120;
			loading = false;
			paused = false;
		}
	}

	if (saving)
	{
		save_cd--;
		if (save_cd <= 0)
		{
			app->SaveGameRequest();
			save_cd = 50;
			saving = false;
			paused = false;
		}
	}

	// dead buttons
	if (dead && !loading)
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && dead_buttons[chosed].state == 1)
		{
			app->audio->PlayFx(click_sound);
			switch (chosed)
			{
			case 0:
				app->frontground->FadeToBlack(-1);
				loading = true;
				break;
			case 1:
				return false;
				break;
			}

			dead_buttons[chosed].state = 2;
		}
	}


	//lose
	if (lose && !loading)
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && lose_button.state == 1)
		{
			app->audio->PlayFx(click_sound);
			lose_button.state = 2;
			return false;
		}
	}
}
	return true;
}

// Called each loop iteration
bool Menu::PostUpdate()
{
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;
	
	r.x = c_x;
	r.y = c_y;

	if (app->scene->fuegoSeguir == true ) {
		seguir-=10;
	
	}
	if (seguir <= 900 )
	{
		app->scene->fuegoSeguir = false;
	}
	if (settings==false && !started) {

	
		app->render->DrawTexture(big_fire_light, c_x + 756, c_y + seguir + 933, &(light_big_fire_anim.GetCurrentFrame()));
		app->render->DrawTexture(big_fire, c_x + 940, c_y + seguir +620, &(big_fire_anim.GetCurrentFrame()));
		app->render->DrawTexture(smook_big_fire, c_x + 1000, c_y + seguir + 300, &(smook_big_fire_anim.GetCurrentFrame()));
		
	}
	
	
	//---------------------------------------------------------HUD PAUSE---------------------------------------------
	//Dimensiones Hud Pause
	PauseMenuHUD.x = c_x+ c_x_menu-500;
	PauseMenuHUD.y = c_y;

	if (app->scene->esc == true ) {

		if (app->scene->GetStartScreenState() != NULL)
		{
			app->render->DrawTexture(app->tex->start_menu, 0 + c_x, 0 + c_y);
		}

		//Hace que el menu se quite
		if (!paused )
		{
			if (c_x_menu >= 100 && stop == false)
			{
				c_x_menu -= 35.0f;

				if (c_x_menu >= -200)
				{
					stop = false;
				}
			}
			
		}

		//Fondo Negro transparente que sale cuando pausas
		if (intro == false && paused)
		{
			app->render->DrawRectangle(r, 0, 0, 0, 200);
		}

		//Cuando pausas se pone un fondo verde (Substituir en un futuro por un HUD creado)
		app->render->DrawRectangle(PauseMenuHUD, 18, 188, 18, 200);


		//Hace que el menu aparezca
		if (paused && !intro && !settings)
		{
		
			if (desMenu == true && c_x_menu <= 400)
			{
				c_x_menu += 15.0f;
			}

			if (c_x_menu >= -50)
			{
				desMenu = false;
			}

			if (paused)
			{
				desMenu = true;	
			}

	 //--------------------BOTONES MENU SCAPE IN GAME
			for (size_t i = 0; i < NUM_PAUSE_BUTTONS; i++)
			{
				//Boton Continuar
				pause_buttons[0].rect.x = c_x+ c_x_menu - 350;
				pause_buttons[0].rect.y = c_y+100;

				//Boton Opciones
				pause_buttons[1].rect.x = c_x + c_x_menu - 350;
				pause_buttons[1].rect.y = c_y+200;

				//Boton Creditos
				pause_buttons[2].rect.x = c_x + c_x_menu - 350;
				pause_buttons[2].rect.y = c_y+300;

				//Boton Salir
				pause_buttons[3].rect.x = c_x + c_x_menu - 350;
				pause_buttons[3].rect.y = c_y +400;
				
				//Recuadro en Botones permanente
				if (pause_buttons[i].state == 0)
				{
					
				}
				//Recuadro en Botones Si pasas por encima
				else if (pause_buttons[i].state == 1)
				{
					app->render->DrawRectangle(pause_buttons[i].rect, inColorR, inColorG, inColorB);
				}

				//Recuadro en Botones cuando haces click Izquiero
				else if (pause_buttons[i].state == 2)
				{
					app->render->DrawRectangle(pause_buttons[i].rect, pColorR, pColorG, pColorB);
				}

				//Imprime las imagenes de los botones
				app->render->DrawTexture(pause_buttons[i].tex, pause_buttons[i].rect.x + 10, pause_buttons[i].rect.y + 10);
			}
		}
	//------------------------------------------------------
	

		//----------------------------------------------------HUD INICIO------------------------------------------
		if (intro && !settings)
		{

			for (size_t i = 0; i < NUM_MENU_BUTTONS; i++)
			{

				//Boton Jugar
				menu_buttons[0].rect.x =c_x + 60 ;
				menu_buttons[0].rect.y = c_y +150;

				///Boton Opciones
				menu_buttons[1].rect.x = c_x + 100;
				menu_buttons[1].rect.y = c_y + 380;

				//Boton Creditos
				menu_buttons[2].rect.x = c_x + 75;
				menu_buttons[2].rect.y = c_y + 570;

				//Boton Salir
				menu_buttons[3].rect.x = c_x + 500;
				menu_buttons[3].rect.y = c_y+ 570;

				//Recuadro en Botones permanente
				if (menu_buttons[i].state == 0)
				{

				}

				//Recuadro en Botones Si pasas por encima
				//Boton Jugar Antorcha
				else if (menu_buttons[0].state == 1)
				{
					app->render->DrawTexture(light_fire1, menu_buttons[0].rect.x-132, menu_buttons[0].rect.y - 90, &(torch_light_1_anim.GetCurrentFrame()));
					app->render->DrawTexture(torch_fire, menu_buttons[0].rect.x + 280, menu_buttons[0].rect.y+20, &(torch_selection_anim.GetCurrentFrame()));
					
				}
				//Boton Opciones Antorcha
				else if (menu_buttons[1].state == 1)
				{
					app->render->DrawTexture(light_fire2, menu_buttons[0].rect.x - 102, menu_buttons[0].rect.y +156, &(torch_light_2_anim.GetCurrentFrame()));
					app->render->DrawTexture(torch_fire, menu_buttons[1].rect.x +291, menu_buttons[1].rect.y-5, &(torch_selection_anim.GetCurrentFrame()));

				}
				//Boton Creditos Antorcha
				else if (menu_buttons[2].state == 1)
				{
					app->render->DrawTexture(light_fire3, menu_buttons[0].rect.x - 130, menu_buttons[0].rect.y +359, &(torch_light_3_anim.GetCurrentFrame()));
					app->render->DrawTexture(torch_fire, menu_buttons[2].rect.x - 55, menu_buttons[2].rect.y+40, &(torch_selection_anim.GetCurrentFrame()));

				}
				//Boton Salir Antorcha
				else if (menu_buttons[3].state == 1)
				{
					app->render->DrawTexture(light_fire4, menu_buttons[0].rect.x +402, menu_buttons[0].rect.y +372, &(torch_light_4_anim.GetCurrentFrame()));
					app->render->DrawTexture(torch_fire, menu_buttons[3].rect.x + 185, menu_buttons[3].rect.y-3, &(torch_selection_anim.GetCurrentFrame()));

				}

				//Recuadro en Botones cuando haces click Izquiero
				else if (menu_buttons[i].state == 2)
				{

				}

				if (credits)
				{
					app->render->DrawTexture(menu_buttons[i].alt_tex, 1000, 500);
				}

				if (i == 0)
				{
					if (started)
					{
						app->render->DrawTexture(menu_buttons[i].alt_tex, menu_buttons[i].rect.x + 10, menu_buttons[i].rect.y + 10);
					}
					else
					{
						app->render->DrawTexture(menu_buttons[i].tex, menu_buttons[i].rect.x + 10, menu_buttons[i].rect.y + 10);
					}

				}
				else
				{
					app->render->DrawTexture(menu_buttons[i].tex, menu_buttons[i].rect.x + 10, menu_buttons[i].rect.y + 10);
				}
			}
		}
		//---------------------------------------------------------HUD PAUSE---------------------------------------------
		if (settings )//&& app->scene->opciones==true)
		{
		
			int z, w;
			app->input->GetMousePosition(z, w);
			
			if (intro == false)
			{
			
				app->render->DrawRectangle(r, 0, 0, 0, 200);
			}
			if(paused)
			app->render->DrawRectangle(PauseMenuHUD, 18, 188, 18, 200);

			for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
			{
				
				settings_buttons[i].rect.x = ((int)win_w -1130) - (settings_buttons[i].rect.w / 2) + c_x;
				settings_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 1)) * (i + 1) + c_y;


				if (settings_buttons[i].state == 0)
				{
					
				}
				else if (settings_buttons[i].state == 1)
				{
					app->render->DrawRectangle(settings_buttons[i].rect, inColorR, inColorG, inColorB);
				}
				else if (settings_buttons[i].state == 2)
				{
					app->render->DrawRectangle(settings_buttons[i].rect, pColorR, pColorG, pColorB);
				}

				if (slider)
				{
					if (z < 50)
					{
						z = 50;
					}
					else if (z > 240)
					{
						z = 240;
					}
					xbarra = z;
					app->render->DrawTexture(settings_buttons[0].alt_tex, z + c_x, settings_buttons[0].rect.y + 10);
					app->audio->SetMusic((z - 0) / 2);
				}
				else
				{
					app->render->DrawTexture(settings_buttons[0].alt_tex, xbarra + c_x, settings_buttons[0].rect.y + 10);
				}

				if (slider2)
				{
					xbarra2 = z;
					if (z < 50)
					{
						z = 50;
					}
					else if (z > 240)
					{
						z = 240;
					}
					
					app->render->DrawTexture(settings_buttons[1].alt_tex, z + c_x, settings_buttons[1].rect.y + 10);
					app->audio->SetFX((z - 100) / 2);
				}
				else
				{
					app->render->DrawTexture(settings_buttons[1].alt_tex, xbarra2 + c_x, settings_buttons[1].rect.y + 10);
				}

				if (vsync && i == 3)
				{
					app->render->DrawTexture(settings_buttons[i].alt_tex, settings_buttons[i].rect.x + 10, settings_buttons[i].rect.y + 10);
				}

				if (fullscreen && i == 2)
				{
					app->render->DrawTexture(settings_buttons[i].alt_tex, settings_buttons[i].rect.x + 10, settings_buttons[i].rect.y + 10);
				}

				app->render->DrawTexture(settings_buttons[i].tex, settings_buttons[i].rect.x + 10, settings_buttons[i].rect.y + 10);

			}
		}

		if (dead)
		{
			app->render->DrawRectangle(r, 0, 0, 0, 200);

			app->render->DrawTexture(gameOver, 0 + c_x, 75);
			app->render->DrawTexture(cat, 950 + c_x, 800);

			for (size_t i = 0; i < NUM_DEAD_BUTTONS; i++)
			{
				dead_buttons[i].rect.x = ((int)win_w / 2) - (dead_buttons[i].rect.w / 2) + c_x;

				if (dead_buttons[i].state == 0)
				{
					app->render->DrawRectangle(dead_buttons[i].rect, idleColorR, idleColorG, idleColorB);
				}
				else if (dead_buttons[i].state == 1)
				{
					app->render->DrawRectangle(dead_buttons[i].rect, inColorR, inColorG, inColorB);
				}
				else if (dead_buttons[i].state == 2)
				{
					app->render->DrawRectangle(dead_buttons[i].rect, pColorR, pColorG, pColorB);
				}

				app->render->DrawTexture(dead_buttons[i].tex, dead_buttons[i].rect.x + 10, dead_buttons[i].rect.y + 10);
			}
		}


		if (lose)
		{
			app->render->DrawRectangle(r, 0, 0, 0, 200);

			app->render->DrawTexture(gameOver, 0 + c_x, 75);
			app->render->DrawTexture(cat, 950 + c_x, 800);

			lose_button.rect.x = ((int)win_w / 2) - (lose_button.rect.w / 2) + c_x;

			if (lose_button.state == 0)
			{
				app->render->DrawRectangle(lose_button.rect, idleColorR, idleColorG, idleColorB);
			}
			else if (lose_button.state == 1)
			{
				app->render->DrawRectangle(lose_button.rect, inColorR, inColorG, inColorB);
			}
			else if (lose_button.state == 2)
			{
				app->render->DrawRectangle(lose_button.rect, pColorR, pColorG, pColorB);
			}

			app->render->DrawTexture(lose_button.tex, lose_button.rect.x + 10, lose_button.rect.y + 10);

		}
	}
	return true;
}

// Called before quitting
bool Menu::CleanUp()
{

	return true;
}

bool Menu::GetGameState()
{
	return paused;
}