#include "App.h"
#include "Textures.h"
#include "Render.h"
#include "Window.h"
#include "Audio.h"
#include "Input.h"
#include "Scene.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Dialog.h"
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
#include "End_Combat_Scene.h"
#include "LogoScreen.h"
#include "Intro_Cutscene.h"
#include "Final_Cutscene.h"
#include "Credits.h"

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

		open_book_sound = app->audio->LoadFx("Assets/audio/fx/open_book.wav");
		click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
		hover_sound = app->audio->LoadFx("Assets/audio/fx/hover.wav");
		win_sound = app->audio->LoadFx("Assets/audio/fx/win.wav");
		lose_sound = app->audio->LoadFx("Assets/audio/fx/lose.wav");

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

		whitemark_128x128 = app->tex->Load("Assets/textures/128x128_whitemark.png");
		whitemark_500x70 = app->tex->Load("Assets/textures/500x70_whitemark.png");
		whitemark_800x150 = app->tex->Load("Assets/textures/800x150_whitemark.png");
		whitemark_1240x680 = app->tex->Load("Assets/textures/1240x680_whitemark.png");
		skills_icons = app->tex->Load("Assets/textures/skill_icons.png");
		accept_tex = app->tex->Load("Assets/textures/accept_cancel.png");
		desc_icons = app->tex->Load("Assets/textures/descriptions_icons.png");
		rew_icons = app->tex->Load("Assets/textures/rewards.png");

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



		win_button.tex = app->tex->Load("Assets/textures/Close_Buton_Win.png"); // Return field
		win_button.alt_tex = app->tex->Load("Assets/textures/Close_Buton_Win_Select.png"); // Return field
	
		lose_buttons[0].tex = app->tex->Load("Assets/textures/Retry_Buton_Lose.png"); // Try again
		lose_buttons[0].alt_tex = app->tex->Load("Assets/textures/Retry_Buton_Lose_Select.png"); // Try again

		lose_buttons[1].tex = app->tex->Load("Assets/textures/Run_Boton_Lose.png"); // Return field
		lose_buttons[1].alt_tex = app->tex->Load("Assets/textures/Run_Boton_Lose_Select.png"); // Return field

		Scape_BackGround = app->tex->Load("Assets/textures/Temporal_Background.png");
		Lose_BackGround = app->tex->Load("Assets/textures/Lose_Screen.png");
		Win_BackGround = app->tex->Load("Assets/textures/Win_Screen.png");

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

		creditsTexture = app->tex->Load("Assets/textures/Creditos.png");

		hover_playing = false;

		// unlock animation
		unlock_cd = 120;
		unlock_state = 0;
		unlock_pos = { 576, 200 };
		unlock_rect = { 0, 0, 128, 128 };
		unknow_tex = app->tex->Load("Assets/textures/unknow.png");
		gear_tex = app->tex->Load("Assets/textures/gear.png");
		items_tex = app->tex->Load("Assets/textures/Objects/items.png");
		object_buttons[0].rect.w = 500;
		object_buttons[1].rect.w = 500;
		unlock_fx = app->audio->LoadFx("Assets/audio/fx/unlock.wav");
		equip_sound = app->audio->LoadFx("Assets/audio/fx/equip.wav");

		sub_newgame = false;
		for (size_t i = 0; i < NUM_ASK_BUTTONS; i++)
		{
			ask_buttons[i].rect.w = 128;
			ask_buttons[i].rect.h = 128;
		}

		count_xp = false;
		xp0 = 0;
		xp1 = 0;
		xp2 = 0;
		xp3 = 0;
		pugi::xml_document saveGame;
		saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
		axp0 = saveGame.child("objects").child("assassin").child("experience").attribute("value").as_int();
		axp1 = saveGame.child("objects").child("healer").child("experience").attribute("value").as_int();
		axp2 = saveGame.child("objects").child("tank").child("experience").attribute("value").as_int();
		axp3 = saveGame.child("objects").child("wizard").child("experience").attribute("value").as_int();

		cursor_tex = app->tex->Load("Assets/textures/cursor_default.png");
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

	if (object_obtained && app->inventory->Enabled() && app->frontground->GetA() <= 50)
	{
		unlock_state = 1;
		object_obtained = false;
		app->audio->PlayFx(unlock_fx);
	}
	
	if ((app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP) && !intro && description_disabled && app->inventory->hide && unlock_state == 0
		&& !app->dialog->InDialog() && app->frontground->fix)
	{
		paused = true;
		menu1 = true;

		if (menu1 == true && (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP) && c_x_menu >= 470 && menu2==false)
		{
			paused = false;
			menu1 = false;
		}

		if (menu2 == true && (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP))
		{
			menu2 = false;
		}
	}


	
	


	if ((app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_O) == KEY_UP) && !intro && !paused && !settings && description_disabled
		&& app->inventory->hide && app->inventory->Enabled() && unlock_state == 0)
	{
		app->inventory->hide = false;
		app->inventory->SetTextCd(30);
		app->audio->PlayFx(open_book_sound);
	}


	if (intro && (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP))
		credits = false;

	if (settings && (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP))
	{
		quitarOpciones = true;
	}

	if (subplaymenu && (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_X) == KEY_UP))
	{
		subplaymenu = false;
	}

	if (app->scene->esc == true)
	{
		int x, y;
		x = app->frontground->c_mouse_pos.x;
		y = app->frontground->c_mouse_pos.y;
		//app->input->GetMousePosition(x, y);

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
		else if (intro && !settings && !sub_newgame)
		{
			for (size_t i = 0; i < NUM_MENU_BUTTONS; i++)
			{
				SDL_Rect rect = menu_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					if (!hover_playing)
					{
						if (app->frontground->first_time && i == 4) {}
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
		else if (intro && !settings && sub_newgame)
		{
			for (size_t i = 0; i < NUM_ASK_BUTTONS; i++)
			{
				SDL_Rect rect = ask_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					if (!hover_playing)
					{
						app->audio->PlayFx(hover_sound);
						hover_playing = true;
					}
					chosed = i;
					ask_buttons[i].state = 1;
				}
				else
				{
					ask_buttons[i].state = 0;
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

		if (unlock_state == 2)
		{
			for (size_t i = 0; i < NUM_OBJECT_BUTTONS; i++)
			{
				SDL_Rect rect = object_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					if (i == 0 && app->frontground->reward[0] == '4')
					{
					}
					else
					{
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
						chosed = i;
						object_buttons[i].state = 1;
					}
				}
				else
				{
					object_buttons[i].state = 0;
				}
			}
		}
	}

	if (app->combat_menu->in_description || app->inventory->in_description)
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

		// pause buttons
		if (paused && !intro && !settings)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && pause_buttons[chosed].state == 1)
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
					menu2 = true;
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
		if (intro && !settings && !credits && !sub_newgame)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && menu_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					subplaymenu = true;
					if (app->frontground->controller)
					{
						if (app->frontground->first_time)
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
					if (!started && !app->frontground->first_time)
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
						subplaymenu = false;
					}
					break;

				case 5: // NEW GAME
					if (!started && app->frontground->first_time)
					{
						app->LoadGame(true); // load now, not at frames end
						app->frontground->SetFirstTime(false);
						app->frontground->move_to = MOVE_TO::SCENE_TOWN1;
						app->frontground->FadeToBlack();
						saving = false;
						intro = false;
						paused = false;
						app->frontground->adventure_phase = -1;
						subplaymenu = false;
						app->inventory->BlockAll();
						app->inventory->ResetItems();
						app->inventory->ResetGear();
						app->inventory->ResetSkills();
						app->physics->ResetMiscelanea();
						app->dialog->ResetShop();
						app->dialog->ResetDialogs();
						app->dialog->SaveRenatoDialog();
					}
					else if (!app->frontground->first_time)
					{
						sub_newgame = true;
						ask_buttons[0].state = 1;
						chosed = 0;
					}
					break;
				}
				if (!app->frontground->controller)
				{
					menu_buttons[chosed].state = 2;
				}
			}
		}

		else if (sub_newgame)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && ask_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					app->LoadGame(true); // load now, not at frames end
					app->frontground->SetFirstTime(false);
					app->frontground->move_to = MOVE_TO::SCENE_CUTSCENE_1;
					app->frontground->FadeToBlack();
					saving = false;
					intro = false;
					paused = false;
					app->frontground->adventure_phase = -1;
					subplaymenu = false;
					app->inventory->BlockAll();
					app->inventory->ResetItems();
					app->inventory->ResetGear();
					app->inventory->ResetSkills();
					app->physics->ResetMiscelanea();
					app->dialog->ResetShop();
					app->dialog->ResetDialogs();
					app->dialog->SaveRenatoDialog();
					sub_newgame = false;
					break;
				case 1:
					sub_newgame = false;
					menu_buttons[5].state = 1;
					ask_buttons[1].state = 0;
					chosed = 5;
					break;
				}

				ask_buttons[chosed].state = 2;
			}
		}

		//settings buttons
		if (settings)
		{
			subplaymenu = false;
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && settings_buttons[chosed].state == 1)
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
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && win_button.state == 1)
			{
				app->audio->PlayFx(click_sound);
				if (!theseion2)
				{
					app->frontground->ReturnToField();
					app->inventory->AddXP(0, app->frontground->combat_xp0);
					app->inventory->AddXP(1, app->frontground->combat_xp1);
					app->inventory->AddXP(2, app->frontground->combat_xp2);
					app->inventory->AddXP(3, app->frontground->combat_xp3);
					app->inventory->AddCoins(app->frontground->combat_gold);
				}
				else
				{
					ENEMIES enemies[4];
					enemies[0] = ENEMIES::NECRO_THESEION;
					enemies[1] = ENEMIES::NOTHING;
					enemies[2] = ENEMIES::DRAGON;
					enemies[3] = ENEMIES::NOTHING;
					app->frontground->move_to = MOVE_TO::COMBAT_FINALCOMBAT;
					app->frontground->FadeInCombat(enemies, "999");
					theseion2 = true;
				}
				
				count_xp = true;
				win_button.state = 2;
				kill_enemy = true;

				if (app->frontground->reward != "999")
				{
					object_obtained = true;
				}
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

			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && lose_buttons[chosed].state == 1)
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

				app->inventory->AddXP(0, -5 - (2 * app->frontground->adventure_phase));
				app->inventory->AddXP(1, -5 - (2 * app->frontground->adventure_phase));
				app->inventory->AddXP(2, -5 - (2 * app->frontground->adventure_phase));
				app->inventory->AddXP(3, -5 - (2 * app->frontground->adventure_phase));
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

			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && scape_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					// sure to scape
					app->frontground->ReturnToField();
					app->frontground->reward = "999";
					if (theseion2)
					{
						theseion2 = false;
						dragonDefeated = false;
					}
					break;
				case 1:
					// cancel scape
					scape = false;
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

		if (unlock_state == 2)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP) && object_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(click_sound);
				switch (chosed)
				{
				case 0:
					// equip and close
					app->inventory->EquipGear(app->frontground->reward.c_str());
					app->audio->PlayFx(equip_sound);
					break;
				case 1:
					// only close
					break;
				}

				app->frontground->reward = "999";
				unlock_state = 0;
				object_buttons[chosed].state = 2;
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
		else if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->frontground->move_to = MOVE_TO::SCENE_FOREST;

			app->frontground->FadeToBlack();
		}
		else if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		{
			app->frontground->move_to = MOVE_TO::SCENE_BATTLEFIELD;

			app->frontground->FadeToBlack();
		}
		else if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN && app->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
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
		}
		else if (app->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		{
			app->inventory->UnlockAll();
			app->inventory->EquipAllMaxGear();
		}
		else if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		{
			app->SaveGameRequest();
		}
		else if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		{
			app->LoadGameRequest(false);
		}
		else if (app->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		{
			app->inventory->AddCoins(30);
		}
		else if (app->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
		{
			app->inventory->AddCoins(-30);
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
	
	return true;
}

// Called each loop iteration
bool Menu::PostUpdate()
{
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;
	
	r.x = c_x;
	r.y = c_y;

	if (count_xp)
	{
		if (app->frontground->combat_xp0 > 0)
		{
			app->frontground->combat_xp0--;
			xp0++;
			while (axp0 + xp0 > 100)
			{
				xp0 -= 100;
			}
		}
		if (app->frontground->combat_xp1 > 0)
		{
			app->frontground->combat_xp1--;
			xp1++;
			while (axp1 + xp1 > 100)
			{
				xp1 -= 100;
			}
		}
		if (app->frontground->combat_xp2 > 0)
		{
			app->frontground->combat_xp2--;
			xp2++;
			while (axp2 + xp2 > 100)
			{
				xp2 -= 100;
			}
		}
		if (app->frontground->combat_xp3 > 0)
		{
			app->frontground->combat_xp3--;
			xp3++;
			while (axp3 + xp3 > 100)
			{
				xp3 -= 100;
			}
		}
		if (app->frontground->combat_gold > 0)
		{
			app->frontground->combat_gold--;
		}
		if (app->frontground->combat_xp0 == 0 && app->frontground->combat_xp1 == 0 && app->frontground->combat_xp2 == 0 && 
			app->frontground->combat_xp3 == 0 && app->frontground->combat_gold == 0)
		{
			count_xp = false;
		}
	}

	if (app->scene->fuegoSeguir == true )
	{
		seguir -= 10;
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

				if (menu_buttons[4].state == 0 && subplaymenu && app->frontground->first_time)
					app->render->DrawTexture(menu_buttons[4].alt_tex2, menu_buttons[4].rect.x + 10, menu_buttons[4].rect.y - 5);

				if (menu_buttons[4].state == 0 && subplaymenu && !app->frontground->first_time)
					app->render->DrawTexture(menu_buttons[4].tex, menu_buttons[4].rect.x + 10, menu_buttons[4].rect.y - 5);

				if (menu_buttons[5].state == 0 && subplaymenu)
					app->render->DrawTexture(menu_buttons[5].tex, menu_buttons[5].rect.x + 10, menu_buttons[5].rect.y - 5);


				//Se iluminan las letras cuando pasas por encima
				if (menu_buttons[4].state == 1 && subplaymenu && app->frontground->first_time)
				{
					app->render->DrawTexture(menu_buttons[4].alt_tex2, menu_buttons[4].rect.x + 10, menu_buttons[4].rect.y - 5);
				}
				//Se iluminan las letras cuando pasas por encima
				if (menu_buttons[4].state == 1 && subplaymenu && !app->frontground->first_time)
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
				app->render->DrawTexture(creditsTexture, PauseMenuHUD.x - 60, PauseMenuHUD.y);
			}
		}

		if (sub_newgame)
		{
			app->render->DrawTexture(whitemark_800x150, 240 + c_x, 300 + c_y);

			SDL_Rect b0;
			if (ask_buttons[0].state == 0)
			{
				b0 = { 0, 0, 128, 128 };
			}
			else if (ask_buttons[0].state == 1)
			{
				b0 = { 0, 128, 128, 128 };
			}
			else if (ask_buttons[0].state == 2)
			{
				b0 = { 0, 256, 128, 128 };
			}

			SDL_Rect b1;
			if (ask_buttons[1].state == 0)
			{
				b1 = { 0, 0, 128, 128 };
			}
			else if (ask_buttons[1].state == 1)
			{
				b1 = { 0, 128, 128, 128 };
			}
			else if (ask_buttons[1].state == 2)
			{
				b1 = { 0, 256, 128, 128 };
			}

			SDL_Rect a_rect = { 0, 0, 128, 128 };
			std::string p_siting;

			ask_buttons[0].rect.x = 400 + c_x;
			ask_buttons[0].rect.y = 400 + c_y;
			ask_buttons[1].rect.x = ask_buttons[0].rect.x + 300;
			ask_buttons[1].rect.y = ask_buttons[0].rect.y;
			app->render->DrawTexture(whitemark_128x128, ask_buttons[0].rect.x, ask_buttons[0].rect.y, &b0);
			app->render->DrawTexture(whitemark_128x128, ask_buttons[1].rect.x, ask_buttons[1].rect.y, &b1);
			app->render->DrawTexture(accept_tex, ask_buttons[0].rect.x, ask_buttons[0].rect.y, &a_rect);
			a_rect = { 128, 0, 128, 128 };
			app->render->DrawTexture(accept_tex, ask_buttons[1].rect.x, ask_buttons[1].rect.y, &a_rect);
			p_siting = "Are you sure to start again?";
			app->fonts->BlitCombatText(320 + c_x, 310 + c_y, app->fonts->textFont3, p_siting.c_str());
			p_siting = "You will lose the actual save.";
			app->fonts->BlitCombatText(320 + c_x, 350 + c_y, app->fonts->textFont3, p_siting.c_str());
		}

		//---------------------------------------------------------Menu Settings Inicio---------------------------------------------
		if (settings)
		{
			
			int w;
			if (ocultarMenu == false) 
			{
				if (c_y_corre >= 0.0f)
				{
					ocultarMenu = true;
				}
				else
					c_y_corre += 50.0f;
			}

			if (ocultarMenu == true && quitarOpciones == true )
			{
				if (c_y_corre <= -700.0f) {
					ocultarMenu = false;
					quitarOpciones = false;
					settings = false;
				}
				else c_y_corre -= 50.0f;
			}
			

		
			if (!app->frontground->controller)
			{
				app->input->GetMousePosition(z1, w);
				app->input->GetMousePosition(z2, w);
			}

			for (size_t i = 0; i < NUM_SETTINGS_BUTTONS; i++)
			{
				settings_buttons[0].rect.x = c_x + 20 + c_y_corre;
				settings_buttons[0].rect.y = c_y + 200;

				settings_buttons[1].rect.x = c_x + 20 + c_y_corre;
				settings_buttons[1].rect.y = c_y + 320 ;

				settings_buttons[2].rect.x = c_x + 20 + c_y_corre;
				settings_buttons[2].rect.y = c_y + 400 ;

				settings_buttons[3].rect.x = c_x + 20 + c_y_corre;
				settings_buttons[3].rect.y = c_y + 500 ;

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

						if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP)
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
					app->render->DrawTexture(settings_buttons[0].alt_tex, z1 + c_x - 3, settings_buttons[0].rect.y + c_y_corre);
					app->audio->SetMusic((z1 - 25) / 2);
				}
				else

				{
					if (c_y_corre >= 0.0f)
					app->render->DrawTexture(settings_buttons[0].alt_tex, xbarra + c_x - 3, settings_buttons[0].rect.y + c_y_corre);
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

						if (app->input->GetKey(SDL_SCANCODE_Z) == KEY_UP)
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
					app->render->DrawTexture(settings_buttons[1].alt_tex, z2 + c_x - 3, settings_buttons[1].rect.y + c_y_corre);
					app->audio->SetFX((z2 - 30) / 2);
				}
				else
				{
					if (c_y_corre >= 0.0f) 
					app->render->DrawTexture(settings_buttons[1].alt_tex, xbarra2 + c_x - 3, settings_buttons[1].rect.y + c_y_corre);
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
		app->render->DrawTexture(Win_BackGround, c_x, c_y);
		//app->render->DrawTexture(combat_win, c_x, c_y);

		win_button.rect.x = ((int)win_w / 2) - (win_button.rect.w / 2) + c_x+530;
		win_button.rect.y = (int)win_h / 2 + 200 + c_y-370;

		if (win_button.state == 0)
		{
			app->render->DrawTexture(win_button.tex, win_button.rect.x , win_button.rect.y);
		}

		else if (win_button.state == 1)
		{
			app->render->DrawTexture(win_button.alt_tex, win_button.rect.x - 20 , win_button.rect.y - 20);
		}

		rect = { 0, 0, 64, 64 };
		app->render->DrawTexture(rew_icons, 100 + (315 * 0), 450, &rect);
		app->fonts->BlitCombatText(170 + (315 * 0), 470, app->fonts->textFont2, std::to_string(app->frontground->combat_xp0).c_str());
		app->render->DrawRectangle({ 60 + (315 * 0), 510, 200, 26 }, 200, 200, 200);
		app->render->DrawRectangle({ 62 + (315 * 0), 512, (axp0 + xp0) * 2 + 1, 22 }, 50, 50, 50);
		app->render->DrawTexture(rew_icons, 100 + (315 * 1), 450, &rect);
		app->fonts->BlitCombatText(170 + (315 * 1), 470, app->fonts->textFont2, std::to_string(app->frontground->combat_xp1).c_str());
		app->render->DrawRectangle({ 60 + (315 * 1), 510, 200, 26 }, 200, 200, 200);
		app->render->DrawRectangle({ 62 + (315 * 1), 512, (axp1 + xp1) * 2 + 1, 22 }, 50, 50, 50);
		app->render->DrawTexture(rew_icons, 100 + (315 * 2), 450, &rect);
		app->fonts->BlitCombatText(170 + (315 * 2), 470, app->fonts->textFont2, std::to_string(app->frontground->combat_xp2).c_str());
		app->render->DrawRectangle({ 60 + (315 * 2), 510, 200, 26 }, 200, 200, 200);
		app->render->DrawRectangle({ 62 + (315 * 2), 512, (axp2 + xp2) * 2 + 1, 22 }, 50, 50, 50);
		app->render->DrawTexture(rew_icons, 100 + (315 * 3), 450, &rect);
		app->fonts->BlitCombatText(170 + (315 * 3), 470, app->fonts->textFont2, std::to_string(app->frontground->combat_xp3).c_str());
		app->render->DrawRectangle({ 60 + (315 * 3), 510, 200, 26 }, 200, 200, 200);
		app->render->DrawRectangle({ 62 + (315 * 3), 512, (axp3 + xp3) * 2 + 1, 22 }, 50, 50, 50);
		
		rect = { 64, 0, 64, 64 };
		for (size_t i = 0; i < 4; i++)
		{
			app->render->DrawTexture(rew_icons, 100 + (315 * i), 550, &rect);
			app->fonts->BlitCombatText(170 + (315 * i), 570, app->fonts->textFont2, std::to_string(app->frontground->combat_gold).c_str());
		}
	}

	if (lose)
	{
		app->render->DrawTexture(Lose_BackGround, c_x, c_y);
		//app->render->DrawTexture(combat_lose, c_x, c_y);

		lose_buttons[0].rect.x = ((int)win_w / 2) - (lose_buttons[0].rect.w / 2) + c_x-400;
		lose_buttons[0].rect.y = (int)win_h / 2  + c_y;
		lose_buttons[0].rect.w = 200;
		lose_buttons[0].rect.h = 100;

		lose_buttons[1].rect.x = ((int)win_w / 2) - (lose_buttons[1].rect.w / 2)  + c_x+280;
		lose_buttons[1].rect.y = (int)win_h / 2  + c_y + 130;
		lose_buttons[1].rect.w = 200;
		lose_buttons[1].rect.h = 100;

		for (size_t i = 0; i < NUM_LOSE_BUTTONS; i++)
		{
			//Retry button
			if (lose_buttons[0].state == 0)
			{
				//rect = { 0, 0, 500, 70 };
				app->render->DrawTexture(lose_buttons[0].tex, lose_buttons[0].rect.x, lose_buttons[0].rect.y);
			}
			else if (lose_buttons[0].state == 1)
			{
				//rect = { 0, 70, 500, 70 };
				app->render->DrawTexture(lose_buttons[0].alt_tex, lose_buttons[0].rect.x - 20, lose_buttons[0].rect.y - 20);
			}

			//Run button
			if (lose_buttons[1].state == 0)
			{
				//rect = { 0, 0, 500, 70 };
				app->render->DrawTexture(lose_buttons[1].tex, lose_buttons[1].rect.x, lose_buttons[1].rect.y);
			}
			else if (lose_buttons[1].state == 1)
			{
				//rect = { 0, 70, 500, 70 };
				app->render->DrawTexture(lose_buttons[1].alt_tex, lose_buttons[1].rect.x-20, lose_buttons[1].rect.y-20);
			}
			else if (lose_buttons[i].state == 2)
			{
				//rect = { 0, 140, 500, 70 };
				//app->render->DrawTexture(whitemark_500x70, lose_buttons[i].rect.x, lose_buttons[i].rect.y, &rect);
			}
		}

		rect = { 0, 0, 64, 64 };
		app->render->DrawTexture(rew_icons, 550, 300, &rect);
		app->fonts->BlitCombatText(620, 300, app->fonts->textFont2, std::to_string(-5 - (2 * app->frontground->adventure_phase)).c_str());
		
		//app->fonts->BlitText(lose_buttons[0].rect.x, lose_buttons[0].rect.y + 15, app->fonts->textFont1, "restart battle");
		//app->fonts->BlitText(lose_buttons[1].rect.x, lose_buttons[1].rect.y + 15, app->fonts->textFont1, "return to field");
	}

	if (scape)
	{
		app->render->DrawTexture(Scape_BackGround, c_x, c_y);
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
				app->render->DrawTexture(whitemark_500x70, scape_buttons[i].rect.x, scape_buttons[i].rect.y, &rect);
			}
			else if (scape_buttons[i].state == 1)
			{
				rect = { 0, 70, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, scape_buttons[i].rect.x, scape_buttons[i].rect.y, &rect);
			}
			else if (scape_buttons[i].state == 2)
			{
				rect = { 0, 140, 500, 70 };
				app->render->DrawTexture(whitemark_500x70, scape_buttons[i].rect.x, scape_buttons[i].rect.y, &rect);
			}
		}

		app->fonts->BlitText(scape_buttons[0].rect.x, scape_buttons[0].rect.y + 15, app->fonts->textFont1, "sure to leave");
		app->fonts->BlitText(scape_buttons[1].rect.x, scape_buttons[1].rect.y + 15, app->fonts->textFont1, "cancel scape");
	}

	// skills descriptions
	if (!description_disabled && app->combat_menu->Enabled())
	{
		switch (app->combat_menu->description_type)
		{
		case 0: DisplayEntityInfo(app->combat_menu->desc_entity);
			break;
		case 1: DisplaySkillInfo(app->combat_menu->desc_skill);
			break;
		}
	}

	if (unlock_state != 0)
	{
		SDL_Rect or = { 0, 0, 128, 128 };
		unlock_cd--;

		if (app->frontground->fast_combat)
		{
			unlock_cd -= 4;
		}

		if (unlock_cd <= 0)
		{
			unlock_state = 2;
			unlock_cd = 120;

			app->inventory->UnlockObject(app->frontground->reward.c_str());
		}
		if (unlock_state == 1)
		{
			if (unlock_cd % 4 == 0)
			{
				unlock_pos.x += 2;
			}
			else if (unlock_cd % 4 == 1)
			{
				unlock_pos.x -= 2;
			}
			else if (unlock_cd % 4 == 2)
			{
				unlock_pos.y += 2;
			}
			else if (unlock_cd % 4 == 3)
			{
				unlock_pos.y -= 2;
			}

			app->render->DrawTexture(whitemark_128x128, unlock_pos.x + c_x, unlock_pos.y + c_y, &or);
			app->render->DrawTexture(unknow_tex, unlock_pos.x + c_x, unlock_pos.y + c_y);
		}
		else
		{
			app->render->DrawTexture(whitemark_128x128, unlock_pos.x + c_x, unlock_pos.y + c_y, &or );

			if (app->frontground->reward[0] != '4')
			{
				app->render->DrawTexture(gear_tex, unlock_pos.x + c_x, unlock_pos.y + c_y, &GetUnlockRect(app->frontground->reward));
			}
			else if (app->frontground->reward[0] == '4')
			{
				app->render->DrawTexture(items_tex, unlock_pos.x + c_x, unlock_pos.y + c_y, &GetUnlockRect(app->frontground->reward));
			}

			object_buttons[0].rect.x = (640 - (object_buttons[0].rect.w / 2) + c_x);
			object_buttons[0].rect.y = unlock_pos.y + 200 + c_y;
			object_buttons[1].rect.x = (640 - (object_buttons[0].rect.w / 2) + c_x);
			object_buttons[1].rect.y = unlock_pos.y + 300 + c_y;

			for (size_t i = 0; i < NUM_OBJECT_BUTTONS; i++)
			{
				if (object_buttons[i].state == 0)
				{
					or = { 0, 0, 500, 70 };
				}
				else if (object_buttons[i].state == 1)
				{
					or = { 0, 70, 500, 70 };
				}
				else if (object_buttons[i].state == 2)
				{
					or = { 0, 140, 500, 70 };
				}

				if (i == 0 && app->frontground->reward[0] == '4')
				{}
				else
				{
					app->render->DrawTexture(whitemark_500x70, object_buttons[i].rect.x, object_buttons[i].rect.y, &or );
				}
			}

			if (app->frontground->reward[0] != '4')
			{
				app->fonts->BlitText(object_buttons[0].rect.x, object_buttons[0].rect.y + 15, app->fonts->textFont1, "Equip and close");
			}
			
			app->fonts->BlitText(object_buttons[1].rect.x, object_buttons[1].rect.y + 15, app->fonts->textFont1, "Close");
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

void Menu::SetWinLoseScape(int n)
{
	if (n == 0)
	{
		if (!win)
		{
			app->audio->PlayFx(win_sound);
		}
		win = true;
		if (app->frontground->controller)
		{
			win_button.state = 1;
			chosed = -1;
		}
	}
	else if (n == 1)
	{
		if (!lose)
		{
			app->audio->PlayFx(lose_sound);
		}
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
	if (app->logo->Enabled()) { app->logo->Disable(); }
	if (app->intro->Enabled()) { app->intro->Disable(); }
	if (app->final_cut->Enabled()) { app->final_cut->Disable(); }
	if (app->scene->Enabled()) { app->scene->Disable(); }
	if (app->town1->Enabled()) { app->town1->Disable(); }
	if (app->town2->Enabled()) { app->town2->Disable(); }
	if (app->forest->Enabled()) { app->forest->Disable(); }
	if (app->battlefield->Enabled()) { app->battlefield->Disable(); }
	if (app->dungeon->Enabled()) { app->dungeon->Disable(); }
	if (app->outside->Enabled()) { app->outside->Disable(); }
	if (app->inside->Enabled()) { app->inside->Disable(); }
	if (app->combat_scene->Enabled()) { app->combat_scene->Disable(); }
	if (app->end_combat_scene->Enabled()) { app->end_combat_scene->Disable(); }
	if (app->credits->Enabled()) { app->credits->Disable(); }
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
	case 9: a = "Lloyd, the reborn dragon"; break;
	case 10: a = "Theseion"; break;
	case 11: a = "Theseion, the necromancer"; break;
	default: a = " "; break;
	}
	const char* res = a.c_str();
	app->fonts->BlitCombatText(50, 50, app->fonts->textFont2, res);

	// Health
	SDL_Rect rect = { 0, 32, 32, 32 };
	app->render->DrawTexture(desc_icons, 50, 100, &rect);
	std::string b = std::to_string(entity->GetActualHealth());
	std::string c = " / ";
	std::string d = std::to_string(entity->GetMaxHealth());
	std::string r = b + c + d;
	res = r.c_str();
	app->fonts->BlitCombatText(85, 100, app->fonts->textFont2, res);

	// Mana
	rect = { 32, 32, 32, 32 };
	app->render->DrawTexture(desc_icons, 50, 150, &rect);
	b = std::to_string(entity->GetActualMana());
	d = std::to_string(entity->GetMaxMana());
	r = b + c + d;
	res = r.c_str();
	app->fonts->BlitCombatText(85, 150, app->fonts->textFont2, res);

	// Speed
	rect = { 64, 32, 32, 32 };
	app->render->DrawTexture(desc_icons, 700, 100, &rect);
	b = std::to_string(entity->GetSpeed());
	r = b;
	res = r.c_str();
	app->fonts->BlitCombatText(735, 100, app->fonts->textFont2, res);

	// Power
	rect = { 128, 32, 32, 32 };
	app->render->DrawTexture(desc_icons, 700, 150, &rect);
	b = std::to_string(entity->GetPower());
	r = b;
	res = r.c_str();
	app->fonts->BlitCombatText(735, 150, app->fonts->textFont2, res);

	// Shield
	if (entity->GetShield() > 0)
	{
		rect = { 96, 32, 32, 32 };
		app->render->DrawTexture(desc_icons, 50, 200, &rect);
		b = std::to_string(entity->GetShield());
		c = ", ";
		d = std::to_string(entity->GetShieldTurns());
		std::string e = " turns remaining";
		r = b + c + d + e;
		res = r.c_str();
		app->fonts->BlitCombatText(85, 200, app->fonts->textFont2, res);
	}

	// Weakness
	a = "Weakness: ";
	switch (entity->GetWeakness())
	{
	case -1: rect = { 160, 0, 32, 32 }; break;
	case 0: rect = { 128, 0, 32, 32 }; break;
	case 1: rect = { 0, 0, 32, 32 }; break;
	case 2: rect = { 32, 0, 32, 32 }; break;
	case 3: rect = { 64, 0, 32, 32 }; break;
	default: rect = { -32, 0, 32, 32 }; break;
	}
	app->render->DrawTexture(desc_icons, 925, 200, &rect);
	r = a;
	res = r.c_str();
	app->fonts->BlitCombatText(700, 200, app->fonts->textFont2, res);

	// Buffs and Debuffs
	entity->DisplayStatusDescription(50, 275);
}

void Menu::DisplaySkillInfo(Skill skill)
{
	int cx = -app->render->camera.x;
	int cy = -app->render->camera.y;

	app->render->DrawTexture(whitemark_1240x680, 20 + cx, 20 + cy);

	// Name
	std::string a = skill.skill_name;
	const char* res = a.c_str();
	app->fonts->BlitCombatText(50 + cx, 50 + cy, app->fonts->textFont2, res);

	// Element
	a = "Element: ";
	std::string b;
	SDL_Rect rect;
	switch (skill.element)
	{
	case 0: rect = { 128, 0, 32, 32 }; break;
	case 1: rect = { 0, 0, 32, 32 }; break;
	case 2: rect = { 32, 0, 32, 32 }; break;
	case 3: rect = { 64, 0, 32, 32 }; break;
	case 4: rect = { 96, 0, 32, 32 }; break;
	default: rect = { -32, 0, 32, 32 }; break;
	}
	app->render->DrawTexture(desc_icons, 240 + cx, 120 + cy, &rect);
	std::string r = a;
	res = r.c_str();
	app->fonts->BlitCombatText(50 + cx, 120 + cy, app->fonts->textFont2, res);

	// Objective
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
	app->render->DrawTexture(skills_icons, 50 + cx, 170 + cy, &rect);
	a = "Objective: ";
	r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(90 + cx, 175 + cy, app->fonts->textFont2, res);

	// Mana cost
	a = "Mana Cost: ";
	b = std::to_string(skill.mana_cost);
	r = a + b;
	res = r.c_str();
	app->fonts->BlitCombatText(800 + cx, 120 + cy, app->fonts->textFont2, res);

	// Buffs mand Debuffs
	app->combat_menu->DisplaySkillEffects(skill, 50 + cx, 350 + cy);

	// Description
	r = "Description:";
	res = r.c_str();
	app->fonts->BlitCombatText(50 + cx, 550 - 34 + cy, app->fonts->textFont2, res);
	r = skill.skill_description0;
	res = r.c_str();
	app->fonts->BlitCombatText(50 + cx, 550 + cy, app->fonts->textFont2, res);
	r = skill.skill_description1;
	res = r.c_str();
	app->fonts->BlitCombatText(50 + cx, 550 + 34 + cy, app->fonts->textFont2, res);
	r = skill.skill_description2;
	res = r.c_str();
	app->fonts->BlitCombatText(50 + cx, 550 + 68 + cy, app->fonts->textFont2, res);
	r = skill.skill_description3;
	res = r.c_str();
	app->fonts->BlitCombatText(50 + cx, 550 + 102 + cy, app->fonts->textFont2, res);
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
	for (size_t i = 0; i < NUM_OBJECT_BUTTONS; i++)
	{
		if (object_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_ASK_BUTTONS; i++)
	{
		if (ask_buttons[i].state == 1)
		{
			return true;
		}
	}

	return false;
}

SDL_Rect Menu::GetUnlockRect(std::string aei)
{
	SDL_Rect res = { -128, 0, 128, 128 };

	if (aei == "999")
	{
		return res;
	}

	if (aei[0] == '0') // assassin
	{
		if (aei[1] == '0') // helmet
		{
			if (aei[2] == '1')
			{
				res = { 0, 0, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 0, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 0, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 0, 128, 128 };
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			if (aei[2] == '1')
			{
				res = { 0, 128, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 128, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 128, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 128, 128, 128 };
			}
		}
		else if (aei[1] == '2') // boots
		{
			if (aei[2] == '1')
			{
				res = { 0, 256, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 256, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 256, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 256, 128, 128 };
			}
		}
		else if (aei[1] == '3') // weapon
		{
			if (aei[2] == '1')
			{
				res = { 0, 384, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 384, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 384, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 384, 128, 128 };
			}
		}
	}
	else if (aei[0] == '1') // healer
	{
		if (aei[1] == '0') // helmet
		{
			if (aei[2] == '1')
			{
				res = { 0, 512, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 512, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 512, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 512, 128, 128 };
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			if (aei[2] == '1')
			{
				res = { 0, 640, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 640, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 640, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 640, 128, 128 };
			}
		}
		else if (aei[1] == '2') // boots
		{
			if (aei[2] == '1')
			{
				res = { 0, 768, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 768, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 768, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 768, 128, 128 };
			}
		}
		else if (aei[1] == '3') // weapon
		{
			if (aei[2] == '1')
			{
				res = { 0, 896, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 896, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 896, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 896, 128, 128 };
			}
		}
	}
	else if (aei[0] == '2') // tank
	{
		if (aei[1] == '0') // helmet
		{
			if (aei[2] == '1')
			{
				res = { 0, 1024, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1024, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1024, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1024, 128, 128 };
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			if (aei[2] == '1')
			{
				res = { 0, 1152, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1152, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1152, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1152, 128, 128 };
			}
		}
		else if (aei[1] == '2') // boots
		{
			if (aei[2] == '1')
			{
				res = { 0, 1280, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1280, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1280, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1280, 128, 128 };
			}
		}
		else if (aei[1] == '3') // weapon
		{
			if (aei[2] == '1')
			{
				res = { 0, 1408, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1408, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1408, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1408, 128, 128 };
			}
		}
	}
	else if (aei[0] == '3') // wizard
	{
		if (aei[1] == '0') // helmet
		{
			if (aei[2] == '1')
			{
				res = { 0, 1536, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1536, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1536, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1536, 128, 128 };
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			if (aei[2] == '1')
			{
				res = { 0, 1664, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1664, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1664, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1664, 128, 128 };
			}
		}
		else if (aei[1] == '2') // boots
		{
			if (aei[2] == '1')
			{
				res = { 0, 1792, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1792, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1792, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1792, 128, 128 };
			}
		}
		else if (aei[1] == '3') // weapon
		{
			if (aei[2] == '1')
			{
				res = { 0, 1920, 128, 128 };
			}
			else if (aei[2] == '2')
			{
				res = { 128, 1920, 128, 128 };
			}
			else if (aei[2] == '3')
			{
				res = { 256, 1920, 128, 128 };
			}
			else if (aei[2] == '4')
			{
				res = { 384, 1920, 128, 128 };
			}
		}
	}
	else if (aei[0] == '4') // items
	{
		switch (aei[1])
		{
		case '0': res = { 256, 0, 128, 128 }; break;
		case '1': res = { 384, 0, 128, 128 }; break;
		case '2': res = { 512, 0, 128, 128 }; break;
		case '3': res = { 0, 128, 128, 128 }; break;
		case '4': res = { 128, 128, 128, 128 }; break;
		case '5': res = { 256, 128, 128, 128 }; break;
		case '6': res = { 384, 128, 128, 128 }; break;
		case '7': res = { 512, 128, 128, 128 }; break;
		}
	}
	else if (aei[0] == '5') // items
	{
		switch (aei[1])
		{
		case '0': res = { 128, 256, 128, 128 }; break;
		case '1': res = { 256, 256, 128, 128 }; break;
		case '2': res = { 384, 256, 128, 128 }; break;
		case '3': res = { 512, 256, 128, 128 }; break;
		}
	}

	return res;
}