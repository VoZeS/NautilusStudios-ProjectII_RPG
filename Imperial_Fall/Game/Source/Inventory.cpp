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
#include "Combat_Manager.h"
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
	open.PushBack({ 0 * px, 0 * py, px, py });
	open.PushBack({ 1 * px, 0 * py, px, py });
	open.PushBack({ 2 * px, 0 * py, px, py });
	open.PushBack({ 3 * px, 0 * py, px, py });
	open.PushBack({ 4 * px, 0 * py, px, py });
	open.PushBack({ 5 * px, 0 * py, px, py });
	open.PushBack({ 0 * px, 1 * py, px, py });
	open.PushBack({ 1 * px, 1 * py, px, py });
	open.PushBack({ 2 * px, 1 * py, px, py });
	open.speed = 0.3f;
	open.loop = false;

	//page1
	page1.PushBack({ 2 * px, 1 * py, px, py });
	page1.speed = 0.1f;
	page1.loop = false;

	// page2
	page2.PushBack({ 5 * px, 1 * py, px, py });
	page2.speed = 0.1f;
	page2.loop = false;

	// page3
	page3.PushBack({ 2 * px, 2 * py, px, py });
	page3.speed = 0.1f;
	page3.loop = false;

	// page4
	page4.PushBack({ 5 * px, 2 * py, px, py });
	page4.speed = 0.1f;
	page4.loop = false;

	// page5
	page5.PushBack({ 2 * px, 3 * py, px, py });
	page5.speed = 0.1f;
	page5.loop = false;

	// 1 to 2
	pass_page1_2.PushBack({ 2 * px, 1 * py, px, py });
	pass_page1_2.PushBack({ 3 * px, 1 * py, px, py });
	pass_page1_2.PushBack({ 4 * px, 1 * py, px, py });
	pass_page1_2.PushBack({ 5 * px, 1 * py, px, py });
	pass_page1_2.speed = PAGE_SPEED;
	pass_page1_2.loop = false;

	// 2 to 3
	pass_page2_3.PushBack({ 5 * px, 1 * py, px, py });
	pass_page2_3.PushBack({ 0 * px, 2 * py, px, py });
	pass_page2_3.PushBack({ 1 * px, 2 * py, px, py });
	pass_page2_3.PushBack({ 2 * px, 2 * py, px, py });
	pass_page2_3.speed = PAGE_SPEED;
	pass_page2_3.loop = false;

	// 3 to 4
	pass_page3_4.PushBack({ 2 * px, 2 * py, px, py });
	pass_page3_4.PushBack({ 3 * px, 2 * py, px, py });
	pass_page3_4.PushBack({ 4 * px, 2 * py, px, py });
	pass_page3_4.PushBack({ 5 * px, 2 * py, px, py });
	pass_page3_4.speed = PAGE_SPEED;
	pass_page3_4.loop = false;

	// 4 to 5
	pass_page4_5.PushBack({ 5 * px, 2 * py, px, py });
	pass_page4_5.PushBack({ 0 * px, 3 * py, px, py });
	pass_page4_5.PushBack({ 1 * px, 3 * py, px, py });
	pass_page4_5.PushBack({ 2 * px, 3 * py, px, py });
	pass_page4_5.speed = PAGE_SPEED;
	pass_page4_5.loop = false;

	// close
	close.PushBack({ 2 * px, 3 * py, px, py });
	close.PushBack({ 3 * px, 3 * py, px, py });
	close.PushBack({ 4 * px, 3 * py, px, py });
	close.PushBack({ 5 * px, 3 * py, px, py });
	close.PushBack({ 0 * px, 4 * py, px, py });
	close.PushBack({ 1 * px, 4 * py, px, py });
	close.PushBack({ 2 * px, 4 * py, px, py });
	close.PushBack({ 3 * px, 4 * py, px, py });
	close.PushBack({ 3 * px, 4 * py, px, py });
	close.PushBack({ 3 * px, 4 * py, px, py });
	close.speed = 0.3f;
	close.loop = false;

	// 2 to 1
	pass_page2_1.PushBack({ 5 * px, 1 * py, px, py });
	pass_page2_1.PushBack({ 4 * px, 1 * py, px, py });
	pass_page2_1.PushBack({ 3 * px, 1 * py, px, py });
	pass_page2_1.PushBack({ 2 * px, 1 * py, px, py });
	pass_page2_1.speed = PAGE_SPEED;
	pass_page2_1.loop = false;

	// 3 to 2
	pass_page3_2.PushBack({ 2 * px, 2 * py, px, py });
	pass_page3_2.PushBack({ 1 * px, 2 * py, px, py });
	pass_page3_2.PushBack({ 0 * px, 2 * py, px, py });
	pass_page3_2.PushBack({ 5 * px, 1 * py, px, py });
	pass_page3_2.speed = PAGE_SPEED;
	pass_page3_2.loop = false;

	// 4 to 3
	pass_page4_3.PushBack({ 5 * px, 2 * py, px, py });
	pass_page4_3.PushBack({ 4 * px, 2 * py, px, py });
	pass_page4_3.PushBack({ 3 * px, 2 * py, px, py });
	pass_page4_3.PushBack({ 2 * px, 2 * py, px, py });
	pass_page4_3.speed = PAGE_SPEED;
	pass_page4_3.loop = false;

	// 5 to 4
	pass_page5_4.PushBack({ 2 * px, 3 * py, px, py });
	pass_page5_4.PushBack({ 1 * px, 2 * py, px, py });
	pass_page5_4.PushBack({ 0 * px, 2 * py, px, py });
	pass_page5_4.PushBack({ 5 * px, 2 * py, px, py });
	pass_page5_4.speed = PAGE_SPEED;
	pass_page5_4.loop = false;

	// left arrow
	l_arrow.PushBack({ 256, 0, 128, 128 });
	l_arrow.PushBack({ 384, 0, 128, 128 });
	l_arrow.speed = 0.02f;

	// right arrow
	r_arrow.PushBack({ 0, 0, 128, 128 });
	r_arrow.PushBack({ 128, 0, 128, 128 });
	r_arrow.speed = 0.02f;

	// open skill
	open_skill.PushBack({ 0, 0, 1280, 720 });
	open_skill.PushBack({ 1280, 0, 1280, 720 });
	open_skill.PushBack({ 2560, 0, 1280, 720 });
	open_skill.PushBack({ 3840, 0, 1280, 720 });
	open_skill.speed = 0.3f;
	open_skill.loop = false;

	// open skill
	close_skill.PushBack({ 3840, 0, 1280, 720 });
	close_skill.PushBack({ 2560, 0, 1280, 720 });
	close_skill.PushBack({ 1280, 0, 1280, 720 });
	close_skill.PushBack({ 0, 0, 1280, 720 });
	close_skill.speed = 0.3f;
	close_skill.loop = false;
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

		submenu = SUB_INV::NOTHING;

		click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
		hover_sound = app->audio->LoadFx("Assets/audio/fx/hover.wav");
		equip_sound = app->audio->LoadFx("Assets/audio/fx/equip.wav");
		unequip_sound = app->audio->LoadFx("Assets/audio/fx/unequip.wav");
		open_book_sound = app->audio->LoadFx("Assets/audio/fx/open_book.wav");
		pass_page_sound = app->audio->LoadFx("Assets/audio/fx/pass_page.wav");
		earn_coins_sound = app->audio->LoadFx("Assets/audio/fx/earn_coins.wav");
		spend_coins_sound = app->audio->LoadFx("Assets/audio/fx/spend_coins.wav");
		earn_point_sound = app->audio->LoadFx("Assets/audio/fx/skill_point.wav");

		book_tex = app->tex->Load("Assets/textures/book_tex.png");
		arrows_tex = app->tex->Load("Assets/textures/book_arrows.png"); 
		skill_tree_tex = app->tex->Load("Assets/textures/skill_tree_page.png");
		whitemark_128x128 = app->tex->Load("Assets/textures/128x128_whitemark.png");
		whitemark_250x70 = app->tex->Load("Assets/textures/250x70_whitemark.png");
		whitemark_800x150 = app->tex->Load("Assets/textures/800x150_whitemark.png");
		hero_tex = app->tex->Load("Assets/textures/heroes_icons_128x128.png");
		items_tex = app->tex->Load("Assets/textures/Objects/items.png");
		gear_tex = app->tex->Load("Assets/textures/gear.png");
		unknow_tex = app->tex->Load("Assets/textures/unknow.png");
		accept_tex = app->tex->Load("Assets/textures/accept_cancel.png");
		misc = app->tex->Load("Assets/textures/skill_books.png");
		app->combat_manager->status_effects = app->tex->Load("Assets/textures/status_effects.png");

		skill_button.rect.w = 250;
		skill_button.rect.h = 70;

		for (size_t i = 0; i < NUM_ITEMS_SELECT_BUTTONS; i++)
		{
			items_select_buttons[i].rect.w = 128;
			items_select_buttons[i].rect.h = 128;
		}

		for (size_t i = 0; i < NUM_GEAR_BUTTONS; i++)
		{
			gear_buttons[i].rect.w = 128;
			gear_buttons[i].rect.h = 128;
			gear_select_buttons[i].rect.w = 128;
			gear_select_buttons[i].rect.h = 128;
			items_buttons[i].rect.w = 128;
			items_buttons[i].rect.h = 128;
		}

		for (size_t i = 0; i < NUM_SKILL_INTERACT_BUTTONS; i++)
		{
			skill_interact_buttons[i].rect.w = 128;
			skill_interact_buttons[i].rect.h = 128;
		}

		for (size_t i = 0; i < NUM_SKILL_TREE_BUTTONS; i++)
		{
			skill_tree_buttons[i].rect.w = 128;
			skill_tree_buttons[i].rect.h = 128;
		}

		cursor.tex = app->tex->Load("Assets/textures/cursor_default.png");

		left_arrow = &l_arrow;
		right_arrow = &r_arrow;

		in_skill_tree = false;
		skill_win = 0;
		skill_saved = -1;
		skill_image0 = app->tex->Load("Assets/textures/skill_images0.png");
		skill_image1 = app->tex->Load("Assets/textures/skill_images1.png");
		skill_image2 = app->tex->Load("Assets/textures/skill_images2.png");
		skill_image3 = app->tex->Load("Assets/textures/skill_images3.png");

		coin = app->tex->Load("Assets/textures/coin.png");
		coins_obtained = 0;
		coins_cd = 0;

		in_description = false;
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
			}
			else if (book_pos == 1 && page1.HasFinished())
			{
				if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
				{
					book = &pass_page1_2;
					page1.Reset();
					count = true;
					info_cd = 15;
					app->audio->PlayFx(pass_page_sound);
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
					info_cd = 15;
					app->audio->PlayFx(pass_page_sound);
				}
				else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
				{
					book = &pass_page2_1;
					page2.Reset();
					count = true;
					info_cd = 10;
					app->audio->PlayFx(pass_page_sound);
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
					info_cd = 15;
					app->audio->PlayFx(pass_page_sound);
				}
				else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
				{
					book = &pass_page3_2;
					page3.Reset();
					count = true;
					info_cd = 10;
					app->audio->PlayFx(pass_page_sound);
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
					info_cd = 15;
					app->audio->PlayFx(pass_page_sound);
				}
				else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
				{
					book = &pass_page4_3;
					page4.Reset();
					count = true;
					info_cd = 10;
					app->audio->PlayFx(pass_page_sound);
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
					info_cd = 10;
					app->audio->PlayFx(pass_page_sound);
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

			if (in_skill_tree && close_skill.HasFinished())
			{
				in_skill_tree = false;
			}

			if ((app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
				&& (book_pos == 1 || book_pos == 2 || book_pos == 3 || book_pos == 4 || book_pos == 5))
			{
				book = &close;
				book_pos = 6;
				count = true;
				app->audio->PlayFx(open_book_sound);
			}
			else if (book_pos == 6 && close.HasFinished())
			{
				hide = true;
			}

			if (show_info && book_pos == 1 && !in_skill_tree)
			{
				for (size_t i = 0; i < NUM_ITEMS_BUTTONS_INV; i++)
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
			else if (show_info && book_pos != 1 && !in_skill_tree)
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
			if (skill_win == 0)
			{
				if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !in_description)
				{
					skill_page = &close_skill;
					open_skill.Reset();
					submenu = SUB_INV::NOTHING;
				}
				else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && in_description)
				{
					in_description = false;
				}

				for (size_t i = 0; i < NUM_SKILL_TREE_BUTTONS; i++)
				{
					SDL_Rect rect = skill_tree_buttons[i].rect;
					if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
					{
						if (!CheckSkillEquiped(page_display - 2, i))
						{
							if (GetSkillParent(i) == -1 || CheckSkillUnlocked(page_display - 2, GetSkillParent(i)))
							{
								if (!hover_playing)
								{
									app->audio->PlayFx(hover_sound);
									hover_playing = true;
								}
								chosed = i;
								skill_tree_buttons[i].state = 1;
							}
							else
							{
								chosed = i;
								skill_tree_buttons[i].state = -1;
							}
						}
						else
						{
							chosed = i;
							skill_tree_buttons[i].state = -1;
						}
					}
					else
					{
						skill_tree_buttons[i].state = 0;
					}
				}
			}
			else
			{
				if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && skill_win == 1)
				{
					skill_win = 0;
				}

				for (size_t i = 0; i < NUM_SKILL_INTERACT_BUTTONS; i++)
				{
					SDL_Rect rect = skill_interact_buttons[i].rect;
					if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
					{
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
						chosed = i;
						skill_interact_buttons[i].state = 1;
					}
					else
					{
						skill_interact_buttons[i].state = 0;
					}
				}
			}
		}
		else if (submenu == SUB_INV::ITEMS)
		{
			if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && !in_description)
			{
				submenu = SUB_INV::NOTHING;
			}
			else if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && in_description)
			{
				in_description = false;
			}

			for (size_t i = 0; i < NUM_ITEMS_BUTTONS_INV; i++)
			{
				items_buttons[i].state = 0;
			}

			for (size_t i = 0; i < NUM_ITEMS_SELECT_BUTTONS && !in_description; i++)
			{
				SDL_Rect rect = items_select_buttons[i].rect;
				if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
				{
					if (!CheckItemEquiped(i) && CheckItemUnlocked(i))
					{
						if (!hover_playing)
						{
							app->audio->PlayFx(hover_sound);
							hover_playing = true;
						}
						chosed = i;
						items_select_buttons[i].state = 1;
					}
					else
					{
						items_select_buttons[i].state = 0;
					}
				}
				else
				{
					items_select_buttons[i].state = 0;
				}
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
					if (CheckGearUnlocked(page_display - 2, (int)submenu - 3, i + 1))
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
		count = true;
		show_info = false;
		page_display = 1;
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
				info_cd--;
				if (info_cd <= 0)
				{
					show_info = !show_info;
					count = !show_info;
					info_cd = 10;

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
					app->audio->PlayFx(click_sound);
					item_submenu = chosed;
					submenu = SUB_INV::ITEMS;

					items_buttons[chosed].state = 2;
				}
				else if ((app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_U) == KEY_UP) && items_buttons[chosed].state == 1)
				{
					app->audio->PlayFx(unequip_sound);
					SaveItemChange(chosed, -1);

					items_buttons[chosed].state = 2;
				}
			}
			else if (show_info && book_pos != 1)
			{
				if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && skill_button.state == 1)
				{
					app->audio->PlayFx(click_sound);
					skill_page = &open_skill;
					close_skill.Reset();
					in_skill_tree = true;
					skill_button.state = 2;
					submenu = SUB_INV::SKILL_TREE;
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
						break;
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
			if (skill_win == 0)
			{
				if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && skill_tree_buttons[chosed].state == 1)
				{
					app->audio->PlayFx(click_sound);
					if (CheckSkillUnlocked(page_display - 2, chosed))
					{
						skill_win = 1;
						skill_saved = chosed;
					}
					else if (GetSkillParent(chosed) == -1 || CheckSkillUnlocked(page_display - 2, GetSkillParent(chosed)))
					{
						if (CheckSkillPoints(page_display - 2, chosed))
						{
							skill_win = 2;
							skill_saved = chosed;
						}
						else
						{
							skill_win = 3;
							skill_saved = chosed;
						}
					}

					skill_tree_buttons[chosed].state = 2;
				}
				else if ((app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && (skill_tree_buttons[chosed].state == 1 || skill_tree_buttons[chosed].state == -1))
				{
					in_description = true;
					desc_skill = GetSkillForInv(page_display - 2, chosed);

					skill_tree_buttons[chosed].state = 0;
				}
			}
			else
			{
				if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && skill_interact_buttons[chosed].state == 1)
				{
					app->audio->PlayFx(click_sound);

					if (skill_win == 1)
					{
						SaveSkillChange(page_display - 2, chosed, skill_saved);
						skill_win = 0;
						skill_saved = -1;
					}
					else if (skill_win == 2)
					{
						switch (chosed)
						{
						case 0:
							UnlockSkill(page_display - 2, skill_saved);
							skill_win = 1;
							break;
						case 1:
							skill_win = 0;
							break;
						}
					}
					else
					{
						skill_win = 0;
						skill_saved = -1;
					}

					skill_interact_buttons[chosed].state = 2;
				}
			}
		}
		else if (submenu == SUB_INV::ITEMS)
		{
			if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && items_select_buttons[chosed].state == 1)
			{
				app->audio->PlayFx(equip_sound);
				SaveItemChange(item_submenu, chosed);
				submenu = SUB_INV::NOTHING;

				items_select_buttons[chosed].state = 2;
			}
			else if ((app->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_T) == KEY_UP) && items_select_buttons[chosed].state == 1)
			{
				in_description = true;
				desc_skill = GetItemForInv(chosed);

				items_select_buttons[chosed].state = 0;
			}
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
		left_arrow->Update();
		right_arrow->Update();
		if (in_skill_tree)
		{
			skill_page->Update();
		}
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
	int cx = -app->render->camera.x;
	int cy = -app->render->camera.y;

	if (!hide)
	{
		SDL_Rect rect = book->GetCurrentFrame();
		SDL_Rect l_rect = left_arrow->GetCurrentFrame();
		SDL_Rect r_rect = right_arrow->GetCurrentFrame();
		SDL_Rect s_rect = { 0, 0, 0, 0 };
		if (in_skill_tree)
		{
			s_rect = skill_page->GetCurrentFrame();
		}

		app->render->DrawTexture(book_tex, cx, cy, &rect);

		// arrows
		if (submenu == SUB_INV::NOTHING && (book == &page1 || book == &page2 || book == &page3 || book == &page4 || book == &page5) && !in_skill_tree)
		{
			switch (page_display)
			{
			case 1:
				app->render->DrawTexture(arrows_tex, 1102 + cx, 550 + cy, &r_rect);
				break;
			case 2:
				app->render->DrawTexture(arrows_tex, 1102 + cx, 550 + cy, &r_rect);
				app->render->DrawTexture(arrows_tex, 50 + cx, 550 + cy, &l_rect);
				break;
			case 3:
				app->render->DrawTexture(arrows_tex, 1102 + cx, 550 + cy, &r_rect);
				app->render->DrawTexture(arrows_tex, 50 + cx, 550 + cy, &l_rect);
				break;
			case 4:
				app->render->DrawTexture(arrows_tex, 1102 + cx, 550 + cy, &r_rect);
				app->render->DrawTexture(arrows_tex, 50 + cx, 550 + cy, &l_rect);
				break;
			case 5:
				app->render->DrawTexture(arrows_tex, 50 + cx, 550 + cy, &l_rect);
				break;
			}
		}

		if (show_info && page_display == 1)
		{
			//items
			SDL_Rect rect;

			for (size_t i = 0; i < NUM_ITEMS_BUTTONS_INV; i++)
			{
				items_buttons[i].rect.x = 280 + cx + (200 * i);
				items_buttons[i].rect.y = 500 + cy;
			}

			for (size_t i = 0; i < NUM_ITEMS_BUTTONS_INV; i++)
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
				items_select_buttons[0].rect.x = 232 + cx;
				items_select_buttons[0].rect.y = 120 + cy;
				items_select_buttons[1].rect.x = items_select_buttons[0].rect.x + 200;
				items_select_buttons[1].rect.y = items_select_buttons[0].rect.y;
				items_select_buttons[2].rect.x = items_select_buttons[0].rect.x;
				items_select_buttons[2].rect.y = items_select_buttons[0].rect.y + 200;
				items_select_buttons[3].rect.x = items_select_buttons[0].rect.x + 200;
				items_select_buttons[3].rect.y = items_select_buttons[0].rect.y + 200;
				items_select_buttons[4].rect.x = 720 + cx;
				items_select_buttons[4].rect.y = 120 + cy;
				items_select_buttons[5].rect.x = items_select_buttons[4].rect.x + 200;
				items_select_buttons[5].rect.y = items_select_buttons[4].rect.y;
				items_select_buttons[6].rect.x = items_select_buttons[4].rect.x;
				items_select_buttons[6].rect.y = items_select_buttons[4].rect.y + 200;
				items_select_buttons[7].rect.x = items_select_buttons[4].rect.x + 200;
				items_select_buttons[7].rect.y = items_select_buttons[4].rect.y + 200;

				for (size_t i = 0; i < NUM_ITEMS_SELECT_BUTTONS; i++)
				{
					if (items_select_buttons[i].state == 0)
					{
						rect = { 0, 0, 128, 128 };
					}
					else if (items_select_buttons[i].state == 1)
					{
						rect = { 0, 128, 128, 128 };
					}
					else if (items_select_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, items_select_buttons[i].rect.x, items_select_buttons[i].rect.y, &rect);

					switch (i)
					{
					case 0: rect = { 256, 0, 128, 128 }; break;
					case 1: rect = { 384, 0, 128, 128 }; break;
					case 2: rect = { 512, 0, 128, 128 }; break;
					case 3: rect = { 0, 128, 128, 128 }; break;
					case 4: rect = { 128, 128, 128, 128 }; break;
					case 5: rect = { 256, 128, 128, 128 }; break;
					case 6: rect = { 384, 128, 128, 128 }; break;
					case 7: rect = { 512, 128, 128, 128 }; break;
					}

					if (CheckItemUnlocked(i))
					{
						app->render->DrawTexture(items_tex, items_select_buttons[i].rect.x, items_select_buttons[i].rect.y, &rect);
						app->fonts->BlitCombatText(items_select_buttons[i].rect.x + 100, items_select_buttons[i].rect.y + 100, app->fonts->textFont2, std::to_string(GetItemUses(i)).c_str());
					}
					else
					{
						app->render->DrawTexture(unknow_tex, items_select_buttons[i].rect.x, items_select_buttons[i].rect.y);
					}
				}
			}
		}
		else if (show_info && page_display != 1 && (!open_skill.HasFinished() || (skill_page == &close_skill && !close_skill.HasFinished())))
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

			
			if (submenu == SUB_INV::HELMET)
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
						DisplayGearHover(page_display - 2, (int)submenu - 3, i + 1);
					}
					else if (gear_select_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);

					if (CheckGearUnlocked(page_display - 2, (int)submenu - 3, i + 1))
					{
						switch (page_display)
						{
						case 2: rect = { i * 128, 0, 128, 128 }; break;
						case 3: rect = { i * 128, 512, 128, 128 }; break;
						case 4: rect = { i * 128, 1024, 128, 128 }; break;
						case 5: rect = { i * 128, 1536, 128, 128 }; break;
						}
						app->render->DrawTexture(gear_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);
					}
					else
					{
						app->render->DrawTexture(unknow_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y);
					}
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
						DisplayGearHover(page_display - 2, (int)submenu - 3, i + 1);
					}
					else if (gear_select_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);

					if (CheckGearUnlocked(page_display - 2, (int)submenu - 3, i + 1))
					{
						switch (page_display)
						{
						case 2: rect = { i * 128, 128, 128, 128 }; break;
						case 3: rect = { i * 128, 640, 128, 128 }; break;
						case 4: rect = { i * 128, 1152, 128, 128 }; break;
						case 5: rect = { i * 128, 1664, 128, 128 }; break;
						}
						app->render->DrawTexture(gear_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);
					}
					else
					{
						app->render->DrawTexture(unknow_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y);
					}
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
						DisplayGearHover(page_display - 2, (int)submenu - 3, i + 1);
					}
					else if (gear_select_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);

					if (CheckGearUnlocked(page_display - 2, (int)submenu - 3, i + 1))
					{
						switch (page_display)
						{
						case 2: rect = { i * 128, 256, 128, 128 }; break;
						case 3: rect = { i * 128, 768, 128, 128 }; break;
						case 4: rect = { i * 128, 1280, 128, 128 }; break;
						case 5: rect = { i * 128, 1792, 128, 128 }; break;
						}
						app->render->DrawTexture(gear_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);
					}
					else
					{
						app->render->DrawTexture(unknow_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y);
					}
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
						DisplayGearHover(page_display - 2, (int)submenu - 3, i + 1);
					}
					else if (gear_select_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);

					if (CheckGearUnlocked(page_display - 2, (int)submenu - 3, i + 1))
					{
						switch (page_display)
						{
						case 2: rect = { i * 128, 384, 128, 128 }; break;
						case 3: rect = { i * 128, 896, 128, 128 }; break;
						case 4: rect = { i * 128, 1408, 128, 128 }; break;
						case 5: rect = { i * 128, 1920, 128, 128 }; break;
						}
						app->render->DrawTexture(gear_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y, &rect);
					}
					else
					{
						app->render->DrawTexture(unknow_tex, gear_select_buttons[i].rect.x, gear_select_buttons[i].rect.y);
					}
				}
			}
		}

		if (show_info && page_display != 1 && in_skill_tree)
		{
			app->render->DrawTexture(skill_tree_tex, cx, cy, &s_rect);

			if (submenu == SUB_INV::SKILL_TREE)
			{
				DisplaySkillPoints(page_display - 2);

				// row 1
				skill_tree_buttons[0].rect.x = 576 + cx;
				skill_tree_buttons[0].rect.y = 42 + cy;
				// row 2
				skill_tree_buttons[1].rect.x = 154 + cx;
				skill_tree_buttons[1].rect.y = skill_tree_buttons[0].rect.y + 180;
				skill_tree_buttons[2].rect.x = skill_tree_buttons[1].rect.x + 282;
				skill_tree_buttons[2].rect.y = skill_tree_buttons[1].rect.y;
				skill_tree_buttons[3].rect.x = skill_tree_buttons[2].rect.x + 282;
				skill_tree_buttons[3].rect.y = skill_tree_buttons[2].rect.y;
				skill_tree_buttons[4].rect.x = skill_tree_buttons[3].rect.x + 282;
				skill_tree_buttons[4].rect.y = skill_tree_buttons[3].rect.y;
				// row 3
				skill_tree_buttons[5].rect.x = skill_tree_buttons[1].rect.x;
				skill_tree_buttons[5].rect.y = skill_tree_buttons[1].rect.y + 170;
				skill_tree_buttons[6].rect.x = skill_tree_buttons[2].rect.x;
				skill_tree_buttons[6].rect.y = skill_tree_buttons[2].rect.y + 170;
				skill_tree_buttons[7].rect.x = skill_tree_buttons[3].rect.x;
				skill_tree_buttons[7].rect.y = skill_tree_buttons[3].rect.y + 170;
				skill_tree_buttons[8].rect.x = skill_tree_buttons[4].rect.x;
				skill_tree_buttons[8].rect.y = skill_tree_buttons[4].rect.y + 170;
				// row 4
				skill_tree_buttons[9].rect.x = 28 + cx;
				skill_tree_buttons[9].rect.y = skill_tree_buttons[5].rect.y + 170;
				skill_tree_buttons[10].rect.x = skill_tree_buttons[9].rect.x + 156;
				skill_tree_buttons[10].rect.y = skill_tree_buttons[5].rect.y + 170;
				skill_tree_buttons[11].rect.x = skill_tree_buttons[10].rect.x + 156;
				skill_tree_buttons[11].rect.y = skill_tree_buttons[5].rect.y + 170;
				skill_tree_buttons[12].rect.x = skill_tree_buttons[11].rect.x + 156;
				skill_tree_buttons[12].rect.y = skill_tree_buttons[5].rect.y + 170;
				skill_tree_buttons[13].rect.x = skill_tree_buttons[12].rect.x + 156;
				skill_tree_buttons[13].rect.y = skill_tree_buttons[5].rect.y + 170;
				skill_tree_buttons[14].rect.x = skill_tree_buttons[13].rect.x + 156;
				skill_tree_buttons[14].rect.y = skill_tree_buttons[5].rect.y + 170;
				skill_tree_buttons[15].rect.x = skill_tree_buttons[14].rect.x + 156;
				skill_tree_buttons[15].rect.y = skill_tree_buttons[5].rect.y + 170;
				skill_tree_buttons[16].rect.x = skill_tree_buttons[15].rect.x + 156;
				skill_tree_buttons[16].rect.y = skill_tree_buttons[5].rect.y + 170;

				for (size_t i = 0; i < NUM_SKILL_TREE_BUTTONS; i++)
				{
					if (skill_tree_buttons[i].state == -1)
					{
						rect = { 0, 0, 128, 128 };
						app->fonts->BlitCombatText(50 + cx, 100 + cy, app->fonts->textFont3, "Skill Name:");
						app->fonts->BlitCombatText(278 + cx, 100 + cy, app->fonts->textFont3, GetSkillForInv(page_display - 2, i).skill_name);
					}
					else if (skill_tree_buttons[i].state == 0)
					{
						rect = { 0, 0, 128, 128 };
					}
					else if (skill_tree_buttons[i].state == 1)
					{
						rect = { 0, 128, 128, 128 };
						app->fonts->BlitCombatText(50 + cx, 100 + cy, app->fonts->textFont3, "Skill Name:");
						app->fonts->BlitCombatText(278 + cx, 100 + cy, app->fonts->textFont3, GetSkillForInv(page_display - 2, i).skill_name);
					}
					else if (skill_tree_buttons[i].state == 2)
					{
						rect = { 0, 256, 128, 128 };
					}

					if (skill_win != 0)
					{
						rect = { 0, 0, 128, 128 };
					}
					app->render->DrawTexture(whitemark_128x128, skill_tree_buttons[i].rect.x, skill_tree_buttons[i].rect.y, &rect);
					switch (page_display)
					{
					case 2: 
						rect = GetSkillRect(i, CheckSkillUnlocked(0, i));
						app->render->DrawTexture(skill_image0, skill_tree_buttons[i].rect.x, skill_tree_buttons[i].rect.y, &rect);
						break;
					case 3:
						rect = GetSkillRect(i, CheckSkillUnlocked(1, i));
						app->render->DrawTexture(skill_image1, skill_tree_buttons[i].rect.x, skill_tree_buttons[i].rect.y, &rect);
						break;
					case 4:
						rect = GetSkillRect(i, CheckSkillUnlocked(2, i));
						app->render->DrawTexture(skill_image2, skill_tree_buttons[i].rect.x, skill_tree_buttons[i].rect.y, &rect);
						break;
					case 5:
						rect = GetSkillRect(i, CheckSkillUnlocked(3, i));
						app->render->DrawTexture(skill_image3, skill_tree_buttons[i].rect.x, skill_tree_buttons[i].rect.y, &rect);
						break;
					}
				}

				// lines
				for (size_t i = 1; i < 5; i++)
				{
					app->render->DrawLine(skill_tree_buttons[0].rect.x + 64, skill_tree_buttons[0].rect.y + 128, skill_tree_buttons[i].rect.x + 64, skill_tree_buttons[i].rect.y, 0, 0, 0);
				}
				for (size_t i = 1; i < 5; i++)
				{
					app->render->DrawLine(skill_tree_buttons[i].rect.x + 64, skill_tree_buttons[i].rect.y + 128, skill_tree_buttons[i + 4].rect.x + 64, skill_tree_buttons[i + 4].rect.y, 0, 0, 0);
				}
				app->render->DrawLine(skill_tree_buttons[5].rect.x + 64, skill_tree_buttons[5].rect.y + 128, skill_tree_buttons[9].rect.x + 64, skill_tree_buttons[9].rect.y, 0, 0, 0);
				app->render->DrawLine(skill_tree_buttons[5].rect.x + 64, skill_tree_buttons[5].rect.y + 128, skill_tree_buttons[10].rect.x + 64, skill_tree_buttons[10].rect.y, 0, 0, 0);
				app->render->DrawLine(skill_tree_buttons[6].rect.x + 64, skill_tree_buttons[6].rect.y + 128, skill_tree_buttons[11].rect.x + 64, skill_tree_buttons[11].rect.y, 0, 0, 0);
				app->render->DrawLine(skill_tree_buttons[6].rect.x + 64, skill_tree_buttons[6].rect.y + 128, skill_tree_buttons[12].rect.x + 64, skill_tree_buttons[12].rect.y, 0, 0, 0);
				app->render->DrawLine(skill_tree_buttons[7].rect.x + 64, skill_tree_buttons[7].rect.y + 128, skill_tree_buttons[13].rect.x + 64, skill_tree_buttons[13].rect.y, 0, 0, 0);
				app->render->DrawLine(skill_tree_buttons[7].rect.x + 64, skill_tree_buttons[7].rect.y + 128, skill_tree_buttons[14].rect.x + 64, skill_tree_buttons[14].rect.y, 0, 0, 0);
				app->render->DrawLine(skill_tree_buttons[8].rect.x + 64, skill_tree_buttons[8].rect.y + 128, skill_tree_buttons[15].rect.x + 64, skill_tree_buttons[15].rect.y, 0, 0, 0);
				app->render->DrawLine(skill_tree_buttons[8].rect.x + 64, skill_tree_buttons[8].rect.y + 128, skill_tree_buttons[16].rect.x + 64, skill_tree_buttons[16].rect.y, 0, 0, 0);

				// skill win
				if (skill_win != 0)
				{
					app->render->DrawTexture(whitemark_800x150, 240 + cx, 300 + cy);

					SDL_Rect b0;
					if (skill_interact_buttons[0].state == 0)
					{
						b0 = { 0, 0, 128, 128 };
					}
					else if (skill_interact_buttons[0].state == 1)
					{
						b0 = { 0, 128, 128, 128 };
					}
					else if (skill_interact_buttons[0].state == 2)
					{
						b0 = { 0, 256, 128, 128 };
					}

					SDL_Rect b1;
					if (skill_interact_buttons[1].state == 0)
					{
						b1 = { 0, 0, 128, 128 };
					}
					else if (skill_interact_buttons[1].state == 1)
					{
						b1 = { 0, 128, 128, 128 };
					}
					else if (skill_interact_buttons[1].state == 2)
					{
						b1 = { 0, 256, 128, 128 };
					}

					SDL_Rect b2;
					if (skill_interact_buttons[2].state == 0)
					{
						b2 = { 0, 0, 128, 128 };
					}
					else if (skill_interact_buttons[2].state == 1)
					{
						b2 = { 0, 128, 128, 128 };
					}
					else if (skill_interact_buttons[2].state == 2)
					{
						b2 = { 0, 256, 128, 128 };
					}

					SDL_Rect b3;
					if (skill_interact_buttons[3].state == 0)
					{
						b3 = { 0, 0, 128, 128 };
					}
					else if (skill_interact_buttons[3].state == 1)
					{
						b3 = { 0, 128, 128, 128 };
					}
					else if (skill_interact_buttons[3].state == 2)
					{
						b3 = { 0, 256, 128, 128 };
					}

					SDL_Rect a_rect = { 0, 0, 128, 128 };
					std::string p_siting;
					switch (skill_win)
					{
					case 1:
						skill_interact_buttons[0].rect.x = 300 + cx;
						skill_interact_buttons[0].rect.y = 380 + cy;
						skill_interact_buttons[1].rect.x = skill_interact_buttons[0].rect.x + 170;
						skill_interact_buttons[1].rect.y = skill_interact_buttons[0].rect.y;
						skill_interact_buttons[2].rect.x = skill_interact_buttons[1].rect.x + 170;
						skill_interact_buttons[2].rect.y = skill_interact_buttons[0].rect.y;
						skill_interact_buttons[3].rect.x = skill_interact_buttons[2].rect.x + 170;
						skill_interact_buttons[3].rect.y = skill_interact_buttons[0].rect.y;
						app->render->DrawTexture(whitemark_128x128, skill_interact_buttons[0].rect.x, skill_interact_buttons[0].rect.y, &b0);
						app->render->DrawTexture(whitemark_128x128, skill_interact_buttons[1].rect.x, skill_interact_buttons[1].rect.y, &b1);
						app->render->DrawTexture(whitemark_128x128, skill_interact_buttons[2].rect.x, skill_interact_buttons[2].rect.y, &b2);
						app->render->DrawTexture(whitemark_128x128, skill_interact_buttons[3].rect.x, skill_interact_buttons[3].rect.y, &b3);
						app->fonts->BlitCombatText(300 + cx, 310 + cy, app->fonts->textFont2, "Choose slot to equip the skill");

						for (size_t i = 0; i < 4; i++)
						{
							switch (page_display)
							{
							case 2:
								rect = GetSkillRect(GetSkillBySlot(page_display - 2, i + 1), true);
								app->render->DrawTexture(skill_image0, skill_interact_buttons[i].rect.x, skill_interact_buttons[i].rect.y, &rect);
								break;
							case 3:
								rect = GetSkillRect(GetSkillBySlot(page_display - 2, i + 1), true);
								app->render->DrawTexture(skill_image1, skill_interact_buttons[i].rect.x, skill_interact_buttons[i].rect.y, &rect);
								break;
							case 4:
								rect = GetSkillRect(GetSkillBySlot(page_display - 2, i + 1), true);
								app->render->DrawTexture(skill_image2, skill_interact_buttons[i].rect.x, skill_interact_buttons[i].rect.y, &rect);
								break;
							case 5:
								rect = GetSkillRect(GetSkillBySlot(page_display - 2, i + 1), true);
								app->render->DrawTexture(skill_image3, skill_interact_buttons[i].rect.x, skill_interact_buttons[i].rect.y, &rect);
								break;
							}
						}
						break;
					case 2:
						skill_interact_buttons[0].rect.x = 400 + cx;
						skill_interact_buttons[0].rect.y = 380 + cy;
						skill_interact_buttons[1].rect.x = skill_interact_buttons[0].rect.x + 300;
						skill_interact_buttons[1].rect.y = skill_interact_buttons[0].rect.y;
						app->render->DrawTexture(whitemark_128x128, skill_interact_buttons[0].rect.x, skill_interact_buttons[0].rect.y, &b0);
						app->render->DrawTexture(whitemark_128x128, skill_interact_buttons[1].rect.x, skill_interact_buttons[1].rect.y, &b1);
						app->render->DrawTexture(accept_tex, skill_interact_buttons[0].rect.x, skill_interact_buttons[0].rect.y, &a_rect);
						a_rect = { 128, 0, 128, 128 };
						app->render->DrawTexture(accept_tex, skill_interact_buttons[1].rect.x, skill_interact_buttons[1].rect.y, &a_rect);
						p_siting = "Unlock Skill using " + std::to_string(GetSkillPoints(skill_saved)) + " points?";
						app->fonts->BlitCombatText(320 + cx, 310 + cy, app->fonts->textFont2, p_siting.c_str());
						break;
					case 3:
						skill_interact_buttons[0].rect.x = 576 + cx;
						skill_interact_buttons[0].rect.y = 380 + cy;
						app->render->DrawTexture(whitemark_128x128, skill_interact_buttons[0].rect.x, skill_interact_buttons[0].rect.y, &b0);
						app->render->DrawTexture(accept_tex, skill_interact_buttons[0].rect.x, skill_interact_buttons[0].rect.y, &a_rect);
						p_siting = "Imposible, skill cost is " + std::to_string(GetSkillPoints(skill_saved)) + " points";
						app->fonts->BlitCombatText(300 + cx, 310 + cy, app->fonts->textFont2, p_siting.c_str());
						break;
					}
				}
			}
		}

		if (in_description)
		{
			app->menu->DisplaySkillInfo(app->inventory->desc_skill);
		}
	}
	else
	{
		DisplayCoins();
	}

	// draw cursor
	if (!app->frontground->controller)
	{
		app->input->GetMousePosition(cursor.pos.x, cursor.pos.y);
		app->render->DrawTexture(cursor.tex, cursor.pos.x + cx, cursor.pos.y + cy);
	}

	return true;
}

