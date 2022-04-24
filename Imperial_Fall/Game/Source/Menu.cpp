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
#include "Inventory.h"
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
#include "Combat_Menu.h"
#include "LogoScreen.h"

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
	if (this->Enabled() && !this->Disabled())
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

		chosed = 0;
		app->win->GetWindowSize(win_w, win_h);

		click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
		hover_sound = app->audio->LoadFx("Assets/audio/fx/hover.wav");

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
		whitemark_1240x680 = app->tex->Load("Assets/textures/1240x680_whitemark.png");
		skills_icons = app->tex->Load("Assets/textures/skill_icons.png");

		win_button.rect.w = 500;
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

		combat_back = app->tex->Load("Assets/textures/Temporal_Background.png");
		combat_win = app->tex->Load("Assets/textures/win_text.png");
		combat_lose = app->tex->Load("Assets/textures/lose_text.png");
		combat_scape = app->tex->Load("Assets/textures/scape_text.png");


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

		hover_playing = false;
		cursor.tex = app->tex->Load("Assets/textures/cursor_default.png");
	}

	return true;
}

// Called each loop iteration
bool Menu::PreUpdate()
{
	intro = !started;

	if (!InAnyButton())
	{
		hover_playing = false;
	}
	
	if (kill_enemy)
	{
		app->entities->KillEnemy();
	}

	if (!app->frontground->controller) // keyboard
	{
		//app->input->GetMousePosition(cursor.pos.x, cursor.pos.y);

		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !intro && description_disabled && app->inventory->hide)
		{
			paused = !paused;
		}

		if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && !intro && !paused && !settings && description_disabled
			&& app->inventory->hide && app->inventory->Enabled())
		{
			app->inventory->hide = false;
			app->inventory->SetTextCd(30);
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
						if (!hover_playing)
						{
							if (app->combat_scene->Enabled() && i == 2) {}
							else
							{
								app->audio->PlayFx(hover_sound);
								hover_playing = true;
							}
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
						if (!hover_playing)
						{
							if (firstime && i == 4) {}
							else
							{
								if (subplaymenu && (i == 4 || i == 5))
								{
									app->audio->PlayFx(hover_sound);
									hover_playing = true;
								}
								else if (!subplaymenu && (i == 0 || i == 1 || i == 2 || i == 3))
								{
									app->audio->PlayFx(hover_sound);
									hover_playing = true;
								}
							}
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
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
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
					if (!hover_playing)
					{
						app->audio->PlayFx(hover_sound);
						hover_playing = true;
					}
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
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
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
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
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
	}
	else // controller
	{
		GamePad& pad = app->input->pads[0];

		if (pad.up == true)
		{
			app->input->SetKey(SDL_SCANCODE_UP, KEY_REPEAT);
		}
		if (pad.down == true)
		{
			app->input->SetKey(SDL_SCANCODE_DOWN, KEY_REPEAT);
		}
		if (pad.left == true)
		{
			app->input->SetKey(SDL_SCANCODE_LEFT, KEY_REPEAT);
		}
		if (pad.right == true)
		{
			app->input->SetKey(SDL_SCANCODE_RIGHT, KEY_REPEAT);
		}
		if (pad.y == true)
		{
			app->input->SetKey(SDL_SCANCODE_U, KEY_REPEAT);
		}


		if (app->input->GetKey(SDL_SCANCODE_U) == KEY_UP && !intro)
		{
			paused = !paused;
			chosed = 0;
		}

		if (intro && subplaymenu && app->input->GetKey(SDL_SCANCODE_U) == KEY_UP)
		{
			subplaymenu = false;
			menu_buttons[0].state = 1;
			chosed = 0;
		}

		if (intro && credits && app->input->GetKey(SDL_SCANCODE_U) == KEY_UP)
		{
			credits = false;
			menu_buttons[2].state = 1;
			chosed = 2;
		}

		if (intro && settings && app->input->GetKey(SDL_SCANCODE_U) == KEY_UP)
		{
			subplaymenu = false;
			settings = false;
			menu_buttons[1].state = 1;
			chosed = 1;
		}

		if (!intro && settings && app->input->GetKey(SDL_SCANCODE_U) == KEY_UP)
		{
			subplaymenu = false;
			settings = false;
			menu_buttons[1].state = 1;
			chosed = 1;
		}

		if (app->scene->esc == true)
		{
			int x, y;
			app->input->GetMousePosition(x, y);

			float cx = -app->render->camera.x;
			float cy = -app->render->camera.y;

			if (paused)
			{
				if (pause_buttons[0].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						pause_buttons[0].state = 0;
						pause_buttons[1].state = 1;
						chosed = 1;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (pause_buttons[1].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						if (app->combat_scene->Enabled())
						{
							pause_buttons[1].state = 0;
							pause_buttons[3].state = 1;
							chosed = 3;
							app->audio->PlayFx(hover_sound);
						}
						else
						{
							pause_buttons[1].state = 0;
							pause_buttons[2].state = 1;
							chosed = 2;
							app->audio->PlayFx(hover_sound);
						}
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						pause_buttons[1].state = 0;
						pause_buttons[0].state = 1;
						chosed = 0;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (pause_buttons[2].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						pause_buttons[2].state = 0;
						pause_buttons[1].state = 1;
						chosed = 1;
						app->audio->PlayFx(hover_sound);
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						pause_buttons[2].state = 0;
						pause_buttons[3].state = 1;
						chosed = 3;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (pause_buttons[3].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						if (app->combat_scene->Enabled())
						{
							pause_buttons[3].state = 0;
							pause_buttons[1].state = 1;
							chosed = 1;
							app->audio->PlayFx(hover_sound);
						}
						else
						{
							pause_buttons[3].state = 0;
							pause_buttons[2].state = 1;
							chosed = 2;
							app->audio->PlayFx(hover_sound);
						}
					}
				}
			}
			else if (intro && !settings)
			{
				if (menu_buttons[0].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						menu_buttons[0].state = 0;
						menu_buttons[1].state = 1;
						chosed = 1;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (menu_buttons[1].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						menu_buttons[1].state = 0;
						menu_buttons[2].state = 1;
						chosed = 2;
						app->audio->PlayFx(hover_sound);
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						menu_buttons[1].state = 0;
						menu_buttons[0].state = 1;
						chosed = 0;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (menu_buttons[2].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						menu_buttons[2].state = 0;
						menu_buttons[3].state = 1;
						chosed = 3;
						app->audio->PlayFx(hover_sound);
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						menu_buttons[2].state = 0;
						menu_buttons[1].state = 1;
						chosed = 1;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (menu_buttons[3].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						menu_buttons[3].state = 0;
						menu_buttons[2].state = 1;
						chosed = 2;
						app->audio->PlayFx(hover_sound);
					}
				}
			}
			else if (intro && subplaymenu)
			{
				if (menu_buttons[4].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						menu_buttons[4].state = 0;
						menu_buttons[5].state = 1;
						chosed = 5;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (menu_buttons[5].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP && !firstime)
					{
						menu_buttons[5].state = 0;
						menu_buttons[4].state = 1;
						chosed = 4;
						app->audio->PlayFx(hover_sound);
					}
				}
			}

			if (settings)
			{
				if (settings_buttons[0].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						settings_buttons[0].state = 0;
						settings_buttons[1].state = 1;
						chosed = 1;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (settings_buttons[1].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						settings_buttons[1].state = 0;
						settings_buttons[2].state = 1;
						chosed = 2;
						app->audio->PlayFx(hover_sound);
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						settings_buttons[1].state = 0;
						settings_buttons[0].state = 1;
						chosed = 0;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (settings_buttons[2].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
					{
						settings_buttons[2].state = 0;
						settings_buttons[3].state = 1;
						chosed = 3;
						app->audio->PlayFx(hover_sound);
					}
					else if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						settings_buttons[2].state = 0;
						settings_buttons[1].state = 1;
						chosed = 1;
						app->audio->PlayFx(hover_sound);
					}
				}
				else if (settings_buttons[3].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_UP) == KEY_UP)
					{
						settings_buttons[3].state = 0;
						settings_buttons[2].state = 1;
						chosed = 2;
						app->audio->PlayFx(hover_sound);
					}
				}
			}

			if (win)
			{
				win_button.state = 1;
			}
			else if (lose)
			{
				if (lose_buttons[0].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						lose_buttons[0].state = 0;
						lose_buttons[1].state = 1;
						chosed = 1;
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
					}
				}
				else if (lose_buttons[1].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						lose_buttons[1].state = 0;
						lose_buttons[0].state = 1;
						chosed = 0;
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
					}
				}
			}
			else if (scape)
			{
				if (scape_buttons[0].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
					{
						scape_buttons[0].state = 0;
						scape_buttons[1].state = 1;
						chosed = 1;
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
					}
				}
				else if (scape_buttons[1].state == 1)
				{
					if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
					{
						scape_buttons[1].state = 0;
						scape_buttons[0].state = 1;
						chosed = 0;
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
					}
				}
			}
		}
	}

	if (app->combat_menu->in_description)
	{
		description_disabled = false;
	}
	else
	{
		description_disabled = true;
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

		if (app->frontground->controller)
		{
			GamePad& pad = app->input->pads[0];

			if (pad.a == true)
			{
				app->input->SetKey(SDL_SCANCODE_Y, KEY_REPEAT);
			}
		}

		// pause buttons
		if (paused && !intro && !settings)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && pause_buttons[chosed].state == 1)
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
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && menu_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					subplaymenu = true;
					if (app->frontground->controller)
					{
						if (firstime)
						{
							menu_buttons[0].state = 0;
							menu_buttons[5].state = 1;
							chosed = 5;
						}
						else
						{
							menu_buttons[0].state = 0;
							menu_buttons[4].state = 1;
							chosed = 4;
						}
					}
					
					break;

				case 1:
					if (!subplaymenu)
					{
						settings = true;
						if (app->frontground->controller)
						{
							settings_buttons[0].state = 1;
							chosed = 0;
						}
					}
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
						app->menu->redtemplar_killed = false;
						subplaymenu = false;
						app->inventory->BlockAll();
						app->inventory->ResetItems();
						app->inventory->ResetGear();
					}
					break;
				}
				if (!app->frontground->controller)
				{
					menu_buttons[chosed].state = 2;
				}
			}
		}

		//settings buttons
		if (settings)
		{
			subplaymenu = false;
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && settings_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);

				switch (chosed)
				{
				case 0:
					if (!app->frontground->controller)
					{
						slider = !slider;
					}
					else
					{
						slider = true;
					}
					
					break;
				case 1:
					if (!app->frontground->controller)
					{
						slider2 = !slider2;
					}
					else
					{
						slider2 = true;
					}

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

					if (app->frontground->controller)
					{
						settings_buttons[2].state = 1;
						chosed = 2;
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

					if (app->frontground->controller)
					{
						settings_buttons[3].state = 1;
						chosed = 3;
					}
					break;
				}
				if (!app->frontground->controller)
				{
					settings_buttons[chosed].state = 2;
				}
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
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && win_button.state == 1)
			{
				app->audio->PlayFx(click_sound);
				app->frontground->ReturnToField();
				app->inventory->UnlockObject(app->frontground->reward.c_str());
				win_button.state = 2;
				kill_enemy = true;
			}
			if (chosed == -1)
			{
				win_button.state = 1;
				chosed = 0;
			}
		}
		else if (lose)
		{
			subplaymenu = false;

			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && lose_buttons[chosed].state == 1)
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
					app->frontground->reward = "999";
					break;
				}

				lose_buttons[chosed].state = 2;
			}
			if (chosed == -1)
			{
				lose_buttons[0].state = 1;
				chosed = 0;
			}
		}
		else if (scape)
		{
			subplaymenu = false;

			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && scape_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					// sure to scape
					app->frontground->ReturnToField();
					app->frontground->reward = "999";
					break;
				case 1:
					// cancel scape
					scape = false;
					if (app->frontground->controller)
					{
						app->combat_menu->SetController();
					}
					break;
				}

				scape_buttons[chosed].state = 2;
			}
			if (chosed == -1)
			{
				scape_buttons[0].state = 1;
				chosed = 0;
			}
		}
	}

	// Tricks
	if (app->frontground->godmode)
	{
		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->frontground->move_to = MOVE_TO::SCENE_TOWN1;

			app->frontground->FadeToBlack();
		}
		else if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->frontground->move_to = MOVE_TO::SCENE_TOWN2;

			app->frontground->FadeToBlack();
		}
		/*else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->frontground->move_to = MOVE_TO::SCENE_FOREST;

			app->frontground->FadeToBlack();
		}*/
		else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->frontground->move_to = MOVE_TO::SCENE_BATTLEFIELD;

			app->frontground->FadeToBlack();
		}
		/*else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->frontground->move_to = MOVE_TO::SCENE_DUNGEON;

			app->frontground->FadeToBlack();
		}
		else if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->frontground->move_to = MOVE_TO::SCENE_OUTSIDE;

			app->frontground->FadeToBlack();
		}
		else if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->frontground->move_to = MOVE_TO::SCENE_INSIDE;

			app->frontground->FadeToBlack();
		}*/
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
	else if (app->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		app->frontground->fast_combat = !app->frontground->fast_combat;
	}
	else if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		app->inventory->UnlockAll();
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
	if (!settings && !started)
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

			if (credits)
			{
				app->render->DrawTexture(team_photo, PauseMenuHUD.x - 70, PauseMenuHUD.y);
			}
		}

		//---------------------------------------------------------HUD PAUSE---------------------------------------------
		if (settings)
		{
			int w;
			if (!app->frontground->controller)
			{
				app->input->GetMousePosition(z1, w);
				app->input->GetMousePosition(z2, w);
			}

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
					if (!app->frontground->controller)
					{
						if (z1 < 25)
						{
							z1 = 25;
						}
						else if (z1 > 215)
						{
							z1 = 215;
						}
					}
					else
					{
						GamePad& pad = app->input->pads[0];

						if (pad.a == true)
						{
							app->input->SetKey(SDL_SCANCODE_Y, KEY_REPEAT);
						}

						if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP)
						{
							if (z1 == 25)
							{
								z1 = 60;
							}
							else if (z1 == 60)
							{
								z1 = 135;
							}
							else if (z1 == 135)
							{
								z1 = 215;
							}
							else if (z1 == 215)
							{
								z1 = 25;
							}
							slider = false;
						}
					}
					
					xbarra = z1;
					app->render->DrawTexture(settings_buttons[0].alt_tex, z1 + c_x - 3, settings_buttons[0].rect.y);
					app->audio->SetMusic((z1 - 25) / 2);
				}
				else

				{
					app->render->DrawTexture(settings_buttons[0].alt_tex, xbarra + c_x - 3, settings_buttons[0].rect.y);
				}

				if (slider2)
				{
					if (!app->frontground->controller)
					{
						if (z2 < 30)
						{
							z2 = 30;
						}
						else if (z2 > 220)
						{
							z2 = 220;
						}
					}
					else
					{
						GamePad& pad = app->input->pads[0];

						if (pad.a == true)
						{
							app->input->SetKey(SDL_SCANCODE_Y, KEY_REPEAT);
						}

						if (app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP)
						{
							if (z2 == 30)
							{
								z2 = 65;
							}
							else if (z2 == 65)
							{
								z2 = 140;
							}
							else if (z2 == 140)
							{
								z2 = 220;
							}
							else if (z2 == 220)
							{
								z2 = 30;
							}
							slider2 = false;
						}
					}

					xbarra2 = z2;
					app->render->DrawTexture(settings_buttons[1].alt_tex, z2 + c_x - 3, settings_buttons[1].rect.y);
					app->audio->SetFX((z2 - 30) / 2);
				}
				else
				{
					app->render->DrawTexture(settings_buttons[1].alt_tex, xbarra2 + c_x - 3, settings_buttons[1].rect.y);
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
		app->render->DrawTexture(combat_back, c_x, c_y);
		app->render->DrawTexture(combat_win, c_x, c_y);

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
		app->render->DrawTexture(combat_back, c_x, c_y);
		app->render->DrawTexture(combat_lose, c_x, c_y);

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
		app->render->DrawTexture(combat_back, c_x, c_y);
		app->render->DrawTexture(combat_scape, c_x, c_y);

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

	// skills descriptions
	if (!description_disabled)
	{
		switch (app->combat_menu->description_type)
		{
		case 0: DisplayEntityInfo(app->combat_menu->desc_entity);
			break;
		case 1: DisplaySkillInfo(app->combat_menu->desc_skill);
			break;
		}
	}

	// draw cursor
	if (!app->frontground->controller && app->inventory->hide)
	{
		app->input->GetMousePosition(cursor.pos.x, cursor.pos.y);
		app->render->DrawTexture(cursor.tex, cursor.pos.x + c_x, cursor.pos.y + c_y);
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
		if (app->frontground->controller)
		{
			win_button.state = 1;
			chosed = -1;
		}
	}
	else if (n == 1)
	{
		lose = true;
		if (app->frontground->controller)
		{
			lose_buttons[0].state = 1;
			chosed = -1;
		}
	}
	else if (n == 2)
	{
		scape = true;
		if (app->frontground->controller)
		{
			scape_buttons[0].state = 1;
			chosed = -1;
		}
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
	app->logo->Disable();
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

void Menu::DisplayEntityInfo(Combat_Entities* entity)
{
	app->render->DrawTexture(whitemark_1240x680, 20, 20);

	// Name
	std::string a;
	switch (entity->GetType())
	{
	case 0: a = "Assassin"; break;
	case 1: a = "Healer"; break;
	case 2: a = "Tank"; break;
	case 3: a = "Wizard"; break;
	case 4: a = "Templar"; break;
	case 5: a = "Mushroom"; break;
	case 6: a = "Goblin"; break;
	case 7: a = "Skeleton"; break;
	case 8: a = "Templar Master"; break;
	default: a = " "; break;
	}
	const char* res = a.c_str();
	app->fonts->BlitCombatText(50, 50, app->fonts->textFont2, res);

	// Health
	a = "Health: ";
	std::string b = std::to_string(entity->GetActualHealth());
	std::string c = " / ";
	std::string d = std::to_string(entity->GetMaxHealth());
	std::string r = a + b + c + d;
	res = r.c_str();
	app->fonts->BlitCombatText(50, 100, app->fonts->textFont2, res);

	// Mana
	a = "Mana: ";
	b = std::to_string(entity->GetActualMana());
	d = std::to_string(entity->GetMaxMana());
	r = a + b + c + d;
	res = r.c_str();
	app->fonts->BlitCombatText(700, 100, app->fonts->textFont2, res);

	// Speed
	a = "Speed: ";
	b = std::to_string(entity->GetSpeed());
	r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(50, 150, app->fonts->textFont2, res);

	// Power
	a = "Power: ";
	b = std::to_string(entity->GetPower());
	r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(700, 150, app->fonts->textFont2, res);

	// Shield
	if (entity->GetShield() > 0)
	{
		a = "Shield: ";
		b = std::to_string(entity->GetShield());
		c = ", ";
		d = std::to_string(entity->GetShieldTurns());
		std::string e = " turns remaining";
		r = a + b + c + d + e;
		res = r.c_str();
		app->fonts->BlitCombatText(50, 200, app->fonts->textFont2, res);
	}

	// Weakness
	a = "Weakness: ";
	switch (entity->GetWeakness())
	{
	case -1: b = "No weakness"; break;
	case 0: b = "Physic"; break;
	case 1: b = "Fire"; break;
	case 2: b = "Lightning"; break;
	case 3: b = "Water"; break;
	default: b = " "; break;
	}
	r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(700, 200, app->fonts->textFont2, res);

	// Buffs and Debuffs
	entity->DisplayStatusDescription(50, 275);
}

void Menu::DisplaySkillInfo(Skill skill)
{
	app->render->DrawTexture(whitemark_1240x680, 20, 20);

	// Name
	std::string a = skill.skill_name;
	const char* res = a.c_str();
	app->fonts->BlitCombatText(50, 50, app->fonts->textFont2, res);

	// Element
	a = "Element: ";
	std::string b;
	switch (skill.element)
	{
	case 0: b = "Physic"; break;
	case 1: b = "Fire"; break;
	case 2: b = "Lightning"; break;
	case 3: b = "Water"; break;
	default: b = " "; break;
	}
	std::string r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(50, 120, app->fonts->textFont2, res);

	// Objective
	SDL_Rect rect;
	if (skill.enemy_objective == ENEMY_OBJECTIVE::ONE_ENEMY)
	{
		rect = { 40, 0, 40, 40 };
		b = "Single Enemy";
	}
	else if (skill.enemy_objective == ENEMY_OBJECTIVE::ALL_ENEMY)
	{
		rect = { 0, 0, 40, 40 };
		b = "Multiple Enemies";
	}
	else if (skill.ally_objective == ALLY_OBJECTIVE::ONE_ALLY)
	{
		rect = { 120, 0, 40, 40 };
		b = "Single Ally";
	}
	else if (skill.ally_objective == ALLY_OBJECTIVE::ALL_ALLY)
	{
		rect = { 80, 0, 40, 40 };
		b = "Multiple Allies";
	}
	else if (skill.ally_objective == ALLY_OBJECTIVE::SELF)
	{
		rect = { 160, 0, 40, 40 };
		b = "Self";
	}
	app->render->DrawTexture(skills_icons, 50, 170, &rect);
	a = "Objective: ";
	r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(90, 175, app->fonts->textFont2, res);

	// Mana cost
	a = "Mana Cost: ";
	b = std::to_string(skill.mana_cost);
	r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(800, 120, app->fonts->textFont2, res);

	// Attack Strenght
	a = "Attack Strenght: ";
	switch (skill.att_strenght)
	{
	case -1: b = "No damage"; break;
	case 0: b = "Low damage"; break;
	case 1: b = "Medium damage"; break;
	case 2: b = "High damage"; break;
	}
	r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(50, 225, app->fonts->textFont2, res);

	// Support Strenght
	a = "Support Strenght: ";
	switch (skill.supp_strenght)
	{
	case -1: b = "No support strenght"; break;
	case 0: b = "Low strenght"; break;
	case 1: b = "Medium strenght"; break;
	case 2: b = "High strenght"; break;
	}
	r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(50, 275, app->fonts->textFont2, res);

	// Buffs mand Debuffs
	app->combat_menu->DisplaySkillEffects(skill, 50, 350);

	// Description
	r = "Description:";
	res = r.c_str();
	app->fonts->BlitCombatText(50, 550 - 34, app->fonts->textFont2, res);
	r = skill.skill_description0;
	res = r.c_str();
	app->fonts->BlitCombatText(50, 550, app->fonts->textFont2, res);
	r = skill.skill_description1;
	res = r.c_str();
	app->fonts->BlitCombatText(50, 550 + 34, app->fonts->textFont2, res);
	r = skill.skill_description2;
	res = r.c_str();
	app->fonts->BlitCombatText(50, 550 + 68, app->fonts->textFont2, res);
	r = skill.skill_description3;
	res = r.c_str();
	app->fonts->BlitCombatText(50, 550 + 102, app->fonts->textFont2, res);
}

bool Menu::InAnyButton()
{
	for (size_t i = 0; i < NUM_BUTTONS; i++)
	{
		if (menu_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_PAUSE_BUTTONS; i++)
	{
		if (pause_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
	{
		if (settings_buttons[i].state == 1)
		{
			return true;
		}
	}
	if (win_button.state == 1)
	{
		return true;
	}
	for (size_t i = 0; i < NUM_LOSE_BUTTONS; i++)
	{
		if (lose_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_SCAPE_BUTTONS; i++)
	{
		if (scape_buttons[i].state == 1)
		{
			return true;
		}
	}

	return false;
}