#ifndef __TEXTURES_H__
#define __TEXTURES_H__

#include "Module.h"

#include "List.h"

struct SDL_Texture;
struct SDL_Surface;

class Textures : public Module
{
public:

	Textures();

	// Destructor
	virtual ~Textures();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called before quitting
	bool CleanUp();

	// Load Texture
	SDL_Texture* const Load(const char* path);
	SDL_Texture* const LoadSurface(SDL_Surface* surface);
	bool UnLoad(SDL_Texture* texture);
	void GetSize(const SDL_Texture* texture, uint& width, uint& height) const;

public:

	List<SDL_Texture*> textures;

	// textures
	SDL_Texture* player_textureR = NULL;
	SDL_Texture* player_textureL = NULL;
	SDL_Texture* hab_tex = NULL;
	SDL_Texture* slime_textureR = NULL;
	SDL_Texture* slime_textureL = NULL;
	SDL_Texture* floper_texture = NULL;
	SDL_Texture* tileX = NULL;
	SDL_Texture* coin_texture = NULL;
	SDL_Texture* heart_texture = NULL;
};


#endif // __TEXTURES_H__