#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Physics.h"

struct SDL_Texture;

class Scene : public Module
{
public:

	Scene();

	// Destructor
	virtual ~Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool GetStartScreenState();

	bool PassLevel(int dest_level);

	bool QuitStartScreen();

	bool ReturnStartScreen();

	bool godmode;

	int current_level = 0;

	int textFontDialog= -1;

	int textFont = -1;

	int limitLenght = 0;
	int limitLenght2 = 0;

	uint letlengh = 0;
	uint letlengh2 = 0;

	int letter_cd = 0;

	bool inDialog = false;
	bool inDialogRenato = false;
	bool inDialogAlly = false;
	bool inDialogEnemy = false;

private:
	SDL_Texture* start_screen;

	SDL_Texture* pathTex;
	SDL_Texture* originTex;

	// Dialog Stuff
	pugi::xml_document dialogFile;
	pugi::xml_node dialog;
	pugi::xml_node renato;
	pugi::xml_node text1;

	std::string linea1String_Renato;
	std::string linea2String_Renato;
	const char* linea1Char_Renato;
	const char* linea2Char_Renato;

	std::string linea1String_Ally;
	std::string linea2String_Ally;
	const char* linea1Char_Ally;
	const char* linea2Char_Ally;


	std::string linea1String_Enemy;
	const char* linea1Char_Enemy;

	bool LoadDialog();

	iPoint origin;
	bool originSelected = false;

};

#endif // __SCENE_H__