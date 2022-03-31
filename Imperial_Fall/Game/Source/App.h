#ifndef __APP_H__
#define __APP_H__

#include "Module.h"
#include "PerfTimer.h"
#include "Timer.h"
#include "List.h"

#include "PugiXml/src/pugixml.hpp"

#define CONFIG_FILENAME		"config.xml"
#define SAVE_STATE_FILENAME "save_game.xml"
#define DIALOG_FILENAME		"dialog.xml"

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
class Menu;
class Frontground;



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
	void LoadGameRequest();
	void SaveGameRequest();
	bool LoadGame();
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
	Menu* menu;
	Frontground* frontground;

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
	bool loadGameRequested;

	pugi::xml_document saveGame;
		
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

};

extern App* app;

#endif	// __APP_H__