// Called before quitting
bool Inventory::CleanUp()
{
	app->tex->UnLoad(book_tex);
	book_tex = NULL;

	for (size_t i = 0; i < MAX_COINS; i++)
	{
		app->physics->coins_in_floor[i].alive = false;
	}
	for (size_t i = 0; i < MAX_BOOKS; i++)
	{
		app->physics->books_in_floor[i].alive = false;
	}
	app->physics->coin_picked = false;
	app->physics->coins_number = 0;
	app->physics->book_picked = false;
	app->physics->book_number = 0;

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
		hero_rect = { 0, 0, 128, 128 };
		name = "Igol";
		break;
	case 1:
		hero = saveGame.child("heroes_stats").child("healer");
		hero_rect = { 128, 0, 128, 128 };
		name = "Gera";
		break;
	case 2:
		hero = saveGame.child("heroes_stats").child("tank");
		hero_rect = { 256, 0, 128, 128 };
		name = "Asteriol";
		break;
	case 3:
		hero = saveGame.child("heroes_stats").child("wizard");
		hero_rect = { 384, 0, 128, 128 };
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
	// health
	std::string s = hero.child("basic_stats").attribute("health").as_string();
	std::string g = std::to_string(SumGearStats(n, 0));
	std::string c = "Health: " + s;
	const char* print = c.c_str();
	app->fonts->BlitCombatText(160 + cx, 300 + cy, app->fonts->textFont2, print);
	c = "+ " + g;
	print = c.c_str();
	app->fonts->BlitCombatText(402 + cx, 300 + cy, app->fonts->textFont3, print);
	// mana
	s = hero.child("basic_stats").attribute("mana").as_string();
	g = std::to_string(SumGearStats(n, 1));
	c = "Mana: " + s;
	print = c.c_str();
	app->fonts->BlitCombatText(160 + cx, 350 + cy, app->fonts->textFont2, print);
	c = "+ " + g;
	print = c.c_str();
	app->fonts->BlitCombatText(370 + cx, 350 + cy, app->fonts->textFont3, print);
	// speed
	s = hero.child("basic_stats").attribute("speed").as_string();
	g = std::to_string(SumGearStats(n, 2));
	c = "Speed: " + s;
	print = c.c_str();
	app->fonts->BlitCombatText(160 + cx, 400 + cy, app->fonts->textFont2, print);
	c = "+ " + g;
	print = c.c_str();
	app->fonts->BlitCombatText(392 + cx, 400 + cy, app->fonts->textFont3, print);
	// power
	s = hero.child("basic_stats").attribute("power").as_string();
	g = std::to_string(SumGearStats(n, 3));
	c = "Power: " + s;
	print = c.c_str();
	app->fonts->BlitCombatText(160 + cx, 450 + cy, app->fonts->textFont2, print);
	c = "+ " + g;
	print = c.c_str();
	app->fonts->BlitCombatText(388 + cx, 450 + cy, app->fonts->textFont3, print);
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
	case -1: rect = { 0, 256, 128, 128 }; break;
	case 0: rect = { 256, 0, 128, 128 }; break;
	case 1: rect = { 384, 0, 128, 128 }; break;
	case 2: rect = { 512, 0, 128, 128 }; break;
	case 3: rect = { 0, 128, 128, 128 }; break;
	case 4: rect = { 128, 128, 128, 128 }; break;
	case 5: rect = { 256, 128, 128, 128 }; break;
	case 6: rect = { 384, 128, 128, 128 }; break;
	case 7: rect = { 512, 128, 128, 128 }; break;
	}
	app->render->DrawTexture(items_tex, items_buttons[0].rect.x, items_buttons[0].rect.y, &rect);
	if (items.attribute("item0").as_int() > -1)
	{
		app->fonts->BlitCombatText(items_buttons[0].rect.x + 100, items_buttons[0].rect.y + 100, app->fonts->textFont2, std::to_string(GetItemUses(items.attribute("item0").as_int())).c_str());
	}
	
	// item 1
	switch (items.attribute("item1").as_int())
	{
	case -1: rect = { 0, 256, 128, 128 }; break;
	case 0: rect = { 256, 0, 128, 128 }; break;
	case 1: rect = { 384, 0, 128, 128 }; break;
	case 2: rect = { 512, 0, 128, 128 }; break;
	case 3: rect = { 0, 128, 128, 128 }; break;
	case 4: rect = { 128, 128, 128, 128 }; break;
	case 5: rect = { 256, 128, 128, 128 }; break;
	case 6: rect = { 384, 128, 128, 128 }; break;
	case 7: rect = { 512, 128, 128, 128 }; break;
	}
	app->render->DrawTexture(items_tex, items_buttons[1].rect.x, items_buttons[1].rect.y, &rect);
	if (items.attribute("item1").as_int() > -1)
	{
		app->fonts->BlitCombatText(items_buttons[1].rect.x + 100, items_buttons[1].rect.y + 100, app->fonts->textFont2, std::to_string(GetItemUses(items.attribute("item1").as_int())).c_str());
	}

	// item 2
	switch (items.attribute("item2").as_int())
	{
	case -1: rect = { 0, 256, 128, 128 }; break;
	case 0: rect = { 256, 0, 128, 128 }; break;
	case 1: rect = { 384, 0, 128, 128 }; break;
	case 2: rect = { 512, 0, 128, 128 }; break;
	case 3: rect = { 0, 128, 128, 128 }; break;
	case 4: rect = { 128, 128, 128, 128 }; break;
	case 5: rect = { 256, 128, 128, 128 }; break;
	case 6: rect = { 384, 128, 128, 128 }; break;
	case 7: rect = { 512, 128, 128, 128 }; break;
	}
	app->render->DrawTexture(items_tex, items_buttons[2].rect.x, items_buttons[2].rect.y, &rect);
	if (items.attribute("item2").as_int() > -1)
	{
		app->fonts->BlitCombatText(items_buttons[2].rect.x + 100, items_buttons[2].rect.y + 100, app->fonts->textFont2, std::to_string(GetItemUses(items.attribute("item2").as_int())).c_str());
	}

	// item 3
	switch (items.attribute("item3").as_int())
	{
	case -1: rect = { 0, 256, 128, 128 }; break;
	case 0: rect = { 256, 0, 128, 128 }; break;
	case 1: rect = { 384, 0, 128, 128 }; break;
	case 2: rect = { 512, 0, 128, 128 }; break;
	case 3: rect = { 0, 128, 128, 128 }; break;
	case 4: rect = { 128, 128, 128, 128 }; break;
	case 5: rect = { 256, 128, 128, 128 }; break;
	case 6: rect = { 384, 128, 128, 128 }; break;
	case 7: rect = { 512, 128, 128, 128 }; break;
	}
	app->render->DrawTexture(items_tex, items_buttons[3].rect.x, items_buttons[3].rect.y, &rect);
	if (items.attribute("item3").as_int() > -1)
	{
		app->fonts->BlitCombatText(items_buttons[3].rect.x + 100, items_buttons[3].rect.y + 100, app->fonts->textFont2, std::to_string(GetItemUses(items.attribute("item3").as_int())).c_str());
	}
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

			// weapon
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
			case 0: rect = { 512, 512, 128, 128 }; break;
			case 1: rect = { 0, 512, 128, 128 }; break;
			case 2: rect = { 128, 512, 128, 128 }; break;
			case 3: rect = { 256, 512, 128, 128 }; break;
			case 4: rect = { 384, 512, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[0].rect.x, gear_buttons[0].rect.y, &rect);

			// chestplate
			switch (page_gear[1])
			{
			case 0: rect = { 512, 640, 128, 128 }; break;
			case 1: rect = { 0, 640, 128, 128 }; break;
			case 2: rect = { 128, 640, 128, 128 }; break;
			case 3: rect = { 256, 640, 128, 128 }; break;
			case 4: rect = { 384, 640, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[1].rect.x, gear_buttons[1].rect.y, &rect);

			// boots
			switch (page_gear[2])
			{
			case 0: rect = { 512, 768, 128, 128 }; break;
			case 1: rect = { 0, 768, 128, 128 }; break;
			case 2: rect = { 128, 768, 128, 128 }; break;
			case 3: rect = { 256, 768, 128, 128 }; break;
			case 4: rect = { 384, 768, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[2].rect.x, gear_buttons[2].rect.y, &rect);

			// weapon
			switch (page_gear[3])
			{
			case 0: rect = { 512, 896, 128, 128 }; break;
			case 1: rect = { 0, 896, 128, 128 }; break;
			case 2: rect = { 128, 896, 128, 128 }; break;
			case 3: rect = { 256, 896, 128, 128 }; break;
			case 4: rect = { 384, 896, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[3].rect.x, gear_buttons[3].rect.y, &rect);
		}
		else if (n == 4) // tank
		{
			// helmet
			switch (page_gear[0])
			{
			case 0: rect = { 512, 1024, 128, 128 }; break;
			case 1: rect = { 0, 1024, 128, 128 }; break;
			case 2: rect = { 128, 1024, 128, 128 }; break;
			case 3: rect = { 256, 1024, 128, 128 }; break;
			case 4: rect = { 384, 1024, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[0].rect.x, gear_buttons[0].rect.y, &rect);

			// chestplate
			switch (page_gear[1])
			{
			case 0: rect = { 512, 1152, 128, 128 }; break;
			case 1: rect = { 0, 1152, 128, 128 }; break;
			case 2: rect = { 128, 1152, 128, 128 }; break;
			case 3: rect = { 256, 1152, 128, 128 }; break;
			case 4: rect = { 384, 1152, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[1].rect.x, gear_buttons[1].rect.y, &rect);

			// boots
			switch (page_gear[2])
			{
			case 0: rect = { 512, 1280, 128, 128 }; break;
			case 1: rect = { 0, 1280, 128, 128 }; break;
			case 2: rect = { 128, 1280, 128, 128 }; break;
			case 3: rect = { 256, 1280, 128, 128 }; break;
			case 4: rect = { 384, 1280, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[2].rect.x, gear_buttons[2].rect.y, &rect);

			// weapon
			switch (page_gear[3])
			{
			case 0: rect = { 512, 1408, 128, 128 }; break;
			case 1: rect = { 0, 1408, 128, 128 }; break;
			case 2: rect = { 128, 1408, 128, 128 }; break;
			case 3: rect = { 256, 1408, 128, 128 }; break;
			case 4: rect = { 384, 1408, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[3].rect.x, gear_buttons[3].rect.y, &rect);
		}
		else if (n == 5) // wizard
		{
			// helmet
			switch (page_gear[0])
			{
			case 0: rect = { 512, 1536, 128, 128 }; break;
			case 1: rect = { 0, 1536, 128, 128 }; break;
			case 2: rect = { 128, 1536, 128, 128 }; break;
			case 3: rect = { 256, 1536, 128, 128 }; break;
			case 4: rect = { 384, 1536, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[0].rect.x, gear_buttons[0].rect.y, &rect);

			// chestplate
			switch (page_gear[1])
			{
			case 0: rect = { 512, 1664, 128, 128 }; break;
			case 1: rect = { 0, 1664, 128, 128 }; break;
			case 2: rect = { 128, 1664, 128, 128 }; break;
			case 3: rect = { 256, 1664, 128, 128 }; break;
			case 4: rect = { 384, 1664, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[1].rect.x, gear_buttons[1].rect.y, &rect);

			// boots
			switch (page_gear[2])
			{
			case 0: rect = { 512, 1792, 128, 128 }; break;
			case 1: rect = { 0, 1792, 128, 128 }; break;
			case 2: rect = { 128, 1792, 128, 128 }; break;
			case 3: rect = { 256, 1792, 128, 128 }; break;
			case 4: rect = { 384, 1792, 128, 128 }; break;
			}
			app->render->DrawTexture(gear_tex, gear_buttons[2].rect.x, gear_buttons[2].rect.y, &rect);

			// weapon
			switch (page_gear[3])
			{
			case 0: rect = { 512, 1920, 128, 128 }; break;
			case 1: rect = { 0, 1920, 128, 128 }; break;
			case 2: rect = { 128, 1920, 128, 128 }; break;
			case 3: rect = { 256, 1920, 128, 128 }; break;
			case 4: rect = { 384, 1920, 128, 128 }; break;
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
void Inventory::DisplayGearHover(int user, int piece, int level)
{
	int cx = -app->render->camera.x;
	int cy = -app->render->camera.y;

	std::string s = std::to_string(GetGearPiece(user, piece, level).health);
	std::string c = "[" + s + "]";
	app->fonts->BlitCombatText(500 + cx, 300 + cy, app->fonts->textFont4, c.c_str());
	s = std::to_string(GetGearPiece(user, piece, level).mana);
	c = "[" + s + "]";
	app->fonts->BlitCombatText(500 + cx, 350 + cy, app->fonts->textFont4, c.c_str());
	s = std::to_string(GetGearPiece(user, piece, level).speed);
	c = "[" + s + "]";
	app->fonts->BlitCombatText(500 + cx, 400 + cy, app->fonts->textFont4, c.c_str());
	s = std::to_string(GetGearPiece(user, piece, level).power);
	c = "[" + s + "]";
	app->fonts->BlitCombatText(500 + cx, 450 + cy, app->fonts->textFont4, c.c_str());
}


void Inventory::SaveItemChange(int n, int change)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node items_stored = saveGame.child("heroes_stats").child("items_stored").child("equiped");

	switch (n)
	{
	case 0:
		items_stored.attribute("item0").set_value(change);
		break;
	case 1:
		items_stored.attribute("item1").set_value(change);
		break;
	case 2:
		items_stored.attribute("item2").set_value(change);
		break;
	case 3:
		items_stored.attribute("item3").set_value(change);
		break;
	}

	saveGame.save_file(HEROES_STATS_FILENAME);
}

bool Inventory::CheckItemEquiped(int n)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node items_stored = saveGame.child("heroes_stats").child("items_stored").child("equiped");

	if (items_stored.attribute("item0").as_int() == n || items_stored.attribute("item1").as_int() == n ||
		items_stored.attribute("item2").as_int() == n || items_stored.attribute("item3").as_int() == n)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Inventory::BlockAll()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node hero;
	pugi::xml_node set;


	for (size_t i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0: hero = saveGame.child("objects").child("assassin"); break;
		case 1: hero = saveGame.child("objects").child("healer"); break;
		case 2: hero = saveGame.child("objects").child("tank"); break;
		case 3: hero = saveGame.child("objects").child("wizard"); break;
		}

		for (size_t j = 0; j < 4; j++)
		{
			switch (j)
			{
			case 0: set = hero.child("helmet"); break;
			case 1: set = hero.child("chest"); break;
			case 2: set = hero.child("boots"); break;
			case 3: set = hero.child("weapon"); break;
			}

			set.attribute("gear1").set_value(false);
			set.attribute("gear2").set_value(false);
			set.attribute("gear3").set_value(false);
			set.attribute("gear4").set_value(false);
		}

		hero.child("experience").attribute("value").set_value(0);

		set = hero.child("skills");
		for (size_t i = 0; i < NUM_SKILL_TREE_BUTTONS; i++)
		{
			std::string p = "skill";
			std::string s = std::to_string(i);
			std::string t = p + s;
			const char* c = t.c_str();

			set.attribute(c).set_value(false);
		}
	}

	set = saveGame.child("objects").child("items").child("unlocked");
	set.attribute("item0").set_value(false);
	set.attribute("item1").set_value(false);
	set.attribute("item2").set_value(false);
	set.attribute("item3").set_value(false);
	set.attribute("item4").set_value(false);
	set.attribute("item5").set_value(false);
	set.attribute("item6").set_value(false);
	set.attribute("item7").set_value(false);

	set = saveGame.child("objects").child("items").child("uses");
	set.attribute("item0").set_value(0);
	set.attribute("item1").set_value(0);
	set.attribute("item2").set_value(0);
	set.attribute("item3").set_value(0);
	set.attribute("item4").set_value(0);
	set.attribute("item5").set_value(0);
	set.attribute("item6").set_value(0);
	set.attribute("item7").set_value(0);

	set = saveGame.child("objects").child("currency");
	set.attribute("assassin_points").set_value(0);
	set.attribute("healer_points").set_value(0);
	set.attribute("tank_points").set_value(0);
	set.attribute("wizard_points").set_value(0);
	set.attribute("gold").set_value(0);

	saveGame.save_file(UNLOCKABLE_OBJECTS_FILENAME);
}

void Inventory::UnlockAll()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node hero;
	pugi::xml_node set;


	for (size_t i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0: hero = saveGame.child("objects").child("assassin"); break;
		case 1: hero = saveGame.child("objects").child("healer"); break;
		case 2: hero = saveGame.child("objects").child("tank"); break;
		case 3: hero = saveGame.child("objects").child("wizard"); break;
		}

		for (size_t j = 0; j < 4; j++)
		{
			switch (j)
			{
			case 0: set = hero.child("helmet"); break;
			case 1: set = hero.child("chest"); break;
			case 2: set = hero.child("boots"); break;
			case 3: set = hero.child("weapon"); break;
			}

			set.attribute("gear1").set_value(true);
			set.attribute("gear2").set_value(true);
			set.attribute("gear3").set_value(true);
			set.attribute("gear4").set_value(true);
		}

		set = hero.child("skills");
		for (size_t i = 0; i < NUM_SKILL_TREE_BUTTONS; i++)
		{
			std::string p = "skill";
			std::string s = std::to_string(i);
			std::string t = p + s;
			const char* c = t.c_str();

			set.attribute(c).set_value(true);
		}
	}

	set = saveGame.child("objects").child("items").child("unlocked");
	set.attribute("item0").set_value(true);
	set.attribute("item1").set_value(true);
	set.attribute("item2").set_value(true);
	set.attribute("item3").set_value(true);
	set.attribute("item4").set_value(true);
	set.attribute("item5").set_value(true);
	set.attribute("item6").set_value(true);
	set.attribute("item7").set_value(true);

	set = saveGame.child("objects").child("items").child("uses");
	set.attribute("item0").set_value(3);
	set.attribute("item1").set_value(3);
	set.attribute("item2").set_value(3);
	set.attribute("item3").set_value(3);
	set.attribute("item4").set_value(3);
	set.attribute("item5").set_value(3);
	set.attribute("item6").set_value(3);
	set.attribute("item7").set_value(3);

	set = saveGame.child("objects").child("currency");
	set.attribute("assassin_points").set_value(99);
	set.attribute("healer_points").set_value(99);
	set.attribute("tank_points").set_value(99);
	set.attribute("wizard_points").set_value(99);
	set.attribute("gold").set_value(999);

	saveGame.save_file(UNLOCKABLE_OBJECTS_FILENAME);
}

void Inventory::ResetItems()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node items_stored = saveGame.child("heroes_stats").child("items_stored").child("equiped");

	items_stored.attribute("item0").set_value(-1);
	items_stored.attribute("item1").set_value(-1);
	items_stored.attribute("item2").set_value(-1);
	items_stored.attribute("item3").set_value(-1);

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

		hero.child("gear").attribute("helmet").set_value(0);
		hero.child("gear").attribute("chest").set_value(0);
		hero.child("gear").attribute("boots").set_value(0);
		hero.child("gear").attribute("weapon").set_value(0);
	}

	saveGame.save_file(HEROES_STATS_FILENAME);
}

void Inventory::ResetSkills()
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

		hero.child("equiped_skills").attribute("skill1").set_value(-1);
		hero.child("equiped_skills").attribute("skill2").set_value(-1);
		hero.child("equiped_skills").attribute("skill3").set_value(-1);
		hero.child("equiped_skills").attribute("skill4").set_value(-1);
	}

	saveGame.save_file(HEROES_STATS_FILENAME);
}

int Inventory::GetItemUses(int n)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node items_stored = saveGame.child("objects").child("items").child("uses");

	std::string p = "item";
	std::string s = std::to_string(n);
	std::string t = p + s;
	const char* c = t.c_str();

	return items_stored.attribute(c).as_int();
}

