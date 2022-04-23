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
#include "Defs.h"
#include "Log.h"

Inventory::Inventory(bool enabled) : Module(enabled)
{
	name.Create("inventory");

	int px = 1280;
	int py = 720;

	// open
	open.PushBack({ 0 * px, 0 * py, px, py });
	open.PushBack({ 0 * px, 0 * py, px, py });
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			open.PushBack({ j * px, i * py, px, py });
		}
	}
	open.PushBack({ 0 * px, 2 * py, px, py });
	open.PushBack({ 1 * px, 2 * py, px, py });
	open.PushBack({ 2 * px, 2 * py, px, py });
	open.PushBack({ 3 * px, 2 * py, px, py });
	open.speed = 0.3f;
	open.loop = false;

	// page1
	page1.PushBack({ 3 * px, 2 * py, px, py });
	page1.speed = 0.1f;
	page1.loop = false;

	// page2
	page2.PushBack({ 3 * px, 3 * py, px, py });
	page2.speed = 0.1f;
	page2.loop = false;

	// page3
	page3.PushBack({ 3 * px, 4 * py, px, py });
	page3.speed = 0.1f;
	page3.loop = false;

	// page4
	page4.PushBack({ 2 * px, 5 * py, px, py });
	page4.speed = 0.1f;
	page4.loop = false;

	// page5
	page5.PushBack({ 2 * px, 6 * py, px, py });
	page5.speed = 0.1f;
	page5.loop = false;

	// 1 to 2
	for (int i = 4; i < 9; i++)
	{
		pass_page1_2.PushBack({ i * px, 2 * py, px, py });
	}
	for (int i = 0; i < 4; i++)
	{
		pass_page1_2.PushBack({ i * px, 3 * py, px, py });
	}
	pass_page1_2.speed = 0.3f;
	pass_page1_2.loop = false;

	// 2 to 3
	for (int i = 4; i < 9; i++)
	{
		pass_page2_3.PushBack({ i * px, 3 * py, px, py });
	}
	for (int i = 0; i < 4; i++)
	{
		pass_page2_3.PushBack({ i * px, 4 * py, px, py });
	}
	pass_page2_3.speed = 0.3f;
	pass_page2_3.loop = false;

	// 3 to 4
	for (int i = 4; i < 9; i++)
	{
		pass_page3_4.PushBack({ i * px, 4 * py, px, py });
	}
	for (int i = 0; i < 3; i++)
	{
		pass_page3_4.PushBack({ i * px, 5 * py, px, py });
	}
	pass_page3_4.speed = 0.3f;
	pass_page3_4.loop = false;

	// 4 to 5
	for (int i = 3; i < 9; i++)
	{
		pass_page4_5.PushBack({ i * px, 5 * py, px, py });
	}
	for (int i = 0; i < 3; i++)
	{
		pass_page4_5.PushBack({ i * px, 6 * py, px, py });
	}
	pass_page4_5.speed = 0.3f;
	pass_page4_5.loop = false;

	// close
	for (int i = 3; i < 9; i++)
	{
		close.PushBack({ i * px, 6 * py, px, py });
	}
	for (int i = 0; i < 8; i++)
	{
		close.PushBack({ i * px, 7 * py, px, py });
	}
	close.PushBack({ 0 * px, 8 * py, px, py });
	close.PushBack({ 9 * px, 7 * py, px, py });
	close.PushBack({ 9 * px, 7 * py, px, py });
	close.PushBack({ 9 * px, 7 * py, px, py });
	close.speed = 0.3f;
	close.loop = false;

	// 2 to 1
	for (int i = 3; i >= 0; i--)
	{
		pass_page2_1.PushBack({ i * px, 3 * py, px, py });
	}
	for (int i = 9; i >= 4; i--)
	{
		pass_page2_1.PushBack({ i * px, 2 * py, px, py });
	}
	pass_page2_1.speed = 0.3f;
	pass_page2_1.loop = false;

	// 3 to 2
	for (int i = 3; i >= 0; i--)
	{
		pass_page3_2.PushBack({ i * px, 4 * py, px, py });
	}
	for (int i = 9; i >= 4; i--)
	{
		pass_page3_2.PushBack({ i * px, 3 * py, px, py });
	}
	pass_page3_2.speed = 0.3f;
	pass_page3_2.loop = false;

	// 4 to 3
	for (int i = 2; i >= 0; i--)
	{
		pass_page4_3.PushBack({ i * px, 5 * py, px, py });
	}
	for (int i = 9; i >= 4; i--)
	{
		pass_page4_3.PushBack({ i * px, 4 * py, px, py });
	}
	pass_page4_3.speed = 0.3f;
	pass_page4_3.loop = false;

	// 5 to 4
	for (int i = 2; i >= 0; i--)
	{
		pass_page5_4.PushBack({ i * px, 6 * py, px, py });
	}
	for (int i = 9; i >= 3; i--)
	{
		pass_page5_4.PushBack({ i * px, 5 * py, px, py });
	}
	pass_page5_4.speed = 0.3f;
	pass_page5_4.loop = false;
}

