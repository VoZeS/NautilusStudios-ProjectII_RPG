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

		book_tex = app->tex->Load("Assets/textures/book_tex.png");
		whitemark128x128 = app->tex->Load("Assets/textures/128x128_whitemark.png");
		hero_tex = app->tex->Load("Assets/textures/heroes_icons.png");
	}

	return true;
}

// Called each loop iteration
bool Inventory::PreUpdate()
{
	if (!hide)
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
			}
			else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{
				book = &pass_page2_1;
				page2.Reset();
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
			}
			else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{
				book = &pass_page3_2;
				page3.Reset();
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
			}
			else if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{
				book = &pass_page4_3;
				page4.Reset();
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

		if (app->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN && (book_pos == 1 || book_pos == 2 || book_pos == 3 || book_pos == 4 || book_pos == 5))
		{
			book = &close;
			book_pos = 6;
		}
		else if (book_pos == 6 && close.HasFinished())
		{
			hide = true;
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
		book->Update();
	}
	else
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

		switch (book_pos)
		{
		case 1: DisplayHero(0); break;
		case 2: DisplayHero(1); break;
		case 3: DisplayHero(2); break;
		case 4: DisplayHero(3); break;
		default: break;
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

	SDL_Rect r = { 0, 0, 128, 128 };
	app->render->DrawTexture(whitemark128x128, 150 + cx, 100 + cy, &r);
	app->render->DrawTexture(hero_tex, 150 + cx, 100 + cy, &hero_rect);

	app->fonts->BlitCombatText(150 + cx, 250 + cy, app->fonts->textFont2, name);
}