Gear Inventory::GetGearPiece(int user, int piece, int level)
{
	Gear new_gear;
	new_gear.health = 0;
	new_gear.mana = 0;
	new_gear.speed = 0;
	new_gear.power = 0;

	if (level == 0)
	{
		return new_gear;
	}

	if (user == 0) // assassin
	{
		if (piece == 0) // helmet
		{
			if (level == 1)
			{
				new_gear.health = 0;
				new_gear.mana = 10;
				new_gear.speed = 2;
				new_gear.power = 0;
			}
			else if (level == 2)
			{
				new_gear.health = 0;
				new_gear.mana = 25;
				new_gear.speed = 5;
				new_gear.power = 0;
			}
			else if (level == 3)
			{
				new_gear.health = 0;
				new_gear.mana = 50;
				new_gear.speed = 10;
				new_gear.power = 0;
			}
			else if (level == 4)
			{
				new_gear.health = 0;
				new_gear.mana = 70;
				new_gear.speed = 18;
				new_gear.power = 0;
			}
		}
		else if (piece == 1) // chestplate
		{
			if (level == 1)
			{
				new_gear.health = 10;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 2;
			}
			else if (level == 2)
			{
				new_gear.health = 25;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 5;
			}
			else if (level == 3)
			{
				new_gear.health = 50;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 10;
			}
			else if (level == 4)
			{
				new_gear.health = 70;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 18;
			}
		}
		else if (piece == 2) // boots
		{
			if (level == 1)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 5;
				new_gear.power = 2;
			}
			else if (level == 2)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 10;
				new_gear.power = 5;
			}
			else if (level == 3)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 18;
				new_gear.power = 10;
			}
			else if (level == 4)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 30;
				new_gear.power = 18;
			}
		}
		else if (piece == 3) // weapon
		{
			if (level == 1)
			{
				new_gear.health = 5;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 5;
			}
			else if (level == 2)
			{
				new_gear.health = 10;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 10;
			}
			else if (level == 3)
			{
				new_gear.health = 18;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 18;
			}
			else if (level == 4)
			{
				new_gear.health = 30;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 30;
			}
		}
	}
	else if (user == 1) // healer
	{
		if (piece == 0) // helmet
		{
			if (level == 1)
			{
				new_gear.health = 0;
				new_gear.mana = 15;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 2)
			{
				new_gear.health = 0;
				new_gear.mana = 35;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 3)
			{
				new_gear.health = 0;
				new_gear.mana = 68;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 4)
			{
				new_gear.health = 0;
				new_gear.mana = 100;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
		}
		else if (piece == 1) // chestplate
		{
			if (level == 1)
			{
				new_gear.health = 10;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 2;
			}
			else if (level == 2)
			{
				new_gear.health = 25;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 5;
			}
			else if (level == 3)
			{
				new_gear.health = 50;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 10;
			}
			else if (level == 4)
			{
				new_gear.health = 70;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 18;
			}
		}
		else if (piece == 2) // boots
		{
			if (level == 1)
			{
				new_gear.health = 0;
				new_gear.mana = 5;
				new_gear.speed = 5;
				new_gear.power = 0;
			}
			else if (level == 2)
			{
				new_gear.health = 0;
				new_gear.mana = 10;
				new_gear.speed = 10;
				new_gear.power = 0;
			}
			else if (level == 3)
			{
				new_gear.health = 0;
				new_gear.mana = 18;
				new_gear.speed = 18;
				new_gear.power = 0;
			}
			else if (level == 4)
			{
				new_gear.health = 0;
				new_gear.mana = 30;
				new_gear.speed = 30;
				new_gear.power = 0;
			}
		}
		else if (piece == 3) // weapon
		{
			if (level == 1)
			{
				new_gear.health = 0;
				new_gear.mana = 5;
				new_gear.speed = 0;
				new_gear.power = 5;
			}
			else if (level == 2)
			{
				new_gear.health = 0;
				new_gear.mana = 10;
				new_gear.speed = 0;
				new_gear.power = 10;
			}
			else if (level == 3)
			{
				new_gear.health = 0;
				new_gear.mana = 18;
				new_gear.speed = 0;
				new_gear.power = 18;
			}
			else if (level == 4)
			{
				new_gear.health = 0;
				new_gear.mana = 30;
				new_gear.speed = 0;
				new_gear.power = 30;
			}
		}
	}
	else if (user == 2) // tank
	{
		if (piece == 0) // helmet
		{
			if (level == 1)
			{
				new_gear.health = 5;
				new_gear.mana = 10;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 2)
			{
				new_gear.health = 10;
				new_gear.mana = 25;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 3)
			{
				new_gear.health = 18;
				new_gear.mana = 30;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 4)
			{
				new_gear.health = 30;
				new_gear.mana = 70;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
		}
		else if (piece == 1) // chestplate
		{
			if (level == 1)
			{
				new_gear.health = 15;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 2)
			{
				new_gear.health = 35;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 3)
			{
				new_gear.health = 68;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 4)
			{
				new_gear.health = 100;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
		}
		else if (piece == 2) // boots
		{
			if (level == 1)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 5;
				new_gear.power = 2;
			}
			else if (level == 2)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 10;
				new_gear.power = 5;
			}
			else if (level == 3)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 18;
				new_gear.power = 10;
			}
			else if (level == 4)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 30;
				new_gear.power = 18;
			}
		}
		else if (piece == 3) // weapon
		{
			if (level == 1)
			{
				new_gear.health = 5;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 5;
			}
			else if (level == 2)
			{
				new_gear.health = 10;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 10;
			}
			else if (level == 3)
			{
				new_gear.health = 18;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 18;
			}
			else if (level == 4)
			{
				new_gear.health = 30;
				new_gear.mana = 0;
				new_gear.speed = 0;
				new_gear.power = 30;
			}
		}
	}

	else if (user == 3) // wizard
	{
		if (piece == 0) // helmet
		{
			if (level == 1)
			{
				new_gear.health = 0;
				new_gear.mana = 10;
				new_gear.speed = 0;
				new_gear.power = 2;
			}
			else if (level == 2)
			{
				new_gear.health = 0;
				new_gear.mana = 25;
				new_gear.speed = 0;
				new_gear.power = 5;
			}
			else if (level == 3)
			{
				new_gear.health = 0;
				new_gear.mana = 50;
				new_gear.speed = 0;
				new_gear.power = 10;
			}
			else if (level == 4)
			{
				new_gear.health = 0;
				new_gear.mana = 70;
				new_gear.speed = 0;
				new_gear.power = 18;
			}
		}
		else if (piece == 1) // chestplate
		{
			if (level == 1)
			{
				new_gear.health = 10;
				new_gear.mana = 5;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 2)
			{
				new_gear.health = 25;
				new_gear.mana = 10;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 3)
			{
				new_gear.health = 50;
				new_gear.mana = 18;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
			else if (level == 4)
			{
				new_gear.health = 70;
				new_gear.mana = 30;
				new_gear.speed = 0;
				new_gear.power = 0;
			}
		}
		else if (piece == 2) // boots
		{
			if (level == 1)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 5;
				new_gear.power = 2;
			}
			else if (level == 2)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 10;
				new_gear.power = 5;
			}
			else if (level == 3)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 18;
				new_gear.power = 10;
			}
			else if (level == 4)
			{
				new_gear.health = 0;
				new_gear.mana = 0;
				new_gear.speed = 30;
				new_gear.power = 18;
			}
		}
		else if (piece == 3) // weapon
		{
			if (level == 1)
			{
				new_gear.health = 0;
				new_gear.mana = 5;
				new_gear.speed = 0;
				new_gear.power = 5;
			}
			else if (level == 2)
			{
				new_gear.health = 0;
				new_gear.mana = 10;
				new_gear.speed = 0;
				new_gear.power = 10;
			}
			else if (level == 3)
			{
				new_gear.health = 0;
				new_gear.mana = 15;
				new_gear.speed = 0;
				new_gear.power = 18;
			}
			else if (level == 4)
			{
				new_gear.health = 0;
				new_gear.mana = 30;
				new_gear.speed = 0;
				new_gear.power = 30;
			}
		}
	}

	return new_gear;
}