// Destructor
Inventory::~Inventory()
{}

// Called before render is available
bool Inventory::Awake()
{

	return true;
}

// Called before the first frame
bool Inventory::Start()
{
	if (this->Enabled() && !this->Disabled())
	{
		hide = true;
		count = true;
		show_info = false;
		page_display = 1;

		submenu = SUB_INV::NOTHING;

		click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
		hover_sound = app->audio->LoadFx("Assets/audio/fx/hover.wav");
		equip_sound = app->audio->LoadFx("Assets/audio/fx/equip.wav");
		unequip_sound = app->audio->LoadFx("Assets/audio/fx/unequip.wav");

		book_tex = app->tex->Load("Assets/textures/book_tex.png");
		whitemark_128x128 = app->tex->Load("Assets/textures/128x128_whitemark.png");
		whitemark_250x70 = app->tex->Load("Assets/textures/250x70_whitemark.png");
		whitemark_800x150 = app->tex->Load("Assets/textures/800x150_whitemark.png");
		hero_tex = app->tex->Load("Assets/textures/heroes_icons.png");
		items_tex = app->tex->Load("Assets/textures/Objects/items.png");
		gear_tex = app->tex->Load("Assets/textures/gear.png");

		skill_button.rect.w = 250;
		skill_button.rect.h = 70;

		for (size_t i = 0; i < NUM_GEAR_BUTTONS; i++)
		{
			gear_buttons[i].rect.w = 128;
			gear_buttons[i].rect.h = 128;
		}

		for (size_t i = 0; i < NUM_GEAR_SELECT_BUTTONS; i++)
		{
			gear_select_buttons[i].rect.w = 128;
			gear_select_buttons[i].rect.h = 128;
			items_buttons[i].rect.w = 128;
			items_buttons[i].rect.h = 128;
		}

		cursor.tex = app->tex->Load("Assets/textures/cursor_default.png");
	}

	return true;
}

