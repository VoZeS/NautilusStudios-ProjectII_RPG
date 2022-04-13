#ifndef __BATTLEFIELD_H__
#define __BATTLEFIELD_H__

#include "Module.h"
#include "Physics.h"

struct SDL_Texture;
enum class ENEMIES;

class Battlefield : public Module
{
public:

	Battlefield(bool enabled);

	// Destructor
	virtual ~Battlefield();

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

#endif // __BATTLEFIELD_H__
