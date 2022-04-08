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
	SDL_Texture* assassin_texture = NULL;
	SDL_Texture* tank_texture = NULL;
	SDL_Texture* healer_texture = NULL;
	SDL_Texture* wizard_texture = NULL;
	SDL_Texture* renato_bueno = NULL;
	SDL_Texture* curandero = NULL;
	SDL_Texture* herrero = NULL;
	SDL_Texture* granjero = NULL;
	SDL_Texture* start_menu = NULL;
	SDL_Texture* target = NULL;
	SDL_Texture* tombstone = NULL;
	SDL_Texture* goblin = NULL;
	SDL_Texture* skeleton = NULL;
	SDL_Texture* mushroom = NULL;
	SDL_Texture* white_templar = NULL;
	SDL_Texture* red_templar = NULL;
	SDL_Texture* heroes_icons = NULL;
	SDL_Texture* enemies_icons = NULL;
	SDL_Texture* turn_icon = NULL;
	SDL_Texture* dead_icon = NULL;
	SDL_Texture* whitemark_64x64 = NULL;
	SDL_Texture* whitemark_400x50 = NULL;
	SDL_Texture* whitemark_110x110 = NULL;
	SDL_Texture* whitemark_128x128 = NULL;
	SDL_Texture* whitemark_1200x140 = NULL;
	SDL_Texture* whitemark_300x80 = NULL;
	SDL_Texture* particles_texture = NULL;

	SDL_Texture* tileX = NULL;
};


#endif // __TEXTURES_H__