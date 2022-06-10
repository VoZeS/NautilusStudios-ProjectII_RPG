#ifndef __CREDITS_H_
#define __CREDITS_H_

#include "Module.h"
#include "Physics.h"
#include "Animation.h"


struct _Mix_Music;
struct SDL_Texture;

class Credits : public Module
{
public:

	Credits(bool enabled);

	// Destructor
	virtual ~Credits();

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

	int creditsCounter = 0;

private:

	SDL_Rect creditsRect;

	SDL_Texture* credits = NULL;

};

#endif // __CREDITS_H_

