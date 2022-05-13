#ifndef __ASSETSMANAGER_H__
#define __ASSETSMANAGER_H__

#include "Module.h"

#include "PhysFS/include/physfs.h"
#include "SDL/include/SDL.h"

#include "External/SDL_image/include/SDL_image.h"
#include "External/SDL_mixer/include/SDL_mixer.h"

class ModuleAssetsManager : public Module
{
public:
	// Constructor
	ModuleAssetsManager(bool enabled);

	// Destructor
	~ModuleAssetsManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Return the bytes of a PhysFS filehandle
	uint LoadData(const char* path, char** buffer) const;

	// Allows you to use pointers to memory instead of files or things such as images or samples
	SDL_Surface* LoadPhysfsTexture(const char* path) const;
	Mix_Chunk* LoadPhysfsFx(const char* path) const;
	Mix_Music* LoadPhysfsMusic(const char* path) const;
	pugi::xml_document* LoadPhysfsXML(const char* path) const;

};

#endif // __ASSETSMANAGER_H__
