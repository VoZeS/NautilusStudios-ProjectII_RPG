#ifndef __MENU_H__
#define __MENU_H__

#include "Module.h"
#include "Animation.h"


#define NUM_PAUSE_BUTTONS 4
#define NUM_MENU_BUTTONS 6
#define NUM_WIN_BUTTONS 1
#define NUM_LOSE_BUTTONS 2
#define NUM_SCAPE_BUTTONS 2
#define NUM_SETTINGS_BUTTONS 4

struct Button {
	SDL_Rect rect = { 0, 0, 220, 70 };
	SDL_Texture* tex = NULL;
	SDL_Texture* alt_tex = NULL;
	SDL_Texture* alt_tex2 = NULL;
	SDL_Texture* alt_tex_selec = NULL;


	int state = 0; // 0 --> idle, 1 --> above, 2 --> pressed
};

class Menu : public Module
{
public:
	Menu(bool enabled);

	virtual ~Menu();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	bool GetGameState();

	bool win;
	bool lose;
	bool scape;
	bool kill_enemy = false;

	SDL_Texture* torch_fire = NULL;
	SDL_Texture* light_fire1 = NULL;
	SDL_Texture* light_fire2 = NULL;
	SDL_Texture* light_fire3 = NULL;
	SDL_Texture* light_fire4 = NULL;

	SDL_Texture* big_fire = NULL;
	SDL_Texture* big_fire_light = NULL;
	SDL_Texture* smook_big_fire = NULL;

	SDL_Texture* space_boton = NULL;

	//Textura del menu in game que sale dandole a ESC
	SDL_Texture* menu_in_game = NULL;

	//Textura que sale dandole a Play
	SDL_Texture* menu_play = NULL;

	//Foto de nuestro gran equipo
	SDL_Texture* team_photo = NULL;

	SDL_Rect PauseMenuHUD;

	// -1 --> all false, 0 --> win, 1 --> lose, 2 --> scape
	void SetWinLoseScape(int n);

	bool ReturnStartScreen();

public:

	SDL_Rect r;
	bool intro;
	bool paused;
	bool settings;
	bool vsync;
	bool fullscreen;
	bool credits;

	int seguir;

	bool firstime = true; // Mira si es la primera vez que juegas al juego
	bool subplaymenu; // Menu que sale cuando le das a Play
	
	bool stop = false;
	bool desMenu = false; //Menu in game que aparece cuando le das a ESC
	float c_x_menu=200.0f; //Posicion del menu in game.

	bool menu = false;

	bool started = false;

	void InitPlayer();

	void DisableAll();

	void SetController()
	{
		pause_buttons[0].state = 1;
		menu_buttons[0].state = 1;
		settings_buttons[0].state = 1;
		win_button.state = 1;
		lose_buttons[0].state = 1;
		scape_buttons[0].state = 1;
	}

	//Dialog checker
	bool redtemplar_killed = false;

private:

	bool description_disabled = true;
	
	Animation torch_selection_anim;
	Animation torch_light_1_anim;
	Animation torch_light_2_anim;
	Animation torch_light_3_anim;
	Animation torch_light_4_anim;

	Animation big_fire_anim;
	Animation light_big_fire_anim;
	Animation smook_big_fire_anim;
	Animation space_boton_anim;

	Animation menu_play_anim;

	int z1 = 60, z2 = 65;
	int xbarra = 145;
	int xbarra2 = 145;
	bool slider;
	bool slider2;

	int chosed;
	Button pause_buttons[NUM_PAUSE_BUTTONS];
	Button menu_buttons[NUM_MENU_BUTTONS];
	Button settings_buttons[NUM_SETTINGS_BUTTONS];
	Button win_button;
	Button lose_buttons[NUM_LOSE_BUTTONS];
	Button scape_buttons[NUM_SCAPE_BUTTONS];

	SDL_Texture* combat_back = NULL;
	SDL_Texture* combat_win = NULL;
	SDL_Texture* combat_lose = NULL;
	SDL_Texture* combat_scape = NULL;

	SDL_Texture* whitemark_500x70 = NULL;

	Uint8 idleColorR = 18;
	Uint8 idleColorG = 188;
	Uint8 idleColorB = 13;
	Uint8 inColorR = 255;
	Uint8 inColorG = 178;
	Uint8 inColorB = 0;
	Uint8 pColorR = 255;
	Uint8 pColorG = 0;
	Uint8 pColorB = 0;

	int load_cd = 120;
	bool loading = false;

	uint win_w, win_h;
	
	int save_cd = 50;
	bool saving = false;

	// sound
	uint click_sound;
	uint hover_sound;
	bool hover_playing = false;
	bool InAnyButton();

	uint menu_music;
	
};

#endif