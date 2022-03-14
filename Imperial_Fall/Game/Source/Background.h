#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "Module.h"

class Background : public Module
{
public:
	Background();

	virtual ~Background();

	bool Awake();

	bool Start();

	bool PreUpdate();

	bool Update(float dt);

	bool PostUpdate();

	bool CleanUp();

	SDL_Rect sky_r;
	SDL_Texture* sky_texture;
	SDL_Rect n_mountain_r;
	SDL_Texture* n_mountain_texture;
	SDL_Rect f_mountain_r;
	SDL_Texture* f_mountain_texture;
	SDL_Rect clouds_r;
	SDL_Texture* clouds_texture;

	int n_mountain_parallaxX = 0;
	int f_mountain_parallaxX = 0;
	int clouds_parallaxX = 0;
};

#endif