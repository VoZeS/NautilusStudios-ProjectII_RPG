#ifndef __SCENE_H__
#define __SCENE_H__

#include "Module.h"
#include "Physics.h"

struct _Mix_Music;
struct SDL_Texture;
enum class ENEMIES;

class Scene : public Module
{
public:

	Scene(bool enabled);

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

	int current_level = 0;

	int textFontDialog= -1;

	int textFont = -1;

	int nh;

	bool fuegoSeguir = false;

	bool esc = false;
	bool desMenu = false;

	float c_y_menu;

	bool space_boton = true; // Desactiva el boton ESPACIO del principio

private:

	SDL_Texture* start_screen;
	SDL_Texture* settings_screen;
};

#endif // __SCENE_H__