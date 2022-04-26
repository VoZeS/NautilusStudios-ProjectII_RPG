#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Menu.h"
#include "Inventory.h"
#include "Fonts.h"
#include "Physics.h"
#include "Frontground.h"
#include "Dialog.h"

#include "Defs.h"
#include "Log.h"

#include <stdlib.h>
#include <time.h>

Dialog::Dialog(bool enabled) : Module(enabled)
{
	name.Create("dialog");

	idle_e.PushBack({ 0, 0, 128, 136 });
	idle_e.PushBack({ 128, 0, 128, 136 });
	idle_e.speed = 0.05f;
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

	press_e = app->tex->Load("Assets/textures/Boton_E.png");
	anim = &idle_e;

	LoadDialog();
	letter_fx = app->audio->LoadFx("Assets/audio/fx/letter.wav");
	letterA_fx = app->audio->LoadFx("Assets/audio/fx/letter_a.wav");
	letterG_fx = app->audio->LoadFx("Assets/audio/fx/letter_g.wav");

	//Text 1
	linea1String_Renato[0] = dialog.child("renato").child("text1").attribute("linea1").as_string();
	linea2String_Renato[0] = dialog.child("renato").child("text1").attribute("linea2").as_string();

	linea1String_Renato[1] = dialog.child("renato").child("text2").attribute("linea1").as_string();
	linea2String_Renato[1] = dialog.child("renato").child("text2").attribute("linea2").as_string();

	linea1String_Renato[2] = dialog.child("renato").child("text3").attribute("linea1").as_string();
	linea2String_Renato[2] = dialog.child("renato").child("text3").attribute("linea2").as_string();

	linea1String_Renato[3] = dialog.child("renato").child("text4").attribute("linea1").as_string();
	linea2String_Renato[3] = dialog.child("renato").child("text4").attribute("linea2").as_string();

	linea1String_Renato[4] = dialog.child("renato").child("text5").attribute("linea1").as_string();
	linea2String_Renato[4] = dialog.child("renato").child("text5").attribute("linea2").as_string();

	for (int i = 0; i < 5; i++)
	{
		linea1Char_Renato[i] = linea1String_Renato[i].c_str();
		linea2Char_Renato[i] = linea2String_Renato[i].c_str();
	}

	linea1String_Herrero = dialog.child("herrero").child("text1").attribute("linea1").as_string();
	linea2String_Herrero = dialog.child("herrero").child("text1").attribute("linea2").as_string();

	linea1Char_Herrero = linea1String_Herrero.c_str();
	linea2Char_Herrero = linea2String_Herrero.c_str();



	linea1String_Granjero = dialog.child("granjero").child("text1").attribute("linea1").as_string();
	linea2String_Granjero = dialog.child("granjero").child("text1").attribute("linea2").as_string();

	linea1Char_Granjero = linea1String_Granjero.c_str();
	linea2Char_Granjero = linea2String_Granjero.c_str();



	linea1String_Medico = dialog.child("granjero").child("text1").attribute("linea1").as_string();
	linea2String_Medico = dialog.child("granjero").child("text1").attribute("linea2").as_string();

	linea1Char_Medico = linea1String_Medico.c_str();
	linea2Char_Medico = linea2String_Medico.c_str();

	linea1String_Aldeano = dialog.child("aldeano").child("text1").attribute("linea1").as_string();

	linea1Char_Aldeano = linea1String_Aldeano.c_str();


	/*
	linea1String_Templario = dialog.child("templario").child("text1").attribute("linea1").as_string();
	linea2String_Templario = dialog.child("templario").child("text1").attribute("linea2").as_string();
	
	linea1Char_Templario = linea1String_Templario.c_str();
	linea2Char_Templario = linea2String_Templario.c_str();


	
	linea1String_Seta = dialog.child("seta").child("text1").attribute("linea1").as_string();
	linea2String_Seta = dialog.child("seta").child("text1").attribute("linea2").as_string();

	linea1Char_Seta = linea1String_Seta.c_str();
	linea2Char_Seta = linea2String_Seta.c_str();
	*/

	in_shop = 0;
	item_saved = NULL;

	for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
	{
		shop_buttons[i].rect.w = 128;
		shop_buttons[i].rect.h = 128;
	}

	for (size_t i = 0; i < NUM_SHOP_INTERACT_BUTTONS; i++)
	{
		shop_interact_buttons[i].rect.w = 128;
		shop_interact_buttons[i].rect.h = 128;
	}

	if (app->frontground->adventure_phase == 0)
	{
		// herrero
		shop1[0].item = "031";
		shop1[0].cost = 15;
		shop1[1].item = "131";
		shop1[1].cost = 15;
		shop1[2].item = "231";
		shop1[2].cost = 15;
		shop1[3].item = "331";
		shop1[3].cost = 15;

		// medico
		shop2[0].item = "40";
		shop2[0].cost = 5;
		shop2[1].item = "41";
		shop2[1].cost = 8;
		shop2[2].item = "44";
		shop2[2].cost = 5;
		shop2[3].item = "45";
		shop2[3].cost = 8;

		// granjero
		shop3[0].item = "40";
		shop3[0].cost = 5;
		shop3[1].item = "40";
		shop3[1].cost = 5;
		shop3[2].item = "40";
		shop3[2].cost = 5;
		shop3[3].item = "40";
		shop3[3].cost = 5;
	}
	else if (app->frontground->adventure_phase == 1)
	{
		// herrero
		shop1[0].item = "032";
		shop1[0].cost = 15;
		shop1[1].item = "132";
		shop1[1].cost = 15;
		shop1[2].item = "232";
		shop1[2].cost = 15;
		shop1[3].item = "332";
		shop1[3].cost = 15;

		// medico
		shop2[0].item = "40";
		shop2[0].cost = 5;
		shop2[1].item = "41";
		shop2[1].cost = 8;
		shop2[2].item = "44";
		shop2[2].cost = 5;
		shop2[3].item = "45";
		shop2[3].cost = 8;

		// granjero
		shop2[0].item = "40";
		shop2[0].cost = 5;
		shop2[1].item = "40";
		shop2[1].cost = 5;
		shop2[2].item = "40";
		shop2[2].cost = 5;
		shop2[3].item = "40";
		shop2[3].cost = 5;
	}
	
	whitemark_128x128 = app->tex->Load("Assets/textures/128x128_whitemark.png");
	whitemark_800x150 = app->tex->Load("Assets/textures/800x150_whitemark.png");
	whitemark_1240x680 = app->tex->Load("Assets/textures/1240x680_whitemark.png");

	click_sound = app->audio->LoadFx("Assets/audio/fx/pop.wav");
	hover_sound = app->audio->LoadFx("Assets/audio/fx/hover.wav");
	hover_playing = false;

	return true;
}

