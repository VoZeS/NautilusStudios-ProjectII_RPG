#ifndef __OUTSIDE_CASTLE_H__
#define __OUTSIDE_CASTLE_H__

#include "Module.h"
#include "Physics.h"

struct SDL_Texture;
enum class ENEMIES;

class Outside_Castle : public Module
{
public:

	Outside_Castle(bool enabled);

	// Destructor
	virtual ~Outside_Castle();

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

#endif // __OUTSIDE_CASTLE_H__
