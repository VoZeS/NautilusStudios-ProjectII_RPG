#ifndef __END_COMBAT_SCENE_H__
#define __END_COMBAT_SCENE_H__

#include "Module.h"
#include "Animation.h"
#include "Physics.h"

#define BLACK_TIME 200

struct SDL_Texture;
enum class ENEMIES;

class End_Combat_Scene : public Module
{
public:

	End_Combat_Scene(bool enabled);

	// Destructor
	virtual ~End_Combat_Scene();

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

	bool in_cutscene = false;
	int cutcene_cd;

	SDL_Texture* whitemark_1200x140;
	uint evil_laugh;
	uint dragon_roar;

	SDL_Texture* fire_tex;
	Animation* fire = NULL;
	Animation fire_loop;

};

#endif // __END_COMBAT_SCENE_H__