int Inventory::SumGearStats(int user, int stat)
{
	int value = 0;
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node hero_gear;

	switch (user)
	{
	case 0:
		hero_gear = saveGame.child("heroes_stats").child("assassin").child("gear");
		break;
	case 1:
		hero_gear = saveGame.child("heroes_stats").child("healer").child("gear");
		break;
	case 2:
		hero_gear = saveGame.child("heroes_stats").child("tank").child("gear");
		break;
	case 3:
		hero_gear = saveGame.child("heroes_stats").child("wizard").child("gear");
		break;
	}

	if (stat == 0) // health
	{
		value += GetGearPiece(user, 0, hero_gear.attribute("helmet").as_int()).health;
		value += GetGearPiece(user, 1, hero_gear.attribute("chest").as_int()).health;
		value += GetGearPiece(user, 2, hero_gear.attribute("boots").as_int()).health;
		value += GetGearPiece(user, 3, hero_gear.attribute("weapon").as_int()).health;
	}
	else if (stat == 1) // mana
	{
		value += GetGearPiece(user, 0, hero_gear.attribute("helmet").as_int()).mana;
		value += GetGearPiece(user, 1, hero_gear.attribute("chest").as_int()).mana;
		value += GetGearPiece(user, 2, hero_gear.attribute("boots").as_int()).mana;
		value += GetGearPiece(user, 3, hero_gear.attribute("weapon").as_int()).mana;
	}
	else if (stat == 2) // speed
	{
		value += GetGearPiece(user, 0, hero_gear.attribute("helmet").as_int()).speed;
		value += GetGearPiece(user, 1, hero_gear.attribute("chest").as_int()).speed;
		value += GetGearPiece(user, 2, hero_gear.attribute("boots").as_int()).speed;
		value += GetGearPiece(user, 3, hero_gear.attribute("weapon").as_int()).speed;
	}
	else if (stat == 3) // power
	{
		value += GetGearPiece(user, 0, hero_gear.attribute("helmet").as_int()).power;
		value += GetGearPiece(user, 1, hero_gear.attribute("chest").as_int()).power;
		value += GetGearPiece(user, 2, hero_gear.attribute("boots").as_int()).power;
		value += GetGearPiece(user, 3, hero_gear.attribute("weapon").as_int()).power;
	}

	return value;
}