// Called each loop iteration
bool Dialog::PreUpdate()
{
	srand(time(NULL));

	int x, y;
	app->input->GetMousePosition(x, y);

	float cx = -app->render->camera.x;
	float cy = -app->render->camera.y;

	if (in_shop != 0 && item_saved == NULL)
	{
		for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
		{
			bool selled = false;
			SDL_Rect rect = shop_buttons[i].rect;
			if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
			{
				switch (in_shop)
				{
				case 1: selled = shop1[i].selled; break;
				case 2: selled = shop2[i].selled; break;
				case 3: selled = shop3[i].selled; break;
				}

				if (!selled)
				{
					if (!hover_playing)
					{
						app->audio->PlayFx(hover_sound);
						hover_playing = true;
					}
					chosed = i;
					shop_buttons[i].state = 1;
				}
			}
			else
			{
				shop_buttons[i].state = 0;
			}
		}
	}
	else if (in_shop != 0)
	{
		for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
		{
			shop_buttons[i].state = 0;
		}

		for (size_t i = 0; i < NUM_SHOP_INTERACT_BUTTONS; i++)
		{
			SDL_Rect rect = shop_interact_buttons[i].rect;
			if (x + cx > rect.x && x + cx < rect.x + rect.w && y + cy > rect.y && y + cy < rect.y + rect.h)
			{
				if (!hover_playing)
				{
					app->audio->PlayFx(hover_sound);
					hover_playing = true;
				}
				chosed = i;
				shop_interact_buttons[i].state = 1;
			}
			else
			{
				shop_interact_buttons[i].state = 0;
			}
		}
	}

	return true;
}

