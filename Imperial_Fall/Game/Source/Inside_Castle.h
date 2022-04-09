#ifndef __INSIDE_CASTLE_H__
#define __INSIDE_CASTLE_H__

#include "Module.h"
#include "Physics.h"

struct SDL_Texture;
enum class ENEMIES;

class Inside_Castle : public Module
{
public:

	Inside_Castle(bool enabled);

	// Destructor
	virtual ~Inside_Castle();

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

#endif // __INSIDE_CASTLE_H__