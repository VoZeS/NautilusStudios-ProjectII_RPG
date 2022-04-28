#ifndef __DUNGEON_H__
#define __DUNGEON_H__

#include "Module.h"
#include "Physics.h"

struct SDL_Texture;
enum class ENEMIES;

class Dungeon : public Module
{
public:

	Dungeon(bool enabled);

	// Destructor
	virtual ~Dungeon();

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

public:
	bool isinIce = false;




};

#endif // __DUNGEON_H__