// Called each loop iteration
bool Inventory::PreUpdate()
{
	int x, y;
	app->input->GetMousePosition(x, y);

	float cx = -app->render->camera.x;
	float cy = -app->render->camera.y;

	if (!hide)
	{
		if (!InAnyButton())
		{
			hover_playing = false;
		}

		if (submenu == SUB_INV::NOTHING)
		{
			if (book_pos == 0 && open.HasFinished())
			{
				book = &page1;
				book_pos = 1;
				//count = true;
			}
			else if (book_pos == 1 && page1.HasFinished())
			{
				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					book = &pass_page1_2;
					page1.Reset();
					count = true;
					text_cd = 20;
				}
			}
			else if (book_pos == 1 && pass_page1_2.HasFinished())
			{
				book = &page2;
				book_pos = 2;
				pass_page1_2.Reset();
			}
			else if (book_pos == 2 && page2.HasFinished())
			{
				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					book = &pass_page2_3;
					page2.Reset();
					count = true;
					text_cd = 20;
				}
				else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
				{
					book = &pass_page2_1;
					page2.Reset();
					count = true;
					text_cd = 10;
				}
			}
			else if (book_pos == 2 && pass_page2_3.HasFinished())
			{
				book = &page3;
				book_pos = 3;
				pass_page2_3.Reset();
			}
			else if (book_pos == 3 && page3.HasFinished())
			{
				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					book = &pass_page3_4;
					page3.Reset();
					count = true;
					text_cd = 20;
				}
				else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
				{
					book = &pass_page3_2;
					page3.Reset();
					count = true;
					text_cd = 10;
				}
			}
			else if (book_pos == 3 && pass_page3_4.HasFinished())
			{
				book = &page4;
				book_pos = 4;
				pass_page3_4.Reset();
			}
			else if (book_pos == 4 && page4.HasFinished())
			{
				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					book = &pass_page4_5;
					page4.Reset();
					count = true;
					text_cd = 20;
				}
				else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
				{
					book = &pass_page4_3;
					page4.Reset();
					count = true;
					text_cd = 10;
				}
			}
			else if (book_pos == 4 && pass_page4_5.HasFinished())
			{
				book = &page5;
				book_pos = 5;
				pass_page4_5.Reset();
			}
			else if (book_pos == 5 && page5.HasFinished())
			{
				if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
				{
					book = &pass_page5_4;
					page5.Reset();
					count = true;
					text_cd = 10;
				}
			}
			else if (book_pos == 2 && pass_page2_1.HasFinished())
			{
				book = &page1;
				book_pos = 1;
				pass_page2_1.Reset();
			}
			else if (book_pos == 3 && pass_page3_2.HasFinished())
			{
				book = &page2;
				book_pos = 2;
				pass_page3_2.Reset();
			}
			else if (book_pos == 4 && pass_page4_3.HasFinished())
			{
				book = &page3;
				book_pos = 3;
				pass_page4_3.Reset();
			}
			else if (book_pos == 5 && pass_page5_4.HasFinished())
			{
				book = &page4;
				book_pos = 4;
				pass_page5_4.Reset();
			}

			if ((app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
				&& (book_pos == 1 || book_pos == 2 || book_pos == 3 || book_pos == 4 || book_pos == 5))
			{
				book = &close;
				book_pos = 6;
				count = true;
			}
			else if (book_pos == 6 && close.HasFinished())
			{
				hide = true;
			}

			if (show_info && book_pos == 1)
			{
				for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
				{
					SDL_Rect rect = items_buttons[i].rect;
					if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
					{
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
						chosed = i;
						items_buttons[i].state = 1;
					}
					else
					{
						items_buttons[i].state = 0;
					}
				}
			}
			else if (show_info && book_pos != 1)
			{
				SDL_Rect rect = skill_button.rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					if (!hover_playing)
					{
						app->audio->PlayFx(hover_sound);
						hover_playing = true;
					}
					skill_button.state = 1;
				}
				else
				{
					skill_button.state = 0;
				}

				for (size_t i = 0; i < NUM_GEAR_BUTTONS; i++)
				{
					SDL_Rect rect = gear_buttons[i].rect;
					if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
					{
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
						chosed = i;
						gear_buttons[i].state = 1;
					}
					else
					{
						gear_buttons[i].state = 0;
					}
				}
			}
		}
		else if (submenu == SUB_INV::SKILL_TREE)
		{

		}
		else if (submenu == SUB_INV::ITEMS)
		{
			if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			{
				submenu = SUB_INV::NOTHING;
			}

			for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
			{
				items_buttons[i].state = 0;
			}
		}
		else
		{
			if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
			{
				submenu = SUB_INV::NOTHING;
			}

			for (size_t i = 0; i < NUM_GEAR_BUTTONS; i++)
			{
				gear_buttons[i].state = 0;
			}

			for (size_t i = 0; i < NUM_GEAR_SELECT_BUTTONS; i++)
			{
				SDL_Rect rect = gear_select_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					if (!hover_playing)
					{
						app->audio->PlayFx(hover_sound);
						hover_playing = true;
					}
					chosed = i;
					gear_select_buttons[i].state = 1;
				}
				else
				{
					gear_select_buttons[i].state = 0;
				}
			}
		}
	}
	else
	{
		book = &open;
		book_pos = 0;
	}

	return true;
}

