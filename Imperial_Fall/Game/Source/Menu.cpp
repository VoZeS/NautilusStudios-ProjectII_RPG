#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Menu.h"
#include "Map.h"
#include "Player.h"
#include "Defs.h"
#include "Log.h"
#include "Town1.h"
#include "Town2.h"
#include "Forest.h"
#include "Battlefield.h"
#include "Dungeon.h"
#include "Outside_Castle.h"
#include "Inside_Castle.h"
#include "Combat_Scene.h"

Menu::Menu(bool enabled) : Module(enabled)
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

	light_big_fire_anim.PushBack({ 4,0,518,405 });
	light_big_fire_anim.PushBack({ 533,0,563,405 });
	light_big_fire_anim.PushBack({ 1106,0,494,405 });
	light_big_fire_anim.speed = 0.165f;
	light_big_fire_anim.loop = true;


	smook_big_fire_anim.PushBack({ 0,0,226,490 });
	smook_big_fire_anim.PushBack({ 460,0,225,490 });
	smook_big_fire_anim.PushBack({ 238,0,217,490 });
	smook_big_fire_anim.speed = 0.06f;
	smook_big_fire_anim.loop = true;


	space_boton_anim.PushBack({ 10,0,195,121 });
	space_boton_anim.PushBack({ 226,0,201,121 });
	space_boton_anim.speed = 0.06f;
	space_boton_anim.loop = true;



	menu_play_anim.PushBack({ 31,0,286,597 });
	menu_play_anim.PushBack({ 345,0,290,597 });
	menu_play_anim.PushBack({ 681,0,286,597 });
	menu_play_anim.speed = 0.2f;
	menu_play_anim.loop = false;
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

	PauseMenuHUD = { 100, 500, 400, 720 }; //Cuadro Menu Pause

	paused = false;
	settings = false;
	win = false;
	lose = false;
	scape = false;
	slider = false;
	slider2 = false;
	fullscreen = false;
	vsync = false;
	credits = false;
	intro = false;
	subplaymenu = false;

	pause_buttons[0].state = 1;
	menu_buttons[0].state = 1;
	settings_buttons[0].state = 1;
	chosed = 0;
	app->win->GetWindowSize(win_w, win_h);

	click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
	hover_sound = app->audio->LoadFx("Assets/audio/fx/water.wav");

	menu_music = app->audio->PlayMusic("Assets/audio/music/menu.ogg");

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

	for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
	{
		settings_buttons[i].rect.x = ((int)win_w / 2) - (settings_buttons[i].rect.w / 2);
		settings_buttons[i].rect.y = ((int)win_h / (NUM_PAUSE_BUTTONS + 1)) * (i + 1);
	}

	whitemark_500x70 = app->tex->Load("Assets/textures/500x70_whitemark.png");

	win_button.rect.w = 600;
	win_button.rect.x = ((int)win_w / 2) - (win_button.rect.w / 2);
	win_button.rect.y = (int)win_h / 2 + 200;

	lose_buttons[0].rect.w = 500;
	lose_buttons[0].rect.x = ((int)win_w / 2) - (lose_buttons[0].rect.w / 2) - 600;
	lose_buttons[0].rect.y = (int)win_h / 2 + 200;
	lose_buttons[1].rect.w = 500;
	lose_buttons[1].rect.x = ((int)win_w / 2) - (lose_buttons[1].rect.w / 2) + 600;
	lose_buttons[1].rect.y = (int)win_h / 2 + 200;

	scape_buttons[0].rect.w = 500;
	scape_buttons[0].rect.x = ((int)win_w / 2) - (lose_buttons[0].rect.w / 2) - 600;
	scape_buttons[0].rect.y = (int)win_h / 2 + 200;
	scape_buttons[1].rect.w = 500;
	scape_buttons[1].rect.x = ((int)win_w / 2) - (lose_buttons[1].rect.w / 2) + 600;
	scape_buttons[1].rect.y = (int)win_h / 2 + 200;

	pause_buttons[0].tex = app->tex->Load("Assets/textures/Continue_In_game.png"); // Continue
	pause_buttons[0].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");

	pause_buttons[1].tex = app->tex->Load("Assets/textures/Settings_In_game.png"); // Settings
	pause_buttons[1].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");

	pause_buttons[2].tex = app->tex->Load("Assets/textures/Back_In_game.png"); // Back to Menu
	pause_buttons[2].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");

	pause_buttons[3].tex = app->tex->Load("Assets/textures/Exit_In_game.png"); // Exit
	pause_buttons[3].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");

	//----------------------------------------------------------------MENU INICIO BOTONES------------------------
	menu_buttons[0].alt_tex = app->tex->Load("Assets/textures/PlaySprite.png"); // Play
	menu_buttons[0].tex = app->tex->Load("Assets/textures/PlayDarkSprite.png"); // Play

	//menu_buttons[0].alt_tex = app->tex->Load("Assets/textures/Continue.png"); // Continue

	menu_buttons[1].alt_tex = app->tex->Load("Assets/textures/SettingsSprite.png"); // Settings
	menu_buttons[1].tex = app->tex->Load("Assets/textures/SettingsDarkSprite.png"); // Settings

	menu_buttons[2].alt_tex = app->tex->Load("Assets/textures/CreditsSprite.png"); // Credits
	menu_buttons[2].tex = app->tex->Load("Assets/textures/CreditsDarkSprite.png"); // Credits

	//menu_buttons[2].alt_tex = app->tex->Load("Assets/textures/CreditsImage.png"); // Credits

	menu_buttons[3].alt_tex = app->tex->Load("Assets/textures/ExitSprite.png"); // Exit
	menu_buttons[3].tex = app->tex->Load("Assets/textures/ExitDarkSprite.png"); // Exit


	menu_buttons[4].tex = app->tex->Load("Assets/textures/ContinueBlackSprite.png"); // Credits
	menu_buttons[4].alt_tex = app->tex->Load("Assets/textures/ContinueSprite.png"); // Credits
	menu_buttons[4].alt_tex2 = app->tex->Load("Assets/textures/Fx.png");

	menu_buttons[5].tex = app->tex->Load("Assets/textures/NewGameBlackSprite.png"); // Credits
	menu_buttons[5].alt_tex = app->tex->Load("Assets/textures/NewGameSprite.png"); // Credits
	//----------------------------------------------------------------

	settings_buttons[0].alt_tex = settings_buttons[1].alt_tex = app->tex->Load("Assets/textures/Slider.png"); // Slider

	settings_buttons[0].tex = app->tex->Load("Assets/textures/Sound.png"); // Audio
	settings_buttons[0].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");
	settings_buttons[0].alt_tex2 = app->tex->Load("Assets/textures/SoundSprite.png");

	settings_buttons[1].tex = app->tex->Load("Assets/textures/Fx.png"); // Fx slider
	settings_buttons[1].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");
	settings_buttons[1].alt_tex2 = app->tex->Load("Assets/textures/FxSprite.png");

	settings_buttons[2].tex = app->tex->Load("Assets/textures/Fullscreen_no.png"); // Fullscreen No
	settings_buttons[2].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png"); // Fullscreen No Selec
	settings_buttons[2].alt_tex = app->tex->Load("Assets/textures/Fullscreen_si.png"); // Fullscreen Si
	

	settings_buttons[3].tex = app->tex->Load("Assets/textures/Vsync_no.png"); // Vsync No
	settings_buttons[3].alt_tex_selec = app->tex->Load("Assets/textures/Fullscreen_No_Select.png");
	settings_buttons[3].alt_tex = app->tex->Load("Assets/textures/Vsync_si.png"); // Vsync Si

	win_button.tex = app->tex->Load("Assets/textures/Exit.png"); // Return field
	lose_buttons[0].tex = app->tex->Load("Assets/textures/Exit.png"); // Try again
	lose_buttons[1].tex = app->tex->Load("Assets/textures/Exit.png"); // Return field

	combat_win = app->tex->Load("Assets/textures/Game_Over.png"); 
	combat_lose = app->tex->Load("Assets/textures/Dead_Image.png");


	torch_fire = app->tex->Load("Assets/textures/Torch_Fire.png");
	light_fire1 = app->tex->Load("Assets/textures/Torch1_light.png");
	light_fire2 = app->tex->Load("Assets/textures/Torch2_light.png");
	light_fire3 = app->tex->Load("Assets/textures/Torch3_light.png");
	light_fire4 = app->tex->Load("Assets/textures/Torch4_light.png");

	big_fire = app->tex->Load("Assets/textures/Big_Fire.png");
	big_fire_light = app->tex->Load("Assets/textures/Big_Fire_Light.png");
	smook_big_fire = app->tex->Load("Assets/textures/Smoke.png");

	space_boton = app->tex->Load("Assets/textures/Space_Boton_Anim.png");

	menu_in_game = app->tex->Load("Assets/textures/OpcionesInGame.png");

	menu_play = app->tex->Load("Assets/textures/Menu_Play.png");

	team_photo = app->tex->Load("Assets/textures/TeamPhoto.png");

	return true;
}