// Called each loop iteration
bool Dialog::Update(float dt)
{
	if (app->frontground->controller)
	{
		GamePad& pad = app->input->pads[0];

		if (pad.b == true)
		{
			app->input->SetKey(SDL_SCANCODE_E, KEY_REPEAT);
		}
	}

	if (in_shop == 0)
	{
		if (app->input->GetKey(SDL_SCANCODE_E) == KEY_UP)
		{
			if (app->physics->inCoins)
			{
				app->inventory->AddCoins(5);
				app->physics->coin_picked = true;
				SetPressE_Hide(true);
			}
			else if (app->physics->inBook)
			{
				app->inventory->AddSkillPoint(app->physics->book_type, 1);
				app->physics->book_picked = true;
				SetPressE_Hide(true);
				app->physics->book_type = -1;
			}
			else if (app->physics->GetInNPC(1))
			{
				if (app->frontground->adventure_phase == 0)
				{
					if (ContinueDialog(renato_text, renato_maxtext - 1))
					{
						letlengh = 0;
						letlengh2 = 0;

						inDialog = true;
						actual_dialog = DIALOGS::RENATO;
						SetPressE_Hide(true);
					}
					else
					{
						inDialog = false;
						actual_dialog = DIALOGS::NO_ONE;
					}
				}
				else if (app->frontground->adventure_phase == 1)
				{
					if (!dialog_finish)
					{
						renato_text = 4;
						letlengh = 0;
						letlengh2 = 0;

						inDialog = true;
						actual_dialog = DIALOGS::RENATO;
						SetPressE_Hide(true);
						dialog_finish = true;
					}
					else
					{
						inDialog = false;
						actual_dialog = DIALOGS::NO_ONE;
						dialog_finish = false;
					}
				}
			}
			else if (app->physics->GetInNPC(2))
			{
				if (ContinueDialog(medico_text, medico_maxtext))
				{
					letlengh = 0;
					letlengh2 = 0;

					inDialog = true;
					actual_dialog = DIALOGS::MEDICO;
					SetPressE_Hide(true);
				}
				else
				{
					inDialog = false;
					actual_dialog = DIALOGS::NO_ONE;
					in_shop = 2;
				}
			}
			else if (app->physics->GetInNPC(3))
			{
				if (ContinueDialog(herrero_text, herrero_maxtext))
				{
					letlengh = 0;
					letlengh2 = 0;

					inDialog = true;
					actual_dialog = DIALOGS::HERRERO;
					SetPressE_Hide(true);
				}
				else
				{
					inDialog = false;
					actual_dialog = DIALOGS::NO_ONE;
					in_shop = 1;
				}
			}
			else if (app->physics->GetInNPC(4))
			{
				if (ContinueDialog(granjero_text, granjero_maxtext))
				{
					letlengh = 0;
					letlengh2 = 0;

					inDialog = true;
					actual_dialog = DIALOGS::GRANJERO;
					SetPressE_Hide(true);
				}
				else
				{
					inDialog = false;
					actual_dialog = DIALOGS::NO_ONE;
					in_shop = 3;
				}
			}
			else if (app->physics->GetInNPC(5))
			{
				if (ContinueDialog(aldeano_text, aldeano_maxtext))
				{
					letlengh = 0;
					letlengh2 = 0;

					inDialog = true;
					actual_dialog = DIALOGS::ALDEANO;
					SetPressE_Hide(true);
				}
				else
				{
					inDialog = false;
					actual_dialog = DIALOGS::NO_ONE;
				}
			}
			else
			{
				inDialog = false;
				actual_dialog = DIALOGS::NO_ONE;
			}
		}
	}
	else if (in_shop != 0 && item_saved == NULL)
	{
		if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		{
			in_shop = 0;
		}

		if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && shop_buttons[chosed].state == 1)
		{
			app->audio->PlayFx(click_sound);
			switch (in_shop)
			{
			case 1: item_saved = &shop1[chosed]; break;
			case 2: item_saved = &shop2[chosed]; break;
			case 3: item_saved = &shop3[chosed]; break;
			}

			shop_buttons[chosed].state = 2;
		}
	}
	else if (in_shop != 0)
	{
		if ((app->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == SDL_PRESSED || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP) && shop_interact_buttons[chosed].state == 1)
		{
			app->audio->PlayFx(click_sound);
			if (item_saved->cost > app->inventory->GetCoins())
			{
				item_saved = NULL;
			}
			else
			{
				if (chosed == 0)
				{
					app->inventory->UnlockObject(item_saved->item.c_str());
					app->inventory->AddCoins(-item_saved->cost);
					item_saved->selled = true;
				}
				item_saved = NULL;
			}

			shop_interact_buttons[chosed].state = 2;
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
			PlayLetterSound();
			letter_cd = 0;
		}
	}
	else // 30 fps
	{
		if (letter_cd >= 120 * dt * speedlet && inDialog == true && letlengh <= limitLenght)
		{
			letlengh++;
			PlayLetterSound();
			letter_cd = 0;
		}
	}
	
	if (app->GetFPS() == 16) // 60 fps
	{
		if (letter_cd >= 60 * dt * speedlet && inDialog == true && letlengh2 <= limitLenght2)
		{
			letlengh2++;
			PlayLetterSound();
			letter_cd = 0;
		}
	}
	else // 30 fps
	{
		if (letter_cd >= 120 * dt * speedlet && inDialog == true && letlengh2 <= limitLenght2)
		{
			letlengh2++;
			PlayLetterSound();
			letter_cd = 0;
		}
	}

	if (!press_e_hide)
	{
		anim->Update();
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
		if (actual_dialog == DIALOGS::RENATO) // RENATO TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "RENATO:");
			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Renato[renato_text], 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Renato[renato_text], 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		else if (actual_dialog == DIALOGS::HERRERO) // ALLY TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "HERRERO:");

			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Herrero, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Herrero, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		else if (actual_dialog == DIALOGS::MEDICO) // ALLY TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "MEDICO:");

			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Medico, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Medico, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		else if (actual_dialog == DIALOGS::GRANJERO) // ALLY TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "GRANJERO:");

			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Granjero, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Granjero, 1, 255, 255, 255, 1920, 1, letlengh2, 2);
		}
		/*else if (actual_dialog == DIALOGS::ENEMIGO) // ENEMIES TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "ENEMY:");
			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Templario, 1, 255, 255, 255, 1920, 1, letlengh, 1);
			app->fonts->BlitTextLetter(c_x + 50, c_y + 640, app->fonts->textFont1, linea2Char_Templario, 1, 255, 255, 255, 1920, 1, letlengh2, 1);

		}*/
		else if (actual_dialog == DIALOGS::ALDEANO) // ALDEANO TALKING
		{
			app->render->DrawTexture(whitemark_300x80, 30 + c_x, 480 + c_y);
			app->render->DrawTexture(whitemark_1200x140, 30 + c_x, 560 + c_y);
			app->fonts->BlitText(c_x + 50, c_y + 500, app->fonts->textFont1, "ALDEANO:");

			app->fonts->BlitTextLetter(c_x + 50, c_y + 600, app->fonts->textFont1, linea1Char_Aldeano, 1, 255, 255, 255, 1920, 1, letlengh, 1);
		}
	}
	else
	{
		letlengh = 0;

		if (in_shop != 0)
		{
			app->render->DrawTexture(whitemark_1240x680, 20 + c_x, 20 + c_y);

			for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
			{
				shop_buttons[0].rect.x = 200 + c_x;
				shop_buttons[0].rect.y = 70 + c_y;
				shop_buttons[1].rect.x = shop_buttons[0].rect.x;
				shop_buttons[1].rect.y = shop_buttons[0].rect.y + 150;
				shop_buttons[2].rect.x = shop_buttons[1].rect.x;
				shop_buttons[2].rect.y = shop_buttons[1].rect.y + 150;
				shop_buttons[3].rect.x = shop_buttons[2].rect.x;
				shop_buttons[3].rect.y = shop_buttons[2].rect.y + 150;
			}

			SDL_Rect rect;
			for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
			{
				if (shop_buttons[i].state == 0)
				{
					rect = { 0, 0, 128, 128 };
				}
				else if (shop_buttons[i].state == 1)
				{
					rect = { 0, 128, 128, 128 };
				}
				else if (shop_buttons[i].state == 2)
				{
					rect = { 0, 256, 128, 128 };
				}
				app->render->DrawTexture(whitemark_128x128, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &rect);
			}

			SDL_Rect s_rect;
			std::string object_cost;
			if (in_shop == 1)
			{
				for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
				{
					s_rect = app->menu->GetUnlockRect(shop1[i].item);
					if (shop1[i].item[0] != '4')
					{
						app->render->DrawTexture(app->inventory->gear_tex, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &s_rect);
					}
					else if (shop1[i].item[0] == '4')
					{
						app->render->DrawTexture(app->inventory->items_tex, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &s_rect);
					}
					object_cost = "Objeto: " + GetObjectForShop(shop1[i].item.c_str());
					app->fonts->BlitCombatText(shop_buttons[i].rect.x + 150, shop_buttons[i].rect.y + 26, app->fonts->textFont2, object_cost.c_str());
					object_cost = "Cost: " + std::to_string(shop1[i].cost) + " coins";
					app->fonts->BlitCombatText(shop_buttons[i].rect.x + 150, shop_buttons[i].rect.y + 66, app->fonts->textFont2, object_cost.c_str());
					if (shop1[i].selled)
					{
						s_rect = { 256, 0, 128, 128 };
						app->render->DrawTexture(app->inventory->accept_tex, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &s_rect);
					}
				}
			}
			else if (in_shop == 2)
			{
				for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
				{
					s_rect = app->menu->GetUnlockRect(shop2[i].item);
					if (shop2[i].item[0] != '4')
					{
						app->render->DrawTexture(app->inventory->gear_tex, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &s_rect);
					}
					else if (shop2[i].item[0] == '4')
					{
						app->render->DrawTexture(app->inventory->items_tex, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &s_rect);
					}
					object_cost = "Objeto: " + GetObjectForShop(shop2[i].item.c_str());
					app->fonts->BlitCombatText(shop_buttons[i].rect.x + 150, shop_buttons[i].rect.y + 26, app->fonts->textFont2, object_cost.c_str());
					object_cost = "Cost: " + std::to_string(shop2[i].cost) + " coins";
					app->fonts->BlitCombatText(shop_buttons[i].rect.x + 150, shop_buttons[i].rect.y + 66, app->fonts->textFont2, object_cost.c_str());
					if (shop2[i].selled)
					{
						s_rect = { 256, 0, 128, 128 };
						app->render->DrawTexture(app->inventory->accept_tex, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &s_rect);
					}
				}
			}
			else if (in_shop == 3)
			{
				for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
				{
					s_rect = app->menu->GetUnlockRect(shop3[i].item);
					if (shop3[i].item[0] != '4')
					{
						app->render->DrawTexture(app->inventory->gear_tex, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &s_rect);
					}
					else if (shop3[i].item[0] == '4')
					{
						app->render->DrawTexture(app->inventory->items_tex, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &s_rect);
					}
					object_cost = "Objeto: " + GetObjectForShop(shop3[i].item.c_str());
					app->fonts->BlitCombatText(shop_buttons[i].rect.x + 150, shop_buttons[i].rect.y + 26, app->fonts->textFont2, object_cost.c_str());
					object_cost = "Cost: " + std::to_string(shop3[i].cost) + " coins";
					app->fonts->BlitCombatText(shop_buttons[i].rect.x + 150, shop_buttons[i].rect.y + 66, app->fonts->textFont2, object_cost.c_str());
					if (shop3[i].selled)
					{
						s_rect = { 256, 0, 128, 128 };
						app->render->DrawTexture(app->inventory->accept_tex, shop_buttons[i].rect.x, shop_buttons[i].rect.y, &s_rect);
					}
				}
			}

			if (item_saved != NULL)
			{
				app->render->DrawTexture(whitemark_800x150, 240 + c_x, 300 + c_y);

				SDL_Rect b0;
				if (shop_interact_buttons[0].state == 0)
				{
					b0 = { 0, 0, 128, 128 };
				}
				else if (shop_interact_buttons[0].state == 1)
				{
					b0 = { 0, 128, 128, 128 };
				}
				else if (shop_interact_buttons[0].state == 2)
				{
					b0 = { 0, 256, 128, 128 };
				}

				SDL_Rect b1;
				if (shop_interact_buttons[1].state == 0)
				{
					b1 = { 0, 0, 128, 128 };
				}
				else if (shop_interact_buttons[1].state == 1)
				{
					b1 = { 0, 128, 128, 128 };
				}
				else if (shop_interact_buttons[1].state == 2)
				{
					b1 = { 0, 256, 128, 128 };
				}

				SDL_Rect a_rect = { 0, 0, 128, 128 };
				std::string p_siting;

				if (item_saved->cost > app->inventory->GetCoins())
				{
					shop_interact_buttons[0].rect.x = 576 + c_x;
					shop_interact_buttons[0].rect.y = 380 + c_y;
					app->render->DrawTexture(whitemark_128x128, shop_interact_buttons[0].rect.x, shop_interact_buttons[0].rect.y, &b0);
					app->render->DrawTexture(app->inventory->accept_tex, shop_interact_buttons[0].rect.x, shop_interact_buttons[0].rect.y, &a_rect);
					p_siting = "Imposible, item cost is " + std::to_string(item_saved->cost) + " coins";
					app->fonts->BlitCombatText(300 + c_x, 310 + c_y, app->fonts->textFont2, p_siting.c_str());
				}
				else
				{
					shop_interact_buttons[0].rect.x = 400 + c_x;
					shop_interact_buttons[0].rect.y = 380 + c_y;
					shop_interact_buttons[1].rect.x = shop_interact_buttons[0].rect.x + 300;
					shop_interact_buttons[1].rect.y = shop_interact_buttons[0].rect.y;
					app->render->DrawTexture(whitemark_128x128, shop_interact_buttons[0].rect.x, shop_interact_buttons[0].rect.y, &b0);
					app->render->DrawTexture(whitemark_128x128, shop_interact_buttons[1].rect.x, shop_interact_buttons[1].rect.y, &b1);
					app->render->DrawTexture(app->inventory->accept_tex, shop_interact_buttons[0].rect.x, shop_interact_buttons[0].rect.y, &a_rect);
					a_rect = { 128, 0, 128, 128 };
					app->render->DrawTexture(app->inventory->accept_tex, shop_interact_buttons[1].rect.x, shop_interact_buttons[1].rect.y, &a_rect);
					p_siting = "Buy Item using " + std::to_string(item_saved->cost) + " coins?";
					app->fonts->BlitCombatText(320 + c_x, 310 + c_y, app->fonts->textFont2, p_siting.c_str());
				}
			}
		}
	}

	SDL_Rect rect = anim->GetCurrentFrame();

	if (!press_e_hide)
	{
		app->render->DrawTexture(press_e, c_x + 1110, c_y + 550, &rect);
	}

	return true;
}

