#ifndef __COMBAT_SCENE_H__
#define __COMBAT_SCENE_H__

#include "Module.h"
#include "Physics.h"

struct SDL_Texture;
enum class ENEMIES;

class Combat_Scene : public Module
{
public:

	Combat_Scene(bool enabled);

	// Destructor
	virtual ~Combat_Scene();

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

};

#endif // __COMBAT_SCENE_H__