// Called each loop iteration
bool Inventory::Update(float dt)
{
	if (!hide)
	{
		if (submenu == SUB_INV::NOTHING)
		{
			if (count)
			{
				text_cd--;
				if (text_cd <= 0)
				{
					show_info = !show_info;
					count = !show_info;
					text_cd = 10;

					if (!show_info)
					{
						if (book == &pass_page2_1)
						{
							page_display = 1;
						}
						else if (book == &pass_page1_2 || book == &pass_page3_2)
						{
							page_display = 2;
						}
						else if (book == &pass_page2_3 || book == &pass_page4_3)
						{
							page_display = 3;
						}
						else if (book == &pass_page3_4 || book == &pass_page5_4)
						{
							page_display = 4;
						}
						else if (book == &pass_page4_5)
						{
							page_display = 5;
						}
						else if (book == &close)
						{
							show_info = false;
							count = false;
						}
					}
				}
			}

			if (show_info && book_pos == 1)
			{
				if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && items_buttons[chosed].state == 1)
				{
					item_submenu = chosed;
					submenu = SUB_INV::ITEMS;

					items_buttons[chosed].state = 2;
				}
			}
			else if (show_info && book_pos != 1)
			{
				if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && skill_button.state == 1)
				{
					app->audio->PlayFx(click_sound);
					// open skill tree
					skill_button.state = 2;
				}
				else if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && gear_buttons[chosed].state == 1)
				{
					app->audio->PlayFx(click_sound);
					switch (chosed)
					{
					case 0:
						submenu = SUB_INV::HELMET;
						break;
					case 1:
						submenu = SUB_INV::CHESTPLATE;
						break;
					case 2:
						submenu = SUB_INV::BOOTS;
						break;
					case 3:
						submenu = SUB_INV::WEAPON;
					}

					gear_buttons[chosed].state = 2;
				}
				else if ((app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_U) == KEY_UP) && gear_buttons[chosed].state == 1)
				{
					app->audio->PlayFx(unequip_sound);
					SaveGearChange(page_display, 0, (SUB_INV)(chosed + 3));

					gear_buttons[chosed].state = 2;
				}
			}
		}
		else if (submenu == SUB_INV::SKILL_TREE)
		{

		}
		else if (submenu == SUB_INV::ITEMS)
		{

		}
		else
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && gear_select_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(equip_sound);
				SaveGearChange(page_display, chosed + 1, submenu);
				submenu = SUB_INV::NOTHING;

				gear_select_buttons[chosed].state = 2;
			}
		}

		book->Update();
	}
	else if (hide)
	{
		open.Reset();
		page1.Reset();
		page2.Reset();
		page3.Reset();
		page4.Reset();
		page5.Reset();
		pass_page1_2.Reset();
		pass_page2_3.Reset();
		pass_page3_4.Reset();
		pass_page4_5.Reset();
		pass_page5_4.Reset();
		pass_page4_3.Reset();
		pass_page3_2.Reset();
		pass_page2_1.Reset();
		close.Reset();
	}

	return true;
}

