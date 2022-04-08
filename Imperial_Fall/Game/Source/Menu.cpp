#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Fonts.h"
#include "Scene.h"
#include "Frontground.h"
#include "Menu.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"

Menu::Menu() : Module()
{
	name.Create("menu");
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

	char lookupTableChars[] = { " !'#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[/]^_ abcdefghijklmnopqrstuvwxyz{|}~ ������a��������a��������" };
	textFont = app->fonts->Load("Assets/textures/pixel_letters.png", lookupTableChars, 8);

	paused = false;
	settings = false;
	dead = false;
	win = false;
	lose = false;
	slider = false;
	slider2 = false;
	fullscreen = false;
	vsync = false;
	credits = false;

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

	win_button.rect.w = 600;
	win_button.rect.x = ((int)win_w / 2) - (win_button.rect.w / 2);
	win_button.rect.y = (int)win_h / 2 + 200;

	lose_buttons[0].rect.w = 500;
	lose_buttons[0].rect.x = ((int)win_w / 2) - (lose_buttons[0].rect.w / 2) - 600;
	lose_buttons[0].rect.y = (int)win_h / 2 + 200;
	lose_buttons[1].rect.w = 500;
	lose_buttons[1].rect.x = ((int)win_w / 2) - (lose_buttons[1].rect.w / 2) + 600;
	lose_buttons[1].rect.y = (int)win_h / 2 + 200;

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

	win_button.tex = app->tex->Load("Assets/textures/Exit.png"); // Return field
	lose_buttons[0].tex = app->tex->Load("Assets/textures/Exit.png"); // Try again
	lose_buttons[1].tex = app->tex->Load("Assets/textures/Exit.png"); // Return field

	combat_win = app->tex->Load("Assets/textures/Game_Over.png"); 
	combat_lose = app->tex->Load("Assets/textures/Dead_Image.png");

	return true;
}

// Called each loop iteration
bool Menu::PreUpdate()
{
	intro = app->scene->GetStartScreenState();

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN  && !dead && intro == false)
	{
		paused = !paused;
	}

	if (settings && app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		settings = false;
	}
	
	int x, y;
	app->input->GetMousePosition(x, y);
	float cx = -app->render->camera.x;
	float cy = -app->render->camera.y;
	for (size_t i = 0; i < NUM_PAUSE_BUTTONS; i++)
	{
		SDL_Rect rect = pause_buttons[i].rect;
		if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
		{
			if (paused)
			{
				//app->audio->PlayFx(hover_sound);
			}
			chosed = i;
			pause_buttons[i].state = 1;
		}
		else 
		{
			pause_buttons[i].state = 0;
		}
	}

	for (size_t i = 0; i < NUM_MENU_BUTTONS; i++)
	{
		SDL_Rect rect = menu_buttons[i].rect;
		if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
		{
			if (intro)
			{
				//app->audio->PlayFx(hover_sound);
			}
			chosed = i;
			menu_buttons[i].state = 1;
		}
		else
		{
			menu_buttons[i].state = 0;
		}
	}

	for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
	{
		SDL_Rect rect = settings_buttons[i].rect;
		if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
		{
			if (settings)
			{
				//app->audio->PlayFx(hover_sound);
			}
			chosed = i;
			settings_buttons[i].state = 1;
		}
		else
		{
			settings_buttons[i].state = 0;
		}
	}

	for (size_t i = 0; i < NUM_DEAD_BUTTONS; i++)
	{
		SDL_Rect rect = dead_buttons[i].rect;
		if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
		{
			if (dead)
			{
				//app->audio->PlayFx(hover_sound);
			}
			chosed = i;
			dead_buttons[i].state = 1;
		}
		else
		{
			dead_buttons[i].state = 0;
		}
	}

	SDL_Rect rect = win_button.rect;
	if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
	{
		win_button.state = 1;
	}
	else
	{
		win_button.state = 0;
	}

	for (size_t i = 0; i < NUM_LOSE_BUTTONS; i++)
	{
		SDL_Rect rect = lose_buttons[i].rect;
		if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
		{
			chosed = i;
			lose_buttons[i].state = 1;
		}
		else
		{
			lose_buttons[i].state = 0;
		}
	}

	return true;
}

