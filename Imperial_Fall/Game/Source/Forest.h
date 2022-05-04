#ifndef __FOREST_H__
#define __FOREST_H__

#include "Module.h"
#include "Physics.h"

struct SDL_Texture;
enum class ENEMIES;

class Forest : public Module
{
public:

	Forest(bool enabled);

	// Destructor
	virtual ~Forest();

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

	SDL_Texture* box_texture = NULL;

	Animation* currentAnimation = NULL;
	Animation movingBox_Anim;
	SDL_Rect boxRect;
};

#endif // __FOREST_H__
