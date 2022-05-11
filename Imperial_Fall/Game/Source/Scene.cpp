#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "Menu.h"
#include "Map.h"
#include "Fonts.h"
#include "Frontground.h"
#include "Combat_Entities.h"
#include "Player.h"
#include "Town1.h"
#include "AssetsManager.h"
#include "Combat_Manager.h"
#include "Combat_Menu.h"
#include "Dialog.h"
#include "Entities.h"
#include "Inventory.h"
#include "LogoScreen.h"
#include "Menu.h"
#include "Particles.h"
#include "Pathfinding.h"

#include "Defs.h"
#include "Log.h"

Scene::Scene(bool enabled) : Module(enabled)
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	// TODO 5: Uncomment all of this, resolve how to load the document from the memory with the link

	char* buffer = NULL;
	pugi::xml_document dataFile;

	int bytesFile = app->assetsmanager->LoadData("data.xml", &buffer);

	// Loading from memory with PUGI: https://pugixml.org/docs/manual.html#loading.memory
	pugi::xml_parse_result result = dataFile.load_buffer(buffer, bytesFile);

	RELEASE_ARRAY(buffer);

	LoadTexFile(dataFile);
	LoadFxFile(dataFile);
	LoadMusFile(dataFile);


	/*if (this->Enabled() && !this->Disabled())
	{
		app->fonts->Enable();

		c_y_menu = -app->render->camera.y + 0; // Posicion de la camara en el inicio del juego

		start_screen = app->tex->Load("Assets/textures/Menu_BackGround
		");
		settings_screen = app->tex->Load("Assets/textures/Settings_BackGround
		");

		//app->audio->PlayMusic("Assets/audio/music/menu.ogg");
		app->audio->StopMusic(1.0f);

		if (!app->menu->Enabled())
		{
			app->menu->Enable();
		}
	}
	*/
	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	if (!app->audio->MusicPlaying())
	{
		app->audio->PlayMusic("Assets/audio/music/menu.ogg");
	}

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	
	bool ret = true;
	int c_x = -app->render->camera.x;
	int c_y = -app->render->camera.y;	


		//app->render->DrawTexture(texture1, app->render->camera.x, app->render->camera.y);
		

	if (app->frontground->controller)
	{
		GamePad& pad = app->input->pads[0];

		if (pad.a == true)
		{
			app->input->SetKey(SDL_SCANCODE_Y, KEY_REPEAT);
		}
	}
	
	//--------------------------------------MENU----------------------------


	//Desplazamiento del fondo al inicio del juego
	//Una vez pulses el Espacio entrara el menu de opciones
	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->GetKey(SDL_SCANCODE_Y) == KEY_UP || desMenu == true)
	{
		space_boton = false;
		desMenu = true;
		c_y_menu -= 10.0f;
		fuegoSeguir = true;

	}

	//Limite de donde la camara llegara al principio del juego
	if (c_y_menu <= -700)
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

	//----------------------------------------------------
	//-------------------Settings
	if (app->menu->settings == true)
	{
		app->render->DrawTexture(settings_screen, c_x, c_y);
	}
	
	//Segunda Pantalla Menu
	if (start_screen != NULL && esc == true && app->menu->settings == false)
	{
		app->render->DrawTexture(start_screen, c_x, c_y - 700);
	}

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");
	
	app->fonts->Disable();
	app->menu->Disable();

	// clean textures
	app->tex->UnLoad(start_screen);
	start_screen = NULL;
	app->tex->UnLoad(settings_screen);
	settings_screen = NULL;

	return true;
}

