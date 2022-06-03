#ifndef __TOWN1_H__
#define __TOWN1_H__

#include "Module.h"
#include "Physics.h"

struct SDL_Texture;
enum class ENEMIES;

class Town1 : public Module
{
public:

	Town1(bool enabled);

	// Destructor
	virtual ~Town1();

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

	SDL_Texture* bonfire = NULL;
	Animation bonfire_anim;

};

#endif // __TOWN1_H__