#include "App.h"
#include "Window.h"
#include "Input.h"
#include "Render.h"
#include "Textures.h"
#include "Audio.h"
#include "Scene.h"
#include "Map.h"
#include "Pathfinding.h"
#include "Physics.h"
#include "Entities.h"
#include "Fonts.h"
#include "Combat_Manager.h"
#include "Combat_Menu.h"
#include "Menu.h"
#include "Particles.h"
#include "Frontground.h"
#include "Town1.h"
#include "Town2.h"
#include "Forest.h"
#include "Battlefield.h"
#include "Dungeon.h"
#include "Outside_Castle.h"
#include "Inside_Castle.h"
#include "Combat_Scene.h"
#include "Dialog.h"
#include "LogoScreen.h"

#include "Defs.h"
#include "Log.h"

#include <iostream>
#include <sstream>

// Constructor
App::App(int argc, char* args[]) : argc(argc), args(args)
{
	win = new Window(true);
	input = new Input(true);
	render = new Render(true);
	tex = new Textures(true);
	audio = new Audio(true);
	scene = new Scene(false);
	map = new Map(false);
	pathfinding = new PathFinding(true);
	physics = new Physics(true);
	entities = new Entities(false);
	fonts = new Fonts(false);
	combat_manager = new Combat_Manager(false);
	combat_menu = new Combat_Menu(false);
	menu = new Menu(true);
	particles = new Particles(false);
	frontground = new Frontground(true);
	town1 = new Town1(false);
	town2 = new Town2(false);
	forest = new Forest(false);
	battlefield = new Battlefield(false);
	dungeon = new Dungeon(false);
	outside = new Outside_Castle(false);
	inside = new Inside_Castle(false);
	combat_scene = new Combat_Scene(false);
	dialog = new Dialog(false);
	logo = new LogoScreen(true);

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(win);
	AddModule(input);
	AddModule(tex);
	AddModule(audio);
	AddModule(scene);
	AddModule(town1);
	AddModule(town2);
	AddModule(forest);
	AddModule(battlefield);
	AddModule(dungeon);
	AddModule(outside);
	AddModule(inside);
	AddModule(combat_scene);
	AddModule(map);
	AddModule(pathfinding);
	AddModule(physics);
	AddModule(entities);
	AddModule(fonts);
	AddModule(combat_manager);
	AddModule(combat_menu);
	AddModule(menu);
	AddModule(particles);
	AddModule(dialog);
	AddModule(logo);
	AddModule(frontground);

	// Render last to swap buffer
	AddModule(render);

	ptimer = new PerfTimer();
	frameDuration = new PerfTimer();
}

// Destructor
App::~App()
{
	// Release modules
	ListItem<Module*>* item = modules.end;

	while(item != NULL)
	{
		RELEASE(item->data);
		item = item->prev;
	}

	modules.Clear();
}

void App::AddModule(Module* module)
{
	module->Init();
	modules.Add(module);
}

// Called before render is available
bool App::Awake()
{
	bool ret = LoadConfig();

	if (ret == true)
	{
		title.Create(configApp.child("title").child_value());
		win->SetTitle(title.GetString());
		FPS = configApp.child("frame_rate").attribute("fps").as_int();
		maxFrameRate = FPS;

		ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->Awake(config.child(item->data->name.GetString()));
			item = item->next;
		}
	}

	return ret;
}

// Called before the first frame
bool App::Start()
{
	startupTime.Start();
	lastSecFrameTime.Start();

	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;

	while(item != NULL && ret == true)
	{
		ret = item->data->Start();
		item = item->next;
	}

	return ret;
}