// Called each loop iteration
bool Menu::PreUpdate()
{
	intro = !started;

	if (kill_enemy)
	{
		app->entities->KillEnemy();
	}

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && intro == false )
	{
		paused = !paused;
	}

	if (intro && app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		subplaymenu = false;

	if (intro && app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		credits = false;

	if (settings && app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
	{
		subplaymenu = false;
		settings = false;
	}

	if (app->scene->esc == true)
	{
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

			if (app->combat_scene->Enabled())
			{
				if (chosed == 2)
				{
					pause_buttons[2].state = 0;
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
					if (intro && !settings && !subplaymenu && !credits)
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
		}

		if (win)
		{
			SDL_Rect rect = win_button.rect;
			if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
			{
				win_button.state = 1;
			}
			else
			{
				win_button.state = 0;
			}
		}
		else if (lose)
		{
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
		}
		else if (scape)
		{
			for (size_t i = 0; i < NUM_SCAPE_BUTTONS; i++)
			{
				SDL_Rect rect = scape_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					chosed = i;
					scape_buttons[i].state = 1;
				}
				else
				{
					scape_buttons[i].state = 0;
				}
			}
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
	space_boton_anim.Update();


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
					paused = true;
					started = true;
					break;
				case 2:
					app->frontground->ReturnStartScreen();

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
		if (intro && !settings && !credits)
		{
			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && menu_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					subplaymenu = true;
					break;

				case 1:
					if (!subplaymenu)
						settings = true;
					break;

				case 2:
					if (!subplaymenu)
					{
						credits = true;
						settings = false;
					}
					break;

				case 3:
					return false;
					break;

				case 4: // PLAY AND CONTINUE
					if (!started && !firstime)
					{
						app->LoadGameRequest(false);
						switch (app->frontground->current_level)
						{
						case 1: app->frontground->move_to = MOVE_TO::SCENE_TOWN1;
							break;
						case 2: app->frontground->move_to = MOVE_TO::SCENE_TOWN2;
							break;
						case 3: app->frontground->move_to = MOVE_TO::SCENE_FOREST;
							break;
						case 4: app->frontground->move_to = MOVE_TO::SCENE_BATTLEFIELD;
							break;
						case 5: app->frontground->move_to = MOVE_TO::SCENE_DUNGEON;
							break;
						case 6: app->frontground->move_to = MOVE_TO::SCENE_OUTSIDE;
							break;
						case 7: app->frontground->move_to = MOVE_TO::SCENE_INSIDE;
							break;
						default:
							break;
						}
						app->frontground->FadeToBlack();
						saving = true;
						intro = false;
						paused = false;
						//started = true;
						subplaymenu = false;
					}
					break;

				case 5: // NEW GAME
					if (!started)
					{
						app->LoadGame(true); // load now, not at frames end
						app->frontground->move_to = MOVE_TO::SCENE_TOWN1;
						app->frontground->FadeToBlack();
						saving = false;
						intro = false;
						paused = false;
						//started = true;
						subplaymenu = false;
					}
					break;
				}

				menu_buttons[chosed].state = 2;
			}
		}

		//settings buttons
		if (settings)
		{
			subplaymenu = false;
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
			subplaymenu = false;
			load_cd--;
			if (load_cd <= 0)
			{
				app->LoadGameRequest(false);
				load_cd = 120;
				loading = false;
				paused = false;
			}
		}

		if (saving)
		{
			subplaymenu = false;
			save_cd--;
			if (save_cd <= 0)
			{
				app->SaveGameRequest();
				save_cd = 50;
				saving = false;
				paused = false;
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
				kill_enemy = true;
			}
		}
		else if (lose)
		{
			subplaymenu = false;

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
		else if (scape)
		{
			subplaymenu = false;

			if (app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED && scape_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					// sure to scape
					app->frontground->ReturnToField();
					break;
				case 1:
					// cancel scape
					scape = false;
					break;
				}

				scape_buttons[chosed].state = 2;
			}
		}
	}

	// Tricks
	if (app->frontground->godmode)
	{
		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			DisableAll();

			app->town1->Enable();

			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(800), PIXELS_TO_METERS(1000));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1000));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1000));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1000));
			app->entities->GetPlayer()->SetPlayerLookDir(1);
		}
		else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			DisableAll();

			app->town2->Enable();

			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(400), PIXELS_TO_METERS(1600));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(200), PIXELS_TO_METERS(1600));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(100), PIXELS_TO_METERS(1600));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(0), PIXELS_TO_METERS(1600));
		}
		else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			DisableAll();

			app->forest->Enable();

			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(450), PIXELS_TO_METERS(500));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(300));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(200));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(450), PIXELS_TO_METERS(100));
		}
		else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			DisableAll();

			app->battlefield->Enable();

			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(600), PIXELS_TO_METERS(2800));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3000));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3100));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(600), PIXELS_TO_METERS(3200));
		}
		else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			DisableAll();

			app->dungeon->Enable();

			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(1100), PIXELS_TO_METERS(200));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(200));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(950), PIXELS_TO_METERS(200));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(900), PIXELS_TO_METERS(200));
		}
		else if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			DisableAll();

			app->outside->Enable();

			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1300));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1500));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1600));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(1000), PIXELS_TO_METERS(1700));
		}
		else if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			DisableAll();

			app->inside->Enable();

			app->entities->GetPlayer()->SetPlayerPosition(PIXELS_TO_METERS(500), PIXELS_TO_METERS(800));
			app->entities->GetPlayer()->SetCompanion0Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(600));
			app->entities->GetPlayer()->SetCompanion1Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(500));
			app->entities->GetPlayer()->SetCompanion2Position(PIXELS_TO_METERS(500), PIXELS_TO_METERS(400));
		}
		else if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		{
			app->SaveGameRequest();
		}
		else if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		{
			app->LoadGameRequest(false);
		}
	}
	
	if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		app->frontground->godmode = !app->frontground->godmode;
	}
	else if (app->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		app->ToggleFPS();
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

	if (app->scene->fuegoSeguir == true )
	{
		seguir-=10;
	
	}
	if (seguir <= 900 )
	{
		app->scene->fuegoSeguir = false;
	}
	if (settings == false && !started)
	{
		app->render->DrawTexture(big_fire_light, c_x + 752, c_y + seguir + 930, &(light_big_fire_anim.GetCurrentFrame()));
		app->render->DrawTexture(big_fire, c_x + 897, c_y + seguir +585, &(big_fire_anim.GetCurrentFrame()));
		app->render->DrawTexture(smook_big_fire, c_x + 960, c_y + seguir + 300, &(smook_big_fire_anim.GetCurrentFrame()));

		//Boton que sale en la primera pantalla para pasarla
		if(app->scene->space_boton)
		app->render->DrawTexture(space_boton, c_x+500 , c_y + seguir+595, &(space_boton_anim.GetCurrentFrame()));
	}
	
	
	//---------------------------------------------------------HUD PAUSE---------------------------------------------
	//Dimensiones Hud Pause
	PauseMenuHUD.x = c_x+ c_x_menu;
	PauseMenuHUD.y = c_y;

	if (app->scene->esc == true)
	{
		//Hace que el menu se quite
		if (!paused && !settings)
		{
			if (c_x_menu >= 90)
			{
				c_x_menu -= 35.0f;
			}
		}

		//Fondo Negro transparente que sale cuando pausas
		if (paused)
		{
			app->render->DrawRectangle(r, 0, 0, 0, 200);
		}

		if (started)
		{
			//Cuando pausas se pone un fondo verde (Substituir en un futuro por un HUD creado)
			app->render->DrawTexture(menu_in_game, PauseMenuHUD.x - 475, PauseMenuHUD.y + 40);
		}

		//Hace que el menu aparezca
		if (paused && !intro && !settings)
		{

			if (desMenu == true && c_x_menu <= 470)
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
				pause_buttons[0].rect.x = c_x + c_x_menu - 460;
				pause_buttons[0].rect.y = c_y + 170;

				//Boton Opciones
				pause_buttons[1].rect.x = c_x + c_x_menu - 460;
				pause_buttons[1].rect.y = c_y + 270;

				//Boton Back to menu
				pause_buttons[2].rect.x = c_x + c_x_menu - 460;
				pause_buttons[2].rect.y = c_y + 370;

				//Boton Salir
				pause_buttons[3].rect.x = c_x + c_x_menu - 460;
				pause_buttons[3].rect.y = c_y + 470;

				//Recuadro en Botones permanente
				if (pause_buttons[i].state == 0)
				{

				}
				//Recuadro en Botones Si pasas por encima
				else if (pause_buttons[0].state == 1)
				{
					app->render->DrawTexture(pause_buttons[0].alt_tex_selec, pause_buttons[0].rect.x, pause_buttons[0].rect.y + 10);
				}
				else if (pause_buttons[1].state == 1)
				{
					app->render->DrawTexture(pause_buttons[1].alt_tex_selec, pause_buttons[1].rect.x, pause_buttons[1].rect.y + 10);
				}
				else if (pause_buttons[2].state == 1)
				{
					app->render->DrawTexture(pause_buttons[2].alt_tex_selec, pause_buttons[2].rect.x, pause_buttons[2].rect.y + 20);
				}
				else if (pause_buttons[3].state == 1)
				{
					app->render->DrawTexture(pause_buttons[3].alt_tex_selec, pause_buttons[3].rect.x, pause_buttons[3].rect.y + 10);
				}

				//Recuadro en Botones cuando haces click Izquiero
				else if (pause_buttons[i].state == 2)
				{
					app->render->DrawRectangle(pause_buttons[i].rect, pColorR, pColorG, pColorB);
				}

				//Imprime las imagenes de los botones
				if (app->combat_scene->Enabled() && i == 2)
				{
					app->render->DrawTexture(menu_buttons[4].alt_tex2, pause_buttons[i].rect.x + 10, pause_buttons[i].rect.y + 40);
				}
				else
				{
					app->render->DrawTexture(pause_buttons[i].tex, pause_buttons[i].rect.x + 10, pause_buttons[i].rect.y + 10);
				}
			}
		}
		//------------------------------------------------------


			//----------------------------------------------------HUD INICIO------------------------------------------
		if (intro && !settings)
		{
			if (subplaymenu)
			{
				app->render->DrawRectangle(r, 0, 0, 0, 200);
				menu_play_anim.Update();
				app->render->DrawTexture(menu_play, c_x + c_x_menu - 10, c_y, &(menu_play_anim.GetCurrentFrame()));

				menu_buttons[4].rect.x = c_x + 70;
				menu_buttons[4].rect.y = c_y + 150;


				menu_buttons[5].rect.x = c_x + 70;
				menu_buttons[5].rect.y = c_y + 250;

				if (menu_buttons[4].state == 0 && subplaymenu && firstime)
					app->render->DrawTexture(menu_buttons[4].alt_tex2, menu_buttons[4].rect.x + 10, menu_buttons[4].rect.y - 5);

				if (menu_buttons[4].state == 0 && subplaymenu && !firstime)
					app->render->DrawTexture(menu_buttons[4].tex, menu_buttons[4].rect.x + 10, menu_buttons[4].rect.y - 5);

				if (menu_buttons[5].state == 0 && subplaymenu)
					app->render->DrawTexture(menu_buttons[5].tex, menu_buttons[5].rect.x + 10, menu_buttons[5].rect.y - 5);


				//Se iluminan las letras cuando pasas por encima
				if (menu_buttons[4].state == 1 && subplaymenu && firstime)
				{
					app->render->DrawTexture(menu_buttons[4].alt_tex2, menu_buttons[4].rect.x + 10, menu_buttons[4].rect.y - 5);
				}
				//Se iluminan las letras cuando pasas por encima
				if (menu_buttons[4].state == 1 && subplaymenu && !firstime)
				{
					app->render->DrawTexture(menu_buttons[4].alt_tex, menu_buttons[4].rect.x, menu_buttons[4].rect.y - 20);
				}
				//Se iluminan las letras cuando pasas por encima
				if (menu_buttons[5].state == 1 && subplaymenu)
				{
					app->render->DrawTexture(menu_buttons[5].alt_tex, menu_buttons[5].rect.x, menu_buttons[5].rect.y - 20);
				}
			}

			//Boton Jugar
			menu_buttons[0].rect.x = c_x + 70;
			menu_buttons[0].rect.y = c_y + 150;
			//Boton Opciones
			menu_buttons[1].rect.x = c_x + 50;
			menu_buttons[1].rect.y = c_y + 385;
			//Boton Creditos
			menu_buttons[2].rect.x = c_x + 65;
			menu_buttons[2].rect.y = c_y + 590;
			//Boton Salir
			menu_buttons[3].rect.x = c_x + 525;
			menu_buttons[3].rect.y = c_y + 590;

			if (!subplaymenu)
			{
				menu_buttons[4].rect.x = c_x + 7000;
				menu_buttons[4].rect.y = c_y + 1500;
				menu_buttons[5].rect.x = c_x + 7000;
				menu_buttons[5].rect.y = c_y + 2500;
				menu_play_anim.Reset();
			}

			//Recuadro en Botones permanente
			if (menu_buttons[0].state == 0 && !subplaymenu)
				app->render->DrawTexture(menu_buttons[0].tex, menu_buttons[0].rect.x + 10, menu_buttons[0].rect.y - 5);

			if (menu_buttons[1].state == 0 && !subplaymenu)
				app->render->DrawTexture(menu_buttons[1].tex, menu_buttons[1].rect.x + 10, menu_buttons[1].rect.y - 5);

			if (menu_buttons[2].state == 0 && !subplaymenu)
				app->render->DrawTexture(menu_buttons[2].tex, menu_buttons[2].rect.x + 10, menu_buttons[2].rect.y - 5);

			if (menu_buttons[3].state == 0 && !subplaymenu)
				app->render->DrawTexture(menu_buttons[3].tex, menu_buttons[3].rect.x + 10, menu_buttons[3].rect.y - 5);

			//Se iluminan las letras cuando pasas por encima
			if (menu_buttons[0].state == 1 && !subplaymenu)
			{
				app->render->DrawTexture(menu_buttons[0].alt_tex, menu_buttons[0].rect.x, menu_buttons[0].rect.y - 20);
			}
			//Se iluminan las letras cuando pasas por encima
			if (menu_buttons[1].state == 1 && !subplaymenu)
			{
				app->render->DrawTexture(menu_buttons[1].alt_tex, menu_buttons[1].rect.x, menu_buttons[1].rect.y - 20);
			}
			//Se iluminan las letras cuando pasas por encima
			if (menu_buttons[2].state == 1 && !subplaymenu)
			{
				app->render->DrawTexture(menu_buttons[2].alt_tex, menu_buttons[2].rect.x, menu_buttons[2].rect.y - 20);
			}
			//Se iluminan las letras cuando pasas por encima
			if (menu_buttons[3].state == 1 && !subplaymenu)
			{
				app->render->DrawTexture(menu_buttons[3].alt_tex, menu_buttons[3].rect.x, menu_buttons[3].rect.y - 20);
			}

			//Recuadro en Botones Si pasas por encima
			//Boton Jugar Antorcha
			if (menu_buttons[0].state == 1 && !subplaymenu)
			{
				app->render->DrawTexture(light_fire1, menu_buttons[0].rect.x - 142, menu_buttons[0].rect.y - 87, &(torch_light_1_anim.GetCurrentFrame()));
				app->render->DrawTexture(torch_fire, menu_buttons[0].rect.x + 280, menu_buttons[0].rect.y + 20, &(torch_selection_anim.GetCurrentFrame()));
			}
			//Boton Opciones Antorcha
			else if (menu_buttons[1].state == 1 && !subplaymenu)
			{
				app->render->DrawTexture(light_fire2, menu_buttons[1].rect.x - 90, menu_buttons[1].rect.y - 80, &(torch_light_2_anim.GetCurrentFrame()));
				app->render->DrawTexture(torch_fire, menu_buttons[1].rect.x + 348, menu_buttons[1].rect.y - 10, &(torch_selection_anim.GetCurrentFrame()));
			}
			//Boton Creditos Antorcha
			else if (menu_buttons[2].state == 1 && !subplaymenu)
			{
				app->render->DrawTexture(light_fire3, menu_buttons[2].rect.x - 140, menu_buttons[2].rect.y - 80, &(torch_light_3_anim.GetCurrentFrame()));
				app->render->DrawTexture(torch_fire, menu_buttons[2].rect.x - 38, menu_buttons[2].rect.y + 20, &(torch_selection_anim.GetCurrentFrame()));
			}
			//Boton Salir Antorcha
			else if (menu_buttons[3].state == 1 && !subplaymenu)
			{
				app->render->DrawTexture(light_fire4, menu_buttons[3].rect.x - 65, menu_buttons[3].rect.y - 67, &(torch_light_4_anim.GetCurrentFrame()));
				app->render->DrawTexture(torch_fire, menu_buttons[3].rect.x + 164, menu_buttons[3].rect.y - 25, &(torch_selection_anim.GetCurrentFrame()));
			}

			
			//Recuadro en Botones cuando haces click Izquiero
			/*/else if (menu_buttons[0].state == 2)
			{
				if (credits)
				{
					app->render->DrawTexture(team_photo, PauseMenuHUD.x - 100, PauseMenuHUD.y);
				}
			}*/

			if (credits)
			{
				app->render->DrawTexture(team_photo, PauseMenuHUD.x - 100, PauseMenuHUD.y);
			}
		}

		//---------------------------------------------------------HUD PAUSE---------------------------------------------
		if (settings)//&& app->scene->opciones==true)
		{
			int z, w;
			app->input->GetMousePosition(z, w);

			for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
			{
				settings_buttons[0].rect.x = c_x + 20;
				settings_buttons[0].rect.y = c_y + 200;

				settings_buttons[1].rect.x = c_x + 20;
				settings_buttons[1].rect.y = c_y + 320;

				settings_buttons[2].rect.x = c_x + 20;
				settings_buttons[2].rect.y = c_y + 400;

				settings_buttons[3].rect.x = c_x + 20;
				settings_buttons[3].rect.y = c_y + 500;

				app->render->DrawTexture(settings_buttons[0].alt_tex2, settings_buttons[0].rect.x + 10, settings_buttons[0].rect.y - 40);
				app->render->DrawTexture(settings_buttons[1].alt_tex2, settings_buttons[1].rect.x + 10, settings_buttons[1].rect.y - 40);

				if (settings_buttons[i].state == 0)
				{

				}
				else if (settings_buttons[0].state == 1)
				{
					app->render->DrawTexture(settings_buttons[0].alt_tex_selec, settings_buttons[0].rect.x + 10, settings_buttons[0].rect.y - 67);
				}
				else if (settings_buttons[1].state == 1)
				{
					app->render->DrawTexture(settings_buttons[1].alt_tex_selec, settings_buttons[1].rect.x + 10, settings_buttons[1].rect.y - 60);
				}
				else if (settings_buttons[2].state == 1)
				{
					app->render->DrawTexture(settings_buttons[2].alt_tex_selec, settings_buttons[2].rect.x + 10, settings_buttons[2].rect.y + 15);
				}
				else if (settings_buttons[3].state == 1)
				{
					app->render->DrawTexture(settings_buttons[3].alt_tex_selec, settings_buttons[3].rect.x + 10, settings_buttons[3].rect.y + 5);
				}
				else if (settings_buttons[i].state == 2)
				{

				}

				if (slider)
				{
					if (z < 25)
					{
						z = 25;
					}
					else if (z > 215)
					{
						z = 215;
					}
					xbarra = z;
					app->render->DrawTexture(settings_buttons[0].alt_tex, z + c_x, settings_buttons[0].rect.y);
					app->audio->SetMusic((z - 0) / 2);
				}
				else

				{
					app->render->DrawTexture(settings_buttons[0].alt_tex, xbarra + c_x, settings_buttons[0].rect.y);
				}

				if (slider2)
				{
					xbarra2 = z;
					if (z < 30)
					{
						z = 30;
					}
					else if (z > 220)
					{
						z = 220;
					}

					app->render->DrawTexture(settings_buttons[1].alt_tex, z + c_x, settings_buttons[1].rect.y);
					app->audio->SetFX((z - 100) / 2);
				}
				else
				{
					app->render->DrawTexture(settings_buttons[1].alt_tex, xbarra2 + c_x, settings_buttons[1].rect.y);
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
	}

	SDL_Rect rect;
	if (win)
	{
		app->render->DrawRectangle(r, 0, 0, 0, 200);

		//app->render->DrawTexture(combat_win, c_x, c_y);

		win_button.rect.x = ((int)win_w / 2) - (win_button.rect.w / 2) + c_x;
		win_button.rect.y = (int)win_h / 2 + 200 + c_y;

		if (win_button.state == 0)
		{
			rect = { 0, 0, 500, 70 };
			app->render->DrawTexture(whitemark_500x70, win_button.rect.x, win_button.rect.y, &rect);
		}
		else if (win_button.state == 1)
		{
			rect = { 0, 70, 500, 70 };
			app->render->DrawTexture(whitemark_500x70, win_button.rect.x, win_button.rect.y, &rect);
		}
		else if (win_button.state == 2)
		{
			rect = { 0, 140, 500, 70 };
			app->render->DrawTexture(whitemark_500x70, win_button.rect.x, win_button.rect.y, &rect);
		}

		app->fonts->BlitText(win_button.rect.x, win_button.rect.y + 15, app->fonts->textFont1, "return to field");
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
				rect = { 0, 0, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, lose_buttons[i].rect.x, lose_buttons[i].rect.y, &rect);
			}
			else if (lose_buttons[i].state == 1)
			{
				rect = { 0, 70, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, lose_buttons[i].rect.x, lose_buttons[i].rect.y, &rect);
			}
			else if (lose_buttons[i].state == 2)
			{
				rect = { 0, 140, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, lose_buttons[i].rect.x, lose_buttons[i].rect.y, &rect);
			}
		}
		
		app->fonts->BlitText(lose_buttons[0].rect.x, lose_buttons[0].rect.y + 15, app->fonts->textFont1, "restart battle");
		app->fonts->BlitText(lose_buttons[1].rect.x, lose_buttons[1].rect.y + 15, app->fonts->textFont1, "return to field");
	}

	if (scape)
	{
		app->render->DrawRectangle(r, 0, 0, 0, 200);

		//app->render->DrawTexture(combat_scape, c_x, c_y);

		scape_buttons[0].rect.x = ((int)win_w / 2) - (scape_buttons[0].rect.w / 2) - 300 + c_x;
		scape_buttons[0].rect.y = (int)win_h / 2 + 200 + c_y;
		scape_buttons[1].rect.x = ((int)win_w / 2) - (scape_buttons[1].rect.w / 2) + 300 + c_x;
		scape_buttons[1].rect.y = (int)win_h / 2 + 200 + c_y;

		for (size_t i = 0; i < NUM_SCAPE_BUTTONS; i++)
		{
			if (scape_buttons[i].state == 0)
			{
				rect = { 0, 0, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, scape_buttons[i].rect.x, lose_buttons[i].rect.y, &rect);
			}
			else if (scape_buttons[i].state == 1)
			{
				rect = { 0, 70, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, scape_buttons[i].rect.x, lose_buttons[i].rect.y, &rect);
			}
			else if (scape_buttons[i].state == 2)
			{
				rect = { 0, 140, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, scape_buttons[i].rect.x, lose_buttons[i].rect.y, &rect);
			}
		}

		app->fonts->BlitText(scape_buttons[0].rect.x, scape_buttons[0].rect.y + 15, app->fonts->textFont1, "sure to leave");
		app->fonts->BlitText(scape_buttons[1].rect.x, scape_buttons[1].rect.y + 15, app->fonts->textFont1, "cancel scape");
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

void Menu::SetWinLoseScape(int n)
{
	if (n == 0)
	{
		win = true;
	}
	else if (n == 1)
	{
		lose = true;
	}
	else if (n == 2)
	{
		scape = true;
	}
	else
	{
		win = false;
		lose = false;
		scape = false;
	}
}

bool Menu::ReturnStartScreen()
{
	started = false;
	app->frontground->SetA_Black();

	return true;
}

void Menu::DisableAll()
{
	app->scene->Disable();
	app->town1->Disable();
	app->town2->Disable();
	app->forest->Disable();
	app->battlefield->Disable();
	app->dungeon->Disable();
	app->outside->Disable();
	app->inside->Disable();
	app->combat_scene->Disable();
}

void Menu::InitPlayer()
{
	if (firstime)
	{
		app->entities->player_init = false;
		firstime = false;
	}

	// after fadeout
	started = true;
}