void Scene::LoadTexFile(const pugi::xml_document& dataFile)
{
	pugi::xml_node tex_node = dataFile.child("data").child("texture");
	app->combat_manager->heroes_icons = app->tex->Load(tex_node.attribute("heroes_icons").as_string());
	app->combat_manager->enemies_icons = app->tex->Load(tex_node.attribute("enemies_icons").as_string());
	app->combat_manager->turn_icon = app->tex->Load(tex_node.attribute("turn_icon").as_string());
	app->combat_manager->dead_icon = app->tex->Load(tex_node.attribute("dead_icon").as_string());
	app->combat_manager->turns_icons = app->tex->Load(tex_node.attribute("turns_icons").as_string());
	app->combat_manager->status_effects = app->tex->Load(tex_node.attribute("status_effects").as_string());

	app->combat_menu->assassin_texture = app->tex->Load(tex_node.attribute("assassin_texture").as_string());
	app->combat_menu->tank_texture = app->tex->Load(tex_node.attribute("tank_texture").as_string());
	app->combat_menu->healer_texture = app->tex->Load(tex_node.attribute("healer_texture").as_string());
	app->combat_menu->wizard_texture = app->tex->Load(tex_node.attribute("wizard_texture").as_string());
	app->combat_menu->target = app->tex->Load(tex_node.attribute("target").as_string());
	app->combat_menu->tombstone = app->tex->Load(tex_node.attribute("tombstone").as_string());
	app->combat_menu->goblin = app->tex->Load(tex_node.attribute("goblin").as_string());
	app->combat_menu->skeleton = app->tex->Load(tex_node.attribute("skeleton").as_string());
	app->combat_menu->mushroom = app->tex->Load(tex_node.attribute("mushroom").as_string());
	app->combat_menu->white_templar = app->tex->Load(tex_node.attribute("white_templar").as_string());
	app->combat_menu->red_templar = app->tex->Load(tex_node.attribute("red_templar").as_string());
	app->combat_menu->dragon_idle = app->tex->Load(tex_node.attribute("dragon_idle").as_string());
	app->combat_menu->dragon_ult = app->tex->Load(tex_node.attribute("dragon_ult").as_string());
	app->combat_menu->theseion = app->tex->Load(tex_node.attribute("theseion").as_string());
	app->combat_menu->armored_templar = app->tex->Load(tex_node.attribute("armored_templar").as_string());
	app->combat_menu->special_buttons = app->tex->Load(tex_node.attribute("special_buttons").as_string());
	app->combat_menu->items = app->tex->Load(tex_node.attribute("items").as_string());
	app->combat_menu->casting = app->tex->Load(tex_node.attribute("casting").as_string());
	app->combat_menu->skills_icons = app->tex->Load(tex_node.attribute("skills_icons").as_string());

	app->dialog->press_e = app->tex->Load(tex_node.attribute("press_e").as_string());

	app->entities->curandero = app->tex->Load(tex_node.attribute("curandero").as_string());
	app->entities->herrero = app->tex->Load(tex_node.attribute("herrero").as_string());
	app->entities->sabio = app->tex->Load(tex_node.attribute("sabio").as_string());
	app->entities->aldeano = app->tex->Load(tex_node.attribute("aldeano").as_string());
	app->entities->granjero = app->tex->Load(tex_node.attribute("granjero").as_string());
	app->entities->renato_bueno = app->tex->Load(tex_node.attribute("renato_bueno").as_string());

	/*
	app->fonts->textFont1 = app->tex->Load(tex_node.attribute("textFont1").as_string());
	app->fonts->textFont2 = app->tex->Load(tex_node.attribute("textFont2").as_string());
	app->fonts->textFont3 = app->tex->Load(tex_node.attribute("textFont3", app->fonts->lookupTableChars, 8).as_string());
	app->fonts->textFont4 = app->tex->Load(tex_node.attribute("textFont4").as_string());
	*/

	app->inventory->book_tex = app->tex->Load(tex_node.attribute("book_tex").as_string());
	app->inventory->arrows_tex = app->tex->Load(tex_node.attribute("arrows_tex").as_string());
	app->inventory->skill_tree_tex = app->tex->Load(tex_node.attribute("skill_tree_tex").as_string());
	app->inventory->hero_tex = app->tex->Load(tex_node.attribute("hero_tex").as_string());
	app->inventory->items_tex = app->tex->Load(tex_node.attribute("items_tex").as_string());
	app->inventory->gear_tex = app->tex->Load(tex_node.attribute("gear_tex").as_string());
	app->inventory->unknow_tex = app->tex->Load(tex_node.attribute("unknow_tex").as_string());
	app->inventory->accept_tex = app->tex->Load(tex_node.attribute("accept_tex").as_string());
	app->inventory->misc = app->tex->Load(tex_node.attribute("misc").as_string());

	app->logo->logo = app->tex->Load(tex_node.attribute("logo").as_string());
	
	app->menu->desc_icons = app->tex->Load(tex_node.attribute("desc_icons").as_string());
	app->menu->rew_icons = app->tex->Load(tex_node.attribute("rew_icons").as_string());
	app->menu->Scape_BackGround = app->tex->Load(tex_node.attribute("Scape_BackGround").as_string());
	app->menu->Lose_BackGround = app->tex->Load(tex_node.attribute("Lose_BackGround").as_string());
	app->menu->Win_BackGround = app->tex->Load(tex_node.attribute("Win_BackGround").as_string());
	app->menu->combat_win = app->tex->Load(tex_node.attribute("combat_win").as_string());
	app->menu->combat_lose = app->tex->Load(tex_node.attribute("combat_lose").as_string());
	app->menu->combat_scape = app->tex->Load(tex_node.attribute("combat_scape").as_string());
	app->menu->torch_fire = app->tex->Load(tex_node.attribute("torch_fire").as_string());
	app->menu->light_fire1 = app->tex->Load(tex_node.attribute("light_fire1").as_string());
	app->menu->light_fire2 = app->tex->Load(tex_node.attribute("light_fire2").as_string());
	app->menu->light_fire3 = app->tex->Load(tex_node.attribute("light_fire3").as_string());
	app->menu->light_fire4 = app->tex->Load(tex_node.attribute("light_fire4").as_string());
	app->menu->big_fire = app->tex->Load(tex_node.attribute("big_fire").as_string());
	app->menu->big_fire_light = app->tex->Load(tex_node.attribute("big_fire_light").as_string());
	app->menu->smook_big_fire = app->tex->Load(tex_node.attribute("smook_big_fire").as_string());
	app->menu->space_boton = app->tex->Load(tex_node.attribute("space_boton").as_string());
	app->menu->menu_in_game = app->tex->Load(tex_node.attribute("menu_in_game").as_string());
	app->menu->menu_play = app->tex->Load(tex_node.attribute("menu_play").as_string());
	app->menu->team_photo = app->tex->Load(tex_node.attribute("team_photo").as_string());

    app->inventory->skill_image0 = app->tex->Load(tex_node.attribute("skill_image0").as_string());
	app->inventory->skill_image1 = app->tex->Load(tex_node.attribute("skill_image1").as_string());
	app->inventory->skill_image2 = app->tex->Load(tex_node.attribute("skill_image2").as_string());
	app->inventory->skill_image3 = app->tex->Load(tex_node.attribute("skill_image3").as_string());
	app->inventory->coin = app->tex->Load(tex_node.attribute("coin").as_string());

	app->particles->texture = app->tex->Load(tex_node.attribute("texture").as_string());

	app->pathfinding->tileX = app->tex->Load(tex_node.attribute("tileX").as_string());

	start_screen = app->tex->Load(tex_node.attribute("start_screen").as_string());
	settings_screen = app->tex->Load(tex_node.attribute("settings_screen").as_string());

	app->combat_menu->whitemark_400x50 = app->tex->Load(tex_node.attribute("whitemark_400x50").as_string());
	app->combat_menu->whitemark_110x110 = app->tex->Load(tex_node.attribute("whitemark_110x110").as_string());
	app->combat_menu->whitemark_128x128 = app->tex->Load(tex_node.attribute("whitemark_128x128").as_string());
	app->combat_menu->whitemark_800x50 = app->tex->Load(tex_node.attribute("whitemark_800x50").as_string());
	
	app->inventory->whitemark_250x70 = app->tex->Load(tex_node.attribute("whitemark_250x70").as_string());
	app->inventory->whitemark_800x150 = app->tex->Load(tex_node.attribute("whitemark_800x150").as_string());

	app->menu->whitemark_1240x680 = app->tex->Load(tex_node.attribute("whitemark_1240x680").as_string());
	
	app->dialog->whitemark_1200x140 = app->tex->Load(tex_node.attribute("whitemark_1200x140").as_string());
	app->dialog->whitemark_300x80 = app->tex->Load(tex_node.attribute("whitemark_300x80").as_string());

	app->combat_manager->whitemark_64x64 = app->tex->Load(tex_node.attribute("whitemark_64x64").as_string());
	app->combat_manager->whitemark_32x32 = app->tex->Load(tex_node.attribute("whitemark_32x32").as_string());
	
	app->menu->whitemark_500x70 = app->tex->Load(tex_node.attribute("whitemark_500x70").as_string());

	
}

void Scene::LoadFxFile(const pugi::xml_document& dataFile)
{
	pugi::xml_node fx_node = dataFile.child("data").child("fx");
	app->audio->LoadFx(fx_node.attribute("file").as_string());
}

void Scene::LoadMusFile(const pugi::xml_document& dataFile)
{
	pugi::xml_node mus_node = dataFile.child("data").child("mus");
	app->audio->PlayMusic(mus_node.attribute("file").as_string());
}