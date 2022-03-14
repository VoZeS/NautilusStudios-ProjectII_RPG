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

private:
	SDL_Texture* start_screen;

	SDL_Texture* pathTex;
	SDL_Texture* originTex;

	iPoint origin;
	bool originSelected = false;

};

#endif // __SCENE_H__