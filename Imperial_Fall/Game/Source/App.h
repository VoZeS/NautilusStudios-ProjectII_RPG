#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"
#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define STARTED_FILENAME "started.xml"
#define CONFIG_FILENAME	"config.xml"
#define ORIGIN_SAVE_STATE_FILENAME "origin_save_game.xml"
#define SAVE_STATE_FILENAME "save_game.xml"
#define DIALOG_FILENAME	"dialog.xml"
#define HEROES_STATS_FILENAME	"heroes_stats.xml"
#define UNLOCKABLE_OBJECTS_FILENAME	"unlockable_objects.xml"
#define MISCELANEA_FILENAME	"miscelanea.xml"

// Modules
class Window;
class Input;
class Render;
class Textures;
class Audio;
class Scene;
class Map;
class PathFinding;
class Physics;
class Entities;
class Fonts;
class Combat_Manager;
class Combat_Menu;
class Menu;
class Inventory;
class Particles;
class Frontground;
class Town1;
class Town2;
class Forest;
class Battlefield;
class Dungeon;
class Outside_Castle;
class Inside_Castle;
class Combat_Scene;
class End_Combat_Scene;
class Dialog;
class LogoScreen;
class ModuleAssetsManager;



class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

    // L02: DONE 1: Create methods to request Load / Save
	void LoadGameRequest(bool set_to_origin);
	void SaveGameRequest();
	bool LoadGame(bool set_to_origin);
	bool SaveGame();

private:

	// Load config file
	// NOTE: It receives config document
	bool LoadConfig();

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate(float dt);

	// Call modules after each loop iteration
	bool PostUpdate();


public:

	// Modules
	Window* win;
	Input* input;
	Render* render;
	Textures* tex;
	Audio* audio;
	Scene* scene;
	Map* map;
	PathFinding* pathfinding;
	Physics* physics;
	Entities* entities;
	Fonts* fonts;
	Combat_Manager* combat_manager;
	Combat_Menu* combat_menu;
	Menu* menu;
	Inventory* inventory;
	Particles* particles;
	Frontground* frontground;
	Town1* town1;
	Town2* town2;
	Forest* forest;
	Battlefield* battlefield;
	Dungeon* dungeon;
	Outside_Castle* outside;
	Inside_Castle* inside;
	Combat_Scene* combat_scene;
	End_Combat_Scene* end_combat_scene;
	Dialog* dialog;
	LogoScreen* logo;
	ModuleAssetsManager* assetsmanager;


private:

	int argc;
	char** args;
	SString title;
	SString organization;

	List<Module *> modules;

	pugi::xml_document configFile;
	pugi::xml_node config;
	pugi::xml_node configApp;

	mutable bool saveGameRequested;
	

	pugi::xml_document originSaveGame;
	pugi::xml_document saveGame;
	bool set_to_origin = false;
		
	PerfTimer* ptimer;

	Timer startupTime;
	Timer frameTime;
	Timer lastSecFrameTime;

	uint64 frameCount = 0;
	uint32 framesPerSecond = 0;
	uint32 lastSecFrameCount = 0;

	float averageFps = 0.0f;
	float dt = 0.0f;

	uint32 maxFrameRate;
	PerfTimer* frameDuration;

	uint32 FPS;

public:
	float GetDT();

	float GetFPS();

	void ToggleFPS();
	bool loadGameRequested;
};

extern App* app;

#endif	// __APP_H__