// Called each loop iteration
bool App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if(input->GetWindowEvent(WE_QUIT) == true)
		ret = false;

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate(dt);

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// Load config from XML file
// NOTE: Function has been redesigned to avoid storing additional variables on the class
bool App::LoadConfig()
{
	bool ret = true;

	pugi::xml_parse_result result = configFile.load_file(CONFIG_FILENAME);

	if (result == NULL)
	{
		LOG("Could not load map xml file config.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		config = configFile.child("config");
		configApp = config.child("app");
	}

	return ret;
}

// ---------------------------------------------
void App::PrepareUpdate()
{
	frameCount++;
	lastSecFrameCount++;

	dt = frameDuration->ReadMs();
	frameDuration->Start();
}

// ---------------------------------------------
void App::FinishUpdate()
{
	if (loadGameRequested == true)
	{
		LoadGame(set_to_origin);
		set_to_origin = false;
	}
	if (saveGameRequested == true)
	{
		SaveGame();
	}
		

	// game time
	float secondsSinceStartup = startupTime.ReadSec();

	if (lastSecFrameTime.Read() > 1000) {
		lastSecFrameTime.Start();
		framesPerSecond = lastSecFrameCount;
		lastSecFrameCount = 0;
		averageFps = (averageFps + framesPerSecond) / 2;
	}

	static char title[256];
	sprintf_s(title, 256, "Av.FPS: %.2f Last sec frames: %i Last dt: %.3f Time since startup: %.3f Frame Count: %I64u ",
		averageFps, framesPerSecond, dt, secondsSinceStartup, frameCount);

	float delay = float(maxFrameRate) - frameDuration->ReadMs();

	PerfTimer* delayt = new PerfTimer();
	delayt->Start();
	if (maxFrameRate > 0 && delay > 0)
	{
		SDL_Delay(delay);
	}

	app->win->SetTitle(title);

	maxFrameRate = FPS;
}

// Call modules before each loop iteration
bool App::PreUpdate()
{
	bool ret = true;

	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}
		
		ret = item->data->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool App::DoUpdate(float dt)
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.start;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool App::PostUpdate()
{
	bool ret = true;
	ListItem<Module*>* item;
	Module* pModule = NULL;

	for(item = modules.start; item != NULL && ret == true; item = item->next)
	{
		pModule = item->data;

		if(pModule->active == false) {
			continue;
		}

		ret = item->data->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool App::CleanUp()
{
	bool ret = true;
	ListItem<Module*>* item;
	item = modules.end;

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}

	return ret;
}

// ---------------------------------------
int App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* App::GetTitle() const
{
	return title.GetString();
}

// ---------------------------------------
const char* App::GetOrganization() const
{
	return organization.GetString();
}

// Load / Save
void App::LoadGameRequest(bool set_to_origin)
{
	loadGameRequested = true;
	this->set_to_origin = set_to_origin;
}

// ---------------------------------------
void App::SaveGameRequest()
{
	saveGameRequested = true;
}

bool App::LoadGame(bool set_to_origin)
{
	bool ret = true;

	pugi::xml_parse_result result;

	if (!set_to_origin)
	{
		// load 
		result = saveGame.load_file(SAVE_STATE_FILENAME);
	}
	else
	{
		// reset 
		result = saveGame.load_file(ORIGIN_SAVE_STATE_FILENAME);
		saveGame.save_file(SAVE_STATE_FILENAME);
	}
	

	if (result == NULL)
	{
		LOG("Could not load map xml file save_game.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->LoadState(saveGame.child("game_state").child(item->data->name.GetString()));
			item = item->next;
		}
	}

	loadGameRequested = false;

	return ret;
}

bool App::SaveGame()
{
	bool ret = true;

	ListItem<Module*>* item;
	item = modules.start;

	pugi::xml_parse_result result = saveGame.load_file(SAVE_STATE_FILENAME);

	if (result == NULL)
	{
		LOG("Could not load map xml file save_game.xml. pugi error: %s", result.description());
		ret = false;
	}
	else
	{
		ListItem<Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			ret = item->data->SaveState(saveGame.child("game_state").child(item->data->name.GetString()));
			item = item->next;
		}
	}

	saveGame.save_file(SAVE_STATE_FILENAME);

	saveGameRequested = false;

	return ret;
}


float App::GetDT()
{
	return dt;
}

float App::GetFPS()
{
	return FPS;
}

void App::ToggleFPS()
{
	if (FPS == 16)
	{
		FPS = 32;
	}
	else
	{
		FPS = 16;
	}
}