// Called each loop iteration
bool Menu::Update(float dt)
{
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
				break;
			case 1:
				settings = true;
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
					app->entities->GetPlayer()->SetPlayerLookDir(1);
					app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(800), PIXELS_TO_METERS(950));
					app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
					app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
					app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(950));
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


	// win
	if (win)
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && win_button.state == 1)
		{
			app->audio->PlayFx(click_sound);
			app->frontground->ReturnToField();
			win_button.state = 2;
		}
	}
	else if (lose)
	{
		if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && lose_buttons[chosed].state == 1)
		{
			app->audio->PlayFx(click_sound);
			switch (chosed)
			{
			case 0:
				// restart combat
				app->frontground->ResetCombat();
				break;
			case 1:
				// return field
				app->frontground->ReturnToField();
				break;
			}
			
			lose_buttons[chosed].state = 2;
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

	if (app->scene->GetStartScreenState() != NULL)
	{
		app->render->DrawTexture(app->tex->start_menu, 0 + c_x, 0 + c_y);
	}

	if (paused && !intro && !settings)
	{
		if (intro == false)
		{
			app->render->DrawRectangle(r, 0, 0, 0, 200);
		}

		for (size_t i = 0; i < NUM_PAUSE_BUTTONS; i++)
		{
			pause_buttons[i].rect.x = ((int)win_w / 2) - (pause_buttons[i].rect.w / 2) + c_x -300;
			pause_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 1)) * (i + 1) + c_y;

			if (pause_buttons[i].state == 0)
			{
				app->render->DrawRectangle(pause_buttons[i].rect, idleColorR, idleColorG, idleColorB);
			}
			else if(pause_buttons[i].state == 1)
			{
				app->render->DrawRectangle(pause_buttons[i].rect, inColorR, inColorG, inColorB);
			}
			else if (pause_buttons[i].state == 2)
			{
				app->render->DrawRectangle(pause_buttons[i].rect, pColorR, pColorG, pColorB);
			}

			app->render->DrawTexture(pause_buttons[i].tex, pause_buttons[i].rect.x + 10, pause_buttons[i].rect.y + 10);
		}
	}

	if (intro && !settings)
	{
		for (size_t i = 0; i < NUM_MENU_BUTTONS; i++)
		{
			menu_buttons[i].rect.x = ((int)win_w / 2) - (menu_buttons[i].rect.w / 2) + c_x - 300;
			menu_buttons[i].rect.y = ((int)win_h / (NUM_MENU_BUTTONS + 1)) * (i + 1) + c_y;

			if (menu_buttons[i].state == 0)
			{
				app->render->DrawRectangle(menu_buttons[i].rect, idleColorR, idleColorG, idleColorB);
			}
			else if (menu_buttons[i].state == 1)
			{
				app->render->DrawRectangle(menu_buttons[i].rect, inColorR, inColorG, inColorB);
			}
			else if (menu_buttons[i].state == 2)
			{
				app->render->DrawRectangle(menu_buttons[i].rect, pColorR, pColorG, pColorB);
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

	if (settings)
	{
		
		int z, w;
		app->input->GetMousePosition(z, w);

		if (intro == false)
		{
			app->render->DrawRectangle(r, 0, 0, 0, 200);
		}

		for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
		{
			settings_buttons[i].rect.x = ((int)win_w / 2) - (settings_buttons[i].rect.w / 2) + c_x;
			settings_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 1)) * (i + 1) + c_y;

			if (settings_buttons[i].state == 0)
			{
				app->render->DrawRectangle(settings_buttons[i].rect, idleColorR, idleColorG, idleColorB);
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
				if (z < 540)
				{
					z = 540;
				}
				else if (z > 729)
				{
					z = 729;
				}
				xbarra = z;
				app->render->DrawTexture(settings_buttons[0].alt_tex, z + c_x, settings_buttons[0].rect.y + 10);
				app->audio->SetMusic((z - 540) / 2);
			}
			else
			{
				app->render->DrawTexture(settings_buttons[0].alt_tex, xbarra + c_x, settings_buttons[0].rect.y + 10);
			}

			if (slider2)
			{
				if (z < 540)
				{
					z = 540;
				}
				else if (z > 729)
				{
					z = 729;
				}
				xbarra2 = z;
				app->render->DrawTexture(settings_buttons[1].alt_tex, z + c_x, settings_buttons[1].rect.y + 10);
				app->audio->SetFX((z - 540) / 2);
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

	/*if (dead)
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
			else if(dead_buttons[i].state == 1)
			{
				app->render->DrawRectangle(dead_buttons[i].rect, inColorR, inColorG, inColorB);
			}
			else if (dead_buttons[i].state == 2)
			{
				app->render->DrawRectangle(dead_buttons[i].rect, pColorR, pColorG, pColorB);
			}

			app->render->DrawTexture(dead_buttons[i].tex, dead_buttons[i].rect.x + 10, dead_buttons[i].rect.y + 10);
		}
	}*/


	if (win)
	{
		app->render->DrawRectangle(r, 0, 0, 0, 200);

		//app->render->DrawTexture(combat_win, c_x, c_y);

		win_button.rect.x = ((int)win_w / 2) - (win_button.rect.w / 2) + c_x;
		win_button.rect.y = (int)win_h / 2 + 200 + c_y;
		
		if (win_button.state == 0)
		{
			app->render->DrawRectangle(win_button.rect, idleColorR, idleColorG, idleColorB);
		}
		else if (win_button.state == 1)
		{
			app->render->DrawRectangle(win_button.rect, inColorR, inColorG, inColorB);
		}
		else if (win_button.state == 2)
		{
			app->render->DrawRectangle(win_button.rect, pColorR, pColorG, pColorB);
		}

		app->fonts->BlitText(win_button.rect.x, win_button.rect.y + 15, textFont, "return to field");
	}

	if (lose)
	{
		app->render->DrawRectangle(r, 0, 0, 0, 200);

		//app->render->DrawTexture(combat_lose, c_x, c_y);

		lose_buttons[0].rect.x = ((int)win_w / 2) - (lose_buttons[0].rect.w / 2) - 300 + c_x;
		lose_buttons[0].rect.y = (int)win_h / 2 + 200 + c_y;
		lose_buttons[1].rect.x = ((int)win_w / 2) - (lose_buttons[1].rect.w / 2) + 300 + c_x;
		lose_buttons[1].rect.y = (int)win_h / 2 + 200 + c_y;

		for (size_t i = 0; i < NUM_LOSE_BUTTONS; i++)
		{
			if (lose_buttons[i].state == 0)
			{
				app->render->DrawRectangle(lose_buttons[i].rect, idleColorR, idleColorG, idleColorB);
			}
			else if (lose_buttons[i].state == 1)
			{
				app->render->DrawRectangle(lose_buttons[i].rect, inColorR, inColorG, inColorB);
			}
			else if (lose_buttons[i].state == 2)
			{
				app->render->DrawRectangle(lose_buttons[i].rect, pColorR, pColorG, pColorB);
			}
		}
		
		app->fonts->BlitText(lose_buttons[0].rect.x, lose_buttons[0].rect.y + 15, textFont, "restart battle");
		app->fonts->BlitText(lose_buttons[1].rect.x, lose_buttons[1].rect.y + 15, textFont, "return to field");
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