// Called each loop iteration
bool Inventory::PostUpdate()
{
	if (!hide)
	{
		int cx = -app->render->camera.x;
		int cy = -app->render->camera.y;

		SDL_Rect rect = book->GetCurrentFrame();

		app->render->DrawTexture(book_tex, cx, cy, &rect);

		if (show_info && page_display == 1)
		{
			//items
			SDL_Rect rect;

			for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
			{
				items_buttons[i].rect.x = 280 + cx + (200 * i);
				items_buttons[i].rect.y = 500 + cy;
			}

			for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
			{
				if (items_buttons[i].state == 0)
				{
					rect = { 0, 0, 128, 128 };
				}
				else if (items_buttons[i].state == 1)
				{
					rect = { 0, 128, 128, 128 };
				}
				else if (items_buttons[i].state == 2)
				{
					rect = { 0, 256, 128, 128 };
				}
				app->render->DrawTexture(whitemark_128x128, items_buttons[i].rect.x, items_buttons[i].rect.y, &rect);
			}

			DisplayItems();

			if (submenu == SUB_INV::ITEMS)
			{
				
			}
		}
		else if (show_info && page_display != 1)
		{
			switch (page_display)
			{
			case 2: DisplayHero(0); break;
			case 3: DisplayHero(1); break;
			case 4: DisplayHero(2); break;
			case 5: DisplayHero(3); break;
			default: break;
			}

			SDL_Rect rect;

			skill_button.rect.x = 270 + cx;
			skill_button.rect.y = 520 + cy;

			if (skill_button.state == 0)
			{
				rect = { 0, 0, 250, 70 };
			}
			else if (skill_button.state == 1)
			{
				rect = { 0, 70, 250, 70 };
			}
			else if (skill_button.state == 2)
			{
				rect = { 0, 140, 250, 70 };
			}
			app->render->DrawTexture(whitemark_250x70, skill_button.rect.x, skill_button.rect.y, &rect);
			app->fonts->BlitCombatText(skill_button.rect.x + 7, skill_button.rect.y + 15, app->fonts->textFont2, "Skill Tree");
			
			gear_buttons[0].rect.x = 720 + cx;
			gear_buttons[0].rect.y = 120 + cy;
			gear_buttons[1].rect.x = gear_buttons[0].rect.x + 200;
			gear_buttons[1].rect.y = gear_buttons[0].rect.y;
			gear_buttons[2].rect.x = gear_buttons[0].rect.x;
			gear_buttons[2].rect.y = gear_buttons[0].rect.y + 200;
			gear_buttons[3].rect.x = gear_buttons[0].rect.x + 200;
			gear_buttons[3].rect.y = gear_buttons[0].rect.y + 200;

			for (size_t i = 0; i < NUM_GEAR_BUTTONS; i++)
			{
				if (gear_buttons[i].state == 0)
				{
					rect = { 0, 0, 128, 128 };
				}
				else if (gear_buttons[i].state == 1)
				{
					rect = { 0, 128, 128, 128 };
				}
				else if (gear_buttons[i].state == 2)
				{
					rect = { 0, 256, 128, 128 };
				}
				app->render->DrawTexture(whitemark_128x128, gear_buttons[i].rect.x, gear_buttons[i].rect.y, &rect);
			}

			DisplayGear(page_display);

			for (size_t i = 0; i < NUM_GEAR_SELECT_BUTTONS; i++)
			{
				gear_select_buttons[i].rect.x = 300 + cx + (200 * i);
				gear_select_buttons[i].rect.y = 500 + cy;
			}

			if (submenu == SUB_INV::SKILL_TREE)
			{

			}
			else if (submenu == SUB_INV::HELMET)
			{
				app->render->DrawTexture(whitemark_800x150, gear_select_buttons[0].rect.x - 36, gear_select_buttons[0].rect.y - 11);

				for (int i = 0; i < NUM_GEAR_SELECT_BUTTONS; i++)
				{
					if (gear_select_buttons[i].state == 0)
					{
						rect = { 0, 0, 128, 128 };
					}
					else if (gear_select_buttons[i].state == 1)
					{
						rect = { 0, 128, 128, 128 };
					}
					else if (gear_select_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);

					rect = { i * 128, 0, 128, 128 };
					app->render->DrawTexture(gear_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);
				}
			}
			else if (submenu == SUB_INV::CHESTPLATE)
			{
				app->render->DrawTexture(whitemark_800x150, gear_select_buttons[0].rect.x - 36, gear_select_buttons[0].rect.y - 11);

				for (int i = 0; i < NUM_GEAR_SELECT_BUTTONS; i++)
				{
					if (gear_select_buttons[i].state == 0)
					{
						rect = { 0, 0, 128, 128 };
					}
					else if (gear_select_buttons[i].state == 1)
					{
						rect = { 0, 128, 128, 128 };
					}
					else if (gear_select_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);

					rect = { i * 128, 128, 128, 128 };
					app->render->DrawTexture(gear_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);
				}
			}
			else if (submenu == SUB_INV::BOOTS)
			{
				app->render->DrawTexture(whitemark_800x150, gear_select_buttons[0].rect.x - 36, gear_select_buttons[0].rect.y - 11);

				for (int i = 0; i < NUM_GEAR_SELECT_BUTTONS; i++)
				{
					if (gear_select_buttons[i].state == 0)
					{
						rect = { 0, 0, 128, 128 };
					}
					else if (gear_select_buttons[i].state == 1)
					{
						rect = { 0, 128, 128, 128 };
					}
					else if (gear_select_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);

					rect = { i * 128, 256, 128, 128 };
					app->render->DrawTexture(gear_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);
				}
			}
			else if (submenu == SUB_INV::WEAPON)
			{
				app->render->DrawTexture(whitemark_800x150, gear_select_buttons[0].rect.x - 36, gear_select_buttons[0].rect.y - 11);

				for (int i = 0; i < NUM_GEAR_SELECT_BUTTONS; i++)
				{
					if (gear_select_buttons[i].state == 0)
					{
						rect = { 0, 0, 128, 128 };
					}
					else if (gear_select_buttons[i].state == 1)
					{
						rect = { 0, 128, 128, 128 };
					}
					else if (gear_select_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);

					rect = { i * 128, 384, 128, 128 };
					app->render->DrawTexture(gear_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);
				}
			}
		}

		// draw cursor
		if (!app->frontground->controller)
		{
			app->input->GetMousePosition(cursor.pos.x, cursor.pos.y);
			app->render->DrawTexture(cursor.tex, cursor.pos.x + cx, cursor.pos.y + cy);
		}
	}

	return true;
}

// Called before quitting
bool Inventory::CleanUp()
{
	app->tex->UnLoad(book_tex);
	book_tex = NULL;

	return true;
}

