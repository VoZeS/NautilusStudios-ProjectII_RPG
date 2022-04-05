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

	int textFont = -1;

	int nh;

	bool fuegoSeguir = false;

	bool esc = false;
	bool desMenu = false;
	
	bool activarMenu = true;
	bool activarSettings = false;
	bool movCamara = false;

	float c_y_menu;
	
	bool daleZom1=false;
	bool daleZom2 = false;
	int zom_x = 0;
	int zom_y = 0;
	int zom_w = 1280;
	int zom_h = 720;


	bool space_boton = true; //Desactiva el boton ESPACIO del principio

	bool opciones = false;
	SDL_Rect r;

	SDL_Texture* start_screen;
private:
	
	SDL_Texture* settings_screen;


	SDL_Texture* pathTex;
	SDL_Texture* originTex;

	iPoint origin;
	bool originSelected = false;

};

#endif // __SCENE_H__