void Inventory::UnlockObject(const char* aei)
{
	if (aei == "999")
	{
		return;
	}

	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node hero;
	pugi::xml_node set;

	if (aei[0] == '0') // assassin
	{
		hero = saveGame.child("objects").child("assassin");
		if (aei[1] == '0') // helmet
		{
			set = hero.child("helmet");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			set = hero.child("chest");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '2') // boots
		{
			set = hero.child("boots");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '3') // weapon
		{
			set = hero.child("weapon");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
	}
	else if (aei[0] == '1') // healer
	{
		hero = saveGame.child("objects").child("healer");
		if (aei[1] == '0') // helmet
		{
			set = hero.child("helmet");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			set = hero.child("chest");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '2') // boots
		{
			set = hero.child("boots");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '3') // weapon
		{
			set = hero.child("weapon");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
	}
	else if (aei[0] == '2') // tank
	{
		hero = saveGame.child("objects").child("tank");
		if (aei[1] == '0') // helmet
		{
			set = hero.child("helmet");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			set = hero.child("chest");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '2') // boots
		{
			set = hero.child("boots");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '3') // weapon
		{
			set = hero.child("weapon");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
	}
	else if (aei[0] == '3') // wizard
	{
		hero = saveGame.child("objects").child("wizard");
		if (aei[1] == '0') // helmet
		{
			set = hero.child("helmet");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '1') // chestplate
		{
			set = hero.child("chest");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '2') // boots
		{
			set = hero.child("boots");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
		else if (aei[1] == '3') // weapon
		{
			set = hero.child("weapon");
			if (aei[2] == '1')
			{
				set.attribute("gear1").set_value(true);
			}
			else if (aei[2] == '2')
			{
				set.attribute("gear2").set_value(true);
			}
			else if (aei[2] == '3')
			{
				set.attribute("gear3").set_value(true);
			}
			else if (aei[2] == '4')
			{
				set.attribute("gear4").set_value(true);
			}
		}
	}
	else if (aei[0] == '4') // items
	{
		hero = saveGame.child("objects").child("items");

		switch (aei[1])
		{
		case '0': 
			hero.child("unlocked").attribute("item0").set_value(true);
			hero.child("uses").attribute("item0").set_value(hero.child("uses").attribute("item0").as_int() + (aei[2] - '0'));
			break;
		case '1': 
			hero.child("unlocked").attribute("item1").set_value(true);
			hero.child("uses").attribute("item1").set_value(hero.child("uses").attribute("item1").as_int() + (aei[2] - '0'));
			break;
		case '2': 
			hero.child("unlocked").attribute("item2").set_value(true);
			hero.child("uses").attribute("item2").set_value(hero.child("uses").attribute("item2").as_int() + (aei[2] - '0'));
			break;
		case '3': 
			hero.child("unlocked").attribute("item3").set_value(true);
			hero.child("uses").attribute("item3").set_value(hero.child("uses").attribute("item3").as_int() + (aei[2] - '0'));
			break;
		case '4': 
			hero.child("unlocked").attribute("item4").set_value(true);
			hero.child("uses").attribute("item4").set_value(hero.child("uses").attribute("item4").as_int() + (aei[2] - '0'));
			break;
		case '5': 
			hero.child("unlocked").attribute("item5").set_value(true);
			hero.child("uses").attribute("item5").set_value(hero.child("uses").attribute("item5").as_int() + (aei[2] - '0'));
			break;
		case '6': 
			hero.child("unlocked").attribute("item6").set_value(true);
			hero.child("uses").attribute("item6").set_value(hero.child("uses").attribute("item6").as_int() + (aei[2] - '0'));
			break;
		case '7': 
			hero.child("unlocked").attribute("item7").set_value(true);
			hero.child("uses").attribute("item7").set_value(hero.child("uses").attribute("item7").as_int() + (aei[2] - '0'));
			break;
		}
	}

	saveGame.save_file(UNLOCKABLE_OBJECTS_FILENAME);
}

void Inventory::EquipGear(const char* aei)
{
	if (aei == "999")
	{
		return;
	}

	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node hero;

	if (aei[0] == '0') // assassin
	{
		hero = saveGame.child("heroes_stats").child("assassin").child("gear");
		if (aei[1] == '0') // helmet
		{
			hero.attribute("helmet").set_value(aei[2] - '0');
		}
		else if (aei[1] == '1') // chestplate
		{
			hero.attribute("chest").set_value(aei[2] - '0');
		}
		else if (aei[1] == '2') // boots
		{
			hero.attribute("boots").set_value(aei[2] - '0');
		}
		else if (aei[1] == '3') // weapon
		{
			hero.attribute("weapon").set_value(aei[2] - '0');
		}
	}
	else if (aei[0] == '1') // healer
	{
		hero = saveGame.child("heroes_stats").child("healer").child("gear");
		if (aei[1] == '0') // helmet
		{
			hero.attribute("helmet").set_value(aei[2] - '0');
		}
		else if (aei[1] == '1') // chestplate
		{
			hero.attribute("chest").set_value(aei[2] - '0');
		}
		else if (aei[1] == '2') // boots
		{
			hero.attribute("boots").set_value(aei[2] - '0');
		}
		else if (aei[1] == '3') // weapon
		{
			hero.attribute("weapon").set_value(aei[2] - '0');
		}
	}
	else if (aei[0] == '2') // tank
	{
		hero = saveGame.child("heroes_stats").child("tank").child("gear");
		if (aei[1] == '0') // helmet
		{
			hero.attribute("helmet").set_value(aei[2] - '0');
		}
		else if (aei[1] == '1') // chestplate
		{
			hero.attribute("chest").set_value(aei[2] - '0');
		}
		else if (aei[1] == '2') // boots
		{
			hero.attribute("boots").set_value(aei[2] - '0');
		}
		else if (aei[1] == '3') // weapon
		{
			hero.attribute("weapon").set_value(aei[2] - '0');
		}
	}
	else if (aei[0] == '3') // wizard
	{
		hero = saveGame.child("heroes_stats").child("wizard").child("gear");
		if (aei[1] == '0') // helmet
		{
			hero.attribute("helmet").set_value(aei[2] - '0');
		}
		else if (aei[1] == '1') // chestplate
		{
			hero.attribute("chest").set_value(aei[2] - '0');
		}
		else if (aei[1] == '2') // boots
		{
			hero.attribute("boots").set_value(aei[2] - '0');
		}
		else if (aei[1] == '3') // weapon
		{
			hero.attribute("weapon").set_value(aei[2] - '0');
		}
	}

	saveGame.save_file(HEROES_STATS_FILENAME);
}

void Inventory::EquipAllMaxGear()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node hero;

	hero = saveGame.child("heroes_stats").child("assassin").child("gear");
	hero.attribute("helmet").set_value(4);
	hero.attribute("chest").set_value(4);
	hero.attribute("boots").set_value(4);
	hero.attribute("weapon").set_value(4);
	hero = saveGame.child("heroes_stats").child("assassin").child("equiped_skills");
	hero.attribute("skill1").set_value(1);
	hero.attribute("skill2").set_value(10);
	hero.attribute("skill3").set_value(11);
	hero.attribute("skill4").set_value(15);
	hero = saveGame.child("heroes_stats").child("healer").child("gear");
	hero.attribute("helmet").set_value(4);
	hero.attribute("chest").set_value(4);
	hero.attribute("boots").set_value(4);
	hero.attribute("weapon").set_value(4);
	hero = saveGame.child("heroes_stats").child("healer").child("equiped_skills");
	hero.attribute("skill1").set_value(10);
	hero.attribute("skill2").set_value(12);
	hero.attribute("skill3").set_value(13);
	hero.attribute("skill4").set_value(14);
	hero = saveGame.child("heroes_stats").child("tank").child("gear");
	hero.attribute("helmet").set_value(4);
	hero.attribute("chest").set_value(4);
	hero.attribute("boots").set_value(4);
	hero.attribute("weapon").set_value(4);
	hero = saveGame.child("heroes_stats").child("tank").child("equiped_skills");
	hero.attribute("skill1").set_value(7);
	hero.attribute("skill2").set_value(9);
	hero.attribute("skill3").set_value(12);
	hero.attribute("skill4").set_value(16);
	hero = saveGame.child("heroes_stats").child("wizard").child("gear");
	hero.attribute("helmet").set_value(4);
	hero.attribute("chest").set_value(4);
	hero.attribute("boots").set_value(4);
	hero.attribute("weapon").set_value(4);
	hero = saveGame.child("heroes_stats").child("wizard").child("equiped_skills");
	hero.attribute("skill1").set_value(5);
	hero.attribute("skill2").set_value(9);
	hero.attribute("skill3").set_value(12);
	hero.attribute("skill4").set_value(14);
	

	saveGame.save_file(HEROES_STATS_FILENAME);
}

void Inventory::UnlockSkill(int owner, int skill)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node skills;
	pugi::xml_attribute points;

	switch (owner)
	{
	case 0: skills = saveGame.child("objects").child("assassin").child("skills");
		points = saveGame.child("objects").child("currency").attribute("assassin_points");  break;
	case 1: skills = saveGame.child("objects").child("healer").child("skills");
		points = saveGame.child("objects").child("currency").attribute("healer_points");  break;
	case 2: skills = saveGame.child("objects").child("tank").child("skills");
		points = saveGame.child("objects").child("currency").attribute("tank_points");  break;
	case 3: skills = saveGame.child("objects").child("wizard").child("skills");
		points = saveGame.child("objects").child("currency").attribute("wizard_points");  break;
	}

	std::string p = "skill";
	std::string s = std::to_string(skill);
	std::string t = p + s;
	const char* c = t.c_str();

	skills.attribute(c).set_value(true);

	points.set_value(points.as_int() - GetSkillPoints(skill));

	saveGame.save_file(UNLOCKABLE_OBJECTS_FILENAME);
}

void Inventory::AddSkillPoint(int owner, int amount)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_attribute points;

	switch (owner)
	{
	case 0: points = saveGame.child("objects").child("currency").attribute("assassin_points"); break;
	case 1: points = saveGame.child("objects").child("currency").attribute("healer_points"); break;
	case 2: points = saveGame.child("objects").child("currency").attribute("tank_points"); break;
	case 3: points = saveGame.child("objects").child("currency").attribute("wizard_points"); break;
	}

	points.set_value(points.as_int() + amount);

	app->audio->PlayFx(earn_point_sound);

	saveGame.save_file(UNLOCKABLE_OBJECTS_FILENAME);
}

bool Inventory::CheckGearUnlocked(int user, int piece, int level)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node hero;
	pugi::xml_node set;
	bool res = false;

	if (user == 0) // assassin
	{
		hero = saveGame.child("objects").child("assassin");
		if (piece == 0) // helmet
		{
			set = hero.child("helmet");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 1) // chestplate
		{
			set = hero.child("chest");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 2) // boots
		{
			set = hero.child("boots");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 3) // weapon
		{
			set = hero.child("weapon");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
	}
	else if (user == 1) // healer
	{
		hero = saveGame.child("objects").child("healer");
		if (piece == 0) // helmet
		{
			set = hero.child("helmet");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 1) // chestplate
		{
			set = hero.child("chest");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 2) // boots
		{
			set = hero.child("boots");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 3) // weapon
		{
			set = hero.child("weapon");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
	}
	else if (user == 1) // healer
	{
		hero = saveGame.child("objects").child("healer");
		if (piece == 0) // helmet
		{
			set = hero.child("helmet");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 1) // chestplate
		{
			set = hero.child("chest");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 2) // boots
		{
			set = hero.child("boots");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 3) // weapon
		{
			set = hero.child("weapon");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
	}
	else if (user == 2) // tank
	{
		hero = saveGame.child("objects").child("tank");
		if (piece == 0) // helmet
		{
			set = hero.child("helmet");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 1) // chestplate
		{
			set = hero.child("chest");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 2) // boots
		{
			set = hero.child("boots");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 3) // weapon
		{
			set = hero.child("weapon");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
	}
	else if (user == 3) // wizard
	{
		hero = saveGame.child("objects").child("tank");
		if (piece == 0) // helmet
		{
			set = hero.child("helmet");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 1) // chestplate
		{
			set = hero.child("chest");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 2) // boots
		{
			set = hero.child("boots");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
		else if (piece == 3) // weapon
		{
			set = hero.child("weapon");
			if (level == 1)
			{
				res = set.attribute("gear1").as_bool();
			}
			else if (level == 2)
			{
				res = set.attribute("gear2").as_bool();
			}
			else if (level == 3)
			{
				res = set.attribute("gear3").as_bool();
			}
			else if (level == 4)
			{
				res = set.attribute("gear4").as_bool();
			}
		}
	}

	return res;
}

bool Inventory::CheckSkillUnlocked(int owner, int skill)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node skills;

	switch (owner)
	{
	case 0: skills = saveGame.child("objects").child("assassin").child("skills"); break;
	case 1: skills = saveGame.child("objects").child("healer").child("skills"); break;
	case 2: skills = saveGame.child("objects").child("tank").child("skills"); break;
	case 3: skills = saveGame.child("objects").child("wizard").child("skills"); break;
	}

	std::string p = "skill";
	std::string s = std::to_string(skill);
	std::string t = p + s;
	const char* c = t.c_str();

	bool ret = skills.attribute(c).as_bool();
	return skills.attribute(c).as_bool();
}

bool Inventory::CheckSkillPoints(int owner, int skill)
{
	bool res = false;
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	int points = 0;

	switch (owner)
	{
	case 0: points = saveGame.child("objects").child("currency").attribute("assassin_points").as_int(); break;
	case 1: points = saveGame.child("objects").child("currency").attribute("healer_points").as_int(); break;
	case 2: points = saveGame.child("objects").child("currency").attribute("tank_points").as_int(); break;
	case 3: points = saveGame.child("objects").child("currency").attribute("wizard_points").as_int(); break;
	}

	if (points >= GetSkillPoints(skill))
	{
		res = true;
	}

	return res;
}

void Inventory::DisplaySkillPoints(int owner)
{
	float cx = -app->render->camera.x;
	float cy = -app->render->camera.y;

	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	int points = 0;

	switch (owner)
	{
	case 0: points = saveGame.child("objects").child("currency").attribute("assassin_points").as_int(); break;
	case 1: points = saveGame.child("objects").child("currency").attribute("healer_points").as_int(); break;
	case 2: points = saveGame.child("objects").child("currency").attribute("tank_points").as_int(); break;
	case 3: points = saveGame.child("objects").child("currency").attribute("wizard_points").as_int(); break;
	}

	std::string s = "Skill Points: " + std::to_string(points);

	app->fonts->BlitCombatText(50 + cx, 50 + cy, app->fonts->textFont3, s.c_str());
}

bool Inventory::CheckSkillEquiped(int owner, int skill)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node equiped_skill;

	switch (owner)
	{
	case 0: equiped_skill = saveGame.child("heroes_stats").child("assassin").child("equiped_skills"); break;
	case 1: equiped_skill = saveGame.child("heroes_stats").child("healer").child("equiped_skills"); break;
	case 2: equiped_skill = saveGame.child("heroes_stats").child("tank").child("equiped_skills"); break;
	case 3: equiped_skill = saveGame.child("heroes_stats").child("wizard").child("equiped_skills"); break;
	}

	if (equiped_skill.attribute("skill1").as_int() == skill || equiped_skill.attribute("skill2").as_int() == skill ||
		equiped_skill.attribute("skill3").as_int() == skill || equiped_skill.attribute("skill4").as_int() == skill)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Inventory::SaveSkillChange(int owner, int skill_slot, int skill_to_insert)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node hero;
	pugi::xml_attribute slot;

	switch (owner)
	{
	case 0: hero = saveGame.child("heroes_stats").child("assassin"); break;
	case 1: hero = saveGame.child("heroes_stats").child("healer"); break;
	case 2: hero = saveGame.child("heroes_stats").child("tank"); break;
	case 3: hero = saveGame.child("heroes_stats").child("wizard"); break;
	}

	switch (skill_slot)
	{
	case 0: slot = hero.child("equiped_skills").attribute("skill1"); break;
	case 1: slot = hero.child("equiped_skills").attribute("skill2"); break;
	case 2: slot = hero.child("equiped_skills").attribute("skill3"); break;
	case 3: slot = hero.child("equiped_skills").attribute("skill4"); break;
	}

	slot.set_value(skill_to_insert);

	saveGame.save_file(HEROES_STATS_FILENAME);
}

bool Inventory::CheckItemUnlocked(int n)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_node items_stored = saveGame.child("objects").child("items").child("unlocked");

	std::string p = "item";
	std::string s = std::to_string(n);
	std::string t = p + s;
	const char* c = t.c_str();

	return items_stored.attribute(c).as_bool();
}

bool Inventory::InAnyButton()
{
	for (size_t i = 0; i < NUM_ITEMS_BUTTONS_INV; i++)
	{
		if (items_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_ITEMS_SELECT_BUTTONS; i++)
	{
		if (items_select_buttons[i].state == 1)
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
	for (size_t i = 0; i < NUM_SKILL_TREE_BUTTONS; i++)
	{
		if (skill_tree_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_SKILL_INTERACT_BUTTONS; i++)
	{
		if (skill_interact_buttons[i].state == 1)
		{
			return true;
		}
	}

	return false;
}

Skill Inventory::GetSkillForInv(int owner, int skill)
{
	Combat_Entities comb = Combat_Entities(owner, skill / 4);

	int ns = skill;

	while (ns >= 4)
	{
		ns -= 4;
	}

	return comb.GetSkill(ns);
}

Skill Inventory::GetItemForInv(int skill)
{
	Combat_Entities comb = Combat_Entities(-1, skill / 4);

	int ns = skill;

	while (ns >= 4)
	{
		ns -= 4;
	}

	return comb.GetSkill(ns);
}

int Inventory::GetSkillParent(int skill)
{
	int res = -1;

	if (skill == 1 || skill == 2 || skill == 3 || skill == 4)
	{
		res = 0;
	}
	else if (skill == 5 || skill == 6 || skill == 7 || skill == 8)
	{
		res = skill - 4;
	}
	else if (skill == 9 || skill == 10)
	{
		res = 5;
	}
	else if (skill == 11 || skill == 12)
	{
		res = 6;
	}
	else if (skill == 13 || skill == 14)
	{
		res = 7;
	}
	else if (skill == 15 || skill == 16)
	{
		res = 8;
	}

	return res;
}

int Inventory::GetSkillPoints(int skill)
{
	int res = 0;

	if (skill == 0 || skill == 1 || skill == 2 || skill == 3 || skill == 4)
	{
		res = 1;
	}
	else if (skill == 5 || skill == 6 || skill == 7 || skill == 8)
	{
		res = 2;
	}
	else if (skill == 9 || skill == 10 || skill == 11 || skill == 12 || skill == 13 || skill == 14 || skill == 15 || skill == 16)
	{
		res = 3;
	}

	return res;
}

SDL_Rect Inventory::GetSkillRect(int skill, bool unlocked)
{
	SDL_Rect rect;

	if (unlocked)
	{
		rect = { skill * 128, 128, 128, 128 };
	}
	else
	{
		rect = { skill * 128, 0, 128, 128 };
	}
	
	return rect;
}

int Inventory::GetSkillBySlot(int owner, int slot)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(HEROES_STATS_FILENAME);
	pugi::xml_node hero;

	std::string p = "skill";
	std::string s = std::to_string(slot);
	std::string t = p + s;
	const char* c = t.c_str();

	switch (owner)
	{
	case 0: hero = saveGame.child("heroes_stats").child("assassin"); break;
	case 1: hero = saveGame.child("heroes_stats").child("healer"); break;
	case 2: hero = saveGame.child("heroes_stats").child("tank"); break;
	case 3: hero = saveGame.child("heroes_stats").child("wizard"); break;
	}

	return hero.child("equiped_skills").attribute(c).as_int();
}

void Inventory::DisplayCoins()
{
	float cx = -app->render->camera.x;
	float cy = -app->render->camera.y;

	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	int coins = saveGame.child("objects").child("currency").attribute("gold").as_int();

	std::string s;
	if (coins < 100)
	{
		if (coins < 10)
		{
			s = "00" + std::to_string(coins);
		}
		else
		{
			s = "0" + std::to_string(coins);
		}
	}
	else
	{
		s = std::to_string(coins);
	}
	
	app->fonts->BlitCombatText(1120 + cx, 50 + cy, app->fonts->textFont2, s.c_str());
	app->render->DrawTexture(coin, 1182 + cx, 34 + cy);

	if (coins_obtained != 0)
	{
		if (coins_obtained > 0)
		{
			if (coins_obtained < 100)
			{
				if (coins_obtained < 10)
				{
					s = "+00" + std::to_string(coins_obtained);
				}
				else
				{
					s = "+0" + std::to_string(coins_obtained);
				}
			}
			else
			{
				s = "+" + std::to_string(coins_obtained);
			}
			
			app->fonts->BlitCombatText(1094 + cx, 85 + cy, app->fonts->textFont4, s.c_str());
		}
		else
		{
			if (coins_obtained > -100)
			{
				if (coins_obtained > -10)
				{
					s = "-00" + std::to_string(abs(coins_obtained));
				}
				else
				{
					s = "-0" + std::to_string(abs(coins_obtained));
				}
			}
			else
			{
				s = "-" + std::to_string(abs(coins_obtained));
			}
			app->fonts->BlitCombatText(1100 + cx, 85 + cy, app->fonts->textFont3, s.c_str());
		}

		coins_cd++;
		if (coins_cd > 60)
		{
			coins_obtained = 0;
			coins_cd = 0;
		}
	}
}

int Inventory::GetCoins()
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	int coins = saveGame.child("objects").child("currency").attribute("gold").as_int();

	return coins;
}

void Inventory::AddCoins(int amount)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_attribute coins = saveGame.child("objects").child("currency").attribute("gold");
	int real_amount;

	if (coins.as_int() + amount > 999)
	{
		real_amount = 999;
	}
	else if (coins.as_int() + amount < 0)
	{
		real_amount = 0;
	}
	else
	{
		real_amount = coins.as_int() + amount;
	}

	coins.set_value(real_amount);
	coins_obtained = amount;

	if (amount > 0)
	{
		app->audio->PlayFx(earn_coins_sound);
	}
	else if (amount < 0)
	{
		app->audio->PlayFx(spend_coins_sound);
	}

	saveGame.save_file(UNLOCKABLE_OBJECTS_FILENAME);
}

void Inventory::AddXP(int amount)
{
	pugi::xml_document saveGame;
	pugi::xml_parse_result result = saveGame.load_file(UNLOCKABLE_OBJECTS_FILENAME);
	pugi::xml_attribute xp;
	int exp_stored;
	int skill_point = 0;

	if (amount > 0)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				xp = saveGame.child("objects").child("assassin").child("experience").attribute("value");

				if (xp.as_int() + amount < 100)
				{
					xp.set_value(xp.as_int() + amount);
				}
				else
				{
					exp_stored = xp.as_int() + amount;
					do
					{
						exp_stored -= 100;
						skill_point++;
					} while (exp_stored >= 100);
					xp.set_value(exp_stored);
					AddSkillPoint(0, skill_point);
				}
			}
			else if (i == 1)
			{
				xp = saveGame.child("objects").child("healer").child("experience").attribute("value");

				if (xp.as_int() + amount < 100)
				{
					xp.set_value(xp.as_int() + amount);
				}
				else
				{
					exp_stored = xp.as_int() + amount;
					do
					{
						exp_stored -= 100;
						skill_point++;
					} while (exp_stored >= 100);
					xp.set_value(exp_stored);
					AddSkillPoint(0, skill_point);
				}
			}
			else if (i == 2)
			{
				xp = saveGame.child("objects").child("tank").child("experience").attribute("value");

				if (xp.as_int() + amount < 100)
				{
					xp.set_value(xp.as_int() + amount);
				}
				else
				{
					exp_stored = xp.as_int() + amount;
					do
					{
						exp_stored -= 100;
						skill_point++;
					} while (exp_stored >= 100);
					xp.set_value(exp_stored);
					AddSkillPoint(0, skill_point);
				}
			}
			else if (i == 3)
			{
				xp = saveGame.child("objects").child("wizard").child("experience").attribute("value");

				if (xp.as_int() + amount < 100)
				{
					xp.set_value(xp.as_int() + amount);
				}
				else
				{
					exp_stored = xp.as_int() + amount;
					do
					{
						exp_stored -= 100;
						skill_point++;
					} while (exp_stored >= 100);
					xp.set_value(exp_stored);
					AddSkillPoint(0, skill_point);
				}
			}
		}
	}
	else if (amount < 0)
	{
		for (size_t i = 0; i < 4; i++)
		{
			if (i == 0)
			{
				xp = saveGame.child("objects").child("assassin").child("experience").attribute("value");
				if (xp.as_int() + amount < 0)
				{
					xp.set_value(0);
				}
				else
				{
					xp.set_value(xp.as_int() + amount);
				}
			}
			else if (i == 1)
			{
				xp = saveGame.child("objects").child("healer").child("experience").attribute("value");
				if (xp.as_int() + amount < 0)
				{
					xp.set_value(0);
				}
				else
				{
					xp.set_value(xp.as_int() + amount);
				}
			}
			else if (i == 2)
			{
				xp = saveGame.child("objects").child("tank").child("experience").attribute("value");
				if (xp.as_int() + amount < 0)
				{
					xp.set_value(0);
				}
				else
				{
					xp.set_value(xp.as_int() + amount);
				}
			}
			else if (i == 3)
			{
				xp = saveGame.child("objects").child("wizard").child("experience").attribute("value");
				if (xp.as_int() + amount < 0)
				{
					xp.set_value(0);
				}
				else
				{
					xp.set_value(xp.as_int() + amount);
				}
			}
		}
	}

	saveGame.save_file(UNLOCKABLE_OBJECTS_FILENAME);
}