void Inventory::DisplayHero(int n)
{
	int cx = -app->render->camera.x;
	int cy = -app->render->camera.y;

	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node hero;
	SDL_Rect hero_rect;
	const char* name = "";

	switch (n)
	{
	case 0:
		hero = saveGame.child("heroes_stats").child("assassin");
		hero_rect = { 0, 0, 64, 64 };
		name = "Igol";
		break;
	case 1:
		hero = saveGame.child("heroes_stats").child("healer");
		hero_rect = { 64, 0, 64, 64 };
		name = "Gera";
		break;
	case 2:
		hero = saveGame.child("heroes_stats").child("tank");
		hero_rect = { 128, 0, 64, 64 };
		name = "Asteriol";
		break;
	case 3:
		hero = saveGame.child("heroes_stats").child("wizard");
		hero_rect = { 192, 0, 64, 64 };
		name = "Fernan";
		break;
	}

	// no display, only check gear
	page_gear[0] = hero.child("gear").attribute("helmet").as_int();
	page_gear[1] = hero.child("gear").attribute("chest").as_int();
	page_gear[2] = hero.child("gear").attribute("boots").as_int();
	page_gear[3] = hero.child("gear").attribute("weapon").as_int();
	//

	SDL_Rect r = { 0, 0, 128, 128 };
	app->render->DrawTexture(whitemark_128x128, 150 + cx, 100 + cy, &r);
	app->render->DrawTexture(hero_tex, 150 + cx, 100 + cy, &hero_rect);

	app->fonts->BlitCombatText(300 + cx, 100 + cy, app->fonts->textFont2, name);
	app->fonts->BlitCombatText(150 + cx, 250 + cy, app->fonts->textFont2, "Stats");
	std::string s = hero.child("basic_stats").attribute("health").as_string();
	std::string c = "Health: " + s;
	const char* print = c.c_str();
	app->fonts->BlitCombatText(160 + cx, 300 + cy, app->fonts->textFont2, print);
	s = hero.child("basic_stats").attribute("mana").as_string();
	c = "Mana: " + s;
	print = c.c_str();
	app->fonts->BlitCombatText(160 + cx, 350 + cy, app->fonts->textFont2, print);
	s = hero.child("basic_stats").attribute("speed").as_string();
	c = "Speed: " + s;
	print = c.c_str();
	app->fonts->BlitCombatText(160 + cx, 400 + cy, app->fonts->textFont2, print);
	s = hero.child("basic_stats").attribute("power").as_string();
	c = "Power: " + s;
	print = c.c_str();
	app->fonts->BlitCombatText(160 + cx, 450 + cy, app->fonts->textFont2, print);
}

void Inventory::DisplayItems()
{
	SDL_Rect rect;

	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node items = saveGame.child("heroes_stats").child("items_stored").child("equiped");

	// item 0
	switch (items.attribute("item0").as_int())
	{
	case 0: rect = { 0, 0, 128, 128 }; break;
	case 1: rect = { 128, 0, 128, 128 }; break;
	case 2: rect = { 256, 0, 128, 128 }; break;
	case 3: rect = { 384, 0, 128, 128 }; break;
	}
	app->render->DrawTexture(items_tex, items_buttons[0].rect.x, items_buttons[0].rect.y, &rect);
	
	// item 1
	switch (items.attribute("item1").as_int())
	{
	case 0: rect = { 0, 0, 128, 128 }; break;
	case 1: rect = { 128, 0, 128, 128 }; break;
	case 2: rect = { 256, 0, 128, 128 }; break;
	case 3: rect = { 384, 0, 128, 128 }; break;
	}
	app->render->DrawTexture(items_tex, items_buttons[1].rect.x, items_buttons[1].rect.y, &rect);

	// item 2
	switch (items.attribute("item2").as_int())
	{
	case 0: rect = { 0, 0, 128, 128 }; break;
	case 1: rect = { 128, 0, 128, 128 }; break;
	case 2: rect = { 256, 0, 128, 128 }; break;
	case 3: rect = { 384, 0, 128, 128 }; break;
	}
	app->render->DrawTexture(items_tex, items_buttons[2].rect.x, items_buttons[2].rect.y, &rect);

	// item 3
	switch (items.attribute("item3").as_int())
	{
	case 0: rect = { 0, 0, 128, 128 }; break;
	case 1: rect = { 128, 0, 128, 128 }; break;
	case 2: rect = { 256, 0, 128, 128 }; break;
	case 3: rect = { 384, 0, 128, 128 }; break;
	}
	app->render->DrawTexture(items_tex, items_buttons[3].rect.x, items_buttons[3].rect.y, &rect);
}