// Called before quitting
bool Dialog::CleanUp()
{
	// clean textures
	app->tex->UnLoad(whitemark_1200x140);
	whitemark_1200x140 = NULL;
	app->tex->UnLoad(whitemark_300x80);
	whitemark_300x80 = NULL;
	app->tex->UnLoad(press_e);
	press_e = NULL;
	anim = NULL;

	item_saved = NULL;

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

void Dialog::PlayLetterSound()
{
	int r = rand() % 3;

	switch (r)
	{
	case 0: app->audio->PlayFx(letter_fx); break;
	case 1: app->audio->PlayFx(letterA_fx); break;
	case 2: app->audio->PlayFx(letterG_fx); break;
	}
}

bool Dialog::ContinueDialog(int& actual_text, int max_text)
{
	actual_text++;
	if (actual_text < max_text)
	{
		return true;
	}
	else 
	{
		actual_text = -1;
		return false;
	}
}

void Dialog::UpdateShop()
{
	for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
	{
		shop1[i].selled = false;
		shop2[i].selled = false;
		shop3[i].selled = false;
	}

	if (app->frontground->adventure_phase == 0)
	{
		// herrero
		shop1[0].item = "031";
		shop1[0].cost = 15;
		shop1[1].item = "131";
		shop1[1].cost = 15;
		shop1[2].item = "231";
		shop1[2].cost = 15;
		shop1[3].item = "331";
		shop1[3].cost = 15;

		// medico
		shop2[0].item = "40";
		shop2[0].cost = 5;
		shop2[1].item = "41";
		shop2[1].cost = 8;
		shop2[2].item = "44";
		shop2[2].cost = 5;
		shop2[3].item = "45";
		shop2[3].cost = 8;

		// granjero
		shop3[0].item = "40";
		shop3[0].cost = 5;
		shop3[1].item = "40";
		shop3[1].cost = 5;
		shop3[2].item = "40";
		shop3[2].cost = 5;
		shop3[3].item = "40";
		shop3[3].cost = 5;
	}
	else if (app->frontground->adventure_phase == 1)
	{
		// herrero
		shop1[0].item = "032";
		shop1[0].cost = 15;
		shop1[1].item = "132";
		shop1[1].cost = 15;
		shop1[2].item = "232";
		shop1[2].cost = 15;
		shop1[3].item = "332";
		shop1[3].cost = 15;

		// medico
		shop2[0].item = "40";
		shop2[0].cost = 5;
		shop2[1].item = "41";
		shop2[1].cost = 8;
		shop2[2].item = "44";
		shop2[2].cost = 5;
		shop2[3].item = "45";
		shop2[3].cost = 8;

		// granjero
		shop2[0].item = "40";
		shop2[0].cost = 5;
		shop2[1].item = "40";
		shop2[1].cost = 5;
		shop2[2].item = "40";
		shop2[2].cost = 5;
		shop2[3].item = "40";
		shop2[3].cost = 5;
	}
}

std::string Dialog::GetObjectForShop(const char* aei)
{
	std::string s;

	if (aei[0] == '0') // assassin
	{
		if (aei[1] == '0') // helmet
		{
			s = "Casco de nivel " + std::to_string(aei[2] - '0') + " para asesino";
		}
		else if (aei[1] == '1') // chestplate
		{
			s = "Peto de nivel " + std::to_string(aei[2] - '0') + " para asesino";
		}
		else if (aei[1] == '2') // boots
		{
			s = "Botas de nivel " + std::to_string(aei[2] - '0') + " para asesino";
		}
		else if (aei[1] == '3') // weapon
		{
			s = "Espada de nivel " + std::to_string(aei[2] - '0') + " para asesino";
		}
	}
	else if (aei[0] == '1') // healer
	{
		if (aei[1] == '0') // helmet
		{
			s = "Casco de nivel " + std::to_string(aei[2] - '0') + " para healer";
		}
		else if (aei[1] == '1') // chestplate
		{
			s = "Peto de nivel " + std::to_string(aei[2] - '0') + " para healer";
		}
		else if (aei[1] == '2') // boots
		{
			s = "Botas de nivel " + std::to_string(aei[2] - '0') + " para healer";
		}
		else if (aei[1] == '3') // weapon
		{
			s = "Lira de nivel " + std::to_string(aei[2] - '0') + " para healer";
		}
	}
	else if (aei[0] == '2') // tank
	{
		if (aei[1] == '0') // helmet
		{
			s = "Casco de nivel " + std::to_string(aei[2] - '0') + " para defensor";
		}
		else if (aei[1] == '1') // chestplate
		{
			s = "Peto de nivel " + std::to_string(aei[2] - '0') + " para defensor";
		}
		else if (aei[1] == '2') // boots
		{
			s = "Botas de nivel " + std::to_string(aei[2] - '0') + " para defensor";
		}
		else if (aei[1] == '3') // weapon
		{
			s = "Escudo de nivel " + std::to_string(aei[2] - '0') + " para defensor";
		}
	}
	else if (aei[0] == '3') // wizard
	{
		if (aei[1] == '0') // helmet
		{
			s = "Casco de nivel " + std::to_string(aei[2] - '0') + " para mago";
		}
		else if (aei[1] == '1') // chestplate
		{
			s = "Peto de nivel " + std::to_string(aei[2] - '0') + " para mago";
		}
		else if (aei[1] == '2') // boots
		{
			s = "Botas de nivel " + std::to_string(aei[2] - '0') + " para mago";
		}
		else if (aei[1] == '3') // weapon
		{
			s = "Baston de nivel " + std::to_string(aei[2] - '0') + " para mago";
		}
	}

	return s;
}

bool Dialog::InAnyButton()
{
	for (size_t i = 0; i < NUM_SHOP_BUTTONS; i++)
	{
		if (shop_buttons[i].state == 1)
		{
			return true;
		}
	}
	for (size_t i = 0; i < NUM_SHOP_INTERACT_BUTTONS; i++)
	{
		if (shop_interact_buttons[i].state == 1)
		{
			return true;
		}
	}

	return false;
}