void Inventory::DisplayGear(int n)
{
	if (n > 1)
	{
		SDL_Rect rect;

		if (n == 2) // assassin
		{
			// helmet
			switch (page_gear[0])
			{
			case 0: rect = { 512, 0, 128, 128 }; break;
			case 1: rect = { 0, 0, 128, 128 }; break;
			case 2: rect = { 128, 0, 128, 128 }; break;
			case 3: rect = { 256, 0, 128, 128 }; break;
			case 4: rect = { 384, 0, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[0].rect.x, gear_buttons[0].rect.y, &rect);

			// chestplate
			switch (page_gear[1])
			{
			case 0: rect = { 512, 128, 128, 128 }; break;
			case 1: rect = { 0, 128, 128, 128 }; break;
			case 2: rect = { 128, 128, 128, 128 }; break;
			case 3: rect = { 256, 128, 128, 128 }; break;
			case 4: rect = { 384, 128, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[1].rect.x, gear_buttons[1].rect.y, &rect);

			// boots
			switch (page_gear[2])
			{
			case 0: rect = { 512, 256, 128, 128 }; break;
			case 1: rect = { 0, 256, 128, 128 }; break;
			case 2: rect = { 128, 256, 128, 128 }; break;
			case 3: rect = { 256, 256, 128, 128 }; break;
			case 4: rect = { 384, 256, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[2].rect.x, gear_buttons[2].rect.y, &rect);

			// helmet
			switch (page_gear[3])
			{
			case 0: rect = { 512, 384, 128, 128 }; break;
			case 1: rect = { 0, 384, 128, 128 }; break;
			case 2: rect = { 128, 384, 128, 128 }; break;
			case 3: rect = { 256, 384, 128, 128 }; break;
			case 4: rect = { 384, 384, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[3].rect.x, gear_buttons[3].rect.y, &rect);
		}
		else if (n == 3) // healer
		{
			// helmet
			switch (page_gear[0])
			{
			case 0: rect = { 512, 0, 128, 128 }; break;
			case 1: rect = { 0, 0, 128, 128 }; break;
			case 2: rect = { 128, 0, 128, 128 }; break;
			case 3: rect = { 256, 0, 128, 128 }; break;
			case 4: rect = { 384, 0, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[0].rect.x, gear_buttons[0].rect.y, &rect);

			// chestplate
			switch (page_gear[1])
			{
			case 0: rect = { 512, 128, 128, 128 }; break;
			case 1: rect = { 0, 128, 128, 128 }; break;
			case 2: rect = { 128, 128, 128, 128 }; break;
			case 3: rect = { 256, 128, 128, 128 }; break;
			case 4: rect = { 384, 128, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[1].rect.x, gear_buttons[1].rect.y, &rect);

			// boots
			switch (page_gear[2])
			{
			case 0: rect = { 512, 256, 128, 128 }; break;
			case 1: rect = { 0, 256, 128, 128 }; break;
			case 2: rect = { 128, 256, 128, 128 }; break;
			case 3: rect = { 256, 256, 128, 128 }; break;
			case 4: rect = { 384, 256, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[2].rect.x, gear_buttons[2].rect.y, &rect);

			// helmet
			switch (page_gear[3])
			{
			case 0: rect = { 512, 384, 128, 128 }; break;
			case 1: rect = { 0, 384, 128, 128 }; break;
			case 2: rect = { 128, 384, 128, 128 }; break;
			case 3: rect = { 256, 384, 128, 128 }; break;
			case 4: rect = { 384, 384, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[3].rect.x, gear_buttons[3].rect.y, &rect);
		}
		else if (n == 4) // tank
		{
			// helmet
			switch (page_gear[0])
			{
			case 0: rect = { 512, 0, 128, 128 }; break;
			case 1: rect = { 0, 0, 128, 128 }; break;
			case 2: rect = { 128, 0, 128, 128 }; break;
			case 3: rect = { 256, 0, 128, 128 }; break;
			case 4: rect = { 384, 0, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[0].rect.x, gear_buttons[0].rect.y, &rect);

			// chestplate
			switch (page_gear[1])
			{
			case 0: rect = { 512, 128, 128, 128 }; break;
			case 1: rect = { 0, 128, 128, 128 }; break;
			case 2: rect = { 128, 128, 128, 128 }; break;
			case 3: rect = { 256, 128, 128, 128 }; break;
			case 4: rect = { 384, 128, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[1].rect.x, gear_buttons[1].rect.y, &rect);

			// boots
			switch (page_gear[2])
			{
			case 0: rect = { 512, 256, 128, 128 }; break;
			case 1: rect = { 0, 256, 128, 128 }; break;
			case 2: rect = { 128, 256, 128, 128 }; break;
			case 3: rect = { 256, 256, 128, 128 }; break;
			case 4: rect = { 384, 256, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[2].rect.x, gear_buttons[2].rect.y, &rect);

			// helmet
			switch (page_gear[3])
			{
			case 0: rect = { 512, 384, 128, 128 }; break;
			case 1: rect = { 0, 384, 128, 128 }; break;
			case 2: rect = { 128, 384, 128, 128 }; break;
			case 3: rect = { 256, 384, 128, 128 }; break;
			case 4: rect = { 384, 384, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[3].rect.x, gear_buttons[3].rect.y, &rect);
		}
		else if (n == 5) // wizard
		{
		// helmet
		switch (page_gear[0])
		{
		case 0: rect = { 512, 0, 128, 128 }; break;
		case 1: rect = { 0, 0, 128, 128 }; break;
		case 2: rect = { 128, 0, 128, 128 }; break;
		case 3: rect = { 256, 0, 128, 128 }; break;
		case 4: rect = { 384, 0, 128, 128 }; break;
		}
		app->render->DrawTexture(gear_tex, gear_buttons[0].rect.x, gear_buttons[0].rect.y, &rect);

		// chestplate
		switch (page_gear[1])
		{
		case 0: rect = { 512, 128, 128, 128 }; break;
		case 1: rect = { 0, 128, 128, 128 }; break;
		case 2: rect = { 128, 128, 128, 128 }; break;
		case 3: rect = { 256, 128, 128, 128 }; break;
		case 4: rect = { 384, 128, 128, 128 }; break;
		}
		app->render->DrawTexture(gear_tex, gear_buttons[1].rect.x, gear_buttons[1].rect.y, &rect);

		// boots
		switch (page_gear[2])
		{
		case 0: rect = { 512, 256, 128, 128 }; break;
		case 1: rect = { 0, 256, 128, 128 }; break;
		case 2: rect = { 128, 256, 128, 128 }; break;
		case 3: rect = { 256, 256, 128, 128 }; break;
		case 4: rect = { 384, 256, 128, 128 }; break;
		}
		app->render->DrawTexture(gear_tex, gear_buttons[2].rect.x, gear_buttons[2].rect.y, &rect);

		// helmet
		switch (page_gear[3])
		{
		case 0: rect = { 512, 384, 128, 128 }; break;
		case 1: rect = { 0, 384, 128, 128 }; break;
		case 2: rect = { 128, 384, 128, 128 }; break;
		case 3: rect = { 256, 384, 128, 128 }; break;
		case 4: rect = { 384, 384, 128, 128 }; break;
		}
		app->render->DrawTexture(gear_tex, gear_buttons[3].rect.x, gear_buttons[3].rect.y, &rect);
		}
	}
}

void Inventory::SaveGearChange(int n, int change, SUB_INV submenu)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node hero;

	switch (n)
	{
	case 2:
		hero = saveGame.child("heroes_stats").child("assassin");
		break;
	case 3:
		hero = saveGame.child("heroes_stats").child("healer");
		break;
	case 4:
		hero = saveGame.child("heroes_stats").child("tank");
		break;
	case 5:
		hero = saveGame.child("heroes_stats").child("wizard");
		break;
	}

	switch (submenu)
	{
	case SUB_INV::HELMET: hero.child("gear").attribute("helmet").set_value(change); break;
	case SUB_INV::CHESTPLATE: hero.child("gear").attribute("chest").set_value(change); break;
	case SUB_INV::BOOTS: hero.child("gear").attribute("boots").set_value(change); break;
	case SUB_INV::WEAPON: hero.child("gear").attribute("weapon").set_value(change); break;
	}

	saveGame.save_file(HEROES_STATS_FILENAME);
}

void Inventory::ResetGear()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node hero;

	for (size_t i = 2; i < 6; i++)
	{
		switch (i)
		{
		case 2:
			hero = saveGame.child("heroes_stats").child("assassin");
			break;
		case 3:
			hero = saveGame.child("heroes_stats").child("healer");
			break;
		case 4:
			hero = saveGame.child("heroes_stats").child("tank");
			break;
		case 5:
			hero = saveGame.child("heroes_stats").child("wizard");
			break;
		}

		hero.child("gear").attribute("helmet").set_value(0); break;
		hero.child("gear").attribute("chest").set_value(0); break;
		hero.child("gear").attribute("boots").set_value(0); break;
		hero.child("gear").attribute("weapon").set_value(0); break;
	}

	saveGame.save_file(HEROES_STATS_FILENAME);
}

bool Inventory::InAnyButton()
{
	for (size_t i = 0; i < NUM_ITEMS_BUTTONS; i++)
	{
		if (items_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_GEAR_BUTTONS; i++)
	{
		if (gear_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_GEAR_SELECT_BUTTONS; i++)
	{
		if (gear_select_buttons[i].state == 1)
		{
			return true;
		}
	}
	if (skill_button.state == 1)
	{
		return true;
	}

	return false;
}